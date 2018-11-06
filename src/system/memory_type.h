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

#ifndef E65_SYSTEM_MEMORY_TYPE_H_
#define E65_SYSTEM_MEMORY_TYPE_H_

#include "../../include/exception.h"

namespace e65 {

	namespace system {

		#define E65_SYSTEM_MEMORY_HEADER "[E65::SYSTEM::MEMORY]"
#ifndef NDEBUG
		#define E65_SYSTEM_MEMORY_EXCEPTION_HEADER E65_SYSTEM_MEMORY_HEADER " "
#else
		#define E65_SYSTEM_MEMORY_EXCEPTION_HEADER
#endif // NDEBUG

		enum {
			E65_SYSTEM_MEMORY_EXCEPTION_ADDRESS = 0,
			E65_SYSTEM_MEMORY_EXCEPTION_OFFSET,
			E65_SYSTEM_MEMORY_EXCEPTION_UNINITIALIZED,
		};

		#define E65_SYSTEM_MEMORY_EXCEPTION_MAX E65_SYSTEM_MEMORY_EXCEPTION_UNINITIALIZED

		static const std::string E65_SYSTEM_MEMORY_EXCEPTION_STR[] = {
			E65_SYSTEM_MEMORY_EXCEPTION_HEADER "Invalid address",
			E65_SYSTEM_MEMORY_EXCEPTION_HEADER "Invalid offset",
			E65_SYSTEM_MEMORY_EXCEPTION_HEADER "Memory uninitialized",
			};

		#define E65_SYSTEM_MEMORY_EXCEPTION_STRING(_TYPE_) \
			(((_TYPE_) > E65_SYSTEM_MEMORY_EXCEPTION_MAX) ? E65_EXCEPTION_UNKNOWN : \
				E65_STRING_CHECK(E65_SYSTEM_MEMORY_EXCEPTION_STR[_TYPE_]))

		#define THROW_E65_SYSTEM_MEMORY_EXCEPTION(_EXCEPT_) \
			THROW_E65_SYSTEM_MEMORY_EXCEPTION_FORMAT(_EXCEPT_, "", "")
		#define THROW_E65_SYSTEM_MEMORY_EXCEPTION_FORMAT(_EXCEPT_, _FORMAT_, ...) \
			E65_EXCEPTION_THROW_FORMAT(E65_SYSTEM_MEMORY_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)

		#define E65_MEMORY_BYTES_PER_KBYTE 1024.f

		#define E65_MEMORY_MEMORY_BLOCK_LENGTH 0x10
		#define E65_MEMORY_MEMORY_FILL 0xea
		#define E65_MEMORY_MEMORY_LENGTH 0x10000
	}
}

#endif // E65_SYSTEM_MEMORY_TYPE_H_