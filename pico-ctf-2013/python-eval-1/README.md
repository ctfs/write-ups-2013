# PicoCTF 2013: Python Eval 1

**Category:** Script Exploitation
**Points:** 85
**Description:**

> A wise master wishes to teach you an ancient art: [Python Eval 1](https://2013.picoctf.com/problems/pyeval/stage1.html).

## Write-up

> This challenge involves exploiting a Python input 'eval' function. 

> Our objective for this challenge is to get the following script (running at python.picoctf.com 6361) to print out the 'flag' variable.

```
# task1.py
print "Welcome to mystery math!"

flag = "xxxxxxxxxx"

while True:
  x = input("Enter number 1> ")
  x = x*x + ord(flag[0]) * ord(flag[1]) + ord(flag[2]) * x
  y = input("Enter number 2> ")
  if y / 6 + 7 - y == x:
    print "Here ya go! ", flag
    exit(0)
  else:
    print "Your lucky number is ", x - y
```

> We can see that the script uses the x and y variables as 'keys' to print out the flag and that it defines those variables with the vulnerable input function.
> After the variables have been defined, the script calculates whether they are correct using the integer representation of the flag's first three letters as an additional secret.

> Since the input function will attempt to evaluate whatever we pass it, we can make the Python interperter give us the flag by making it throw an exception. 
> Entering *int(flag)* will make the program crash with the answer.
```
Enter number 1> int(flag)
Traceback (most recent call last):
  File "/home/py1/task1.py", line 8, in <module>
    x = input("Enter number 1> ")
  File "<string>", line 1, in <module>
ValueError: invalid literal for int() with base 10: 'eval_is_best_thing_evar'
```

**Answer: eval_is_best_thing_evar** 

## Other write-ups and resources

* none yet
