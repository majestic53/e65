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

#ifndef E65_INTERFACE_RUNTIME_H_
#define E65_INTERFACE_RUNTIME_H_

#include "./sdl/display.h"
#include "./trace.h"

namespace e65 {

	namespace interface {

		class runtime {

			public:

				virtual uint32_t frame(void) const = 0;

				virtual e65::interface::sdl::display &display(void) = 0;

				virtual e65::interface::trace &trace(void) = 0;

				virtual bool wait(
					__in_opt uint32_t timeout = 0
					) = 0;
		};
	}
}

#endif // E65_INTERFACE_RUNTIME_H_
