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

#ifndef E65_DEFINE_LEVEL_H_
#define E65_DEFINE_LEVEL_H_

namespace e65 {

	enum {
		E65_LEVEL_ERROR = 0,
		E65_LEVEL_WARNING,
		E65_LEVEL_INFORMATION,
		E65_LEVEL_VERBOSE,
	};

	#define E65_LEVEL_MAX e65::E65_LEVEL_VERBOSE

	static const std::string E65_LEVEL_STR[] = {
		"Error", "Warning", "Information", "Verbose",
		};

	#define E65_LEVEL_STRING(_TYPE_) \
		(((_TYPE_) > E65_LEVEL_MAX) ? E65_STRING_UNKNOWN : \
			E65_STRING_CHECK(e65::E65_LEVEL_STR[_TYPE_]))
}

#endif // E65_DEFINE_LEVEL_H_
