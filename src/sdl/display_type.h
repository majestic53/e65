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

#ifndef E65_SDL_DISPLAY_TYPE_H_
#define E65_SDL_DISPLAY_TYPE_H_

#include "../../include/exception.h"

namespace e65 {

	namespace sdl {

		#define E65_SDL_DISPLAY_HEADER "[E65::SDL::DISPLAY]"
#ifndef NDEBUG
		#define E65_SDL_DISPLAY_EXCEPTION_HEADER E65_SDL_DISPLAY_HEADER " "
#else
		#define E65_SDL_DISPLAY_EXCEPTION_HEADER
#endif // NDEBUG

		enum {
			E65_SDL_DISPLAY_EXCEPTION_EXTERNAL = 0,
			E65_SDL_DISPLAY_EXCEPTION_POSITION,
			E65_SDL_DISPLAY_EXCEPTION_UNINITIALIZED,
		};

		#define E65_SDL_DISPLAY_EXCEPTION_MAX E65_SDL_DISPLAY_EXCEPTION_UNINITIALIZED

		static const std::string E65_SDL_DISPLAY_EXCEPTION_STR[] = {
			E65_SDL_DISPLAY_EXCEPTION_HEADER "External exception",
			E65_SDL_DISPLAY_EXCEPTION_HEADER "Invalid pixel position",
			E65_SDL_DISPLAY_EXCEPTION_HEADER "Display uninitialized",
			};

		#define E65_SDL_DISPLAY_EXCEPTION_STRING(_TYPE_) \
			(((_TYPE_) > E65_SDL_DISPLAY_EXCEPTION_MAX) ? E65_EXCEPTION_UNKNOWN : \
				E65_STRING_CHECK(E65_SDL_DISPLAY_EXCEPTION_STR[_TYPE_]))

		#define THROW_E65_SDL_DISPLAY_EXCEPTION(_EXCEPT_) \
			THROW_E65_SDL_DISPLAY_EXCEPTION_FORMAT(_EXCEPT_, "", "")
		#define THROW_E65_SDL_DISPLAY_EXCEPTION_FORMAT(_EXCEPT_, _FORMAT_, ...) \
			E65_EXCEPTION_THROW_FORMAT(E65_SDL_DISPLAY_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)

		#define E65_DISPLAY_HEIGHT 32
		#define E65_DISPLAY_SCALE 8.f
		#define E65_DISPLAY_WIDTH 32

		#define E65_DISPLAY_SDL_FLAGS (SDL_WINDOW_RESIZABLE)
		#define E65_DISPLAY_SDL_FULLSCREEN_FLAGS (SDL_WINDOW_FULLSCREEN_DESKTOP)
		#define E65_DISPLAY_SDL_RENDERER_FLAGS (SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)
		#define E65_DISPLAY_SDL_RENDERER_QUALITY "0"

		#define E65_SDL_DISPLAY_PIXEL_INDEX(_X_, _Y_) \
			((E65_DISPLAY_WIDTH * (_Y_)) + (_X_))

		enum {
			E65_COLOR_BLACK = 0,
			E65_COLOR_WHITE,

			// TODO: add additional color support
		};

		#define E65_COLOR_MAX E65_COLOR_WHITE

		static const e65::sdl::color_t E65_DISPLAY_COL[] = {
			{{ 0x00, 0x00, 0x00, 0xff, }},
			{{ 0xff, 0xff, 0xff, 0xff, }},
			};

		#define E65_DISPLAY_COLOR(_TYPE_) \
			(((_TYPE_) > E65_COLOR_MAX) ? E65_DISPLAY_COL[E65_COLOR_BLACK] : \
				E65_DISPLAY_COL[_TYPE_])

		#define E65_DISPLAY_BACKGROUND E65_DISPLAY_COLOR(E65_COLOR_BLACK)
	}
}

#endif // E65_SDL_DISPLAY_TYPE_H_
