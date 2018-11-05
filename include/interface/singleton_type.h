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

#ifndef E65_INTERFACE_SINGLETON_TYPE_H_
#define E65_INTERFACE_SINGLETON_TYPE_H_

#include "../exception.h"

namespace e65 {

	namespace interface {

		#define E65_INTERFACE_SINGLETON_HEADER "[E65::INTERFACE::SINGLETON]"
#ifndef NDEBUG
		#define E65_INTERFACE_SINGLETON_EXCEPTION_HEADER E65_INTERFACE_SINGLETON_HEADER " "
#else
		#define E65_INTERFACE_SINGLETON_EXCEPTION_HEADER
#endif // NDEBUG

		enum {
			E65_INTERFACE_SINGLETON_EXCEPTION_INITIALIZED = 0,
			E65_INTERFACE_SINGLETON_EXCEPTION_INITIALIZING,
			E65_INTERFACE_SINGLETON_EXCEPTION_UNINITIALIZED,
		};

		#define E65_INTERFACE_SINGLETON_EXCEPTION_MAX E65_INTERFACE_SINGLETON_EXCEPTION_UNINITIALIZED

		static const std::string E65_INTERFACE_SINGLETON_EXCEPTION_STR[] = {
			E65_INTERFACE_SINGLETON_EXCEPTION_HEADER "Singleton initialized",
			E65_INTERFACE_SINGLETON_EXCEPTION_HEADER "Singleton intiialization failed",
			E65_INTERFACE_SINGLETON_EXCEPTION_HEADER "Singleton uninitialized",
			};

		#define E65_INTERFACE_SINGLETON_EXCEPTION_STRING(_TYPE_) \
			(((_TYPE_) > E65_INTERFACE_SINGLETON_EXCEPTION_MAX) ? E65_EXCEPTION_UNKNOWN : \
				E65_STRING_CHECK(E65_INTERFACE_SINGLETON_EXCEPTION_STR[_TYPE_]))

		#define THROW_E65_INTERFACE_SINGLETON_EXCEPTION(_EXCEPT_) \
			THROW_E65_INTERFACE_SINGLETON_EXCEPTION_FORMAT(_EXCEPT_, "", "")
		#define THROW_E65_INTERFACE_SINGLETON_EXCEPTION_FORMAT(_EXCEPT_, _FORMAT_, ...) \
			E65_EXCEPTION_THROW_FORMAT(E65_INTERFACE_SINGLETON_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)

		enum {
			E65_SINGLETON_BUS = 0,
			E65_SINGLETON_CPU,
			E65_SINGLETON_DISPLAY,
			E65_SINGLETON_MMU,
			E65_SINGLETON_RUNTIME,
			E65_SINGLETON_TRACE,
		};

		#define E65_SINGLETON_MAX E65_SINGLETON_TRACE

		static const std::string E65_SINGLETON_STR[] = {
			"Bus", "Cpu", "Display", "Mmu", "Runtime", "Trace",
			};

		#define E65_SINGLETON_STRING(_TYPE_) \
			(((_TYPE_) > E65_SINGLETON_MAX) ? E65_STRING_UNKNOWN : \
				E65_STRING_CHECK(E65_SINGLETON_STR[_TYPE_]))
	}
}

#endif // E65_INTERFACE_SINGLETON_TYPE_H_
