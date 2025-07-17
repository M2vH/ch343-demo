CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -I../../common/include
TARGET = shared_library_demo
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

# Debug build
debug: CXXFLAGS += -DDEBUG -O0
debug: $(TARGET)

# Release build
release: CXXFLAGS += -O2 -DNDEBUG
release: $(TARGET)

.PHONY: all clean run debug release
