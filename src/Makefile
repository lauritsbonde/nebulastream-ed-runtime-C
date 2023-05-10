# RIOT Stuff
APPLICATION = NSED_Runtime
PROJECTBASE = $(CURDIR)
BOARD ?= native

RIOTBASE ?= $(CURDIR)/../../RIOT


ifneq ($(BOARD), native)
# LoRaWAN Stuff

# Currently only supports otaa
ACTIVATION_MODE ?= otaa

APPEUI ?= 0000000000000000
DEVEUI ?= 70b3d57ed005d48f
APPKEY ?= 4485f8cb42f3f8fc3b3d10094be1303c

# Send a message every 20s after joining the network
SEND_PERIOD_S ?= 20

LORA_REGION ?= EU868

# Include the Semtech-loramac package
USEMODULE += saul_default
USEMODULE += netdev_default
DRIVER ?= sx1276
USEPKG += semtech-loramac
USEMODULE += auto_init_loramac
USEMODULE += semtech_loramac_rx

USEMODULE += $(DRIVER)
USEMODULE += fmt

CFLAGS += -DSEND_PERIOD_S=$(SEND_PERIOD_S)
CFLAGS += -DUSE_OTAA

endif

# Nanopb stuff
USEPKG += nanopb
PROTOBUF_PATH = $(CURDIR)/proto

# Timer stuff
USEMODULE += ztimer
USEMODULE += ztimer_sec

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

CREATE_STACKTEST = 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

include $(RIOTBASE)/Makefile.include

# OTAA compile time configuration keys
CFLAGS += -DCONFIG_LORAMAC_APP_KEY_DEFAULT=\"$(APPKEY)\"
CFLAGS += -DCONFIG_LORAMAC_APP_EUI_DEFAULT=\"$(APPEUI)\"
CFLAGS += -DCONFIG_LORAMAC_DEV_EUI_DEFAULT=\"$(DEVEUI)\"
CFLAGS += -DTHREAD_STACKSIZE_MAIN='(50 * 1024)'
CFLAGS += -Wall -Wextra -Wformat -Werror=format-security -Werror=array-bounds -g3