#!/bin/bash

# Build script for VelocityVortex

echo "Building VelocityVortex..."

# Create build directory if it doesn't exist
mkdir -p build
cd build

# Run CMake
echo "Running CMake..."
cmake ..

if [ $? -ne 0 ]; then
    echo "CMake configuration failed!"
    exit 1
fi

# Build the project
echo "Building..."
make

if [ $? -ne 0 ]; then
    echo "Build failed!"
    exit 1
fi

echo "Build successful! Run './build/VelocityVortex' to start the game."
