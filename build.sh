#!/bin/bash

SOURCE_DIR="./gates"
OUTPUT_DIR="./targets"

for source_file in "$SOURCE_DIR"/*.c; do

    base_name=$(basename "$source_file" .c)
    
    gcc "$source_file" -o "$OUTPUT_DIR/$base_name"
    
    if [ $? -eq 0 ]; then
        echo "Compiled $source_file successfully!"
    else
        echo "Error compiling $source_file"
        exit 1
    fi
done