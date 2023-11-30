#!/bin/bash

# Check if the number of arguments is correct
if [ "$#" -ne 2 ]; then
    echo "Error: Please provide both filesdir and searchstr as arguments."
    exit 1
fi

filesdir="$1"
searchstr="$2"

# Check if filesdir is a directory
if [ ! -d "$filesdir" ]; then
    echo "Error: '$filesdir' is not a directory."
    exit 1
fi

# Count the number of files and matching lines
file_count=$(find "$filesdir" -type f | wc -l)
match_count=$(grep -r "$searchstr" "$filesdir" | wc -l)

# Print the results
echo "The number of files are $file_count and the number of matching lines are $match_count"

