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

#ifndef E65_INTERFACE_CONSOLE_MMU_H_
#define E65_INTERFACE_CONSOLE_MMU_H_

#include <vector>
#include "../../define.h"

namespace e65 {

	namespace interface {

		namespace console {

			class mmu {

				public:

					virtual std::string dump(
						__in uint16_t origin,
						__in uint16_t length
						) const = 0;

					virtual uint8_t read(
						__in uint16_t address
						) const = 0;

					virtual uint16_t read_word(
						__in uint16_t address
						) const = 0;

					virtual void write(
						__in uint16_t address,
						__in uint8_t value
						) = 0;

					virtual void write_word(
						__in uint16_t address,
						__in uint16_t value
						) = 0;
			};
		}
	}
}

#endif // E65_INTERFACE_CONSOLE_MMU_H_
