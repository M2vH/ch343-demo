# Development Environment Setup

This project uses VS Code workspace files and C++ configuration templates to support multiple host environments. All configuration templates are organized in the `config/` directory.

## Quick Setup

1. **Run the setup script:**
   ```bash
   ./scripts/setup-dev-env.sh
   ```

This will:
- Create a VS Code workspace file from the template
- Set up C++ configuration for your platform
- Create tasks and launch configurations
- Detect your system and recommend the best configuration

For detailed setup instructions and troubleshooting, see the sections below.

## Project Structure

```
ch343-demo/
├── docs/                    # Documentation
│   └── DEVELOPMENT.md       # This file
├── scripts/                 # Build and setup scripts
│   ├── setup-dev-env.sh     # Environment setup script
│   └── build.sh             # Build script
├── config/                  # Configuration templates
│   ├── vscode/              # VS Code configuration templates
│   │   ├── c_cpp_properties.json.sample
│   │   ├── tasks.json.sample
│   │   └── launch.json.sample
│   └── workspace/           # Workspace templates
│       └── ch343-demo.code-workspace.sample
├── src/                     # Source code
│   ├── main.cpp             # Main application
│   └── Makefile             # Build configuration
└── .vscode/                 # Generated VS Code config (gitignored)
    ├── c_cpp_properties.json
    ├── tasks.json
    └── launch.json
```

## Manual Setup

### 1. Copy Configuration Templates

```bash
# Copy workspace template
cp config/workspace/ch343-demo.code-workspace.sample ch343-demo.code-workspace

# Copy VS Code configuration templates
mkdir -p .vscode
cp config/vscode/c_cpp_properties.json.sample .vscode/c_cpp_properties.json
cp config/vscode/tasks.json.sample .vscode/tasks.json
cp config/vscode/launch.json.sample .vscode/launch.json
```

### 2. Open the Workspace

- In VS Code: File → Open Workspace from File → select `ch343-demo.code-workspace`
- Or from command line: `code ch343-demo.code-workspace`

### 3. Select Your Configuration

- Press `Ctrl+Shift+P` (or `Cmd+Shift+P` on macOS)
- Type "C/C++: Select a Configuration"
- Choose the configuration that matches your system

## Supported Configurations

The template includes configurations for:

- **Linux-GCC**: Standard GCC on Linux distributions
- **Linux-Clang**: Clang compiler on Linux
- **WSL-GCC**: Windows Subsystem for Linux with GCC
- **macOS-GCC**: Homebrew GCC on macOS
- **macOS-Clang**: Xcode Clang on macOS
- **Windows-MinGW**: MinGW-w64 on Windows
- **Windows-MSVC**: Microsoft Visual C++ compiler

## Customization

### Compiler Paths
Edit the `compilerPath` in your `c_cpp_properties.json` to match your system:

```json
"compilerPath": "/usr/bin/g++"          // Linux/WSL
"compilerPath": "/usr/local/bin/g++"     // macOS Homebrew
"compilerPath": "/usr/bin/clang++"       // Clang
"compilerPath": "C:/msys64/mingw64/bin/g++.exe"  // Windows MinGW
```

### Include Paths
Add additional include directories as needed:

```json
"includePath": [
    "${workspaceFolder}/**",
    "/usr/include/**",
    "/usr/local/include/**",
    "/path/to/your/libraries/**"
]
```

### Build System
The workspace includes tasks for:
- `Build C++ Project` (default build)
- `Clean Build`
- `Debug Build`
- `Release Build`
- `Run Program`

### Debugging
A debug configuration is included that:
- Builds the project in debug mode
- Launches GDB debugger
- Sets up pretty-printing

## Platform-Specific Notes

### Linux/WSL
- Install build tools: `sudo apt install build-essential gdb`
- GCC/G++ should be available at `/usr/bin/`

### macOS
- Install Xcode Command Line Tools: `xcode-select --install`
- Or install via Homebrew: `brew install gcc`

### Windows
- **MinGW**: Install MSYS2 and MinGW-w64
- **MSVC**: Install Visual Studio with C++ tools
- **WSL**: Use the Linux instructions within WSL

## Troubleshooting

### "Unable to resolve configuration" errors
1. Verify your compiler is installed and accessible
2. Check the `compilerPath` in your `c_cpp_properties.json`
3. Select the correct configuration for your platform

### IntelliSense not working
1. Ensure the correct configuration is selected
2. Reload the VS Code window: `Ctrl+Shift+P` → "Developer: Reload Window"
3. Check that include paths are correct for your system
