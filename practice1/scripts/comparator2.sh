#!/bin/bash
# Реализовать компаратор для сравнения содержимого двух текстовых файлов, располагающегося после первого
# вхождения подстроки «Result:␣».

file1=$1
file2=$2
echo "x" > "new1.txt"
echo "x" > "new2.txt"
cat "$file1" >> "new1.txt"
cat "$file2" >> "new2.txt"
file1="new1.txt"
file2="new2.txt"
cat "$file1" >> "out1.txt"
cat "$file2" >> "out2.txt"

sed '1,/Result:/ d' < "$file1" > "out3_1.txt"
cat "out3_1.txt" > "out3.txt"
comm -13 <(sort -u "out3.txt") <(sort -u "out1.txt") > "out4.txt"
< "out4.txt"  tail -n1 > "out3.txt"
cat "out3_1.txt" > "out1.txt"
rm out3.txt out3_1.txt out4.txt

sed '1,/Result:/ d' < "$file2" > "out3_1.txt"
cat "out3_1.txt" > "out3.txt"
comm -13 <(sort -u "out3.txt") <(sort -u "out2.txt") > "out4.txt"
< "out4.txt"  tail -n1 > "out3.txt"
cat "out3_1.txt" > "out2.txt"
rm out3.txt out3_1.txt out4.txt new1.txt new2.txt

if cmp -s "out1.txt" "out2.txt" ; then
    exit 0
else exit 1
fi
rm "out1.txt" "out2.txt"