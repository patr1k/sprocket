#!/usr/bin/env bash

CC=gcc
EMCC=emcc

SRC_DIR=src
BUILD_DIR=build
OUTPUT_BIN=sprocket

# Prepare build directory
rm -rf $BUILD_DIR
mkdir $BUILD_DIR

# Compile C source into object files
OBJECT_FILES=""
for file in $(find "$SRC_DIR" -type f); do
    filename=${file##*/}
    $CC -c $file -o $BUILD_DIR/${filename%.c}.o -I./include
    OBJECT_FILES+="$BUILD_DIR/${filename%.c}.o "
done

# Link object files into binary
$CC -o $BUILD_DIR/$OUTPUT_BIN $OBJECT_FILES

# Clean up build dir
rm -rf $BUILD_DIR/*.o

# Compile C source into WASM object files
OBJECT_FILES=""
for file in $(find "$SRC_DIR" -type f); do
    filename=${file##*/}
    $EMCC -g -c $file -o $BUILD_DIR/${filename%.c}.o -I./include
    OBJECT_FILES+="$BUILD_DIR/${filename%.c}.o "
done

# Link object files into binary
$EMCC -o $BUILD_DIR/$OUTPUT_BIN.js $OBJECT_FILES

# Clean up build dir
rm -rf $BUILD_DIR/*.o