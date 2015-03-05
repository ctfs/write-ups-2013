#!/usr/bin/python
import os

'''
Inspired by: http://pthree.org/2012/02/17/ecb-vs-cbc-encryption/

First need to recreate a 54 byte header version of all the files just because it's faster and you don't need to solve for the whole files:

for file in *; do dd if=$file bs=1 count=54 of=$file.small; done

 My solution: write up the helper utils below, piecewise discover what the files are and build out a working header for one of them (and thus the key) until you can examine the encrypted BMP, find the original, then decrypt all the files.

 First try: attempt = 'GIF89'
 Find the following: key of 62b7de6117
 And files:

Trying GIF89 against file5.enc.small produes key: 62b7de6117.

0000   4D 54 68 64 00             MThd. //MIDI
0000   FF D8 FF E0 00             ..... //JPG
0000   89 50 4E 47 0D             .PNG. //PNG
0000   1F 8B 08 00 F6             ..... //GZIP
0000   42 4D 3E 7E 04             BM>~. //BMP
0000   47 49 46 38 39             GIF89 //GIF
0000   D0 CF 11 E0 A1             ..... //DOC
0000   42 4D 3E 7E 04             BM>~. //BMP
0000   25 50 44 46 2D             %PDF- //PDF


But I wanted to do it with an "in the wild" BMP to make it easier to solve. 


Nevermind -- word docs are like cheating:

d0 cf 11 e0 a1 b1 1a e1 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 3b 00 03 00 fe ff 09 00 06 00 00 00 00 00 00 00 00 00 00 00 02 00 00 00 9a 00 00 00 00 00 00 00 00 10 00 00 02 00 00 00 01 00 00 00 fe ff ff ff 00 00 00 00 00 00 00 00 80 00 00 00 ff ff ff ff ff ff

That produces the following BMP header: 

0000000: 424d 3e7e 0400 0000 0000 3e00 0000 2800  BM>~......>...(.
0000010: 0000 ac05 0000 4006 0000 0100 0100 0000  ......@.........
0000020: 0000 007e 0400 c40e 0000 c40e 0000 0000  ...~............
0000030: c900 0000 0000                           ......

From there, you can either replace, view the image and figure out what it is, or you can just extract the size. That plus the google search: 

https://www.google.com/search?biw=1664&bih=908&tbs=ift%3Abmp%2Cisz%3Aex%2Ciszw%3A1452%2Ciszh%3A1600&tbm=isch&sa=1&q=bmp&oq=bmp

Produces the original unmolested BMP, then you use that to extract the 256 byte key, then decrypt everything. 

'''
def hexdump(src, length=32):
	result = []
	digits = 4 if isinstance(src, unicode) else 2
	for i in xrange(0, len(src), length):
		s = src[i:i+length]
		hexa = b' '.join(["%0*X" % (digits, ord(x))  for x in s])
		text = b''.join([x if 0x20 <= ord(x) < 0x7F else b'.'  for x in s])
		result.append( b"%04X   %-*s   %s" % (i, length*(digits + 1), hexa, text) )
	return b'\n'.join(result)

def sxor(s1,s2):    
    return ''.join(chr(ord(a) ^ ord(b)) for a,b in zip(s1,s2))

def lxor(s1, s2):
	'''designed to work with different length strings, auto-repeats to the longest length'''
	out= ''
	for x in range(max(len(s1),len(s2))):
		out += chr(ord(s1[x % len(s1)]) ^ ord(s2[x % len(s2)]))
	return out


ct = []
for root,dirs,files in os.walk('.'):
	for file in files:
		if file.endswith('.small'):
			ct.append([file,open(file,'r').read()])

attempt = 'd0 cf 11 e0 a1 b1 1a e1 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 3e 00 03 00 fe ff 09 00 06 00 00 00 00 00 00 00 00 00 00 00 01 00 00 00 9a 00 00 00 00 00 00 00 00 10 00 00 02 00 00 00 01 00 00 00 fe ff ff ff 00 00 00 00 00 00 00 00 80 00 00 00 ff ff ff ff ff ff'.replace(' ','').decode('hex')
key = ''.decode('hex')

#Switch back and forth when pivoting on different fields. 
for item in ct:
	potentialkey = sxor(attempt,item[1])
	print('Trying %s against %s produes key: %s.\n' % (attempt, item[0], potentialkey.encode('hex')))
	output= []
	for compare in ct:
		result = sxor(potentialkey,compare[1])
		print(hexdump(result))
'''

potentialkey = sxor(attempt,ct[6][1])
print('Trying %s against %s produes key: %s.\n' % (attempt, ct[0][0], potentialkey.encode('hex')))
output= []
for compare in ct:
	result = sxor(potentialkey,compare[1])
	print(hexdump(result))
'''
