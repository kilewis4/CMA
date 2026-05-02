CC = gcc
CFLAGS = -Wall -Wextra -I./include

# All source files in src/
SRC = src/allocator.c \
      src/debug.c \
      src/memory_pool.c \
      src/strategies.c

# Automatically turn each .c into a .o
OBJ = $(SRC:.c=.o)

# Test sources (each test file gets its own binary)
TEST_SRC = tests/basic_tests.c \
           tests/benchmark_tests.c \
           tests/coalescing_tests.c \
           tests/edge_tests.c \
           tests/fragmentation_tests.c \
           tests/reuse_tests.c \
           tests/split_tests.c \
           tests/stress_tests.c

TEST_BINS = $(TEST_SRC:.c=)

TARGET = allocator

# =====================
# Main build
# =====================
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Compile any .c to .o
%.o: %.c include/allocator.h
	$(CC) $(CFLAGS) -c $< -o $@

# =====================
# Tests
# =====================
tests/%: tests/%.c $(OBJ)
	$(CC) $(CFLAGS) -o $@ $< $(OBJ)

test: $(TEST_BINS)
	@for t in $(TEST_BINS); do \
		echo "Running $$t..."; \
		./$$t; \
	done

# =====================
# Cleanup
# =====================
clean:
	rm -f $(OBJ) $(TARGET) $(TEST_BINS)
