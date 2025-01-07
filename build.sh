#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Define build directory
BUILD_DIR="build"

# Clean the build directory
echo "Cleaning build directory..."
rm -rf "$BUILD_DIR"
mkdir "$BUILD_DIR"

# Run CMake and build
echo "Running CMake and Make..."
cd "$BUILD_DIR"
cmake ..
make
