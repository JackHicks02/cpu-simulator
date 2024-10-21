#!/bin/bash

mkdir -p object

for file in ./gates/*.c
do
    filename=$(basename "$file" .c)

    gcc -c "$file" -o "./object/$filename.o"
done

chmod +x build-libs.sh
