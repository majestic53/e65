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

#ifndef E65_TYPE_THREAD_TYPE_H_
#define E65_TYPE_THREAD_TYPE_H_

#include "../../include/exception.h"

namespace e65 {

	namespace type {

		#define E65_TYPE_THREAD_HEADER "[E65::TYPE::THREAD]"
#ifndef NDEBUG
		#define E65_TYPE_THREAD_EXCEPTION_HEADER E65_TYPE_THREAD_HEADER " "
#else
		#define E65_TYPE_THREAD_EXCEPTION_HEADER
#endif // NDEBUG

		enum {
			E65_TYPE_THREAD_EXCEPTION_NOTIFIABLE = 0,
			E65_TYPE_THREAD_EXCEPTION_STATE,
		};

		#define E65_TYPE_THREAD_EXCEPTION_MAX E65_TYPE_THREAD_EXCEPTION_STATE

		static const std::string E65_TYPE_THREAD_EXCEPTION_STR[] = {
			E65_TYPE_THREAD_EXCEPTION_HEADER "Thread is not notifiable",
			E65_TYPE_THREAD_EXCEPTION_HEADER "Invalid thread state transition",
			};

		#define E65_TYPE_THREAD_EXCEPTION_STRING(_TYPE_) \
			(((_TYPE_) > E65_TYPE_THREAD_EXCEPTION_MAX) ? E65_EXCEPTION_UNKNOWN : \
				E65_STRING_CHECK(E65_TYPE_THREAD_EXCEPTION_STR[_TYPE_]))

		#define THROW_E65_TYPE_THREAD_EXCEPTION(_EXCEPT_) \
			THROW_E65_TYPE_THREAD_EXCEPTION_FORMAT(_EXCEPT_, "", "")
		#define THROW_E65_TYPE_THREAD_EXCEPTION_FORMAT(_EXCEPT_, _FORMAT_, ...) \
			THROW_E65_EXCEPTION_FORMAT(E65_TYPE_THREAD_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)

		#define E65_THREAD_MAX E65_THREAD_PAUSE

		static const std::string E65_THREAD_STR[] = {
			"Stop", "Run", "Pause",
			};

		#define E65_THREAD_STRING(_TYPE_) \
			(((_TYPE_) > E65_THREAD_MAX) ? E65_STRING_UNKNOWN : \
				E65_STRING_CHECK(E65_THREAD_STR[_TYPE_]))
	}
}

#endif // E65_TYPE_THREAD_TYPE_H_
