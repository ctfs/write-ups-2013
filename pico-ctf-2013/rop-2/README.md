# PicoCTF 2013: ROP 1

**Category:** Binary Exploitation
**Points:** 120
**Description:**

> ROP is a classic technique for getting around address randomization and
> non-executable memory. This sequence will teach you the basics.
>
> Problem available on the shell machine in /problems/ROP_2_20f65dd0bcbe267d ,
> downloadable [here](https://2013.picoctf.com/problems/rop2-20f65dd0bcbe267d)  with source [here](https://2013.picoctf.com/problems/rop2-20f65dd0bcbe267d.c).
>
>

## Write-up
This is a ROP challenge. ASLR is enabled, meaning that libc and stack
addresses are random. Also, NX is enabled, meaning that there is no
simultaneously writable and executable space in memory. RIP Shellcode.
Luckily for us, the programmer has left a trail of breadcrumbs for us.

```C
char * not_used = "/bin/bash";

int not_called() {
    return system("/bin/date");
}

void vulnerable_function() {
    char buf[128];
    read(STDIN_FILENO, buf, 256);
}
```

Unlike in [ROP 1](rop-1), the call to `not_called()` doesn't automatically give
us a shell. However, with a bit of hacking chicanery, this won't be an issue. 

In order for you to understand this exploit, I'm going to teach you a bit about the
GOT and PLT. In any ASLR enabled binary (and most normal binaries for that
matter) there has to be a way for the binary to 'know' where the libc functions
are at. The binary creates a PLT stub for functions used in the source. These
are **always at a constant address**. This PLT stub is essentially a wrapper
function for the actual function in libc. The GOT contains the actual adresses
in libc for the functions used in the program. The actual adresses change from
runtime to runtime, but pointers to the same function are **always in the same
spot in the GOT**.

So what does this mean for us?

It means that the function `not_called()` can be avoided altogether. Since
there is a call to `system()` in the binary, we can just call that instead and
feed it our own argument. Mwahahahaa.

We'll start with finding the offset for `$eip`.

```
python -c 'print "A"*140 + "BBBB" ' | strace ./rop2-20f65dd0bcbe267d
...
--- SIGSEGV {si_signo=SIGSEGV, si_code=SEGV_MAPERR, si_addr=0x42424242} ---
```

After 140 junk bytes, we have control of `$eip`. As I mentioned before, we need
to supply the PLT stub for `system()` so we can call it with our own argument.

```
objdump -d rop2-20f65dd0bcbe267d | grep system
...
080483a0 <system@plt>:
```

We get an adress of 0x080483a0. We can put this into `$eip` followed by a bogus
four byte return address (we don't need to call another function in this
problem) and the pointer to what we want to call system on. Conveniently
enough, `char * not_used = "/bin/bash";` is exactly what we need.
 

## Other write-ups and resources

* none yet
