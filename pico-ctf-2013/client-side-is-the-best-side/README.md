# PicoCTF 2013: Client-Side is the Best Side

**Category:** Web Vuln
**Points:** 75
**Description:**

> Luckily the ship has a [web-based authentication system](https://2013.picoctf.com/problems/clientside.html)! Hmm…even though you don't know the password, I bet you can still get in!

## Write-up

Ctrl+U > viewsource :

```javascript
  function verify() {
    checkpass = document.getElementById("pass").value;
    if (md5(checkpass) == "03318769a5ee1354f7479acc69755e7c") {
      alert("Correct!");
      document.location="./aebe515f7c62b96ad7de047c11aa3228.html";
    }
    else {
      alert("Incorrect password");
    }
  }
```

Surprise: *document.location="./aebe515f7c62b96ad7de047c11aa3228.html";*

Full link:

https://2013.picoctf.com/problems/aebe515f7c62b96ad7de047c11aa3228.html

**Answer:** cl13nt_s1d3_1s_w0rst_s1d3

## Other write-ups and resources

* none yet