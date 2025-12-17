# --------------------------------------------------
# Project configuration
# --------------------------------------------------
PROJECT     := neoncoin
CXX         := g++
CXXFLAGS    := -std=c++14 -Wall -Wextra -O2
LDFLAGS     := -lcryptopp -lsqlite3

SRC_DIR     := src
BIN_DIR     := bin
BUILD_DIR   := build

# --------------------------------------------------
# Automatically find all .cpp files recursively
# --------------------------------------------------
SRCS := $(shell find $(SRC_DIR) -name "*.cpp")
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# --------------------------------------------------
# Default target
# --------------------------------------------------
all: $(BIN_DIR)/$(PROJECT)

# --------------------------------------------------
# Link final binary
# --------------------------------------------------
$(BIN_DIR)/$(PROJECT): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# --------------------------------------------------
# Compile source files (supports subdirectories)
# --------------------------------------------------
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -c $< -o $@

# --------------------------------------------------
# Cleanup
# --------------------------------------------------
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean
