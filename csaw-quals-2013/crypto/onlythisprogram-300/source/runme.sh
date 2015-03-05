#!/bin/bash
rm -rf output
mkdir output
rm secretkey.dat
for file in input/*
do
	./onlythisprogram.py --infile $file --outfile output/file$((COUNT++)).enc
done

