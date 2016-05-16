#!/usr/bin/env sh
rm -f a.out main.o test.h5 bench.csv bench.svg system.txt
h5c++ main.cc
python bench.py
R -f plotResults.R
inxi -b -c 0 > system.txt
