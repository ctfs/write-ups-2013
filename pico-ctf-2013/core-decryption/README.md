# PicoCTF 2013: Core Decryption

**Category:** Forensic
**Points:** 120
**Description:**

> In a ruined city on a forgotten world, you find a broken cogitator controlling access to the Vault. You have blueprints for the machine, and a stickynote attached to the monitor with the encrypted input. The machine seems to have crashed while decrypting, and generated a core dump, too. Maybe if you can get the encryption keys out of the core dump, you can decrypt the ciphertext and get the vault open... [Files available for download here](https://2013.picoctf.com/problems/core_decrypt.tar) on on the shell machine in `/problems/core_decrypt.tar`
>
> [Offline file](core_decrypt.tar)

## Write-up

I don't solve this challenge...

Core Decryption was another one of those painful problems. Though not hard, it's hard to find what direction you need to take. First off, you can't just run GDB with the core file. 
You have to compile the cryptor.c with `gcc -m32 -g cryptor.c -o cryptor`, we compile it in 32 bit mode with debugging symbols ON. This is the key to getting the core dump running. Running the core file and binary through GDB with the following commands:

```linux
root@neuron:~$ gdb cryptor core.26474
(gdb) bt
#0  0x08048564 in swap (sbox=0xffffd17c "", i=-11652, j=16) at cryptor.c:7
#1  0x08048719 in crypt (inf=0x0, keyf=0xffffd17c, outf=0xf7ffda5c) at cryptor.c:42
#2  0x08048894 in main (argc=4, argv=0xffffd374) at cryptor.c:67
(gdb) f 1
#1  0x08048719 in crypt (inf=0x0, keyf=0xffffd17c, outf=0xf7ffda5c) at cryptor.c:42
42 tmp ^= next_prg(sbox,&i,&j);
(gdb) info locals
sbox = "\000\001\002\003\004\005\006\a\b\t\n\v\f\r\016\017\020\021\022\023\024\025\026\027\030\031\032\033\034\035\036\037 !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\177\200\201\202\203\204\205\206\207\210\211\212\213\214\215\216\217\220\221\222\223\224\225\226\227\230\231\232\233\234\235\236\237\240\241\242\243\244\245\246\247\250\251\252\253\254\255\256\257\260\261\262\263\264\265\266\267\270\271\272\273\274\275\276\277\300\301\302\303\304\305\306\307\310\311\312\313\314\315\316\317\320\321\322\323\324\325\326\327\330\331\332\333\334\335\336\337\340\341\342\343\344\345\346\347\350\351\352\353\354\355\356\357\360\361\362\363\364\365\366\367\370\371\372\373\374\375\376\377"
i = 0
j = -135168078
key = "\305\344L\004\273/\\\020\272u\033×L\334", 
tmp = 247 '\367'
```

So we see that there is a key variable here. At first, we wondered what to do with it, what did "incomplete sequence" mean? We decided to ignore it, because if you refer back to the code, you know that the key will be 16 bytes long. We took the key, turned into hex so Python wouldn't have any trouble with it, and we got our result.

```python
import random, base64
def crypt(data, key):
    x = 0
    box = range(256)
    for i in range(256):
        x = (x + box[i] + ord(key[i % len(key)])) % 256
        box[i], box[x] = box[x], box[i]
    x = y = 0
    out = []
    for char in data:
        x = (x + 1) % 256
        y = (y + box[x]) % 256
        box[x], box[y] = box[y], box[x]
        out.append(chr(ord(char) ^ box[(box[x] + box[y]) % 256]))
    return ''.join(out)
with open('ENCRYPTED', 'rb') as f:
        content = f.read()
print crypt(content, 'c5e44c04bb2f5c10ba751bc3974cdcdc'.decode('hex'))
```

The message, decrypted with RC4, was:

```
Well, assuming you're able to actually keep the secret keyfile safe, this is a legitimate way to encrypt files!
Your key is: astronomy_ceremony_times
```

**Answer:** astronomy_ceremony_times

## Other write-ups and resources

* none yet