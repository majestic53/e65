# E65
# Copyright (C) 2018 David Jolly
#
# E65 is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# E65 is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

CC=clang++
CC_FLAGS=-march=native -std=c++17 -Wall -Werror
DIR_BUILD=./../../build/test/
DIR_INCLUDE_FUNCTIONAL=./../include/functional/
DIR_INCLUDE_INTERFACE=./../include/interface/
DIR_SRC_FUNCTIONAL=./functional/
DIR_SRC_INTERFACE=./interface/
LIB=libe65_test.a

all: build archive

### LIBRARY ###

archive:
	@echo ''
	@echo '--- BUILDING LIBRARY -----------------------'
	ar rcs $(DIR_BUILD)$(LIB) $(DIR_BUILD)functional_processor.o \
		$(DIR_BUILD)interface_processor.o
	@echo '--- DONE -----------------------------------'
	@echo ''

build: build_functional build_interface

### FUNCTIONAL ###

build_functional: functional_processor.o

functional_processor.o: $(DIR_SRC_FUNCTIONAL)processor.cpp $(DIR_INCLUDE_FUNCTIONAL)processor.h
	$(CC) $(CC_FLAGS) $(CC_BUILD_FLAGS) $(CC_TRACE_FLAGS) -c $(DIR_SRC_FUNCTIONAL)processor.cpp -o $(DIR_BUILD)functional_processor.o

### INTERFACE ###

build_interface: interface_processor.o

interface_processor.o: $(DIR_SRC_INTERFACE)processor.cpp $(DIR_INCLUDE_INTERFACE)processor.h
	$(CC) $(CC_FLAGS) $(CC_BUILD_FLAGS) $(CC_TRACE_FLAGS) -c $(DIR_SRC_INTERFACE)processor.cpp -o $(DIR_BUILD)interface_processor.o
