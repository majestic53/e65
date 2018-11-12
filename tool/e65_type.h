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

#define E65_FLAG_DELIMITER "-"
#define E65_FLAG_POSTFIX "input"
#define E65_FLAG_PREFIX "e65"

#define E65_NOTICE "Copyright (C) 2018 David Jolly"

#define E65_PROMPT "> "

#define E65_USAGE_COLUMN_WIDTH 16

enum {
	E65_COMMAND_CYCLE = 0,
	E65_COMMAND_EXIT,
	E65_COMMAND_FRAME,
	E65_COMMAND_HELP,
	E65_COMMAND_IRQ,
	E65_COMMAND_NMI,
	E65_COMMAND_STEP,
	E65_COMMAND_VERSION,
};

#define E65_COMMAND_MAX E65_COMMAND_VERSION

static const std::string E65_COMMAND_DESC[] = {
	"Display processor cycle",
	"Exit debug mode",
	"Display video frame",
	"Display help information",
	"Signal processor with IRQ",
	"Signal processor with NMI",
	"Step processor through a single cycle",
	"Display version information",
	};

#define E65_COMMAND_DESCRIPTION(_TYPE_) \
	(((_TYPE_) > E65_COMMAND_MAX) ? E65_STRING_UNKNOWN : \
		E65_STRING_CHECK(E65_COMMAND_DESC[_TYPE_]))

static const std::string E65_COMMAND_LONG_STR[] = {
	"cycle",
	"exit",
	"frame",
	"help",
	"irq",
	"nmi",
	"step",
	"version",
	};

#define E65_COMMAND_LONG_STRING(_TYPE_) \
	(((_TYPE_) > E65_COMMAND_MAX) ? E65_STRING_UNKNOWN : \
		E65_STRING_CHECK(E65_COMMAND_LONG_STR[_TYPE_]))

static const std::string E65_COMMAND_SHORT_STR[] = {
	"c",
	"q",
	"f",
	"h",
	"i",
	"n",
	"s",
	"v",
	};

#define E65_COMMAND_SHORT_STRING(_TYPE_) \
	(((_TYPE_) > E65_COMMAND_MAX) ? E65_STRING_UNKNOWN : \
		E65_STRING_CHECK(E65_COMMAND_SHORT_STR[_TYPE_]))

std::map<std::string, int> E65_COMMAND_MAP = {
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_CYCLE), E65_COMMAND_CYCLE),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_CYCLE), E65_COMMAND_CYCLE),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_EXIT), E65_COMMAND_EXIT),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_EXIT), E65_COMMAND_EXIT),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_FRAME), E65_COMMAND_FRAME),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_FRAME), E65_COMMAND_FRAME),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_HELP), E65_COMMAND_HELP),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_HELP), E65_COMMAND_HELP),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_IRQ), E65_COMMAND_IRQ),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_IRQ), E65_COMMAND_IRQ),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_NMI), E65_COMMAND_NMI),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_NMI), E65_COMMAND_NMI),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_STEP), E65_COMMAND_STEP),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_STEP), E65_COMMAND_STEP),
	std::make_pair(E65_COMMAND_LONG_STRING(E65_COMMAND_VERSION), E65_COMMAND_VERSION),
	std::make_pair(E65_COMMAND_SHORT_STRING(E65_COMMAND_VERSION), E65_COMMAND_VERSION),
	};

#define E65_IS_COMMAND(_STRING_) \
	(E65_COMMAND_MAP.find(_STRING_) != E65_COMMAND_MAP.end())

#define E65_COMMAND_ID(_STRING_) \
	E65_COMMAND_MAP.find(_STRING_)->second

std::map<int, size_t> E65_COMMAND_LENGTH_MAP = {
	std::make_pair(E65_COMMAND_CYCLE, 0),
	std::make_pair(E65_COMMAND_EXIT, 0),
	std::make_pair(E65_COMMAND_FRAME, 0),
	std::make_pair(E65_COMMAND_HELP, 0),
	std::make_pair(E65_COMMAND_IRQ, 0),
	std::make_pair(E65_COMMAND_NMI, 0),
	std::make_pair(E65_COMMAND_STEP, 0),
	std::make_pair(E65_COMMAND_VERSION, 0),
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
