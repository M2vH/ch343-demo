#!/bin/bash

# Build script for the COM port communication project
# This script builds the project in WSL2 Ubuntu environment

echo "Building COM Port Communication Test..."
echo "======================================"

# Check if we're in WSL
if grep -q Microsoft /proc/version; then
    echo "✓ Running in WSL environment"
else
    echo "⚠ Warning: Not running in WSL - some features may not work"
fi

# Check if the serial device exists
if [ -e "/dev/ttyACM0" ]; then
    echo "✓ Serial device /dev/ttyACM0 found"
else
    echo "⚠ Warning: Serial device /dev/ttyACM0 not found"
    echo "  Make sure your UART module is connected and bound to WSL"
fi

# Check for required tools
if command -v g++ &> /dev/null; then
    echo "✓ g++ compiler found"
else
    echo "✗ g++ compiler not found"
    echo "Please install build-essential: sudo apt update && sudo apt install build-essential"
    exit 1
fi

if command -v make &> /dev/null; then
    echo "✓ make found"
else
    echo "✗ make not found"
    echo "Please install make: sudo apt update && sudo apt install make"
    exit 1
fi

# Build the project
echo ""
echo "Building project..."
make clean
make

if [ $? -eq 0 ]; then
    echo ""
    echo "✓ Build successful!"
    echo "Run the program with: ./test"
    echo "Or use: make run"
else
    echo ""
    echo "✗ Build failed!"
    exit 1
fi
