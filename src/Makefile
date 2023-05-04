# RIOT Stuff
APPLICATION = NSED_Runtime
PROJECTBASE = $(CURDIR)
BOARD ?= arduino-mkrwan1300

RIOTBASE ?= $(CURDIR)/../../RIOT

# LoRaWAN Stuff

# Assuming that we use OTAA activation mode
ACTIVATION_MODE ?= otaa

DEVEUI ?= 0000000000000000
APPEUI ?= 0000000000000000
APPKEY ?= 00000000000000000000000000000000

# # Send a message every 20s after joining the network
SEND_PERIOD_S ?= 20

LORA_REGION ?= EU868

# Include the Semtech-loramac package
USEPKG += semtech-loramac
# USEMODULE += auto_init_loramac

USEMODULE += $(DRIVER)
USEMODULE += fmt

CFLAGS += -DSEND_PERIOD_S=$(SEND_PERIOD_S)
CFLAGS += -DUSE_OTAA

# Nanopb stuff
USEPKG += nanopb
PROTOBUF_PATH = $(CURDIR)/proto

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

include $(RIOTBASE)/Makefile.include

# OTAA compile time configuration keys
CFLAGS += -DCONFIG_LORAMAC_APP_KEY_DEFAULT=\"$(APPKEY)\"
CFLAGS += -DCONFIG_LORAMAC_APP_EUI_DEFAULT=\"$(APPEUI)\"
CFLAGS += -DCONFIG_LORAMAC_DEV_EUI_DEFAULT=\"$(DEVEUI)\"
