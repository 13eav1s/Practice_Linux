#!/bin/bash
gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wvla -Wfloat-conversion -o app.exe main.c -lm
./"app.exe"