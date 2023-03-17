# shamelessly stolen and modified from https://spin.atomicobject.com/2016/08/26/makefile-c-projects/
# include protoc specific rules from nanopb
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
include ./external/linux/nanopb/extra/nanopb.mk
else ifeq ($(UNAME), Darwin)
include ./external/mac/nanopb/extra/nanopb.mk
endif

# Name of target executable
TARGET_EXEC ?= EDRuntime

# Compiler used
CC = gcc

# top level dirs used
BUILD_DIR ?= ./build
SRC_DIRS ?= ./src

# here we find the specific files
SRCS := $(shell find $(SRC_DIRS) -name *.c)
SRCS += $(NANOPB_CORE)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

# and include them for the compiler
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
ifeq ($(UNAME), Linux)
INC_DIRS += ./external/linux/nanopb
else ifeq ($(UNAME), Darwin)
INC_DIRS += ./external/mac/nanopb
endif
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CFLAGS := $(INC_FLAGS)

# protoc specific options. Basically remove path from the #includes in the generated c files
PROTOC_OPTS += --nanopb_opt=--strip-path

# all target
all: $(BUILD_DIR)/$(TARGET_EXEC)

# to build the target executable we need to link all .o files
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# to build .o files we need to compile all *.c files
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


# special target to generate proto files. The rules for getting the *.pb.* files are in nanopb.mk
proto: proto/EndDeviceProtocol.pb.c
	$(MKDIR_P) $(SRC_DIRS)/proto
	mv ./proto/*.pb.* $(SRC_DIRS)/proto/

# clean target to remove generated proto files
proto_clean:
	rm $(SRC_DIRS)/proto/*


clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p

echo: 
	echo $(INC_FLAGS)

main:    #target name
	make clean
	$(MKDIR_P) ./build
	$(CC) $(CFLAGS) $(SRC_DIRS)/*/*.c $(SRC_DIRS)/*.c -o $(BUILD_DIR)/EDRuntime -Wall
	echo "Build to build folder"

buildAndRun:
	make clean
	make all
	$(BUILD_DIR)/EDRuntime