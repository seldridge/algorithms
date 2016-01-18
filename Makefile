DIR_BUILD = build
DIR_SRC   = src

OBJECTS = $(addprefix $(DIR_BUILD)/,$(notdir $(shell \
	find src/main | grep "\\.\(c\)$$" | sed -e 's/\(.\+\)\.\(.\+\)/\1-\2.o/')))
TARGETS = $(addprefix $(DIR_BUILD)/,$(notdir $(shell \
	find src/test | grep "\\.[a-zA-Z0-9]\+$$" | sed -e 's/\(.\+\)\.\(.\+\)/\1-\2/')))

# C compiler and options
GCC = gcc

# C++ compiler and options
G++ = g++

vpath %.c $(DIR_SRC)/main/c
vpath %.c $(DIR_SRC)/test/c

.PHONY: all clean test

all: $(OBJECTS) $(TARGETS)

$(DIR_BUILD)/%-c.o: %.c
	$(GCC) -O2 -I $(DIR_SRC)/main/c $< -c -o $@

$(DIR_BUILD)/%-c: %.c $(OBJECTS)
	$(GCC) -O2 -I $(DIR_SRC)/main/c $< $(OBJECTS) -o $@

test:
	$(DIR_BUILD)/sort-insertion-c
	$(DIR_BUILD)/sort-merge-c
	$(DIR_BUILD)/sort-heap-c
	$(DIR_BUILD)/sort-quick-c

clean:
	rm -rf $(DIR_BUILD)/*
