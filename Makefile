# ms8x32 - 256-bit integers, grouped as eight 32-bit words.
# Copyright (C) 2023  Maciej Sawka <maciejsawka@gmail.com> <msaw328@kretes.xyz>
# 
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

.PHONY: all clear test

.DEFAULT_GOAL := all

# build directory
build:
	mkdir -p build/lib build/test

# C compiler flags
CFLAGS := -Wall -Werror -Wextra -pedantic -std=c99 -I./include/

# List of source files
SRC := base.c arithmetic.c cmp.c conv.c internal.c debug.c
SRC := $(patsubst %,src/%,$(SRC))

# List of object files of the library
OBJ := $(patsubst src/%.c,build/lib/%.o,$(SRC))

# 1 source file = 1 object file
build/lib/%.o: src/%.c
	$(CC) -c $(CFLAGS) $^ -o $@

# All object files = 1 library file
build/lib/libms8x32.so: $(OBJ)
	$(CC) -shared $(CFLAGS) $^ -o $@

# List of test source files
TEST_SRC := \
	arithmetic/addition.c arithmetic/multiplication.c \
	cmp.c \
	conv/bytes.c conv/u32.c

TEST_SRC := $(patsubst %,test/%,$(TEST_SRC))

# List of object files of the library
TEST_BIN := $(patsubst test/%.c,build/test/%,$(TEST_SRC))

# 1 test source file = 1 test binary
build/test/%: test/%.c
	mkdir -p $(shell dirname $@) && $(CC) $(CFLAGS) -I./test -lms8x32 -L./build/lib $^ -o $@

# Phony targets below this point
all: build build/lib/libms8x32.so

test: build build/lib/libms8x32.so $(TEST_BIN)

clear:
	rm -rf build
