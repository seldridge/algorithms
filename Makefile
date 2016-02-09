DIR_BUILD = build
DIR_SRC   = src

C_OBJECTS = $(addprefix $(DIR_BUILD)/,$(notdir $(shell \
	find src/main/c | grep "\\.\(c\)$$" | \
	sed -e 's/\(.\+\)\.\(.\+\)/\1-\2.o/')))
C_TARGETS = $(addprefix $(DIR_BUILD)/,$(notdir $(shell \
	find src/test/c | grep "\\.[a-zA-Z0-9]\+$$" | \
	sed -e 's/\(.\+\)\.\(.\+\)/\1-\2/')))

CC_HEADERS = $(shell find src/main/cc -regex ".+\.h")
CC_OBJECTS = $(addprefix $(DIR_BUILD)/,$(notdir $(shell \
	find src/main/cc | grep "\\.\(cc\)$$" | \
	sed -e 's/\(.\+\)\.\(.\+\)/\1-\2.o/')))
CC_TARGETS = $(addprefix $(DIR_BUILD)/,$(notdir $(shell \
	find src/test/cc | grep "\\.[a-zA-Z0-9]\+$$" | \
	sed -e 's/\(.\+\)\.\(.\+\)/\1-\2/')))

# C options
GCC = gcc
C_FLAGS = -g -O2 -Wall -Werror

# C++ options
CC_LINT = cpplint
GPP = g++
CC_FLAGS = -std=c++11 -g -O2 -Wall -Werror

# C++ compiler and options
G++ = g++

vpath %.c $(DIR_SRC)/main/c
vpath %.c $(DIR_SRC)/test/c

vpath %.cc $(DIR_SRC)/main/cc
vpath %.cc $(DIR_SRC)/test/cc

.PHONY: all clean test

all: $(C_TARGETS) $(CC_TARGETS)

$(DIR_BUILD)/%-c.o: %.c
	$(GCC) $(C_FLAGS) -I $(DIR_SRC)/main/c $< -c -o $@

$(DIR_BUILD)/%-c: %.c $(C_OBJECTS)
	$(GCC) $(C_FLAGS) -I $(DIR_SRC)/main/c $< $(C_OBJECTS) -o $@

$(DIR_BUILD)/%-cc.o: %.cc $(CC_HEADERS)
	@ cat $< | grep ^#include | awk '{print $$2}' | xargs $(CC_LINT)
	$(CC_LINT) $<
	$(GPP) $(CC_FLAGS) -I . $< -c -o $@

$(DIR_BUILD)/%-cc: %.cc $(CC_OBJECTS) $(CC_HEADERS)
	@ cat $< | grep ^#include | awk '{print $$2}' | xargs $(CC_LINT)
	$(CC_LINT) $<
	$(GPP) $(CC_FLAGS) -I . $< $(CC_OBJECTS) -o $@
	echo $(CC_HEADERS)

test:
	$(DIR_BUILD)/sort-insertion-c
	$(DIR_BUILD)/sort-merge-c
	$(DIR_BUILD)/sort-heap-c
	$(DIR_BUILD)/sort-quick-c

clean:
	rm -rf $(DIR_BUILD)/*
