# Makefile for building the object oriented C library and complementary binaries
# part of the embedded-software module at the UAS Münster
# Author: Daniel Knüppe (@DanielKnueppe)

TARGETS = motor_driver
LIBRARY = ooc
LIB_DIR = OO-C
BUILD_DIR = build

INC_DIRS = $(wildcard */inc) ./WiringPi/wiringPi
SRCS = $(foreach T, $(TARGETS), $(wildcard $T/src/*.c))
LIB_SRCS = $(foreach L, $(LIB_DIR), $(wildcard $L/src/*.c))

LIB_OBJS = $(foreach S, $(notdir $(LIB_SRCS)), $(BUILD_DIR)/$(basename $(S)).o)
OBJS = 	$(foreach S, $(notdir $(SRCS)), $(BUILD_DIR)/$(basename $(S)).o)
OBJS += $(LIB_OBJS)

CC = arm-linux-gnueabihf-gcc
CC_FLAGS = -ggdb3 -Og -std=c99
LD_FLAGS = -L./WiringPi/wiringPi
LIBS = wiringPi m crypt rt pthread
WARNINGS = all extra pedantic cast-align cast-qual disabled-optimization \
		   format=2 logical-op missing-declarations missing-include-dirs shadow \
		   redundant-decls sign-conversion strict-overflow=5 switch-default undef \
		   maybe-uninitialized duplicated-cond pointer-arith 
DEFINES = _GNU_SOURCE UNIT_TEST

all : $(BUILD_DIR) $(BUILD_DIR)/lib$(LIBRARY).a $(OBJS) $(foreach T, $(TARGETS), $(BUILD_DIR)/$T) #test

$(BUILD_DIR) :
	mkdir $@

$(BUILD_DIR)/%.o : */src/%.c */inc/%.h
	$(CC) -o $@ -c $< $(CC_FLAGS) \
	$(foreach D, $(INC_DIRS), -I$D) \
	$(foreach D, $(LIB_DIRS), -L$D) \
	$(foreach W, $(WARNINGS), -W$W) \
	$(foreach L, $(LIBS),     -l$L) \
	$(foreach D, $(DEFINES),  -D$D)

$(BUILD_DIR)/%.o : */src/%.c
	$(CC) -o $@ -c $< $(CC_FLAGS) \
	$(foreach D, $(INC_DIRS), -I$D) \
	$(foreach D, $(LIB_DIRS), -L$D) \
	$(foreach W, $(WARNINGS), -W$W) \
	$(foreach L, $(LIBS),     -l$L) \
	$(foreach D, $(DEFINES),  -D$D)

$(BUILD_DIR)/lib$(LIBRARY).a : $(LIB_OBJS)
	ar rcs $@ $^ 

###############################################################################
# These templates in conjunction with the following foreach loops serve
# the purpose of creating make targets, that have different parameters
# but where every parameter can be determined through rules.
# also for some reason automatic variables don't work inside said template
###############################################################################
define OBJECT_template
$1 : $2
	$(CC) -o $1 -c $(firstword $2) $(CC_FLAGS) \
	$(foreach D, $(INC_DIRS), -I$D) \
	$(foreach D, $(LIB_DIRS), -L$D) \
	$(foreach W, $(WARNINGS), -W$W) \
	$(foreach L, $(LIBS),     -l$L) \
	$(foreach D, $(DEFINES),  -D$D)
endef

define TARGET_template
$1 : $2 $(BUILD_DIR)/lib$(LIBRARY).a
	$(CC) -o $1 $2 -L$(BUILD_DIR) -l$(LIBRARY) \
	$(CC_FLAGS) $(LD_FLAGS) \
	$(foreach D, $(INC_DIRS), -I$D) \
	$(foreach D, $(LIB_DIRS), -L$D) \
	$(foreach W, $(WARNINGS), -W$W) \
	$(foreach L, $(LIBS),     -l$L) \
	$(foreach D, $(DEFINES),  -D$D)
endef

#$(eval $(call OBJECT_template, $(BUILD_DIR)/%.o, */src/%.c */inc/%.h))
#$(eval $(call OBJECT_template, $(BUILD_DIR)/%.o, */src/%.c))

$(foreach T, $(TARGETS), $(eval $(call TARGET_template, $(BUILD_DIR)/$T, \
		$(foreach S, $(basename $(notdir $(wildcard $T/src/*.c))), $(BUILD_DIR)/$S.o))))
###############################################################################

clean :
	rm -rf $(BUILD_DIR)

.PHONY : all clean #test

#include testsuite/test.mk

