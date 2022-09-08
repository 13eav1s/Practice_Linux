#!/bin/bash
# Реализовать компаратор для сравнения последовательностей действительных чисел, располагающихся в двух текстовых
# файлах, с игнорированием остального содержимого.
re="[0-9-]-"
file1="$1"
file2="$2"
flag=0

<"$file1" grep -E -o "$re*" > "out1_temp.txt"

<"$file2" grep -E -o "$re*" > "out2_temp.txt"
if cmp -s "out1_temp.txt" "out2_temp.txt" ; then
    flag=0
else
    flag=1
fi
rm "out1_temp.txt" "out2_temp.txt"
exit "$flag"
