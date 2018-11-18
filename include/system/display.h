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

#ifndef E65_SYSTEM_DISPLAY_H_
#define E65_SYSTEM_DISPLAY_H_

#include <vector>
#include <SDL2/SDL.h>
#include "../interface/singleton.h"
#include "../interface/system/display.h"

namespace e65 {

	namespace system {

		typedef union {

			struct {
				uint32_t blue : 8;
				uint32_t green : 8;
				uint32_t red : 8;
				uint32_t alpha : 8;
			};

			uint32_t raw;
		} color_t;

		class display :
				public e65::interface::singleton<e65::system::display>,
				public e65::interface::system::display {

			public:

				~display(void);

				void clear(void);

				bool fullscreen(void) const override;

				bool hidden(void) const override;

				uint32_t pixel(
					__in uint32_t x,
					__in uint32_t y
					) const override;

				void set_frame_rate(
					__in float frame_rate
					) override;

				void set_fullscreen(
					__in bool fullscreen
					) override;

				void set_hidden(
					__in bool hidden
					) override;

				void set_pixel(
					__in uint32_t index,
					__in uint8_t color
					) override;

				void set_pixel(
					__in uint32_t x,
					__in uint32_t y,
					__in int color
					) override;

				void set_title(
					__in const std::string &title
					) override;

				void show(void) const;

				std::string title(void) const override;

				std::string to_string(void) const override;

			protected:

				friend class e65::interface::singleton<e65::system::display>;

				display(void);

				display(
					__in const display &other
					) = delete;

				display &operator=(
					__in const display &other
					) = delete;

				bool on_initialize(
					__in const void *context,
					__in size_t length
					) override;

				void on_uninitialize(void) override;

				std::vector<e65::system::color_t> m_pixel;

				SDL_Renderer *m_renderer;

				SDL_Texture *m_texture;

				std::string m_title;

				SDL_Window *m_window;
		};
	}
}

#endif // E65_SYSTEM_DISPLAY_H_
