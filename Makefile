# Compiler options
CC = g++
CFLAGS = -std=c++14 -Wall -g
LINKING = -lgdi32

# Directories
SRC_DIR = src
BUILD_DIR = build
APP_NAME = main


# Source files and output file name
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
TARGET = $(APP_NAME).exe

# Rule to build the target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LINKING) -o $@

# Rule to compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

# Create the build directory
# $(shell mkdir $(BUILD_DIR) 2>/dev/null)

# Clean rule
clean:
	rm -rf $(BUILD_DIR)/* $(TARGET)
