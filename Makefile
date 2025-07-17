# CH343 Demo Project - Root Makefile
# Builds all examples and manages the project

.PHONY: all clean examples help list

# Default target
all: examples

# Build all examples
examples:
	@echo "Building all examples..."
	@cd examples/01-basic-serial && $(MAKE)
	@cd examples/02-shared-library && $(MAKE)
	@echo "All examples built successfully!"

# Clean all examples
clean:
	@echo "Cleaning all examples..."
	@cd examples/01-basic-serial && $(MAKE) clean
	@cd examples/02-shared-library && $(MAKE) clean
	@echo "All examples cleaned!"

# List all available examples
list:
	@echo "Available examples:"
	@echo "  01-basic-serial     - Original serial communication example"
	@echo "  02-shared-library   - Example using shared SerialPort class"
	@echo ""
	@echo "To build a specific example:"
	@echo "  cd examples/01-basic-serial && make"
	@echo "  cd examples/02-shared-library && make"

# Show help
help:
	@echo "CH343 Demo Project Makefile"
	@echo "=========================="
	@echo ""
	@echo "Available targets:"
	@echo "  all        - Build all examples (default)"
	@echo "  examples   - Build all examples"
	@echo "  clean      - Clean all examples"
	@echo "  list       - List all available examples"
	@echo "  help       - Show this help message"
	@echo ""
	@echo "Project structure:"
	@echo "  examples/          - Code samples and experiments"
	@echo "  common/           - Shared utilities and libraries"
	@echo "  docs/             - Documentation"
	@echo "  scripts/          - Build and setup scripts"
	@echo "  config/           - Configuration templates"
