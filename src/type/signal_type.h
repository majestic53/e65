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

#ifndef E65_TYPE_SIGNAL_TYPE_H_
#define E65_TYPE_SIGNAL_TYPE_H_

#include "../../include/exception.h"

namespace e65 {

	namespace type {

		#define E65_TYPE_SIGNAL_HEADER "[E65::TYPE::SIGNAL]"
#ifndef NDEBUG
		#define E65_TYPE_SIGNAL_EXCEPTION_HEADER E65_TYPE_SIGNAL_HEADER " "
#else
		#define E65_TYPE_SIGNAL_EXCEPTION_HEADER
#endif // NDEBUG

		enum {
			E65_TYPE_SIGNAL_EXCEPTION_ABANDONED = 0,
		};

		#define E65_TYPE_SIGNAL_EXCEPTION_MAX E65_TYPE_SIGNAL_EXCEPTION_ABANDONED

		static const std::string E65_TYPE_SIGNAL_EXCEPTION_STR[] = {
			E65_TYPE_SIGNAL_EXCEPTION_HEADER "Signal abandoned",
			};

		#define E65_TYPE_SIGNAL_EXCEPTION_STRING(_TYPE_) \
			(((_TYPE_) > E65_TYPE_SIGNAL_EXCEPTION_MAX) ? E65_STRING_UNKNOWN : \
				E65_STRING_CHECK(E65_TYPE_SIGNAL_EXCEPTION_STR[_TYPE_]))

		#define THROW_E65_TYPE_SIGNAL_EXCEPTION(_EXCEPT_) \
			THROW_E65_TYPE_SIGNAL_EXCEPTION_FOMAT(_EXCEPT_, "", "")
		#define THROW_E65_TYPE_SIGNAL_EXCEPTION_FOMAT(_EXCEPT_, _FORMAT_, ...) \
			E65_THROW_EXCEPTION_FORMAT(E65_TYPE_SIGNAL_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)

		#define E65_SIGNAL_MAX E65_SIGNAL_ABANDON

		static const std::string E65_SIGNAL_STR[] = {
			"Clear", "Notify", "Timeout", "Abandon",
			};

		#define E65_SIGNAL_STRING(_TYPE_) \
			(((_TYPE_) > E65_SIGNAL_MAX) ? E65_STRING_UNKNOWN : \
				E65_STRING_CHECK(E65_SIGNAL_STR[_TYPE_]))
	}
}

#endif // E65_TYPE_SIGNAL_TYPE_H_
