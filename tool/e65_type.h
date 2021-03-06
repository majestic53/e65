/**
 * E65
 * Copyright (C) 2018 David Jolly
 *
 * E65 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * E65 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef E65_TYPE_H_
#define E65_TYPE_H_

#include <map>
#include "../include/e65.h"
#include "../include/runtime.h"

enum {
	E65_EXCEPTION_COMMAND_ARGUMENT = 0,
	E65_EXCEPTION_COMMAND_ERROR,
	E65_EXCEPTION_COMMAND_RESPONSE,
	E65_EXCEPTION_COMAMND_UNSUPPORTED,
	E65_EXCEPTION_FLAG_INVALID,
	E65_EXCEPTION_FLAG_UNSUPPORTED,
	E65_EXCEPTION_PATH_REDEFINED,
	E65_EXCEPTION_PATH_UNDEFINED,
};

#define E65_EXCEPTION_MAX E65_EXCEPTION_PATH_UNDEFINED

static const std::string E65_EXCEPTION_STR[] = {
	"Undefined command argument",
	"Command failed",
	"Malformed command response",
	"Unsupported command",
	"Invalid flag",
	"Unsupported flag",
	"Path redefined",
	"Undefined path",
	};

#define E65_EXCEPTION_STRING(_TYPE_) \
	(((_TYPE_) > E65_EXCEPTION_MAX) ? E65_EXCEPTION_UNKNOWN : \
		E65_STRING_CHECK(E65_EXCEPTION_STR[_TYPE_]))

enum {
	E65_FLAG_DEBUG = 0,
	E65_FLAG_HELP,
	E65_FLAG_HEX,
	E65_FLAG_VERSION,
};

#define E65_FLAG_MAX E65_FLAG_VERSION

#define E65_ARGUMENT_COUNT_MIN 2

#define E65_ARGUMENT_WILDCARD "*"

#define E65_FLAG_DELIMITER "-"
#define E65_FLAG_POSTFIX "input"
#define E65_FLAG_PREFIX "e65"

#define E65_NOTICE "Copyright (C) 2018 David Jolly"

#define E65_PROMPT " $ "

#define E65_USAGE_COLUMN_LONG_WIDTH 38
#define E65_USAGE_COLUMN_SHORT_WIDTH 24

enum {

	// breakpoint
	E65_COMMAND_BREAKPOINT_CLEAR = 0,
	E65_COMMAND_BREAKPOINT_LIST,
	E65_COMMAND_BREAKPOINT_SET,

	// memory
	E65_COMMAND_MEMORY_DUMP,
	E65_COMMAND_MEMORY_READ,
	E65_COMMAND_MEMORY_READ_WORD,
	E65_COMMAND_MEMORY_WRITE,
	E65_COMMAND_MEMORY_WRITE_WORD,

	// processor
	E65_COMMAND_PROCESSOR_ACCUMULATOR,
	E65_COMMAND_PROCESSOR_ACCUMULATOR_SET,
	E65_COMMAND_PROCESSOR_BREAK,
	E65_COMMAND_PROCESSOR_CORE,
	E65_COMMAND_PROCESSOR_CYCLE,
	E65_COMMAND_PROCESSOR_DISASSEMBLE,
	E65_COMMAND_PROCESSOR_FLAGS,
	E65_COMMAND_PROCESSOR_FLAGS_SET,
	E65_COMMAND_PROCESSOR_INDEX_X,
	E65_COMMAND_PROCESSOR_INDEX_X_SET,
	E65_COMMAND_PROCESSOR_INDEX_Y,
	E65_COMMAND_PROCESSOR_INDEX_Y_SET,
	E65_COMMAND_PROCESSOR_IRQ,
	E65_COMMAND_PROCESSOR_NMI,
	E65_COMMAND_PROCESSOR_PROGRAM_COUNTER,
	E65_COMMAND_PROCESSOR_PROGRAM_COUNTER_SET,
	E65_COMMAND_PROCESSOR_RESET,
	E65_COMMAND_PROCESSOR_RUN,
	E65_COMMAND_PROCESSOR_STACK_POINTER,
	E65_COMMAND_PROCESSOR_STACK_POINTER_SET,
	E65_COMMAND_PROCESSOR_STEP,
	E65_COMMAND_PROCESSOR_STEP_FRAME,
	E65_COMMAND_PROCESSOR_STOP,
	E65_COMMAND_PROCESSOR_STOP_CLEAR,
	E65_COMMAND_PROCESSOR_WAIT,
	E65_COMMAND_PROCESSOR_WAIT_CLEAR,

	// video
	E65_COMMAND_VIDEO_FRAME,
	E65_COMMAND_VIDEO_FRAME_CYCLE,
	E65_COMMAND_VIDEO_FREQUENCY,
	E65_COMMAND_VIDEO_FULLSCREEN,
	E65_COMMAND_VIDEO_HIDE,
	E65_COMMAND_VIDEO_PIXEL,
	E65_COMMAND_VIDEO_PIXEL_SET,

	// built-in
	E65_COMMAND_HELP,
	E65_COMMAND_VERSION,
	E65_COMMAND_EXIT,
};

#define E65_COMMAND_BUILT_IN E65_COMMAND_HELP
#define E65_COMMAND_BREAKPOINT E65_COMMAND_BREAKPOINT_CLEAR
#define E65_COMMAND_MEMORY E65_COMMAND_MEMORY_DUMP
#define E65_COMMAND_PROCESSOR E65_COMMAND_PROCESSOR_ACCUMULATOR
#define E65_COMMAND_VIDEO E65_COMMAND_VIDEO_FRAME

#define E65_COMMAND_MAX E65_COMMAND_EXIT

static const std::string E65_COMMAND_ARG[] = {

	// breakpoint
	"<address|*>",
	"",
	"<address>",

	// memory
	"<address> <offset>",
	"<address>",
	"<address>",
	"<address> <value>",
	"<address> <value>",

	// processor
	"",
	"<value>",
	"",
	"",
	"",
	"<address> <offset>",
	"",
	"<value>",
	"",
	"<value>",
	"",
	"<value>",
	"",
	"",
	"",
	"<value>",
	"",
	"",
	"",
	"<value>",
	"<offset>",
	"<offset>",
	"",
	"",
	"",
	"",

	// video
	"",
	"",
	"",
	"<value>",
	"<value>",
	"<x> <y>",
	"<x> <y> <color>",

	// built-in
	"",
	"",
	"",
	};

#define E65_COMMAND_ARGUMENTS(_TYPE_) \
	(((_TYPE_) > E65_COMMAND_MAX) ? E65_STRING_UNKNOWN : \
		E65_STRING_CHECK(E65_COMMAND_ARG[_TYPE_]))

static const std::string E65_COMMAND_DESC[] = {

	// breakpoint
	"Clear breakpoint at a given address",
	"List all breakpoints",
	"Set breakpoint at a given address",

	// memory
	"Dump memory at an address for a given offset",
	"Read byte from a given memory address",
	"Read word from a given memory address",
	"Write byte to a given memory address",
	"Write word to a given memory address",

	// processor
	"Display processor accumulator",
	"Set processor accumulator to given value",
	"Break processor",
	"Display processor core",
	"Display current processor cycle",
	"Disassemble instructions at a given address and offset",
	"Display processor flags",
	"Set processor flags to given value",
	"Display processor index-x",
	"Set processor index-x to given value",
	"Display processor index-y",
	"Set processor index-y to given value",
	"Signal processor with a maskable interrupt",
	"Signal processor with a non-maskable interrupt",
	"Display processor program counter",
	"Set processor program counter to given value",
	"Reset processor",
	"Run processor",
	"Display processor stack pointer",
	"Set processor stack pointer to given value",
	"Step processor through a given number of steps",
	"Step processor through a given number of frames",
	"Set processor stop flag",
	"Clear processor stop flag",
	"Set processor wait flag",
	"Clear processor wait flag",

	// video
	"Display current video frame",
	"Display video frame cycle count",
	"Display video frequency (Hz)",
	"Fullscreen display window",
	"Hide display window",
	"Retrieve display pixel at a given coordinate",
	"Set display pixel at a given coordinate",

	// built-in
	"Display help information",
	"Display version information",
	"Exit debug mode",
	};

#define E65_COMMAND_DESCRIPTION(_TYPE_) \
	(((_TYPE_) > E65_COMMAND_MAX) ? E65_STRING_UNKNOWN : \
		E65_STRING_CHECK(E65_COMMAND_DESC[_TYPE_]))

static const std::string E65_COMMAND_LONG_STR[] = {

	// breakpoint
	"clear",
	"list",
	"set",

	// memory
	"dump",
	"read",
	"read-word",
	"write",
	"write-word",

	// processor
	"accumulator",
	"accumulator-set",
	"break",
	"core",
	"cycle",
	"disassemble",
	"flags",
	"flags-set",
	"index-x",
	"index-x-set",
	"index-y",
	"index-y-set",
	"irq",
	"nmi",
	"program-counter",
	"program-counter-set",
	"reset",
	"run",
	"stack-pointer",
	"stack-pointer-set",
	"step",
	"step-frame",
	"stop",
	"stop-clear",
	"wait",
	"wait-clear",

	// video
	"frame",
	"frame-cycle",
	"frequency",
	"fullscreen",
	"hide",
	"pixel",
	"pixel-set",

	// built-in
	"help",
	"version",
	"exit",
	};

#define E65_COMMAND_LONG_STRING(_TYPE_) \
	(((_TYPE_) > E65_COMMAND_MAX) ? E65_STRING_UNKNOWN : \
		E65_STRING_CHECK(E65_COMMAND_LONG_STR[_TYPE_]))

static const std::string E65_COMMAND_SHORT_STR[] = {

	// breakpoint
	"bc",
	"bl",
	"bp",

	// memory
	"d",
	"r",
	"rw",
	"w",
	"ww",

	// processor
	"a",
	"as",
	"b",
	"c",
	"cy",
	"dasm",
	"flg",
	"flgs",
	"x",
	"xs",
	"y",
	"ys",
	"i",
	"n",
	"pc",
	"pcs",
	"rst",
	"g",
	"sp",
	"sps",
	"s",
	"sf",
	"ss",
	"sc",
	"ws",
	"wc",

	// video
	"f",
	"fc",
	"frq",
	"fs",
	"h",
	"p",
	"ps",

	// built-in
	"?",
	"v",
	"q",
	};

#define E65_COMMAND_SHORT_STRING(_TYPE_) \
	(((_TYPE_) > E65_COMMAND_MAX) ? E65_STRING_UNKNOWN : \
		E65_STRING_CHECK(E65_COMMAND_SHORT_STR[_TYPE_]))

std::map<std::string, int> E65_COMMAND_MAP = {

	// breakpoint
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_BREAKPOINT_CLEAR), E65_COMMAND_BREAKPOINT_CLEAR),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_BREAKPOINT_CLEAR), E65_COMMAND_BREAKPOINT_CLEAR),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_BREAKPOINT_LIST), E65_COMMAND_BREAKPOINT_LIST),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_BREAKPOINT_LIST), E65_COMMAND_BREAKPOINT_LIST),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_BREAKPOINT_SET), E65_COMMAND_BREAKPOINT_SET),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_BREAKPOINT_SET), E65_COMMAND_BREAKPOINT_SET),

	// memory
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_MEMORY_DUMP), E65_COMMAND_MEMORY_DUMP),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_MEMORY_DUMP), E65_COMMAND_MEMORY_DUMP),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_MEMORY_READ), E65_COMMAND_MEMORY_READ),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_MEMORY_READ), E65_COMMAND_MEMORY_READ),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_MEMORY_READ_WORD), E65_COMMAND_MEMORY_READ_WORD),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_MEMORY_READ_WORD), E65_COMMAND_MEMORY_READ_WORD),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_MEMORY_WRITE), E65_COMMAND_MEMORY_WRITE),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_MEMORY_WRITE), E65_COMMAND_MEMORY_WRITE),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_MEMORY_WRITE_WORD), E65_COMMAND_MEMORY_WRITE_WORD),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_MEMORY_WRITE_WORD), E65_COMMAND_MEMORY_WRITE_WORD),

	// processor
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_PROCESSOR_ACCUMULATOR), E65_COMMAND_PROCESSOR_ACCUMULATOR),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_PROCESSOR_ACCUMULATOR), E65_COMMAND_PROCESSOR_ACCUMULATOR),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_PROCESSOR_ACCUMULATOR_SET), E65_COMMAND_PROCESSOR_ACCUMULATOR_SET),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_PROCESSOR_ACCUMULATOR_SET), E65_COMMAND_PROCESSOR_ACCUMULATOR_SET),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_PROCESSOR_BREAK), E65_COMMAND_PROCESSOR_BREAK),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_PROCESSOR_BREAK), E65_COMMAND_PROCESSOR_BREAK),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_PROCESSOR_CORE), E65_COMMAND_PROCESSOR_CORE),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_PROCESSOR_CORE), E65_COMMAND_PROCESSOR_CORE),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_PROCESSOR_CYCLE), E65_COMMAND_PROCESSOR_CYCLE),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_PROCESSOR_CYCLE), E65_COMMAND_PROCESSOR_CYCLE),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_PROCESSOR_DISASSEMBLE), E65_COMMAND_PROCESSOR_DISASSEMBLE),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_PROCESSOR_DISASSEMBLE), E65_COMMAND_PROCESSOR_DISASSEMBLE),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_PROCESSOR_FLAGS), E65_COMMAND_PROCESSOR_FLAGS),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_PROCESSOR_FLAGS), E65_COMMAND_PROCESSOR_FLAGS),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_PROCESSOR_FLAGS_SET), E65_COMMAND_PROCESSOR_FLAGS_SET),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_PROCESSOR_FLAGS_SET), E65_COMMAND_PROCESSOR_FLAGS_SET),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_PROCESSOR_INDEX_X), E65_COMMAND_PROCESSOR_INDEX_X),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_PROCESSOR_INDEX_X), E65_COMMAND_PROCESSOR_INDEX_X),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_PROCESSOR_INDEX_X_SET), E65_COMMAND_PROCESSOR_INDEX_X_SET),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_PROCESSOR_INDEX_X_SET), E65_COMMAND_PROCESSOR_INDEX_X_SET),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_PROCESSOR_INDEX_Y), E65_COMMAND_PROCESSOR_INDEX_Y),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_PROCESSOR_INDEX_Y), E65_COMMAND_PROCESSOR_INDEX_Y),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_PROCESSOR_INDEX_Y_SET), E65_COMMAND_PROCESSOR_INDEX_Y_SET),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_PROCESSOR_INDEX_Y_SET), E65_COMMAND_PROCESSOR_INDEX_Y_SET),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_PROCESSOR_IRQ), E65_COMMAND_PROCESSOR_IRQ),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_PROCESSOR_IRQ), E65_COMMAND_PROCESSOR_IRQ),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_PROCESSOR_NMI), E65_COMMAND_PROCESSOR_NMI),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_PROCESSOR_NMI), E65_COMMAND_PROCESSOR_NMI),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_PROCESSOR_PROGRAM_COUNTER), E65_COMMAND_PROCESSOR_PROGRAM_COUNTER),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_PROCESSOR_PROGRAM_COUNTER), E65_COMMAND_PROCESSOR_PROGRAM_COUNTER),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_PROCESSOR_PROGRAM_COUNTER_SET), E65_COMMAND_PROCESSOR_PROGRAM_COUNTER_SET),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_PROCESSOR_PROGRAM_COUNTER_SET), E65_COMMAND_PROCESSOR_PROGRAM_COUNTER_SET),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_PROCESSOR_RESET), E65_COMMAND_PROCESSOR_RESET),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_PROCESSOR_RESET), E65_COMMAND_PROCESSOR_RESET),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_PROCESSOR_RUN), E65_COMMAND_PROCESSOR_RUN),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_PROCESSOR_RUN), E65_COMMAND_PROCESSOR_RUN),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_PROCESSOR_STACK_POINTER), E65_COMMAND_PROCESSOR_STACK_POINTER),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_PROCESSOR_STACK_POINTER), E65_COMMAND_PROCESSOR_STACK_POINTER),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_PROCESSOR_STACK_POINTER_SET), E65_COMMAND_PROCESSOR_STACK_POINTER_SET),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_PROCESSOR_STACK_POINTER_SET), E65_COMMAND_PROCESSOR_STACK_POINTER_SET),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_PROCESSOR_STEP), E65_COMMAND_PROCESSOR_STEP),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_PROCESSOR_STEP), E65_COMMAND_PROCESSOR_STEP),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_PROCESSOR_STEP_FRAME), E65_COMMAND_PROCESSOR_STEP_FRAME),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_PROCESSOR_STEP_FRAME), E65_COMMAND_PROCESSOR_STEP_FRAME),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_PROCESSOR_STOP), E65_COMMAND_PROCESSOR_STOP),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_PROCESSOR_STOP), E65_COMMAND_PROCESSOR_STOP),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_PROCESSOR_STOP_CLEAR), E65_COMMAND_PROCESSOR_STOP_CLEAR),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_PROCESSOR_STOP_CLEAR), E65_COMMAND_PROCESSOR_STOP_CLEAR),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_PROCESSOR_WAIT), E65_COMMAND_PROCESSOR_WAIT),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_PROCESSOR_WAIT), E65_COMMAND_PROCESSOR_WAIT),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_PROCESSOR_WAIT_CLEAR), E65_COMMAND_PROCESSOR_WAIT_CLEAR),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_PROCESSOR_WAIT_CLEAR), E65_COMMAND_PROCESSOR_WAIT_CLEAR),

	// video
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_VIDEO_FRAME), E65_COMMAND_VIDEO_FRAME),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_VIDEO_FRAME), E65_COMMAND_VIDEO_FRAME),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_VIDEO_FRAME_CYCLE), E65_COMMAND_VIDEO_FRAME_CYCLE),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_VIDEO_FRAME_CYCLE), E65_COMMAND_VIDEO_FRAME_CYCLE),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_VIDEO_FREQUENCY), E65_COMMAND_VIDEO_FREQUENCY),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_VIDEO_FREQUENCY), E65_COMMAND_VIDEO_FREQUENCY),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_VIDEO_FULLSCREEN), E65_COMMAND_VIDEO_FULLSCREEN),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_VIDEO_FULLSCREEN), E65_COMMAND_VIDEO_FULLSCREEN),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_VIDEO_HIDE), E65_COMMAND_VIDEO_HIDE),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_VIDEO_HIDE), E65_COMMAND_VIDEO_HIDE),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_VIDEO_PIXEL), E65_COMMAND_VIDEO_PIXEL),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_VIDEO_PIXEL), E65_COMMAND_VIDEO_PIXEL),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_VIDEO_PIXEL_SET), E65_COMMAND_VIDEO_PIXEL_SET),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_VIDEO_PIXEL_SET), E65_COMMAND_VIDEO_PIXEL_SET),

	// built-in
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_HELP), E65_COMMAND_HELP),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_HELP), E65_COMMAND_HELP),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_VERSION), E65_COMMAND_VERSION),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_VERSION), E65_COMMAND_VERSION),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_EXIT), E65_COMMAND_EXIT),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_EXIT), E65_COMMAND_EXIT),
	};

#define E65_IS_COMMAND(_STRING_) \
	(E65_COMMAND_MAP.find(_STRING_) != E65_COMMAND_MAP.end())

#define E65_COMMAND_ID(_STRING_) \
	E65_COMMAND_MAP.find(_STRING_)->second

std::map<int, size_t> E65_COMMAND_LENGTH_MAP = {

	// breakpoint
	std::make_pair(E65_COMMAND_BREAKPOINT_CLEAR, 1),
	std::make_pair(E65_COMMAND_BREAKPOINT_LIST, 0),
	std::make_pair(E65_COMMAND_BREAKPOINT_SET, 1),

	// memory
	std::make_pair(E65_COMMAND_MEMORY_DUMP, 2),
	std::make_pair(E65_COMMAND_MEMORY_READ, 1),
	std::make_pair(E65_COMMAND_MEMORY_READ_WORD, 1),
	std::make_pair(E65_COMMAND_MEMORY_WRITE, 2),
	std::make_pair(E65_COMMAND_MEMORY_WRITE_WORD, 2),

	// processor
	std::make_pair(E65_COMMAND_PROCESSOR_ACCUMULATOR, 0),
	std::make_pair(E65_COMMAND_PROCESSOR_ACCUMULATOR_SET, 1),
	std::make_pair(E65_COMMAND_PROCESSOR_BREAK, 0),
	std::make_pair(E65_COMMAND_PROCESSOR_CORE, 0),
	std::make_pair(E65_COMMAND_PROCESSOR_CYCLE, 0),
	std::make_pair(E65_COMMAND_PROCESSOR_DISASSEMBLE, 2),
	std::make_pair(E65_COMMAND_PROCESSOR_FLAGS, 0),
	std::make_pair(E65_COMMAND_PROCESSOR_FLAGS_SET, 1),
	std::make_pair(E65_COMMAND_PROCESSOR_INDEX_X, 0),
	std::make_pair(E65_COMMAND_PROCESSOR_INDEX_X_SET, 1),
	std::make_pair(E65_COMMAND_PROCESSOR_INDEX_Y, 0),
	std::make_pair(E65_COMMAND_PROCESSOR_INDEX_Y_SET, 1),
	std::make_pair(E65_COMMAND_PROCESSOR_IRQ, 0),
	std::make_pair(E65_COMMAND_PROCESSOR_NMI, 0),
	std::make_pair(E65_COMMAND_PROCESSOR_PROGRAM_COUNTER, 0),
	std::make_pair(E65_COMMAND_PROCESSOR_PROGRAM_COUNTER_SET, 1),
	std::make_pair(E65_COMMAND_PROCESSOR_RESET, 0),
	std::make_pair(E65_COMMAND_PROCESSOR_RUN, 0),
	std::make_pair(E65_COMMAND_PROCESSOR_STACK_POINTER, 0),
	std::make_pair(E65_COMMAND_PROCESSOR_STACK_POINTER_SET, 1),
	std::make_pair(E65_COMMAND_PROCESSOR_STEP, 1),
	std::make_pair(E65_COMMAND_PROCESSOR_STEP_FRAME, 1),
	std::make_pair(E65_COMMAND_PROCESSOR_STOP, 0),
	std::make_pair(E65_COMMAND_PROCESSOR_STOP_CLEAR, 0),
	std::make_pair(E65_COMMAND_PROCESSOR_WAIT, 0),
	std::make_pair(E65_COMMAND_PROCESSOR_WAIT_CLEAR, 0),

	// video
	std::make_pair(E65_COMMAND_VIDEO_FRAME, 0),
	std::make_pair(E65_COMMAND_VIDEO_FRAME_CYCLE, 0),
	std::make_pair(E65_COMMAND_VIDEO_FREQUENCY, 0),
	std::make_pair(E65_COMMAND_VIDEO_FULLSCREEN, 1),
	std::make_pair(E65_COMMAND_VIDEO_HIDE, 1),
	std::make_pair(E65_COMMAND_VIDEO_PIXEL, 2),
	std::make_pair(E65_COMMAND_VIDEO_PIXEL_SET, 3),

	// built-in
	std::make_pair(E65_COMMAND_HELP, 0),
	std::make_pair(E65_COMMAND_VERSION, 0),
	std::make_pair(E65_COMMAND_EXIT, 0),
	};

#define E65_COMMAND_LENGTH(_TYPE_) \
	E65_COMMAND_LENGTH_MAP.find(_TYPE_)->second

static const std::string E65_FLAG_DESC[] = {
	"Enter debug mode",
	"Display help information",
	"Load ihex file",
	"Display version information",
	};

#define E65_FLAG_DESCRIPTION(_TYPE_) \
	(((_TYPE_) > E65_FLAG_MAX) ? E65_STRING_UNKNOWN : \
		E65_STRING_CHECK(E65_FLAG_DESC[_TYPE_]))

static const std::string E65_FLAG_LONG_STR[] = {
	E65_FLAG_DELIMITER E65_FLAG_DELIMITER "debug",
	E65_FLAG_DELIMITER E65_FLAG_DELIMITER "help",
	E65_FLAG_DELIMITER E65_FLAG_DELIMITER "ihex",
	E65_FLAG_DELIMITER E65_FLAG_DELIMITER "version",
	};

#define E65_FLAG_LONG_STRING(_TYPE_) \
	(((_TYPE_) > E65_FLAG_MAX) ? E65_STRING_UNKNOWN : \
		E65_STRING_CHECK(E65_FLAG_LONG_STR[_TYPE_]))

static const std::string E65_FLAG_SHORT_STR[] = {
	E65_FLAG_DELIMITER "d",
	E65_FLAG_DELIMITER "h",
	E65_FLAG_DELIMITER "i",
	E65_FLAG_DELIMITER "v",
	};

#define E65_FLAG_SHORT_STRING(_TYPE_) \
	(((_TYPE_) > E65_FLAG_MAX) ? E65_STRING_UNKNOWN : \
		E65_STRING_CHECK(E65_FLAG_SHORT_STR[_TYPE_]))

std::map<std::string, int> E65_FLAG_MAP = {
	std::make_pair(E65_FLAG_LONG_STRING(E65_FLAG_DEBUG), E65_FLAG_DEBUG),
	std::make_pair(E65_FLAG_SHORT_STRING(E65_FLAG_DEBUG), E65_FLAG_DEBUG),
	std::make_pair(E65_FLAG_LONG_STRING(E65_FLAG_HELP), E65_FLAG_HELP),
	std::make_pair(E65_FLAG_SHORT_STRING(E65_FLAG_HELP), E65_FLAG_HELP),
	std::make_pair(E65_FLAG_LONG_STRING(E65_FLAG_HEX), E65_FLAG_HEX),
	std::make_pair(E65_FLAG_SHORT_STRING(E65_FLAG_HEX), E65_FLAG_HEX),
	std::make_pair(E65_FLAG_LONG_STRING(E65_FLAG_VERSION), E65_FLAG_VERSION),
	std::make_pair(E65_FLAG_SHORT_STRING(E65_FLAG_VERSION), E65_FLAG_VERSION),
	};

#define E65_IS_FLAG(_STRING_) \
	(E65_FLAG_MAP.find(_STRING_) != E65_FLAG_MAP.end())

#define E65_FLAG_ID(_STRING_) \
	E65_FLAG_MAP.find(_STRING_)->second

#endif // E65_TYPE_H_
