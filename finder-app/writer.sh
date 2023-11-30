#!/bin/bash

# Check if the number of arguments is correct
if [ "$#" -ne 2 ]; then
    echo "Error: Please provide both writefile and writestr as arguments."
    exit 1
fi

writefile="$1"
writestr="$2"

# Create the directory path if it doesn't exist
mkdir -p "$(dirname "$writefile")"

# Write content to the specified file
echo "$writestr" > "$writefile"

# Check if the file was created successfully
if [ $? -ne 0 ]; then
    echo "Error: Failed to create or write to the file '$writefile'."
    exit 1
fi

echo "Content successfully written to '$writefile'."

