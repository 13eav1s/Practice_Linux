#!/bin/bash

for i in ./*; do
    if [[ $i != *.sh ]] && [[ $i != *.c ]]; then
        rm "$i" 2> proga.error
    fi
done
rm proga.error
