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

#ifndef E65_INTERFACE_SYSTEM_INPUT_H_
#define E65_INTERFACE_SYSTEM_INPUT_H_

#include "./memory.h"

namespace e65 {

	namespace interface {

		namespace system {

			class input {

				public:

					virtual void key(
						__in e65::interface::system::memory &memory,
						__in int value
						) = 0;
			};
		}
	}
}

#endif // E65_INTERFACE_SYSTEM_INPUT_H_
