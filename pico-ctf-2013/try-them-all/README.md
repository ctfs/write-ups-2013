# PicoCTF 2013: Try Them All!

**Category:** Crypto
**Points:** 45
**Description:**

> You have found a passwd file containing salted passwords. An unprotected configuration file has revealed a salt of 5948. The hashed password for the 'admin' user appears to be 02ed2bf40532f187ec9334ef37f75591, try to brute force this password.

## Write-up

Hint: There are [MD5 implementations](http://userpages.umbc.edu/~mabzug1/cs/md5/md5.html) for every major programming language. If you don't know what a [salt](http://en.wikipedia.org/wiki/Salt_%28cryptography%29) is, don't worry, it's just a string appended to the password.

Quote: "*it's just a string appended to the password*"

We'll focus on **salt of** `5948` and **hashed password** `02ed2bf40532f187ec9334ef37f75591`. Two values is different with every machine. But we'll understand the progress is:

```md5_encrypt(cleartext password + salt number) => hashed password```

This [code](trythemall.js) bruteforce cleartext password base on [Linux standar dictionary password](cracklib-small.txt). To run it, must install [Node.js](http://nodejs.org/download/). And remember to edit trythemall.js.

**Answer:** allege

## Other write-ups and resources

* none yet