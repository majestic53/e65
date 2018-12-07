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

#include "../../../include/system/video.h"
#include "../../../include/system/memory.h"
#include "../../include/interface/video.h"
#include "./video_type.h"

namespace e65 {

	namespace test {

		namespace interface {

			video::video(void) :
				e65::test::type::fixture(e65::test::type::E65_FIXTURE_INTERFACE_VIDEO)
			{
				return;
			}

			video::~video(void)
			{
				return;
			}

			bool
			video::frame(
				__in e65::interface::system::video &video,
				__in e65::interface::system::memory &memory
				)
			{
				return (video.frame() == E65_TEST_INTERFACE_VIDEO_FRAME_VALUE);
			}

			void
			video::on_clear(void)
			{
				return;
			}

			std::string
			video::on_failure(
				__in int test
				)
			{
				return E65_TEST_INTERFACE_VIDEO_STRING(test);
			}

			bool
			video::on_run(
				__in int test
				)
			{
				bool result = true;

				try {
					e65::system::memory &memory = e65::system::memory::acquire();
					e65::system::video &video = e65::system::video::acquire();

					memory.initialize();
					video.initialize();

					switch(test) {
						case E65_TEST_INTERFACE_VIDEO_FRAME:
							result = frame(video, memory);
							break;
						case E65_TEST_INTERFACE_VIDEO_PIXEL:
							result = pixel(video, memory);
							break;
						case E65_TEST_INTERFACE_VIDEO_SET_PIXEL:
							result = set_pixel(video, memory);
							break;
						default:
							break;
					}

					video.uninitialize();
					memory.uninitialize();
				} catch(...) {
					result = false;
				}

				return result;
			}

			bool
			video::on_run_all(
				__inout std::set<int> &test
				)
			{
				int iter = 0;
				bool result = true;

				for(iter = 0; iter <= E65_TEST_INTERFACE_VIDEO_MAX; ++iter) {

					if(!on_run(iter)) {
						test.insert(iter);
						result = false;
					}
				}

				return result;
			}

			bool
			video::pixel(
				__in e65::interface::system::video &video,
				__in e65::interface::system::memory &memory
				)
			{
				bool result;
				uint32_t x = (std::rand() % E65_VIDEO_WIDTH), y = (std::rand() % E65_VIDEO_HEIGHT);

				result = ((video.pixel(memory, x, y) % E65_COLOR_MAX) == e65::type::E65_COLOR_BROWN);
				if(result) {
					uint8_t color = std::rand();

					x = (std::rand() % E65_VIDEO_WIDTH);
					y = (std::rand() % E65_VIDEO_HEIGHT);
					video.set_pixel(memory, x, y, color);

					result = (video.pixel(memory, x, y) == color);
					if(result) {

						try {
							x = (E65_VIDEO_WIDTH + 1), y = (E65_VIDEO_HEIGHT + 1);
							video.pixel(memory, x, y);
							result = false;
						} catch(...) { }
					}
				}

				return result;
			}

			bool
			video::set_pixel(
				__in e65::interface::system::video &video,
				__in e65::interface::system::memory &memory
				)
			{
				bool result;
				uint8_t color = std::rand();
				uint32_t x = (std::rand() % E65_VIDEO_WIDTH), y = (std::rand() % E65_VIDEO_HEIGHT);

				video.set_pixel(memory, x, y, color);

				result = (video.pixel(memory, x, y) == color);
				if(result) {

					try {
						x = (E65_VIDEO_WIDTH + 1), y = (E65_VIDEO_HEIGHT + 1);
						video.set_pixel(memory, x, y, color);
						result = false;
					} catch(...) { }
				}

				return result;
			}

			std::string
			video::to_string(void) const
			{
				std::stringstream result;

				result << E65_TEST_INTERFACE_VIDEO_HEADER << "(" << E65_STRING_HEX(uintptr_t, this) << ")"
					<< " Fixture=" << e65::test::type::fixture::to_string();

				return result.str();
			}
		}
	}
}
