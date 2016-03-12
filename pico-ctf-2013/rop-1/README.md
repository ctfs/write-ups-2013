# PicoCTF 2013: ROP 1

**Category:** Binary Exploitation
**Points:** 95
**Description:**

> ROP is a classic technique for getting around address randomization and
> non-executable memory. This sequence will teach you the basics.
>
> Problem available on the shell machine in /problems/ROP_1_fa6168f4d8eba0eb ,
> downloadable here with source here.
>
>

## Write-up

We have encryption algorithms and cipher text.

A little edit, we can generate input as string (length = 10, characters: 0-9,a-z (1-255 ASCII)).
Then encrypt and compare with cipher text.

Source: [solve.py](solve.py)

```python
verify_arr = [193, 35, 9, 33, 1, 9, 3, 33, 9, 225]
password = ""
for i in xrange(0,10):
  for j in xrange(1,256):
    k = (((j << 5) | (j >> 3)) ^ 111) & 255
    if k == verify_arr[i]:
      password = password + chr(j)

print password
```

**Answer:** ub3rs3cr3t

## Other write-ups and resources

* none yet
