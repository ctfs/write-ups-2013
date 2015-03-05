#!/usr/bin/python
import os
import sys
import argparse

blocksize=256

parser = argparse.ArgumentParser(description="Custom encryption algorithm because a friend said that's the way to do it. Anyway, it's called 'Only This Program' since I'm pretty sure that only this program can securely decrypt the files as long as you don't give out your secret.dat file created when you encrypt something.")
parser.add_argument('--infile', metavar='i', nargs='?', type=argparse.FileType('r'), help='input file, defaults to standard in', default=sys.stdin)
parser.add_argument('--outfile', metavar='o', nargs='?', type=argparse.FileType('wb'), help='output file, defaults to standard out', default=sys.stdout)
parser.add_argument('--secretkey', metavar='s', nargs='?', type=argparse.FileType('a+'), help='output file, defaults to secretkey.dat', default='secretkey.dat')

args = parser.parse_args()


sys.stderr.write('\nReading random bytes from OS. If hung, please introduce entropy.\n')

args.secretkey.truncate()

while (args.secretkey.tell() < blocksize):
# maybe remove the next line for release since it makes it more obvious the key only generates once?
	sys.stdout.write('.')
	args.secretkey.write(os.urandom(1))

counter=0
args.secretkey.seek(0)
keydata = args.secretkey.read(blocksize)

while 1:
	byte = args.infile.read(1)
	if not byte:
		break
	args.outfile.write(chr(ord(keydata[counter % len(keydata)]) ^ ord(byte)))
	counter+=1

sys.stderr.write('\nSecret keyfile: %s\nInput file: %s\nOutput file: %s\nTotal bytes: %d \n' % (args.secretkey.name, args.infile.name, args.outfile.name, counter))


