# CH343 Examples and Code Samples

This directory contains various code samples and experiments for CH343 serial communication.

## Available Examples

### 01-basic-serial
**Original Implementation**
- Self-contained serial communication example
- Includes SerialPort class implementation inline
- Good for learning the basics
- **Use case**: Understanding serial communication fundamentals

```bash
cd examples/01-basic-serial
make run
```

### 02-shared-library
**Shared Library Implementation**
- Uses the common SerialPort library
- Demonstrates configuration changes
- Tests multiple baud rates
- More advanced features
- **Use case**: Production-ready code structure

```bash
cd examples/02-shared-library
make run
```

## Creating New Examples

### Directory Structure for New Examples

```
examples/
└── 03-your-example/
    ├── main.cpp         # Your code
    ├── Makefile         # Build configuration
    └── README.md        # Documentation
```

### Template Makefile

```makefile
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -I../../common/include
TARGET = your_example_name
COMMON_SRC = ../../common/src/serial_port.cpp
SOURCES = main.cpp $(COMMON_SRC)

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Clean build artifacts
clean:
	rm -f $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
```

### Using the Shared Library

```cpp
#include "../../common/include/serial_port.hpp"
#include <iostream>

int main() {
    CH343::SerialPort port;
    
    if (!port.open("/dev/ttyACM0", 115200)) {
        std::cerr << "Failed to open serial port" << std::endl;
        return 1;
    }
    
    // Your code here...
    
    return 0;
}
```

## Industry Best Practices Applied

### ✅ **Separation of Concerns**
- **Common utilities**: `common/` directory
- **Examples**: Each in its own directory
- **Configuration**: Separate makefiles per example

### ✅ **Scalable Structure**
- Easy to add new examples
- No conflicts between different experiments
- Clear naming convention

### ✅ **Reusable Components**
- Shared `SerialPort` class in `common/`
- Consistent build system
- Template-based approach

### ✅ **Documentation**
- Each example documents its purpose
- Clear build instructions
- Usage examples

## Building All Examples

From the project root:

```bash
# Build all examples
make examples

# Clean all examples
make clean

# List available examples
make list

# Show help
make help
```

## Example Ideas for Future Development

### 03-protocol-parser
- Implement a custom protocol parser
- Handle structured messages
- Error detection and correction

### 04-async-communication
- Non-blocking I/O
- Event-driven architecture
- Multiple concurrent connections

### 05-data-logging
- Log serial data to files
- Timestamp management
- Data visualization

### 06-unit-tests
- Unit tests for SerialPort class
- Mock serial devices
- Automated testing

### 07-performance-testing
- Benchmark different configurations
- Measure throughput
- Latency analysis

This structure follows industry best practices used by major projects like:
- **Arduino libraries** (examples/ directory)
- **Qt framework** (separate example projects)
- **Boost libraries** (modular examples)
- **Google projects** (clear separation of concerns)
