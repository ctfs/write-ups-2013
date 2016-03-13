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
for practice**

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
## Other write-ups and resources

* none yet
