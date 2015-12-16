# PicoCTF 2013: GETKey

**Category:** WebVuln
**Points:** 50
**Description:**

> There's bound to be a key on the spaceport's [hidden website](https://2013.picoctf.com/problems/getquery/index.php)

## Write-up

HTML code similar:

```html
<form action="?admin=false&competition=ccdc" method="GET">
	<input type="hidden" name="admin" value="false" /> 
	<input type="hidden" name="competition" value="ccdc" /> 
	<p><input type="submit" value="Get Key"></p>
</form>
```

We focus on ```method="GET"```, input will be displayed in the URL

Origin: 

```
[...]/index.php?admin=false&competition=ccdc
```

Solve: 

```
[...]/index.php?admin=true&competition=picoctf

FLAG: 9fa449c061d64f58de600dfacaa6bd5d
```

**Answer:** 9fa449c061d64f58de600dfacaa6bd5d

## Other write-ups and resources

* none yet