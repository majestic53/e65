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

#ifndef E65_TEST_TYPE_H_
#define E65_TEST_TYPE_H_

#include <map>
#include "../../include/define.h"

enum {
	E65_TEST_EXCEPTION_FLAG_INVALID = 0,
	E65_TEST_EXCEPTION_FLAG_UNSUPPORTED,
	E65_TEST_EXCEPTION_TYPE_INVALID,
};

#define E65_TEST_EXCEPTION_MAX E65_TEST_EXCEPTION_TYPE_INVALID

static const std::string E65_TEST_EXCEPTION_STR[] = {
	"Invalid flag",
	"Unsupported flag",
	"Invalid type",
	};

#define E65_TEST_EXCEPTION_STRING(_TYPE_) \
	(((_TYPE_) > E65_TEST_EXCEPTION_MAX) ? E65_EXCEPTION_UNKNOWN : \
		E65_STRING_CHECK(E65_TEST_EXCEPTION_STR[_TYPE_]))

#define E65_TEST "E65-TEST"

#define E65_TEST_ARGUMENT_COUNT_MIN 0

#define E65_TEST_COLUMN_WIDTH 38

#define E65_TEST_FLAG_DELIMITER "-"
#define E65_TEST_FLAG_PREFIX "e65_test"

enum {
	E65_TEST_FLAG_HELP = 0,
	E65_TEST_FLAG_VERSION,
};

#define E65_TEST_FLAG_MAX E65_TEST_FLAG_VERSION

#define E65_TEST_NOTICE "Copyright (C) 2018 David Jolly"

#define E65_TEST_USAGE_COLUMN_WIDTH 24

static const std::string E65_TEST_FLAG_DESC[] = {
	"Display help information",
	"Display version information",
	};

#define E65_TEST_FLAG_DESCRIPTION(_TYPE_) \
	(((_TYPE_) > E65_TEST_FLAG_MAX) ? E65_STRING_UNKNOWN : \
		E65_STRING_CHECK(E65_TEST_FLAG_DESC[_TYPE_]))

static const std::string E65_TEST_FLAG_LONG_STR[] = {
	E65_TEST_FLAG_DELIMITER E65_TEST_FLAG_DELIMITER "help",
	E65_TEST_FLAG_DELIMITER E65_TEST_FLAG_DELIMITER "version",
	};

#define E65_TEST_FLAG_LONG_STRING(_TYPE_) \
	(((_TYPE_) > E65_TEST_FLAG_MAX) ? E65_STRING_UNKNOWN : \
		E65_STRING_CHECK(E65_TEST_FLAG_LONG_STR[_TYPE_]))

static const std::string E65_TEST_FLAG_SHORT_STR[] = {
	E65_TEST_FLAG_DELIMITER "h",
	E65_TEST_FLAG_DELIMITER "v",
	};

#define E65_TEST_FLAG_SHORT_STRING(_TYPE_) \
	(((_TYPE_) > E65_TEST_FLAG_MAX) ? E65_STRING_UNKNOWN : \
		E65_STRING_CHECK(E65_TEST_FLAG_SHORT_STR[_TYPE_]))

static std::map<std::string, int> E65_TEST_FLAG_MAP = {
	std::make_pair(E65_TEST_FLAG_LONG_STRING(E65_TEST_FLAG_HELP), E65_TEST_FLAG_HELP),
	std::make_pair(E65_TEST_FLAG_SHORT_STRING(E65_TEST_FLAG_HELP), E65_TEST_FLAG_HELP),
	std::make_pair(E65_TEST_FLAG_LONG_STRING(E65_TEST_FLAG_VERSION), E65_TEST_FLAG_VERSION),
	std::make_pair(E65_TEST_FLAG_SHORT_STRING(E65_TEST_FLAG_VERSION), E65_TEST_FLAG_VERSION),
	};

#endif // E65_TEST_TYPE_H_
