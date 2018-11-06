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
DIR_BIN_INCLUDE=./../bin/include/
DIR_BIN_LIB=./../bin/lib/
DIR_BUILD=./../build/
DIR_INCLUDE=./../include/
DIR_INCLUDE_SYSTEM=./../include/system/
DIR_INCLUDE_TYPE=./../include/type/
DIR_SRC=./
DIR_SRC_SYSTEM=./system/
DIR_SRC_TYPE=./type/
LIB=libe65.a

all: build archive

### LIBRARY ###

archive:
	@echo ''
	@echo '--- BUILDING LIBRARY -----------------------'
	ar rcs $(DIR_BIN_LIB)$(LIB) $(DIR_BUILD)base_e65.o $(DIR_BUILD)base_exception.o $(DIR_BUILD)base_runtime.o $(DIR_BUILD)base_trace.o \
		$(DIR_BUILD)system_bus.o $(DIR_BUILD)system_display.o $(DIR_BUILD)system_input.o $(DIR_BUILD)system_memory.o \
			$(DIR_BUILD)system_processor.o $(DIR_BUILD)system_video.o \
		$(DIR_BUILD)type_signal.o $(DIR_BUILD)type_thread.o
	cp $(DIR_INCLUDE)e65.h $(DIR_BIN_INCLUDE)
	@echo '--- DONE -----------------------------------'
	@echo ''

build: build_base build_system build_type

### BASE ###

build_base: base_e65.o base_exception.o base_runtime.o base_trace.o

base_e65.o: $(DIR_SRC)e65.cpp $(DIR_INCLUDE)e65.h
	$(CC) $(CC_FLAGS) $(CC_BUILD_FLAGS) $(CC_TRACE_FLAGS) -c $(DIR_SRC)e65.cpp -o $(DIR_BUILD)base_e65.o

base_exception.o: $(DIR_SRC)exception.cpp $(DIR_INCLUDE)exception.h
	$(CC) $(CC_FLAGS) $(CC_BUILD_FLAGS) $(CC_TRACE_FLAGS) -c $(DIR_SRC)exception.cpp -o $(DIR_BUILD)base_exception.o

base_runtime.o: $(DIR_SRC)runtime.cpp $(DIR_INCLUDE)runtime.h
	$(CC) $(CC_FLAGS) $(CC_BUILD_FLAGS) $(CC_TRACE_FLAGS) -c $(DIR_SRC)runtime.cpp -o $(DIR_BUILD)base_runtime.o

base_trace.o: $(DIR_SRC)trace.cpp $(DIR_INCLUDE)trace.h
	$(CC) $(CC_FLAGS) $(CC_BUILD_FLAGS) $(CC_TRACE_FLAGS) -c $(DIR_SRC)trace.cpp -o $(DIR_BUILD)base_trace.o

### SYSTEM ###

build_system: system_bus.o system_display.o system_input.o system_memory.o system_processor.o system_video.o

system_bus.o: $(DIR_SRC_SYSTEM)bus.cpp $(DIR_INCLUDE_SYSTEM)bus.h
	$(CC) $(CC_FLAGS) $(CC_BUILD_FLAGS) $(CC_TRACE_FLAGS) -c $(DIR_SRC_SYSTEM)bus.cpp -o $(DIR_BUILD)system_bus.o

system_display.o: $(DIR_SRC_SYSTEM)display.cpp $(DIR_INCLUDE_SYSTEM)display.h
	$(CC) $(CC_FLAGS) $(CC_BUILD_FLAGS) $(CC_TRACE_FLAGS) -c $(DIR_SRC_SYSTEM)display.cpp -o $(DIR_BUILD)system_display.o

system_input.o: $(DIR_SRC_SYSTEM)input.cpp $(DIR_INCLUDE_SYSTEM)input.h
	$(CC) $(CC_FLAGS) $(CC_BUILD_FLAGS) $(CC_TRACE_FLAGS) -c $(DIR_SRC_SYSTEM)input.cpp -o $(DIR_BUILD)system_input.o

system_memory.o: $(DIR_SRC_SYSTEM)memory.cpp $(DIR_INCLUDE_SYSTEM)memory.h
	$(CC) $(CC_FLAGS) $(CC_BUILD_FLAGS) $(CC_TRACE_FLAGS) -c $(DIR_SRC_SYSTEM)memory.cpp -o $(DIR_BUILD)system_memory.o

system_processor.o: $(DIR_SRC_SYSTEM)processor.cpp $(DIR_INCLUDE_SYSTEM)processor.h
	$(CC) $(CC_FLAGS) $(CC_BUILD_FLAGS) $(CC_TRACE_FLAGS) -c $(DIR_SRC_SYSTEM)processor.cpp -o $(DIR_BUILD)system_processor.o

system_video.o: $(DIR_SRC_SYSTEM)video.cpp $(DIR_INCLUDE_SYSTEM)video.h
	$(CC) $(CC_FLAGS) $(CC_BUILD_FLAGS) $(CC_TRACE_FLAGS) -c $(DIR_SRC_SYSTEM)video.cpp -o $(DIR_BUILD)system_video.o

### TYPE ###

build_type: type_signal.o type_thread.o

type_signal.o: $(DIR_SRC_TYPE)signal.cpp $(DIR_INCLUDE_TYPE)signal.h
	$(CC) $(CC_FLAGS) $(CC_BUILD_FLAGS) $(CC_TRACE_FLAGS) -c $(DIR_SRC_TYPE)signal.cpp -o $(DIR_BUILD)type_signal.o

type_thread.o: $(DIR_SRC_TYPE)thread.cpp $(DIR_INCLUDE_TYPE)thread.h
	$(CC) $(CC_FLAGS) $(CC_BUILD_FLAGS) $(CC_TRACE_FLAGS) -c $(DIR_SRC_TYPE)thread.cpp -o $(DIR_BUILD)type_thread.o
