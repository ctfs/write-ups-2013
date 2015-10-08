# PicoCTF 2013: Trivial

**Category:** Crypto
**Points:** 45
**Description:**

> An unlocked terminal is displaying the following:
>
> > Encryption complete, ENC(???,T0pS3cre7key) = Bot kmws mikferuigmzf rmfrxrwqe abs perudsf! Nvm kda ut ab8bv_w4ue0_ab8v_DDU
>
> You poke around and find this interesting [file](https://2013.picoctf.com/problems/encrypt.py).
>
> [offline file](encrypt.py)

## Write-up

Run encrypt.py: "Usage: D:\Downloads\encrypt.py SECRET_KEY PLAINTEXT"

Quote:

```python
print "Encryption complete, ENC(%s,%s) = %s"%(plaintext,key,ciphertext)
```

We can know:

* key = "T0pS3cre7key"
* ciphertext = "Bot kmws mikferuigmzf rmfrxrwqe abs perudsf! Nvm kda ut ab8bv_w4ue0_ab8v_DDU"

```python
plaintext = sys.argv[2]

ciphertext = ""
for i in range(len(plaintext)):
  rotate_amount = keychars.index(key[i%len(key)])
  if plaintext[i] in alphaL:
    enc_char = ord('a') + (ord(plaintext[i])-ord('a')+rotate_amount)%26
  elif plaintext[i] in alphaU:
    enc_char = ord('A') + (ord(plaintext[i])-ord('A')+rotate_amount)%26
  elif plaintext[i] in num:
    enc_char = ord('0') + (ord(plaintext[i])-ord('0')+rotate_amount)%10
  else:
    enc_char = ord(plaintext[i])
  ciphertext = ciphertext + chr(enc_char)
```

We can see rotate_amount is a real key. Encryption is add it, so decryption is sub it.

Make easy change:

```python
plaintext = sys.argv[2]

ciphertext = ""
for i in range(len(plaintext)):
  rotate_amount = keychars.index(key[i%len(key)])
  if plaintext[i] in alphaL:
    enc_char = ord('a') + (ord(plaintext[i])-ord('a')-rotate_amount)%26
  elif plaintext[i] in alphaU:
    enc_char = ord('A') + (ord(plaintext[i])-ord('A')-rotate_amount)%26
  elif plaintext[i] in num:
    enc_char = ord('0') + (ord(plaintext[i])-ord('0')-rotate_amount)%10
  else:
    enc_char = ord(plaintext[i])
  ciphertext = ciphertext + chr(enc_char)
```

Now input ciphertext replace for plaintext: "Usage: D:\Downloads\encrypt.py SECRET_KEY CIPHERTEXT"

```
[...]You hawe successfully decrypwed the message! The key is th4ts_w0rs3_th4n_DES
```

**Answer:** th4ts_w0rs3_th4n_DES

## Other write-ups and resources

* none yet