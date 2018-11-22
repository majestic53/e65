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

#ifndef E65_SYSTEM_VIDEO_H_
#define E65_SYSTEM_VIDEO_H_

#include "../interface/system/video.h"
#include "./display.h"

namespace e65 {

	namespace system {

		class video :
				public e65::type::singleton<e65::system::video>,
				public e65::interface::system::video {

			public:

				~video(void);

				void clear(
					__in e65::interface::system::memory &memory
					);

				e65::interface::system::display &display(void) override;

				uint32_t frame(void) const override;

				void step(
					__in e65::interface::system::memory &memory
					);

				std::string to_string(void) const override;

			protected:

				friend class e65::type::singleton<e65::system::video>;

				video(void);

				video(
					__in const video &other
					) = delete;

				video &operator=(
					__in const video &other
					) = delete;

				bool on_initialize(
					__in const void *context,
					__in size_t length
					) override;

				void on_uninitialize(void) override;

				e65::system::display &m_display;

				uint32_t m_frame;
		};
	}
}

#endif // E65_SYSTEM_VIDEO_H_
