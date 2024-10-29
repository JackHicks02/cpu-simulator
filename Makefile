# Compiler and flags
CC = gcc
CFLAGS = -Wall -Iinclude -O3

# Directories
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include
TEST_DIR = tests

# Source and object files, excluding main.c for testing
SRCS := $(wildcard $(SRC_DIR)/*.c)
TEST_SRCS := $(filter-out $(SRC_DIR)/main.c, $(SRCS))
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
TEST_OBJS := $(TEST_SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Target executable
TARGET = $(BUILD_DIR)/computer

# Default rule
all: $(TARGET)

# Link object files into the final executable, including main.o
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile each source file into an object file
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean up build artifacts
clean:
	rm -rf $(BUILD_DIR)

# Run all test files in the tests directory, without main.o
test: $(TEST_OBJS)
	@mkdir -p $(BUILD_DIR)/tests
	@for test_file in $(wildcard $(TEST_DIR)/*.c); do \
		test_exec=$(BUILD_DIR)/tests/$$(basename $$test_file .c); \
		$(CC) $(CFLAGS) $$test_file $(TEST_OBJS) -o $$test_exec && \
		echo "Running $$test_exec" && $$test_exec; \
	done
