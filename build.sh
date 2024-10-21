#!/bin/bash

SOURCE_DIR="./object"
MAIN_FILE="main.c"
OUTPUT_FILE="./target/computer"

# Check if --compile-libs flag is passed
COMPILE_LIBS=0

if [ "$1" = "--compile-libs" ]; then
    COMPILE_LIBS=1
fi

if [ $COMPILE_LIBS -eq 1 ]; then
    echo "Compiling libraries..."
    ./build-libs.sh
    
    if [ $? -ne 0 ]; then
        echo "Error compiling libraries."
        exit 1
    fi
fi

OBJECT_FILES=$(ls $SOURCE_DIR/*.o 2> /dev/null)

if [ -z "$OBJECT_FILES" ]; then
    echo "No object files found. Please compile the libraries first."
    exit 1
fi


gcc $MAIN_FILE $OBJECT_FILES -o $OUTPUT_FILE

if [ $? -eq 0 ]; then
    echo "Build successful! Executable is $OUTPUT_FILE"
else
    echo "Build failed."
    exit 1
fi
