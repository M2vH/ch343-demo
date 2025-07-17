# Development Environment Setup

This project uses VS Code workspace files and C++ configuration templates to support multiple host environments.

## Quick Setup

1. **Copy the workspace template:**
   ```bash
   cp ch343-demo.code-workspace.sample ch343-demo.code-workspace
   ```

2. **Copy the C++ configuration template:**
   ```bash
   cp .vscode/c_cpp_properties.json.sample .vscode/c_cpp_properties.json
   ```

3. **Open the workspace:**
   - In VS Code: File → Open Workspace from File → select `ch343-demo.code-workspace`
   - Or from command line: `code ch343-demo.code-workspace`

4. **Select your configuration:**
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
