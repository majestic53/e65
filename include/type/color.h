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

		static const std::string E65_LEVEL_COL[] = {
			"\x1b[91m", "\x1b[93m", "\x1b[94m", "\x1b[90m",
			};

		#define E65_LEVEL_COLOR(_TYPE_) \
			(((_TYPE_) > E65_LEVEL_MAX) ? E65_LEVEL_COLOR_RESET : \
				E65_STRING_CHECK(e65::type::E65_LEVEL_COL[_TYPE_]))

		#define E65_LEVEL_COLOR_RESET "\x1b[0m"

		typedef union {

			struct {
				uint32_t blue : 8;
				uint32_t green : 8;
				uint32_t red : 8;
				uint32_t alpha : 8;
			};

			uint32_t raw;
		} color_t;
	}
}

#endif // E65_TYPE_COLOR_H_
