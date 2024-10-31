# Compiler and flags
CC = gcc
CFLAGS = -Wall -Iinclude -O3

# Windows compiler and flags
WIN_CC = x86_64-w64-mingw32-gcc
WIN_CFLAGS = -Wall -Iinclude -O3

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

# Target executables
TARGET = $(BUILD_DIR)/computer
WIN_TARGET = $(BUILD_DIR)/computer.exe

# Default rule to build both Linux and Windows executables
all: $(TARGET) $(WIN_TARGET)

# Link object files into the final executable, including main.o for Linux
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Link object files into the Windows executable
$(WIN_TARGET): $(OBJS)
	$(WIN_CC) $(WIN_CFLAGS) -o $@ $^

# Compile each source file into an object file for Linux
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile each source file into an object file for Windows
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(WIN_CC) $(WIN_CFLAGS) -c $< -o $@

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean up build artifacts
clean:
	rm -rf $(BUILD_DIR)

# Run all test files in the tests directory, without main.o for Linux
test: $(TEST_OBJS)
	@mkdir -p $(BUILD_DIR)/tests
	@for test_file in $(wildcard $(TEST_DIR)/*.c); do \
		test_exec=$(BUILD_DIR)/tests/$$(basename $$test_file .c); \
		$(CC) $(CFLAGS) $$test_file $(TEST_OBJS) -o $$test_exec && \
		echo "Running $$test_exec" && $$test_exec; \
	done

# Windows test target (optional)
test_win: $(TEST_OBJS)
	@mkdir -p $(BUILD_DIR)/tests
	@for test_file in $(wildcard $(TEST_DIR)/*.c); do \
		test_exec=$(BUILD_DIR)/tests/$$(basename $$test_file .c).exe; \
		$(WIN_CC) $(WIN_CFLAGS) $$test_file $(TEST_OBJS) -o $$test_exec && \
		echo "Running $$test_exec" && ./$$test_exec; \
	done

