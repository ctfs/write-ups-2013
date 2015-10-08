# PicoCTF 2013: Grep is Your Friend

**Category:** Trivia
**Points:** 40
**Description:**

> After plugging the robot into the computer, the robot asks for the name of a file containing the string `SECRET AUTH CODE`. You can find it using the [command-line interface](https://2013.picoctf.com/webshell) in `/problems/grep.tar` or by downloading [all of the files](https://2013.picoctf.com/problems/grep.tar).
>
> [file offline](grep.tar)

## Write-up

In Linux host, extract rar file, then use `grep` command.

```bash
	$ tar xzvf grep.tar
	$ cd grep
	$ strings * | grep "SECRET AUTH CODE"
	fHYYpdrfeOCHyQicfe96xfw==: SECRET AUTH CODES
```

**Answer:** fHYYpdrfeOCHyQicfe96xfw==

## Other write-ups and resources

* none yet