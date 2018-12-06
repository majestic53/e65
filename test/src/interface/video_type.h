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

#ifndef E65_TEST_INTERFACE_VIDEO_TYPE_H_
#define E65_TEST_INTERFACE_VIDEO_TYPE_H_

#include "../../../include/type/exception.h"

namespace e65 {

	namespace test {

		namespace interface {

			#define E65_TEST_INTERFACE_VIDEO_HEADER "[E65::TEST::INTERFACE::VIDEO]"
#ifndef NDEBUG
			#define E65_TEST_INTERFACE_VIDEO_EXCEPTION_HEADER E65_TEST_INTERFACE_VIDEO_HEADER " "
#else
			#define E65_TEST_INTERFACE_VIDEO_EXCEPTION_HEADER
#endif // NDEBUG

			enum {
				E65_TEST_INTERFACE_VIDEO_EXCEPTION_NONE = 0,
			};

			#define E65_TEST_INTERFACE_VIDEO_EXCEPTION_MAX E65_TEST_INTERFACE_VIDEO_EXCEPTION_NONE

			static const std::string E65_TEST_INTERFACE_VIDEO_EXCEPTION_STR[] = {
				E65_TEST_INTERFACE_VIDEO_EXCEPTION_HEADER "",
				};

			#define E65_TEST_INTERFACE_VIDEO_EXCEPTION_STRING(_TYPE_) \
				(((_TYPE_) > E65_TEST_INTERFACE_VIDEO_EXCEPTION_MAX) ? E65_STRING_UNKNOWN : \
					E65_STRING_CHECK(E65_TEST_INTERFACE_VIDEO_EXCEPTION_STR[_TYPE_]))

			#define THROW_E65_TEST_INTERFACE_VIDEO_EXCEPTION(_EXCEPT_) \
				THROW_E65_TEST_INTERFACE_VIDEO_EXCEPTION_FOMAT(_EXCEPT_, "", "")
			#define THROW_E65_TEST_INTERFACE_VIDEO_EXCEPTION_FOMAT(_EXCEPT_, _FORMAT_, ...) \
				E65_EXCEPTION_THROW_FORMAT(E65_TEST_INTERFACE_VIDEO_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)

			#define E65_TEST_INTERFACE_VIDEO_FRAME_VALUE 0

			enum {
				E65_TEST_INTERFACE_VIDEO_FRAME = 0,
				E65_TEST_INTERFACE_VIDEO_PIXEL,
				E65_TEST_INTERFACE_VIDEO_SET_PIXEL,
			};

			#define E65_TEST_INTERFACE_VIDEO_MAX E65_TEST_INTERFACE_VIDEO_SET_PIXEL

			static const std::string E65_TEST_INTERFACE_VIDEO_STR[] = {
				"Frame",
				"Pixel",
				"Set-Pixel",
				};

			#define E65_TEST_INTERFACE_VIDEO_STRING(_TYPE_) \
				(((_TYPE_) > E65_TEST_INTERFACE_VIDEO_MAX) ? E65_STRING_UNKNOWN : \
					E65_STRING_CHECK(E65_TEST_INTERFACE_VIDEO_STR[_TYPE_]))
		}
	}
}

#endif // E65_TEST_INTERFACE_VIDEO_TYPE_H_
