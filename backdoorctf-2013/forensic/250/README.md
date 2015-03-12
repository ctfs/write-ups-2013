# Backdoor CTF 2015: Forensics 250

**Category:** Forensics
**Points:** 250
**Solves:** 
**Description:** 

> h4x0r is fed up with all your attacks on his castle and has decided to retaliate by attacking us back. He sent us a mail with [this image](bbb.png) as a warning. Hope you can figure out his warning message:-
> 
> MD5 of the message is the answer.

## Write-up

We are given a picture:

![](bbb.png)

Using `stegsolve`, we see that this picture contains a hidden binary text:

![](solved.bmp)

Extract these bits and convert them to `0`s and `1`s with this [script](get.py):

```bash
$ python get.py
011011010110111101100100011001010111001001101110011101110110000101110010011001100110000101110010011001010000000000000000000000000000
```

We convert the binary output to ASCII text using a small perl command and pipe the output to `xxd` to avoid scrambling our shell:

```bash
$ python get.py | perl -lpe '$_=pack"B*",$_' | xxd
0000000: 6d6f 6465 726e 7761 7266 6172 6500 0000  modernwarfare...
0000010: 000a
```

MD5 the resulting readable text and you got the flag:

```bash
$ echo modernwarfare | md5
3c87b2bc2f0e1143ecb67aa8570ffc1b
$ echo -n modernwarfare | md5
d2432052b887f9e09fb8fa44b11861ef
```

The flag is either `3c87b2bc2f0e1143ecb67aa8570ffc1b` or `d2432052b887f9e09fb8fa44b11861ef`.
## Other write-ups and resources

* none yet