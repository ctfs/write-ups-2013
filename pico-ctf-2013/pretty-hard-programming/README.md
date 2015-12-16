# PicoCTF 2013: Pretty Hard Programming

**Category:** Script Exploitation
**Points:** 95
**Description:**

> If you can guess the admin's password you can get a key
> [Problem](https://2013.picoctf.com/problems/php1/)[Source](https://2013.picoctf.com/problems/php1/index.phps)

## Write-up
Looking at the source code we see that we must get the password variable to match the secret_key variable.
We also notice that the variables are extracted (initialized) when we send a GET request. Changing the url to:
https://2013.picoctf.com/problems/php1/index.php?password=fakepassword&secret_key=fakepassword give us the flag.

**Answer:** php_means_youre_going_to_have_a_bad_time

## Other write-ups and resources

* none yet
