# Project Name
TARGET = PatchSkeleton

# Sources
CPP_SOURCES = patchsm_skeleton.cpp

# Library Locations
LIBDAISY_DIR = ../libdaisy/
DAISYSP_DIR = ../DaisySP/

# Core location, and generic Makefile.
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile