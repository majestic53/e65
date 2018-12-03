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

#ifndef E65_RUNTIME_TYPE_H_
#define E65_RUNTIME_TYPE_H_

#include "../include/type/exception.h"

namespace e65 {

	#define E65_RUNTIME_HEADER "[E65::RUNTIME]"
#ifndef NDEBUG
	#define E65_RUNTIME_EXCEPTION_HEADER E65_RUNTIME_HEADER " "
#else
	#define E65_RUNTIME_EXCEPTION_HEADER
#endif // NDEBUG

	enum {
		E65_RUNTIME_EXCEPTION_EXTERNAL = 0,
		E65_RUNTIME_EXCEPTION_FILE_MALFORMED,
		E65_RUNTIME_EXCEPTION_FILE_NOT_FOUND,
		E65_RUNTIME_EXCEPTION_UNINITIALIZED,
	};

	#define E65_RUNTIME_EXCEPTION_MAX E65_RUNTIME_EXCEPTION_UNINITIALIZED

	static const std::string E65_RUNTIME_EXCEPTION_STR[] = {
		E65_RUNTIME_EXCEPTION_HEADER "External exception",
		E65_RUNTIME_EXCEPTION_HEADER "Malformed file",
		E65_RUNTIME_EXCEPTION_HEADER "File not found",
		E65_RUNTIME_EXCEPTION_HEADER "Runtime uninitialized",
		};

	#define E65_RUNTIME_EXCEPTION_STRING(_TYPE_) \
		(((_TYPE_) > E65_RUNTIME_EXCEPTION_MAX) ? E65_EXCEPTION_UNKNOWN : \
			E65_STRING_CHECK(E65_RUNTIME_EXCEPTION_STR[_TYPE_]))

	#define THROW_E65_RUNTIME_EXCEPTION(_EXCEPT_) \
		THROW_E65_RUNTIME_EXCEPTION_FORMAT(_EXCEPT_, "", "")
	#define THROW_E65_RUNTIME_EXCEPTION_FORMAT(_EXCEPT_, _FORMAT_, ...) \
		E65_EXCEPTION_THROW_FORMAT(E65_RUNTIME_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)

	#define E65_RUNTIME_SDL_FLAGS (SDL_INIT_TIMER | SDL_INIT_VIDEO)

	#define E65_RUNTIME_SDL_DEBUG_BREAK_KEY SDL_SCANCODE_B
	#define E65_RUNTIME_SDL_DEBUG_RUN_KEY SDL_SCANCODE_G
	#define E65_RUNTIME_SDL_FULLSCREEN_KEY SDL_SCANCODE_F11
	#define E65_RUNTIME_SDL_INTERRUPT_MASKABLE_KEY SDL_SCANCODE_M
	#define E65_RUNTIME_SDL_INTERRUPT_NON_MASKABLE_KEY SDL_SCANCODE_N
	#define E65_RUNTIME_SDL_REFRESH_KEY SDL_SCANCODE_F5
	#define E65_RUNTIME_SDL_RESET_KEY SDL_SCANCODE_R

	static const std::string E65_RUNTIME_EVENT_STR[] = {
		"Break",
		"Breakpoint",
		"Maskable-Interrupt",
		"Non-maskable-Interrupt",
		"Stop",
		"Wait",
		};

	#define E65_RUNTIME_EVENT_MAX E65_EVENT_WAIT

	#define E65_RUNTIME_EVENT_STRING(_TYPE_) \
		(((_TYPE_) > E65_RUNTIME_EVENT_MAX) ? E65_STRING_UNKNOWN : \
			E65_STRING_CHECK(E65_RUNTIME_EVENT_STR[_TYPE_]))
}

#endif // E65_RUNTIME_TYPE_H_
