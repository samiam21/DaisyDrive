# Project Name
TARGET = DaisyTemplate

CPPFLAGS += -DUSBCON
CPPFLAGS += -DUSBD_VID=0x0483
CPPFLAGS += -DUSBD_PID=0x5740
CPPFLAGS += -DUSB_MANUFACTURER="Unknown"
CPPFLAGS += -DUSB_PRODUCT="\"ELECTROSMITH_DAISY CDC in FS Mode\""
CPPFLAGS += -DHAL_PCD_MODULE_ENABLED

# Sources
CPP_SOURCES = src/main.cpp

# Library Locations
LIBDAISY_DIR = lib/libdaisy
DAISYSP_DIR = lib/DaisySP

# Core location, and generic makefile.
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile

