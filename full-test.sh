#!/bin/bash
# Run unit tests for the assignment

# Automate these steps from the readme:
# Create a build subdirectory, change into it, run
# cmake .. && make && run the assignment-autotest application
while true
do
    echo "Performing some task..."
    
    # Add your commands or tasks here

    # Sleep for 1 minute (60 seconds)
    sleep 60
done

mkdir -p build
cd build
cmake ..
make clean
make
cd ..
./build/assignment-autotest/assignment-autotest
