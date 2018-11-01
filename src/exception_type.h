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

#ifndef E65_EXCEPTION_TYPE_H_
#define E65_EXCEPTION_TYPE_H_

namespace e65 {

	#define E65_EXCEPTION_HEADER "[E65::EXCEPTION]"
#ifndef NDEBUG
	#define E65_EXCEPTION_EXCEPTION_HEADER E65_EXCEPTION_HEADER " "
#else
	#define E65_EXCEPTION_EXCEPTION_HEADER
#endif // NDEBUG

	enum {
		E65_EXCEPTION_EXCEPTION_MALFORMED = 0,
	};

	#define E65_EXCEPTION_EXCEPTION_MAX E65_EXCEPTION_EXCEPTION_MALFORMED

	static const std::string E65_EXCEPTION_EXCEPTION_STR[] = {
		E65_EXCEPTION_EXCEPTION_HEADER "Malformed",
		};

	#define E65_EXCEPTION_EXCEPTION_STRING(_TYPE_) \
		(((_TYPE_) > E65_EXCEPTION_EXCEPTION_MAX) ? E65_EXCEPTION_UNKNOWN : \
			E65_STRING_CHECK(E65_EXCEPTION_EXCEPTION_STR[_TYPE_]))
}

#endif // E65_EXCEPTION_TYPE_H_
