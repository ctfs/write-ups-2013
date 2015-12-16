#!/usr/bin/env python

verify_arr = [193, 35, 9, 33, 1, 9, 3, 33, 9, 225]
password = ""
for i in xrange(0,10):
  for j in xrange(1,256):
    k = (((j << 5) | (j >> 3)) ^ 111) & 255
    if k == verify_arr[i]:
      password = password + chr(j)

print password
