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

BUILD_FLAGS_DBG=CC_BUILD_FLAGS=-g
BUILD_FLAGS_REL=CC_BUILD_FLAGS=-O3\ -DNDEBUG
DIR_BUILD=../build/test/
DIR_ROOT=./
DIR_SRC=./src/
DIR_TOOL=./tool/
JOB_SLOTS=4
TOOL=e65_test
TRACE?=0
TRACE_FLAGS_DBG=CC_TRACE_FLAGS=-DTRACE_COLOR\ -DTRACE=
TRACE_FLAGS_REL=CC_TRACE_FLAGS=-DTRACE_COLOR\ -DTRACE=0

all: debug

debug: clean init lib_debug exe_debug

release: clean init lib_release exe_release

### SETUP ###

clean:
	rm -rf $(DIR_BUILD)

init:
	mkdir -p $(DIR_BUILD)

### LIBRARY ###

lib_debug:
	@echo ''
	@echo '============================================'
	@echo 'BUILDING TEST LIBRARIES (DEBUG)'
	@echo '============================================'
	cd $(DIR_SRC) && make $(BUILD_FLAGS_DBG) $(TRACE_FLAGS_DBG)$(TRACE) build -j $(JOB_SLOTS)
	cd $(DIR_SRC) && make archive

lib_release:
	@echo ''
	@echo '============================================'
	@echo 'BUILDING TEST LIBRARIES (RELEASE)'
	@echo '============================================'
	cd $(DIR_SRC) && make $(BUILD_FLAGS_REL) $(TRACE_FLAGS_REL) build -j $(JOB_SLOTS)
	cd $(DIR_SRC) && make archive

### EXECUTABLE ###

exe_debug:
	@echo ''
	@echo '============================================'
	@echo 'BUILDING TEST EXECUTABLES (DEBUG)'
	@echo '============================================'
	cd $(DIR_TOOL) && make $(BUILD_FLAGS_DBG) $(TRACE_FLAGS_DBG)$(TRACE)

exe_release:
	@echo ''
	@echo '============================================'
	@echo 'BUILDING TEST EXECUTABLES (RELEASE)'
	@echo '============================================'
	cd $(DIR_TOOL) && make $(BUILD_FLAGS_REL) $(TRACE_FLAGS_REL)

### MISC ###

lines:
	@echo ''
	@echo '============================================'
	@echo 'CALCULATING LINE COUNT'
	@echo '============================================'
	cloc $(DIR_ROOT)

memory:
	@echo ''
	@echo '============================================'
	@echo 'RUNNING MEMORY TEST'
	@echo '============================================'
	valgrind --leak-check=full --show-leak-kinds=all $(DIR_BUILD)$(TOOL)

static:
	@echo ''
	@echo '============================================'
	@echo 'RUNNING STATIC ANALYSIS'
	@echo '============================================'
	cppcheck --enable=all --std=c++11 $(DIR_SRC)
