#!/bin/bash

SOURCE_DIR="./object"
MAIN_FILE="main.c"
OUTPUT_FILE="./target/computer"

# Check flags
COMPILE_LIBS=0
RUN_EXECUTABLE=0

for arg in "$@"; do
    if [ "$arg" = "--libs" ]; then
        COMPILE_LIBS=1
    elif [ "$arg" = "--run" ]; then
        RUN_EXECUTABLE=1
    fi
done

if [ $COMPILE_LIBS -eq 1 ]; then
    echo "Compiling libraries..."
    ./build-libs.sh

    if [ $? -ne 0 ]; then
        echo "Error compiling libraries."
        exit 1
    fi
fi

OBJECT_FILES=$(ls $SOURCE_DIR/*.o 2>/dev/null)

if [ -z "$OBJECT_FILES" ]; then
    echo "No object files found. Please compile the libraries first."
    exit 1
fi

gcc -O3 $MAIN_FILE $OBJECT_FILES -o $OUTPUT_FILE

if [ $? -eq 0 ]; then
    echo "Build successful! Executable is $OUTPUT_FILE"
    if [ $RUN_EXECUTABLE -eq 1 ]; then
        echo "Running $OUTPUT_FILE..."
        $OUTPUT_FILE
    fi
else
    echo "Build failed."
    exit 1
fi
