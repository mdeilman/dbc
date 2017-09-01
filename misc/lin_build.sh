#!/usr/bin/env bash

echo "Compiling $1 into build dir"
gcc -std=c99 -Wall -Wextra -g -O0 $1.c -o ../build/$1.out
