#!/bin/bash

# Check for the correct number of arguments
if [ "$#" -ne 3 ]; then
    echo "Usage: $0 <source_file.c> <assembly_file.s> <output_name>"
    exit 1
fi

# Extract the arguments into meaningful variable names
source_file="$1"
assembly_file="$2"
output_name="$3"

# Compile the C source file into an object file
gcc -g -c "$source_file" -o "${source_file%.c}.o"

# Assemble the assembly file into an object file
as -g "$assembly_file" -o "${assembly_file%.s}.o"

# Link the object files into the final executable
gcc "${source_file%.c}.o" "${assembly_file%.s}.o" -o "$output_name"
