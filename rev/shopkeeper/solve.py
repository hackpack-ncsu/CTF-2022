from pwn import *
import ctypes

r = process("./chal")

libc = ctypes.CDLL('/lib/x86_64-linux-gnu/libc.so.6')

r.recvuntil(b"4) Leave Shop\n")
r.sendline(b'2')
r.recvuntil(b"2) An Orange (3 coins)\n")
r.sendline(b'1')
r.recvline()
r.sendline(b'!')
r.recvuntil(b"4) Leave Shop\n")
r.sendline(b'1')
r.recvuntil(b"3) The Key to the Flag (100 coins)\n")
r.sendline(b'1')
r.recvline()
r.sendline(b'@')
r.recvuntil(b"4) Leave Shop\n")
r.sendline(b'1')
r.recvuntil(b"3) The Key to the Flag (100 coins)\n")
r.sendline(b'3')
r.recvline()
r.sendline(b'2')
r.recvuntil(b"4) Leave Shop\n")
r.sendline(b'3')

r.recvuntil(b'Congrats!! You have the key!\n')
print(r.recvline())
r.recvuntil(b"Time: ")
time_val = r.recvline()[:-1]
libc.srand(int(time_val))

coins = 0x13
while coins != 0x37:
    r.recvuntil(b'How much money do you want to bet?\n')
    r.send(b'6')
    rand_val = str(libc.rand() % 10).encode("utf-8")
    r.send(rand_val)
    coins += 6

r.recvuntil(b'Correct!\n')
print(r.recvline())