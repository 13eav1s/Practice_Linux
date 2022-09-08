#!/bin/bash
# neg_case.sh принимает в качестве аргументов файл для подмены входного потока
# и, при наличии, файл ключей, с которыми вызывается приложение. neg_case.sh file_stream_in [file_app_args]
# (a) Рабочей папкой скрипт считает свою папку.
# (b) Скрипт ожидает от приложения ненулевой код возврата в случае ошибки.
# (c) Скрипт по умолчанию работает в «молчаливом режиме», возвращает нуль при успешном тестировании, иначе — не нуль.
# (d) Мусор после работы скрипта не очищается.
file_in="$1"
rez="$?"
out_code=0
if [[ "$USE_VALGRIND" == "" ]]; then
    "../../app.exe" < "$file_in" > "program_out.txt"
    rez="$?"
    out_code=0
    if [[ ! $rez -eq 0 ]]; then
        out_code=0
    else
        out_code=1
    fi
    rm "program_out.txt"
    exit $out_code
else
    valgrind --log-file="../../trash.txt" ../../app.exe < "$file_in" > "program_out.txt"
    rez="?"
    if [[ -s "../../trash.txt" ]]; then
        rm "program_out.txt"
        exit 0
    else
        echo "Memory_fail"
        rm "program_out.txt"
        exit 1
    fi
fi
exit "$out_code"
