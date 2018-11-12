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
CC_FLAGS=-march=native -std=gnu++11 -Wall -Werror
CC_FLAGS_EXT=-pthread -lreadline -lSDL2 -lSDL2main
DIR_BIN=./../bin/
DIR_BIN_LIB=./../bin/lib/
DIR_BUILD=./../build/
DIR_TOOL=./
EXE=e65
LIB=libe65.a

all: exe

### EXECUTABLE ###

exe:
	@echo ''
	@echo '--- BUILDING EXECUTABLE --------------------'
	$(CC) $(CC_FLAGS) $(CC_FLAGS_EXT) $(CC_BUILD_FLAGS) $(CC_TRACE_FLAGS) $(DIR_TOOL)$(EXE).cpp $(DIR_BIN_LIB)$(LIB) -o $(DIR_BIN)$(EXE)
	@echo '--- DONE -----------------------------------'
	@echo ''
