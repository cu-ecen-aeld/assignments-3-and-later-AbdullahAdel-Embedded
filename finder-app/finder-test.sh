#!/bin/bash
# Tester script for assignment 1 and assignment 2

set -e
set -u

NUMFILES=10
WRITESTR="AELD_IS_FUN"
WRITEDIR="/tmp/aeld-data"
username=$(cat conf/username.txt)

if [ $# -lt 3 ]; then
    echo "Using default value ${WRITESTR} for string to write"
    if [ $# -lt 1 ]; then
        echo "Using default value ${NUMFILES} for the number of files to write"
    else
        NUMFILES=$1
    fi
else
    NUMFILES=$1
    WRITESTR=$2
    WRITEDIR="/tmp/aeld-data/$3"
fi

MATCHSTR="The number of files are ${NUMFILES} and the number of matching lines are ${NUMFILES}"

echo "Writing ${NUMFILES} files containing string '${WRITESTR}' to ${WRITEDIR}"

# remove temporary directories
rm -rf /tmp/aeld-data

set +e
echo "$OUTPUTSTRING" | grep "$MATCHSTR"
if [ $? -eq 0 ]; then
    echo "success"
    exit 0
else
    echo "failed: expected $MATCHSTR in $OUTPUTSTRING but instead found"
    exit 1
fi

