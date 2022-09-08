#!/bin/bash
# pos_case.sh принимает в качестве аргументов файл для подмены входного потока, файл эталонных выходных данных и, при
# наличии, файл ключей, с которыми вызывается приложение.
# pos_case.sh file_stream_in file_stream_out_expect [file_app_args]
# (a) Рабочей папкой скрипт считает свою папку.
# (b) Скрипт ожидает от приложения нулевой код возврата в случае успеха.
# (c) Скрипт по умолчанию работает в «молчаливом режиме», возвращает нуль при успешном тестировании, иначе — не нуль.
# (d) Мусор после работы скрипта не очищается.

file_in="$1"
file_out="$2"
#file_app_args="$3"
if [[ "$USE_VALGRIND" == "" ]]; then
    ../../app.exe < "$file_in" > "program_out.txt"
    rez="$?"
    ./comparator2.sh "program_out.txt" "$file_out"
    cmp_exit="$?"
    rm "program_out.txt"
    if [[ $cmp_exit -eq 0 ]]; then
        exit "$rez"
    else exit 1
    fi
else
    cmp_exit=0
    valgrind --log-file="../../trash.txt" ../../app.exe < "$file_in" > "program_out.txt"
    if [[ -s "../../trash.txt" ]]; then
        cmp_exit=0
        rez="$?"
        ./comparator2.sh "program_out.txt" "$file_out"
        cmp_exit="$?"
        rm "program_out.txt"
        if [[ $cmp_exit -eq 0 ]]; then
            exit "$rez"
        else exit 1
        fi
    else
        rm "program_out.txt"
        cmp_exit=1
    fi
fi
exit "$cmp_exit"