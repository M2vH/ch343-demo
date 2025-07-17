# Comunication on COM Port

We are using Win11 as our host machine.
We are running ubuntu 22.04 on WSL2.
We connect an UART module to USB on Windows host

We bind and attach the USB Port to WSL using `usbipd` as admin in `pwsh`

```text
pwsh> usbipd list
Connected:
BUSID  VID:PID    DEVICE                                                        STATE
1-2    1a86:55d3  USB-Enhanced-SERIAL CH343 (COM4)                              Shared
1-6    045e:0990  Surface Camera Front, Surface IR Camera Front                 Not shared
1-10   8087:0026  Intel(R) Wireless Bluetooth(R)                                Not shared

Persisted:
GUID                                  DEVICE
da5b906e-1fa9-4d45-b588-2741bffdd1a2  USB-Enhanced-SERIAL CH343 (COM3)

pwsh> usbipd attach --wsl --busid 1-2
usbipd: info: Using WSL distribution 'Ubuntu-22.04' to attach; the device will be available in all WSL 2 distributions.
usbipd: info: Detected networking mode 'nat'.
usbipd: info: Using IP address 172.17.160.1 to reach the host.
```

---

## Switch to WSL dev environment

Open Ubuntu 22.04 on WSL:

look for our UART Module as `/dev/ttyACM0`

```bash
ls /dev/ttyAC*
```

Output:

```text
/dev/ttyACM0
```

## Quick Start

### Development Environment Setup

For first-time setup, run the automated setup script:

```bash
./scripts/setup-dev-env.sh
```

This will:
- Create a VS Code workspace file from the template
- Set up C++ configuration for your platform
- Detect your system and recommend the best configuration

For detailed setup instructions and troubleshooting, see [docs/DEVELOPMENT.md](docs/DEVELOPMENT.md).

### Building and Running

1. Open the workspace: `code ch343-demo.code-workspace`
2. Build the project: `Ctrl+Shift+P` → "Tasks: Run Task" → "Build C++ Project"
3. Run the program: `Ctrl+Shift+P` → "Tasks: Run Task" → "Run Program"

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

```bash
# change to `./src` directory
cd ./src
```

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
// main.cpp - Full implementation provided
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

### User Story

As a developer i want to test the communication with a simple commandline program.
The program `Test` will write and receive text on COM Port.
To check the integration, we will cross-connect the RX and TX line on the module with hard wires.
The commandline program will be written in C++
The IDE will be VS Code

The program MUST run on the ubuntu 22.04 WSL2 container
