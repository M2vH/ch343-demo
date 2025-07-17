# Comunication on COM Port

We are using Win11 as our host machine.
We are running ubuntu 22.04 on WSL2.
We connect an UART module to USB.

We bind and attach the USB Port to WSL using `usbipd`

Opening Ubuntu 22.04 on WSL:

    - we can see our UART Module as `/dev/ttyACM0`

## User Story

As a developer i want to test the communication with a simple commandline program.
The program `Test` will write and receive text on COM Port.
To check the integration, we will cross-connect the RX and TX line on themodule with hard wires.
The commandline program must be written in C++
The IDE must be VS Code
The program MUST run on the ubuntu 22.04 WSL2 container

## Project Structure

```
├── test.cpp              # Main C++ source file with SerialPort class
├── Makefile              # Build configuration with multiple targets
├── build.sh              # Build script with environment checks
├── .vscode/              # VS Code configuration
│   ├── tasks.json        # Build and run tasks
│   ├── c_cpp_properties.json # IntelliSense configuration
│   └── launch.json       # Debug configuration
├── .gitignore            # Git ignore patterns
└── ReadMe.md             # This file
```

## Quick Start

1. **Build the project:**
   ```bash
   make
   ```

2. **Run the program:**
   ```bash
   make run
   ```

3. **For development in VS Code:**
   - Press `Ctrl+Shift+P` → "Tasks: Run Task" → "Build C++ Project"
   - Press `F5` to debug (requires C++ extension)

## Clipboard

```cpp
// test.cpp - Full implementation provided
// Serial communication class with proper UART configuration
// Includes loopback testing capability
```

```bash
# Build commands
make              # Build the project
make run          # Build and run
make clean        # Clean build artifacts
make debug        # Build with debug symbols
make release      # Build optimized version

# Or use the build script
chmod +x build.sh
./build.sh
```
