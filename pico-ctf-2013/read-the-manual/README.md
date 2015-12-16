# PicoCTF 2013: Read the Manual

**Category:** Crypto
**Points:** 30
**Description:**

> On the back of the broken panel you see a recovery [manual](tmp2xfLwN.txt). You need to find the emergency repair key in order to put the robot into `autoboot` mode, but it appears to be ciphered using a Caesar cipher.

## Write-up

Quote: "*but it appears to be ciphered using a Caesar cipher*"

We'll use a tool [Decrypt CAESAR Online](http://www.xarg.org/tools/caesar-cipher)

With k = 10, cleartext is: 

```
Instruction manual for Toaster Model 0X653F IMPORTANT: To enter automatic recovery mode, 
enter the following recovery key 'tamwxxgkqzac' Boolean logic and IPv0,[...]
```

**Answer:** tamwxxgkqzac

## Other write-ups and resources

* none yet