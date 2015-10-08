# PicoCTF 2013: RSA

**Category:** Crypto
**Points:** 70
**Description:**

> Math is cool! Use the RSA algorithm to decode the secret message, c, p, q, and e are parameters for the RSA algorithm. [Problem](https://2013.picoctf.com/problems/rsa.txt)
>
> [offline file](rsa.txt)

## Write-up

What is RSA algorithm? [Wikipedia](http://en.wikipedia.org/wiki/RSA_(cryptosystem))

We will focus to "Key generation":

**1. Choose two distinct prime numbers p and q.**

* For security purposes, the integers p and q should be chosen at random, and should be of similar bit-length. Prime integers can be efficiently found using a primality test.

**2. Compute n = pq.**

* n is used as the modulus for both the public and private keys. Its length, usually expressed in bits, is the key length.

**3. Compute `φ(n) = φ(p)φ(q) = (p − 1)(q − 1) = n - (p + q -1)`, where φ is Euler's totient function.**

**4. Choose an integer e such that 1 < e < φ(n) and gcd(e, φ(n)) = 1; i.e., e and φ(n) are coprime.**

* e is released as the public key exponent.
* e having a short bit-length and small Hamming weight results in more efficient encryption – most commonly 216 + 1 = 65,537. However, much smaller values of e (such as 3) have been shown to be less secure in some settings.

**5. Determine d as d ≡ e−1 (mod φ(n)); i.e., d is the multiplicative inverse of e (modulo φ(n)).**

* This is more clearly stated as: solve for d given `d*e ≡ 1 (mod φ(n))`
* This is often computed using the extended Euclidean algorithm. Using the pseudocode in the Modular integers section, inputs a and n correspond to e and φ(n), respectively.
* d is kept as the private key exponent.

Use module gmpy2 in python2:

```python
import gmpy2

[...]

invert(x, m)
# invert(x, m) returns y such that x * y == 1 modulo m, or 0 if no such y exists.

[...]
```

Install [gmpy2](https://code.google.com/p/gmpy/downloads/list) is required.

Code:

```python
#!/usr/bin/python2
import gmpy2

p =  9648423029010515676590551740010426534945737639235739800643989352039852507298491399561035009163427050370107570733633350911691280297777160200625281665378483
q =  11874843837980297032092405848653656852760910154543380907650040190704283358909208578251063047732443992230647903887510065547947313543299303261986053486569407
e =  65537
c =  83208298995174604174773590298203639360540024871256126892889661345742403314929861939100492666605647316646576486526217457006376842280869728581726746401583705899941768214138742259689334840735633553053887641847651173776251820293087212885670180367406807406765923638973161375817392737747832762751690104423869019034
t = (p-1)*(q-1)
n = p*q

# returns d such that e * d == 1 modulo t, or 0 if no such y exists.
d = gmpy2.invert(e,t)

# Decryption
m = pow(c,d,n)
print "Solved ! m = %d" % m
```

**Answer:** 5577446633554466577768879988

## Other write-ups and resources

* none yet