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

#ifndef E65_TRACE_TYPE_H_
#define E65_TRACE_TYPE_H_

#include <tuple>
#include "../include/exception.h"

namespace e65 {

	#define E65_TRACE_HEADER "[E65::TRACE]"
#ifndef NDEBUG
	#define E65_TRACE_EXCEPTION_HEADER E65_TRACE_HEADER " "
#else
	#define E65_TRACE_EXCEPTION_HEADER
#endif // NDEBUG

	enum {
		E65_TRACE_EXCEPTION_EMPTY = 0,
		E65_TRACE_EXCEPTION_MALFORMED,
		E65_TRACE_EXCEPTION_UNINITIALIZED,
	};

	#define E65_TRACE_EXCEPTION_MAX E65_TRACE_EXCEPTION_UNINITIALIZED

	static const std::string E65_TRACE_EXCEPTION_STR[] = {
		E65_TRACE_EXCEPTION_HEADER "Trace queue empty",
		E65_TRACE_EXCEPTION_HEADER "Malformed",
		E65_TRACE_EXCEPTION_HEADER "Trace uninitialized",
		};

	#define E65_TRACE_EXCEPTION_STRING(_TYPE_) \
		(((_TYPE_) > E65_TRACE_EXCEPTION_MAX) ? E65_EXCEPTION_UNKNOWN : \
			E65_STRING_CHECK(E65_TRACE_EXCEPTION_STR[_TYPE_]))

	#define THROW_E65_TRACE_EXCEPTION(_EXCEPT_) \
		THROW_E65_TRACE_EXCEPTION_FORMAT(_EXCEPT_, "", "")
	#define THROW_E65_TRACE_EXCEPTION_FORMAT(_EXCEPT_, _FORMAT_, ...) \
		E65_EXCEPTION_THROW_FORMAT(E65_TRACE_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)

	#define E65_LEVEL_MAX E65_LEVEL_VERBOSE

	static const std::string E65_LEVEL_COL[] = {
		"\x1b[91m", "\x1b[93m", "\x1b[94m", "\x1b[90m",
		};

	#define E65_LEVEL_COLOR(_TYPE_) \
		(((_TYPE_) > E65_LEVEL_MAX) ? E65_LEVEL_COLOR_RESET : \
			E65_STRING_CHECK(E65_LEVEL_COL[_TYPE_]))

	#define E65_LEVEL_COLOR_RESET "\x1b[0m"

	static const std::string E65_LEVEL_STR[] = {
		"Error", "Warning", "Information", "Verbose",
		};

	#define E65_LEVEL_STRING(_TYPE_) \
		(((_TYPE_) > E65_LEVEL_MAX) ? E65_STRING_UNKNOWN : \
			E65_STRING_CHECK(E65_LEVEL_STR[_TYPE_]))

	#define E65_TRACE_QUEUE_MAX 4096

	#define E65_TRACE_TIMESTAMP_FORMAT "%Y-%m-%d %H:%M:%S"
	#define E65_TRACE_TIMESTAMP_LENGTH 32

	enum {
		E65_TRACE_FILE = 0,
		E65_TRACE_FUNCTION,
		E65_TRACE_LEVEL,
		E65_TRACE_LINE,
		E65_TRACE_MESSAGE,
		E65_TRACE_TIMESTAMP,
	};

	#define E65_TRACE_VALUE(_TYPE_, _TUPLE_) \
		std::get<_TYPE_>(_TUPLE_)
}

#endif // E65_TRACE_TYPE_H_
