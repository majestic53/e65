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

#ifndef E65_INTERFACE_SYSTEM_BUS_H_
#define E65_INTERFACE_SYSTEM_BUS_H_

#include "./input.h"
#include "./video.h"

namespace e65 {

	namespace interface {

		namespace system {

			class bus {

				public:

					virtual void clear(void) = 0;

					virtual e65::interface::system::display &display(void) = 0;

					virtual e65::interface::system::input &input(void) = 0;

					virtual void load(
						__in const std::string &path
						) = 0;

					virtual e65::interface::system::memory &memory(void) = 0;

					virtual uint32_t tick(void) const = 0;

					virtual e65::interface::system::video &video(void) = 0;
			};
		}
	}
}

#endif // E65_INTERFACE_SYSTEM_BUS_H_
