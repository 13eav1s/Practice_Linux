#!/bin/bash


opts="O1 O2 O3 O0 Os"
programms="programm_1 programm_2 programm_3"
for i in $programms; do
    for opt in $opts; do
        gcc -std=c99 -Wall -Werror -Wpedantic -Wextra \
        -"${opt}" \
        "$i".c -o ./apps/"${i}"_"${opt}".exe
        echo "${i}"_"${opt}".exe готово
    done
done