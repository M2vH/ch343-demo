CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
TARGET = test
SOURCES = test.cpp

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

# Debug build with additional flags
debug: CXXFLAGS += -DDEBUG -O0
debug: $(TARGET)

# Release build with optimizations
release: CXXFLAGS += -O2 -DNDEBUG
release: $(TARGET)

# Install dependencies (if needed)
install-deps:
	@echo "No additional dependencies required for this project"

.PHONY: all clean run debug release install-deps
