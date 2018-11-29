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

#ifndef E65_INTERFACE_SYSTEM_DISPLAY_H_
#define E65_INTERFACE_SYSTEM_DISPLAY_H_

#include "../../define.h"

namespace e65 {

	namespace interface {

		namespace system {

			class display {

				public:

					virtual uint32_t frequency(void) const = 0;

					virtual bool fullscreen(void) const = 0;

					virtual bool hidden(void) const = 0;

					virtual int pixel(
						__in uint32_t x,
						__in uint32_t y
						) const = 0;

					virtual void set_frame_rate(
						__in float frame_rate
						) = 0;

					virtual void set_fullscreen(
						__in bool fullscreen
						) = 0;

					virtual void set_hidden(
						__in bool hidden
						) = 0;

					virtual void set_pixel(
						__in uint32_t index,
						__in uint8_t color
						) = 0;

					virtual void set_pixel(
						__in uint32_t x,
						__in uint32_t y,
						__in int color
						) = 0;

					virtual void set_title(
						__in const std::string &title
						) = 0;

					virtual void show(void) const = 0;

					virtual std::string title(void) const = 0;
			};
		}
	}
}

#endif // E65_INTERFACE_SYSTEM_DISPLAY_H_
