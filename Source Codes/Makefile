# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -g

# Target executable name
TARGET = othello

# Build directory
BUILD_DIR = build

# Source files
SRCS = main.cpp Game.cpp Player.cpp Board.cpp

# Object files - now prefixed with build directory
OBJS = $(addprefix $(BUILD_DIR)/, $(SRCS:.cpp=.o))

# Default rule
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Create the build directory before compiling
$(OBJS): | $(BUILD_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Rule to compile source files into object files in the build directory
$(BUILD_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Release rule - cleans and rebuilds with optimization
release:
	@echo "Building in release mode..."
	@$(MAKE) clean
	@$(MAKE) all CXXFLAGS="-std=c++20 -Wall -O3"

# Clean rule
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Run rule
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run release
