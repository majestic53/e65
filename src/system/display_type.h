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

#ifndef E65_SYSTEM_DISPLAY_TYPE_H_
#define E65_SYSTEM_DISPLAY_TYPE_H_

#include "../../include/type/exception.h"

namespace e65 {

	namespace system {

		#define E65_SYSTEM_DISPLAY_HEADER "[E65::SYSTEM::DISPLAY]"
#ifndef NDEBUG
		#define E65_SYSTEM_DISPLAY_EXCEPTION_HEADER E65_SYSTEM_DISPLAY_HEADER " "
#else
		#define E65_SYSTEM_DISPLAY_EXCEPTION_HEADER
#endif // NDEBUG

		enum {
			E65_SYSTEM_DISPLAY_EXCEPTION_EXTERNAL = 0,
			E65_SYSTEM_DISPLAY_EXCEPTION_INDEX,
			E65_SYSTEM_DISPLAY_EXCEPTION_POSITION,
			E65_SYSTEM_DISPLAY_EXCEPTION_UNINITIALIZED,
		};

		#define E65_SYSTEM_DISPLAY_EXCEPTION_MAX E65_SYSTEM_DISPLAY_EXCEPTION_UNINITIALIZED

		static const std::string E65_SYSTEM_DISPLAY_EXCEPTION_STR[] = {
			E65_SYSTEM_DISPLAY_EXCEPTION_HEADER "External exception",
			E65_SYSTEM_DISPLAY_EXCEPTION_HEADER "Invalid pixel index",
			E65_SYSTEM_DISPLAY_EXCEPTION_HEADER "Invalid pixel position",
			E65_SYSTEM_DISPLAY_EXCEPTION_HEADER "Display uninitialized",
			};

		#define E65_SYSTEM_DISPLAY_EXCEPTION_STRING(_TYPE_) \
			(((_TYPE_) > E65_SYSTEM_DISPLAY_EXCEPTION_MAX) ? E65_EXCEPTION_UNKNOWN : \
				E65_STRING_CHECK(E65_SYSTEM_DISPLAY_EXCEPTION_STR[_TYPE_]))

		#define THROW_E65_SYSTEM_DISPLAY_EXCEPTION(_EXCEPT_) \
			THROW_E65_SYSTEM_DISPLAY_EXCEPTION_FORMAT(_EXCEPT_, "", "")
		#define THROW_E65_SYSTEM_DISPLAY_EXCEPTION_FORMAT(_EXCEPT_, _FORMAT_, ...) \
			E65_EXCEPTION_THROW_FORMAT(E65_SYSTEM_DISPLAY_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)

		#define E65_DISPLAY_HEIGHT 32
		#define E65_DISPLAY_SCALE 12.f
		#define E65_DISPLAY_WIDTH 32

		#define E65_DISPLAY_FLAGS (SDL_WINDOW_RESIZABLE)
		#define E65_DISPLAY_FULLSCREEN_FLAGS (SDL_WINDOW_FULLSCREEN_DESKTOP)
		#define E65_DISPLAY_RENDERER_FLAGS (SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)
		#define E65_DISPLAY_RENDERER_QUALITY "0"

		#define E65_DISPLAY_PIXEL_INDEX(_X_, _Y_) \
			((E65_DISPLAY_WIDTH * (_Y_)) + (_X_))

		#define E65_COLOR_MAX e65::type::E65_COLOR_LIGHT_GREY

		static const e65::type::color_t E65_DISPLAY_COL[] = {
			{{ 0, 0, 0, 255, }},
			{{ 255, 255, 255, 255, }},
			{{ 0, 0, 204, 255, }},
			{{ 207, 190, 114, 255, }},
			{{ 123, 80, 117, 255, }},
			{{ 22, 210, 115, 255, }},
			{{ 164, 101, 52, 255, }},
			{{ 0, 212, 237, 255, }},
			{{ 0, 121, 245, 255, }},
			{{ 2, 89, 143, 255, }},
			{{ 41, 41, 239, 255, }},
			{{ 83, 87, 85, 255, }},
			{{ 133, 138, 136, 255, }},
			{{ 52, 226, 138, 255, }},
			{{ 207, 159, 114, 255, }},
			{{ 182, 189, 186, 255, }},
			};

		#define E65_DISPLAY_COLOR(_TYPE_) \
			(((_TYPE_) > E65_COLOR_MAX) ? E65_DISPLAY_COL[e65::type::E65_COLOR_BLACK] : \
				E65_DISPLAY_COL[_TYPE_])

		static const std::string E65_DISPLAY_COL_STR[] = {
			"Black", "White", "Red", "Cyan", "Purple", "Green", "Blue", "Yellow", "Orange", "Brown",
			"Light-red", "Dark-grey", "Grey", "Light-green", "Light-blue", "Light-grey",
			};

		#define E65_DISPLAY_COLOR_STRING(_TYPE_) \
			(((_TYPE_) > E65_COLOR_MAX) ? E65_STRING_UNKNOWN : \
				E65_STRING_CHECK(E65_DISPLAY_COL_STR[_TYPE_]))

		#define E65_DISPLAY_COLOR_BACKGROUND E65_DISPLAY_COLOR(e65::type::E65_COLOR_BLACK)
	}
}

#endif // E65_SYSTEM_DISPLAY_TYPE_H_
