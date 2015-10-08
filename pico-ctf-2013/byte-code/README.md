# PicoCTF 2013: Byte Code

**Category:** ACM
**Points:** 70
**Description:**

> You need to authenticate with the guard to gain access to the loading bay! Enter the root password from the vault application to retrieve the passkey! [This](https://2013.picoctf.com/autoproblems/tmpBPWe7T.zip) class file is the executable for the vault application.
>
> [offline file](tmpBPWe7T.zip)

## Write-up

Use [tool](http://www.showmycode.com) to decrypt Java code.

```java
key = new char[10]; 
key[0] = 'A'; 
key[1] = 'o'; 
key[2] = 'J'; 
key[3] = 'k'; 
key[4] = 'V'; 
key[5] = 'h'; 
key[6] = 'L'; 
key[7] = 'w'; 
key[8] = 'U'; 
key[9] = 'R'; 
Console console = system.console(); 
for(string s = ""; !s.equals("ThisIsth3mag1calString4458"); 
	s = console.readLine("Enter password:", new object[0])); 

for(int i = 0; i < key.length; i++) 
	system.out.print(key[i]);
```

It's not difficult to see the key.

**Answer:** AoJkVhLwUR

## Other write-ups and resources

* none yet