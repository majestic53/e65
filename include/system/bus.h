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

#ifndef E65_SYSTEM_BUS_H_
#define E65_SYSTEM_BUS_H_

#include "../interface/runtime.h"
#include "./input.h"
#include "./processor.h"
#include "./video.h"

namespace e65 {

	namespace system {

		class bus :
				public e65::interface::singleton<e65::system::bus>,
				public e65::interface::system::bus {

			public:

				~bus(void);

				void clear(void) override;

				e65::interface::system::display &display(void) override;

				e65::interface::system::input &input(void) override;

				void load(
					__in const std::string &path
					) override;

				e65::interface::system::memory &memory(void) override;

				e65::interface::system::processor &processor(void) override;

				void step(
					__in e65::interface::runtime &runtime
					);

				void step_frame(
					__in e65::interface::runtime &runtime
					);

				uint32_t tick(void) const override;

				std::string to_string(void) const override;

				e65::interface::system::video &video(void) override;

			protected:

				friend class e65::interface::singleton<e65::system::bus>;

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

				e65::system::display &m_display;

				e65::system::input &m_input;

				e65::system::memory &m_memory;

				e65::system::processor &m_processor;

				uint32_t m_tick;

				e65::system::video &m_video;
		};
	}
}

#endif // E65_SYSTEM_BUS_H_
