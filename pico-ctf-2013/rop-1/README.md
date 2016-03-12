# PicoCTF 2013: ROP 1

**Category:** Binary Exploitation
**Points:** 95
**Description:**

> ROP is a classic technique for getting around address randomization and
> non-executable memory. This sequence will teach you the basics.
>
> Problem available on the shell machine in /problems/ROP_1_fa6168f4d8eba0eb ,
> downloadable [here](https://2013.picoctf.com/problems/rop1-fa6168f4d8eba0eb)  with source [here](https://2013.picoctf.com/problems/rop1-fa6168f4d8eba0eb.c).
>
>

## Write-up
Looking at the C code, there is an interesting function:
```C
int not_called() {
return system("/bin/bash");
}
```

## Other write-ups and resources

* none yet
