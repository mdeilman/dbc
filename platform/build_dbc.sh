#!/usr/bin/env bash

echo "Compiling $1 into build dir"
gcc -std=c99 -fdump-rtl-expand -Wall -Wextra -g -O0 dbc.c -o ../build/dbc.out
