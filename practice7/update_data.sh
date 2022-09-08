#!/bin/bash

programms="programm_1 programm_2 programm_3"
sizes=""
opts="O1 O2 O3 O0 Os"
count=100

i=300000

while [ $i -le 600000 ]
do
    sizes="$sizes $i"
    ((i+=15000))
done

if [ ! -z $1 ]; then
    count=$1
fi
if [ ! -z $2 ]; then
    sizes=$2
fi
if [ ! -z $3 ]; then
    programms=$3
fi
if [ ! -z $4 ]; then
    opts=$4
fi


for prog in $programms; do
    for co in $(seq "$count"); do
        for opt in $opts; do
            for i in $sizes; do
                echo -n -e "${prog}_""${opt}_""${i}\t $co/$count \r"
                ./apps/"${prog}"_"${opt}".exe "${i}">>./data/"${prog}"_"${opt}"_"${i}".txt
            done
        done
    done
done
