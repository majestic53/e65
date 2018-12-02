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

#ifndef E65_TYPE_COLOR_H_
#define E65_TYPE_COLOR_H_

#include <map>

namespace e65 {

	namespace type {

		enum {
			E65_COLOR_BLACK = 0,
			E65_COLOR_WHITE,
			E65_COLOR_RED,
			E65_COLOR_CYAN,
			E65_COLOR_PURPLE,
			E65_COLOR_GREEN,
			E65_COLOR_BLUE,
			E65_COLOR_YELLOW,
			E65_COLOR_ORANGE,
			E65_COLOR_BROWN,
			E65_COLOR_LIGHT_RED,
			E65_COLOR_DARK_GREY,
			E65_COLOR_GREY,
			E65_COLOR_LIGHT_GREEN,
			E65_COLOR_LIGHT_BLUE,
			E65_COLOR_LIGHT_GREY,
		};

		#define E65_COLOR_MAX e65::type::E65_COLOR_LIGHT_GREY

		typedef union {

			struct {
				uint32_t blue : 8;
				uint32_t green : 8;
				uint32_t red : 8;
				uint32_t alpha : 8;
			};

			uint32_t raw;
		} color_t;

		static const e65::type::color_t E65_COL[] = {
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

		#define E65_COLOR(_TYPE_) \
			e65::type::E65_COL[(_TYPE_) % E65_COLOR_MAX]

		static const std::string E65_COL_STR[] = {
			"Black", "White", "Red", "Cyan", "Purple", "Green", "Blue", "Yellow", "Orange", "Brown",
			"Light-red", "Dark-grey", "Grey", "Light-green", "Light-blue", "Light-grey",
			};

		#define E65_COLOR_STRING(_TYPE_) \
			(((_TYPE_) > E65_COLOR_MAX) ? E65_STRING_UNKNOWN : \
				E65_STRING_CHECK(e65::type::E65_COL_STR[_TYPE_]))

		static const std::map<uint32_t, int> E65_COLOR_MAP = {
			std::make_pair(E65_COL[E65_COLOR_BLACK].raw, E65_COLOR_BLACK),
			std::make_pair(E65_COL[E65_COLOR_WHITE].raw, E65_COLOR_WHITE),
			std::make_pair(E65_COL[E65_COLOR_RED].raw, E65_COLOR_RED),
			std::make_pair(E65_COL[E65_COLOR_CYAN].raw, E65_COLOR_CYAN),
			std::make_pair(E65_COL[E65_COLOR_PURPLE].raw, E65_COLOR_PURPLE),
			std::make_pair(E65_COL[E65_COLOR_GREEN].raw, E65_COLOR_GREEN),
			std::make_pair(E65_COL[E65_COLOR_BLUE].raw, E65_COLOR_BLUE),
			std::make_pair(E65_COL[E65_COLOR_YELLOW].raw, E65_COLOR_YELLOW),
			std::make_pair(E65_COL[E65_COLOR_ORANGE].raw, E65_COLOR_ORANGE),
			std::make_pair(E65_COL[E65_COLOR_BROWN].raw, E65_COLOR_BROWN),
			std::make_pair(E65_COL[E65_COLOR_LIGHT_RED].raw, E65_COLOR_LIGHT_RED),
			std::make_pair(E65_COL[E65_COLOR_DARK_GREY].raw, E65_COLOR_DARK_GREY),
			std::make_pair(E65_COL[E65_COLOR_GREY].raw, E65_COLOR_GREY),
			std::make_pair(E65_COL[E65_COLOR_LIGHT_GREEN].raw, E65_COLOR_LIGHT_GREEN),
			std::make_pair(E65_COL[E65_COLOR_LIGHT_BLUE].raw, E65_COLOR_LIGHT_BLUE),
			std::make_pair(E65_COL[E65_COLOR_LIGHT_GREY].raw, E65_COLOR_LIGHT_GREY),
			};

		static const std::string E65_LEVEL_COL[] = {
			"\x1b[91m", "\x1b[93m", "\x1b[94m", "\x1b[90m",
			};

		#define E65_LEVEL_COLOR(_TYPE_) \
			(((_TYPE_) > E65_LEVEL_MAX) ? E65_LEVEL_COLOR_RESET : \
				E65_STRING_CHECK(e65::type::E65_LEVEL_COL[_TYPE_]))

		#define E65_LEVEL_COLOR_RESET "\x1b[0m"
	}
}

#endif // E65_TYPE_COLOR_H_
