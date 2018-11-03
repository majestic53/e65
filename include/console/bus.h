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

#ifndef E65_CONSOLE_BUS_H_
#define E65_CONSOLE_BUS_H_

#include "../interface/runtime.h"
#include "../interface/singleton.h"
#include "../sdl/display.h"

namespace e65 {

	namespace console {

		class bus :
				public e65::interface::singleton<e65::console::bus>,
				public e65::interface::console::bus {

			public:

				~bus(void);

				e65::interface::sdl::display &display(void) override;

				void input(
					__in int key
					) override;

				uint32_t tick(void) const override;

				std::string to_string(void) const override;

				void update(
					__in e65::interface::runtime &runtime
					);

			protected:

				friend class e65::interface::singleton<e65::console::bus>;

				bus(void);

				bus(
					__in const bus &other
					) = delete;

				bus &operator=(
					__in const bus &other
					) = delete;

				bool on_initialize(
					__in const void *context,
					__in size_t length
					) override;

				void on_uninitialize(void) override;

				e65::sdl::display &m_display;

				uint32_t m_tick;
		};
	}
}

#endif // E65_CONSOLE_BUS_H_
