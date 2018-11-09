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

#ifndef E65_INTERFACE_SYSTEM_PROCESSOR_H_
#define E65_INTERFACE_SYSTEM_PROCESSOR_H_

#include "./memory.h"

namespace e65 {

	namespace interface {

		namespace system {

			class processor {

				public:

					virtual uint8_t accumulator(void) const = 0;

					virtual uint32_t cycle(void) const = 0;

					virtual uint8_t flags(void) const = 0;

					virtual bool halted(void) const = 0;

					virtual uint8_t index_x(void) const = 0;

					virtual uint8_t index_y(void) const = 0;

					virtual void interrupt(
						__in e65::interface::system::memory &memory,
						__in bool maskable
						) = 0;

					virtual uint16_t program_counter(void) const = 0;

					virtual void reset(
						__in e65::interface::system::memory &memory
						) = 0;

					virtual void set_accumulator(
						__in uint8_t value
						) = 0;

					virtual void set_flags(
						__in uint8_t value
						) = 0;

					virtual void set_halt(
						__in bool value
						) = 0;

					virtual void set_index_x(
						__in uint8_t value
						) = 0;

					virtual void set_index_y(
						__in uint8_t value
						) = 0;

					virtual void set_program_counter(
						__in uint16_t value
						) = 0;

					virtual void set_stack_pointer(
						__in uint8_t value
						) = 0;

					virtual void set_stop(
						__in bool value
						) = 0;

					virtual uint8_t stack_pointer(void) const = 0;

					virtual bool stopped(void) const = 0;
			};
		}
	}
}

#endif // E65_INTERFACE_SYSTEM_PROCESSOR_H_
