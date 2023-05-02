# RIOT Stuff
APPLICATION = NSED_Runtime
PROJECTBASE = ./src
BOARD ?= arduino-mkrwan1300

RIOTBASE ?= $(CURDIR)/../../RIOT

# LoRaWAN Stuff

# Assuming that we use OTAA activation mode
ACTIVATION_MODE = otaa

DEVEUI ?= 0000000000000000
APPEUI ?= 0000000000000000
APPKEY ?= 00000000000000000000000000000000

# Send a message every 20s after joining the network
SEND_PERIOD_S ?= 20

LORA_REGION ?= EU868

# Include the Semtech-loramac package
USEPKG += semtech-loramac
USEMODULE += auto_init_loramac

USEMODULE += $(DRIVER)
USEMODULE += fmt
FEATURES_OPTIONAL += periph_rtc

CFLAGS += -DSEND_PERIOD_S=$(SEND_PERIOD_S)
CFLAGS += -DUSE_OTAA

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1


USEMODEULE += protobuf-c

include $(RIOTBASE)/Makefile.include

# OTAA compile time configuration keys
CFLAGS += -DCONFIG_LORAMAC_APP_KEY_DEFAULT=\"$(APPKEY)\"
CFLAGS += -DCONFIG_LORAMAC_APP_EUI_DEFAULT=\"$(APPEUI)\"
CFLAGS += -DCONFIG_LORAMAC_DEV_EUI_DEFAULT=\"$(DEVEUI)\"

# # shamelessly stolen and modified from https://spin.atomicobject.com/2016/08/26/
# UNAME := $(shell uname)

# # Name of target executable
# TARGET_EXEC ?= EDRuntime

# # Compiler used
# CC = gcc

# #Top level dirs used
# BUILD_DIR ?= ./build
# SRC_DIRS ?= ./src

# # Here we find the specific files
# SRCS := $(shell find $(SRC_DIRS) -name *.c)
# OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
# DEPS := $(OBJS:.o=.d)

# # And include them for the compiler
# INC_DIRS := $(shell find $(SRC_DIRS) -type d)

# INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# # Compiler flags
# CFLAGS := $(INC_FLAGS) $(shell pkg-config --cflags 'libprotobuf-c >= 1.0.0')

# # All target
# all: $(BUILD_DIR)/$(TARGET_EXEC)

# # To build the target executable we need to link all .o files
# $(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
# 	$(CC) $(OBJS) -o $@ $(LDFLAGS) $(shell pkg-config --libs 'libprotobuf-c >= 1.0.0')

# # To build .o files we need to compile *.c files
# $(BUILD_DIR)/%.c.o: %.c
# 	$(MKDIR_P) $(dir $@)
# 	$(CC) $(CFLAGS) -c $< -o $@

# # Clean target to remove generated proto files
# proto_clean:
# 	rm ${SRC_DIRS}/proto/*.pb-c.*

# proto:
# 	$(shell cd $(SRC_DIRS)/proto; protoc-c --c_out=. *.proto)

# clean:
# 	$(RM) -r $(BUILD_DIR)

# -include $(DEPS)

# MKDIR_P ?= mkdir -p

# echo:
# 	echo $(INC_FLAGS)

# buildAndRun:
# 	make clean
# 	make all
# 	$(BUILD_DIR)/EDRuntime


# test:
# 	make clean
# 	make all
# 	$(BUILD_DIR)/EDRuntime test

# testProtocol:
# 	make clean
# 	make all
# 	$(BUILD_DIR)/EDRuntime test protocol

# testExpression:
# 	make clean
# 	make all
# 	$(BUILD_DIR)/EDRuntime test expression

