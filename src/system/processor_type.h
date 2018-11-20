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

#ifndef E65_SYSTEM_PROCESSOR_TYPE_H_
#define E65_SYSTEM_PROCESSOR_TYPE_H_

#include "../../include/exception.h"

namespace e65 {

	namespace system {

		#define E65_SYSTEM_PROCESSOR_HEADER "[E65::SYSTEM::PROCESSOR]"
#ifndef NDEBUG
		#define E65_SYSTEM_PROCESSOR_EXCEPTION_HEADER E65_SYSTEM_PROCESSOR_HEADER " "
#else
		#define E65_SYSTEM_PROCESSOR_EXCEPTION_HEADER
#endif // NDEBUG

		enum {
			E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_CODE = 0,
			E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_LENGTH,
			E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED,
		};

		#define E65_SYSTEM_PROCESSOR_EXCEPTION_MAX E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED

		static const std::string E65_SYSTEM_PROCESSOR_EXCEPTION_STR[] = {
			E65_SYSTEM_PROCESSOR_EXCEPTION_HEADER "Invalid command code",
			E65_SYSTEM_PROCESSOR_EXCEPTION_HEADER "Invalid command length",
			E65_SYSTEM_PROCESSOR_EXCEPTION_HEADER "Input uninitialized",
			};

		#define E65_SYSTEM_PROCESSOR_EXCEPTION_STRING(_TYPE_) \
			(((_TYPE_) > E65_SYSTEM_PROCESSOR_EXCEPTION_MAX) ? E65_EXCEPTION_UNKNOWN : \
				E65_STRING_CHECK(E65_SYSTEM_PROCESSOR_EXCEPTION_STR[_TYPE_]))

		#define THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(_EXCEPT_) \
			THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(_EXCEPT_, "", "")
		#define THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(_EXCEPT_, _FORMAT_, ...) \
			E65_EXCEPTION_THROW_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)

		#define E65_PROCESSOR_ADDRESS_MASKABLE_INTERRUPT 0xfffe
		#define E65_PROCESSOR_ADDRESS_NON_MASKABLE_INTERRUPT 0xfffa
		#define E65_PROCESSOR_ADDRESS_RESET_INTERRUPT 0xfffc

		#define E65_PROCESSOR_INTERRUPT_CYCLES 7

		#define E65_PROCESSOR_REGISTER_ACCUMULATOR 0x00
		#define E65_PROCESSOR_REGISTER_FLAGS \
			(E65_PFLAG(e65::type::E65_PFLAG_BREAKPOINT) \
				| E65_PFLAG(e65::type::E65_PFLAG_IRQ_DISABLE) \
				| E65_PFLAG(e65::type::E65_PFLAG_UNUSED))
		#define E65_PROCESSOR_REGISTER_INDEX_X 0x00
		#define E65_PROCESSOR_REGISTER_INDEX_Y 0x00
		#define E65_PROCESSOR_REGISTER_STACK_POINTER 0xfd
		#define E65_PROCESSOR_REGISTER_STACK_POINTER_BASE 0x100
	}
}

#endif // E65_SYSTEM_PROCESSOR_TYPE_H_
