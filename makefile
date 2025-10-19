CC = gcc
# Add a -Werror when doing github tests
CFLAGS = -Wall -Wextra -std=c11 -g
BUILD_DIR := ./build
SRC_DIRS := ./src
TARGET_EXEC := gone
SRCS := $(wildcard $(SRC_DIRS)/*.c)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

TARGET = gone
RM = rm -rf $(BUILD_DIR)
MKDIR_P = mkdir -p $(1)

# PHONY is for stuff that doesn't create files.
.PHONY: all run clean

all: $(BUILD_DIR)/$(TARGET_EXEC)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	@echo "Creating executable: $@"
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(BUILD_DIR)/%.c.o: %.c
	@echo "Building $<"
	$(call MKDIR_P,$(dir $@))
	$(CC) $(CFLAGS) -c $< -o $@

INPUT ?= test.gone
run: $(BUILD_DIR)/$(TARGET_EXEC)
	@echo "Running $(TARGET_EXEC) with input: $(INPUT)"
	$(BUILD_DIR)/$(TARGET_EXEC) $(INPUT)

clean:
	$(RM)