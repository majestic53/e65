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

#ifndef E65_INTERFACE_TRACE_H_
#define E65_INTERFACE_TRACE_H_

#include "../define.h"

namespace e65 {

	namespace interface {

		class trace {

			public:

				virtual bool empty(void) const = 0;

				virtual void flush(void) = 0;

				virtual void generate(
					__in int level,
					__in const std::string &prefix,
					__in const std::string &message,
					__in const std::string &file,
					__in const std::string &function,
					__in size_t line,
					__in const char *format,
					...
					) = 0;

				virtual size_t size(void) const = 0;
		};
	}
}

#endif // E65_INTERFACE_TRACE_H_
