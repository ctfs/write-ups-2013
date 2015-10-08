# PicoCTF 2013: Bitwise

**Category:** ACM
**Points:** 55
**Description:**

> You see the doors to the loading bay of the hangar, but they are locked. However, you are able to extract the password verification program from the control panel... Can you find the password to gain access to the loading bay?
>
> Available in [Python](https://2013.picoctf.com/problems/bit.py) or [Java](https://2013.picoctf.com/problems/Bit.java)
>
> offline files: [Python](bitwise.py) | [Java](bitwise.java)

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