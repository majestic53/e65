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

#ifndef E65_SYSTEM_BUS_TYPE_H_
#define E65_SYSTEM_BUS_TYPE_H_

#include "../../include/exception.h"

namespace e65 {

	namespace system {

		#define E65_SYSTEM_BUS_HEADER "[E65::SYSTEM::BUS]"
#ifndef NDEBUG
		#define E65_SYSTEM_BUS_EXCEPTION_HEADER E65_SYSTEM_BUS_HEADER " "
#else
		#define E65_SYSTEM_BUS_EXCEPTION_HEADER
#endif // NDEBUG

		enum {
			E65_SYSTEM_BUS_EXCEPTION_CHECKSUM = 0,
			E65_SYSTEM_BUS_EXCEPTION_EMPTY,
			E65_SYSTEM_BUS_EXCEPTION_END,
			E65_SYSTEM_BUS_EXCEPTION_LENGTH,
			E65_SYSTEM_BUS_EXCEPTION_START,
			E65_SYSTEM_BUS_EXCEPTION_UNINITIALIZED,
			E65_SYSTEM_BUS_EXCEPTION_UNSUPPORTED,
		};

		#define E65_SYSTEM_BUS_EXCEPTION_MAX E65_SYSTEM_BUS_EXCEPTION_UNSUPPORTED

		static const std::string E65_SYSTEM_BUS_EXCEPTION_STR[] = {
			E65_SYSTEM_BUS_EXCEPTION_HEADER "Data checksum mismatch",
			E65_SYSTEM_BUS_EXCEPTION_HEADER "Empty data",
			E65_SYSTEM_BUS_EXCEPTION_HEADER "Expecting end of file",
			E65_SYSTEM_BUS_EXCEPTION_HEADER "Invalid data length",
			E65_SYSTEM_BUS_EXCEPTION_HEADER "Expecting start of line",
			E65_SYSTEM_BUS_EXCEPTION_HEADER "Bus uninitialized",
			E65_SYSTEM_BUS_EXCEPTION_HEADER "Unsupported data type",
			};

		#define E65_SYSTEM_BUS_EXCEPTION_STRING(_TYPE_) \
			(((_TYPE_) > E65_SYSTEM_BUS_EXCEPTION_MAX) ? E65_EXCEPTION_UNKNOWN : \
				E65_STRING_CHECK(E65_SYSTEM_BUS_EXCEPTION_STR[_TYPE_]))

		#define THROW_E65_SYSTEM_BUS_EXCEPTION(_EXCEPT_) \
			THROW_E65_SYSTEM_BUS_EXCEPTION_FORMAT(_EXCEPT_, "", "")
		#define THROW_E65_SYSTEM_BUS_EXCEPTION_FORMAT(_EXCEPT_, _FORMAT_, ...) \
			E65_EXCEPTION_THROW_FORMAT(E65_SYSTEM_BUS_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)

		enum {
			E65_HEX_DATA = 0,
			E65_HEX_END,
		};

		#define E65_HEX_ADDRESS_OFFSET 4
		#define E65_HEX_ADDRESS_ORIGIN 3

		#define E65_HEX_CHARACTER_START ':'

		#define E65_HEX_DATA_OFFSET 2
		#define E65_HEX_DATA_ORIGIN 9

		#define E65_HEX_LENGTH_MIN 11

		#define E65_HEX_LENGTH_OFFSET 2
		#define E65_HEX_LENGTH_ORIGIN 1

		#define E65_HEX_TYPE_OFFSET 2
		#define E65_HEX_TYPE_ORIGIN 7
	}
}

#endif // E65_SYSTEM_BUS_TYPE_H_
