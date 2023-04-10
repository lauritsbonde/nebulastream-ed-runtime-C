# shamelessly stolen and modified from https://spin.atomicobject.com/2016/08/26/
UNAME := $(shell uname)

# Name of target executable
TARGET_EXEC ?= EDRuntime

# Compiler used
CC = gcc

#Top level dirs used
BUILD_DIR ?= ./build
SRC_DIRS ?= ./src

# Here we find the specific files
SRCS := $(shell find $(SRC_DIRS) -name *.c)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

# And include them for the compiler
INC_DIRS := $(shell find $(SRC_DIRS) -type d)

INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# Compiler flags
CFLAGS := $(INC_FLAGS) $(shell pkg-config --cflags 'libprotobuf-c >= 1.0.0')

# All target
all: $(BUILD_DIR)/$(TARGET_EXEC)

# To build the target executable we need to link all .o files
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS) $(shell pkg-config --libs 'libprotobuf-c >= 1.0.0')

# To build .o files we need to compile *.c files
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target to remove generated proto files
proto_clean:
	rm ${SRC_DIRS}/proto/*.pb-c.*

proto:
	$(shell cd $(SRC_DIRS)/proto; protoc-c --c_out=. *.proto)

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p

echo:
	echo $(INC_FLAGS)

buildAndRun:
	make clean
	make all
	$(BUILD_DIR)/EDRuntime


test:
	make clean
	make all
	$(BUILD_DIR)/EDRuntime test

testProtocol:
	make clean
	make all
	$(BUILD_DIR)/EDRuntime test protocol

testExpression:
	make clean
	make all
	$(BUILD_DIR)/EDRuntime test expression

