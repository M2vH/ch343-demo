#!/bin/bash

# CH343 Demo Development Environment Setup Script

echo "🔧 Setting up CH343 Demo development environment..."

# Create workspace file from template
if [ ! -f "ch343-demo.code-workspace" ]; then
    if [ -f "ch343-demo.code-workspace.sample" ]; then
        cp ch343-demo.code-workspace.sample ch343-demo.code-workspace
        echo "✅ Created workspace file: ch343-demo.code-workspace"
    else
        echo "❌ Template file ch343-demo.code-workspace.sample not found"
        exit 1
    fi
else
    echo "ℹ️  Workspace file already exists: ch343-demo.code-workspace"
fi

# Create C++ properties file from template
if [ ! -f ".vscode/c_cpp_properties.json" ]; then
    if [ -f ".vscode/c_cpp_properties.json.sample" ]; then
        cp .vscode/c_cpp_properties.json.sample .vscode/c_cpp_properties.json
        echo "✅ Created C++ properties file: .vscode/c_cpp_properties.json"
    else
        echo "❌ Template file .vscode/c_cpp_properties.json.sample not found"
        exit 1
    fi
else
    echo "ℹ️  C++ properties file already exists: .vscode/c_cpp_properties.json"
fi

# Detect system and suggest configuration
echo ""
echo "🔍 Detecting your system..."

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    if grep -q Microsoft /proc/version 2>/dev/null; then
        echo "🐧 Detected: Windows Subsystem for Linux (WSL)"
        echo "📋 Recommended configuration: WSL-GCC"
    else
        echo "🐧 Detected: Linux"
        echo "📋 Recommended configuration: Linux-GCC"
    fi
    
    # Check for compilers
    if command -v g++ &> /dev/null; then
        echo "✅ g++ found at: $(which g++)"
    else
        echo "❌ g++ not found. Install with: sudo apt install build-essential"
    fi
    
    if command -v clang++ &> /dev/null; then
        echo "✅ clang++ found at: $(which clang++)"
        echo "📋 Alternative configuration: Linux-Clang"
    fi
    
elif [[ "$OSTYPE" == "darwin"* ]]; then
    echo "🍎 Detected: macOS"
    
    if command -v clang++ &> /dev/null; then
        echo "✅ clang++ found at: $(which clang++)"
        echo "📋 Recommended configuration: macOS-Clang"
    fi
    
    if command -v g++ &> /dev/null; then
        echo "✅ g++ found at: $(which g++)"
        echo "📋 Alternative configuration: macOS-GCC"
    else
        echo "ℹ️  Install g++ with: brew install gcc"
    fi
    
elif [[ "$OSTYPE" == "msys" ]] || [[ "$OSTYPE" == "cygwin" ]]; then
    echo "🪟 Detected: Windows (MSYS2/Cygwin)"
    echo "📋 Recommended configuration: Windows-MinGW"
    
else
    echo "❓ Unknown OS: $OSTYPE"
    echo "📋 Please manually select the appropriate configuration"
fi

echo ""
echo "🚀 Setup complete! Next steps:"
echo "1. Open VS Code with: code ch343-demo.code-workspace"
echo "2. Press Ctrl+Shift+P and run 'C/C++: Select a Configuration'"
echo "3. Choose the recommended configuration for your system"
echo "4. Try building with Ctrl+Shift+P → 'Tasks: Run Task' → 'Build C++ Project'"
echo ""
echo "📖 For more details, see DEVELOPMENT.md"
