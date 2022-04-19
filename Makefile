NAME = main-service

WORK_DIR 	= $(shell pwd)
SRC_DIR  	= $(WORK_DIR)/src
BUILD_DIR 	= $(WORK_DIR)/build
INCLUDE_DIR = $(WORK_DIR)/include

PACKAGE 	= $(BUILD_DIR)/$(NAME) 

# set stdc++ 17 and multi-threads
CXXFLAGS += -Wall -std=c++17 -pthread
MODULES = $(filter-out src,$(notdir $(shell find $(SRC_DIR) -type d ) ) )
INCLUDES = $(addprefix -I ,$(INCLUDE_DIR))

OBJ_DIR = $(BUILD_DIR)/$(NAME)-obj

# modules optional loading
ifeq ($(MODS),)
SOURCES = $(shell find src -name "*.cpp")
else
SOURCES = $(shell find $(addprefix src/,$(MODS)) -name "*.cpp")
endif

# include shell colors definitions 
-include scripts/colors.mk

# include variables and rules generated by Kconfig automatically
-include include/config/auto.conf
-include include/config/auto.conf.cmd

ifeq ($(wildcard .config),)
$(warning $(COLOR_RED)Warning: .config does not exists!$(COLOR_END))
$(warning $(COLOR_RED)To build the project, first run 'make menuconfig'$(COLOR_END))
endif

remove_quote = $(patsubst "%",%,$(1))

# re-configure default compilr
ifneq ($(CONFIG_CC),)
CXX = $(call remove_quote,$(CONFIG_CC))
endif

# compilr optimization level (default -o2)
ifneq ($(CONFIG_CC_OPT),)
CXXFLAGS += $(call remove_quote,$(CONFIG_CC_OPT))
endif

# debug mode , and C define "DEBUG" added
ifeq ($(CONFIG_CC_DEBUG),y)
CXXFLAGS += -DDEBUG -g
endif

# build project by origin Makefile
include scripts/build.mk

# import menuconfig makefile
include scripts/config.mk

.PHONY :  clean .detect

# detect 
.detect :
ifeq ($(CONFIG_CC_DEBUG),y)
	@echo "$(C_YELLOW)Debug mode start up$(C_END)"
endif
	@echo "$(C_BLUE)Module <$(MODULES)> has been detected...$(C_END)"

# remove build dictionary
clean :
	-rm -rf $(BUILD_DIR)
