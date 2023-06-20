#!/bin/sh
gcc -fpermissive -g -lm test.cpp munit.c munit.h d1.cpp -o test.o && ./test.o
