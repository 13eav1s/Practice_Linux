#!/bin/bash
# Автотесты
ls ../data > "tests.txt"
< "tests.txt" grep "neg" > "neg.txt"
< "tests.txt" grep "pos.*in" > "in.txt"
< "tests.txt" grep "pos.*out" > "out.txt"
i=0
while IFS= read -r line
do
    i=$((i + 1))
    arr_neg[$i]="../data/$line"
done < "neg.txt"
i=0
while IFS= read -r line
do
    i=$((i + 1))
    arr_pos_in[$i]="../data/$line"
done < "in.txt"
i=0
while IFS= read -r line
do
    i=$((i + 1))
    arr_pos_out[$i]="../data/$line"
done < "out.txt"
i=0
k=0
e=0
while [[ $i -lt ${#arr_neg[*]} ]]; do
    i=$((i + 1))
    ./neg_case.sh "${arr_neg[$i]}"
    ex_code="$?"
    if [[ "$ex_code" -eq 0 ]]; then
        k=$((k + 1))
        e=1
    fi
    if [[ $e -eq 1 ]]; then
            e=0
            echo "NEG_TEST $i passed"
        else
            echo "NEG_TEST $i failed"
        fi
done
echo "$k/$i neg tests passed"
i=0
k=0
e=0
while [[ $i -lt ${#arr_pos_in[*]} ]]; do
    i=$((i + 1))
    ./pos_case.sh "${arr_pos_in[$i]}" "${arr_pos_out[$i]}"
    ex_code="$?"
    if [[ "$ex_code" -eq 0 ]]; then
        e=1
        k=$((k + 1))
    fi
    if [[ $e -eq 1 ]]; then
        e=0
        echo "POS_TEST $i passed"
    else
        echo "POS_TEST $i failed"
    fi
done
echo "$k/$i pos tests passed"
rm "neg.txt" "in.txt" "out.txt" "tests.txt"