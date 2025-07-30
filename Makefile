CC = clang
CFLAGS = -Wall -Wextra -Iinclude

SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include
LIB_NAME = cRegex

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

TARGET_LIB = $(BUILD_DIR)/$(LIB_NAME).a

all: $(TARGET_LIB)

$(TARGET_LIB): $(OBJ)
	ar rcs $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
