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
DIR_INCLUDE_TYPE=./../include/type/
DIR_SRC_FUNCTIONAL=./functional/
DIR_SRC_INTERFACE=./interface/
DIR_SRC_TYPE=./type/
LIB=libe65_test.a

all: build archive

### LIBRARY ###

archive:
	@echo ''
	@echo '--- BUILDING TEST LIBRARY ------------------'
	ar rcs $(DIR_BUILD)$(LIB) $(DIR_BUILD)functional_processor.o\
			$(DIR_BUILD)interface_input.o $(DIR_BUILD)interface_memory.o $(DIR_BUILD)interface_processor.o $(DIR_BUILD)interface_video.o \
		$(DIR_BUILD)type_fixture.o
	@echo '--- DONE -----------------------------------'
	@echo ''

build: build_functional build_interface build_type

### FUNCTIONAL ###

build_functional: functional_processor.o

functional_processor.o: $(DIR_SRC_FUNCTIONAL)processor.cpp $(DIR_INCLUDE_FUNCTIONAL)processor.h
	$(CC) $(CC_FLAGS) $(CC_BUILD_FLAGS) $(CC_TRACE_FLAGS) -c $(DIR_SRC_FUNCTIONAL)processor.cpp -o $(DIR_BUILD)functional_processor.o

### INTERFACE ###

build_interface: interface_input.o interface_memory.o interface_processor.o interface_video.o

interface_input.o: $(DIR_SRC_INTERFACE)input.cpp $(DIR_INCLUDE_INTERFACE)input.h
	$(CC) $(CC_FLAGS) $(CC_BUILD_FLAGS) $(CC_TRACE_FLAGS) -c $(DIR_SRC_INTERFACE)input.cpp -o $(DIR_BUILD)interface_input.o

interface_memory.o: $(DIR_SRC_INTERFACE)memory.cpp $(DIR_INCLUDE_INTERFACE)memory.h
	$(CC) $(CC_FLAGS) $(CC_BUILD_FLAGS) $(CC_TRACE_FLAGS) -c $(DIR_SRC_INTERFACE)memory.cpp -o $(DIR_BUILD)interface_memory.o

interface_processor.o: $(DIR_SRC_INTERFACE)processor.cpp $(DIR_INCLUDE_INTERFACE)processor.h
	$(CC) $(CC_FLAGS) $(CC_BUILD_FLAGS) $(CC_TRACE_FLAGS) -c $(DIR_SRC_INTERFACE)processor.cpp -o $(DIR_BUILD)interface_processor.o

interface_video.o: $(DIR_SRC_INTERFACE)video.cpp $(DIR_INCLUDE_INTERFACE)video.h
	$(CC) $(CC_FLAGS) $(CC_BUILD_FLAGS) $(CC_TRACE_FLAGS) -c $(DIR_SRC_INTERFACE)video.cpp -o $(DIR_BUILD)interface_video.o

### TYPE ###

build_type: type_fixture.o

type_fixture.o: $(DIR_SRC_TYPE)fixture.cpp $(DIR_INCLUDE_TYPE)fixture.h
	$(CC) $(CC_FLAGS) $(CC_BUILD_FLAGS) $(CC_TRACE_FLAGS) -c $(DIR_SRC_TYPE)fixture.cpp -o $(DIR_BUILD)type_fixture.o
