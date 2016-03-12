# PicoCTF 2013: PHP 3

**Category:** Script Exploitation
**Points:** 120
**Description:**

> It looks like [this site](http://2013.picoctf.com/problems/php3/) uses MD5 to hash passwords, but I don't think they're doing it quite right...

## Write-up
We're given the following script and the task of exploiting it to get the flag.
```
<html>
<head>
Secure Web Login
</head>
<body>
<?php
if($_POST[user] && $_POST[pass]) {
  mysql_connect("localhost","php3","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
  mysql_select_db("php3");

  $user = $_POST[user];
  $pass = md5($_POST[pass], True);
  $query = @mysql_fetch_array(mysql_query("select user from php3 where (user='$user') and (pw='$pass')"));

  if($query[user]=="admin") {
    echo "<p>Logged in! Key: xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx </p>";
  }

  if($query[user] != "admin") {
    echo("<p>You are not admin!</p>");
  }
}

?>
<form method=post action=index.php>
<input type=text name=user value="Username">
<input type=password name=pass value="Password">
<input type=submit>
</form>
</body>
<a href="index.phps">Source</a>
</html>
```
> We can solve the challenge simply by putting in **admin') --** as the username and **pass** as the password.
> This converts the mySQL query in the script to treat everything after the username as a comment. Thus giving us the answer.

***Note as of 12 March 2016 , this challenge is offline. This writeup is included for learning purposes.***

**Answer: 8ab9b92c174dd483ad17cee1bb0c5bdb** 

## Other write-ups and resources

* [http://blog.phuongnam.org/2013/07/picoctf.html](http://blog.phuongnam.org/2013/07/picoctf.html)
* [https://github.com/elc1798/stuyfyre-picoctf-2013/blob/master/PHP3-120/Solution.txt](https://github.com/elc1798/stuyfyre-picoctf-2013/blob/master/PHP3-120/Solution.txt)
