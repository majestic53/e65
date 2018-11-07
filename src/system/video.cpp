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

#include "../../include/system/video.h"
#include "../../include/trace.h"
#include "./video_type.h"

namespace e65 {

	namespace system {

		video::video(void) :
			e65::interface::singleton<e65::system::video>(e65::interface::E65_SINGLETON_VIDEO),
			m_display(e65::system::display::acquire()),
			m_frame(0)
		{
			E65_TRACE_ENTRY();

			std::srand(std::time(nullptr));

			E65_TRACE_EXIT();
		}

		video::~video(void)
		{
			E65_TRACE_ENTRY();
			E65_TRACE_EXIT();
		}

		void
		video::clear(
			__in e65::interface::system::memory &memory
			)
		{
			uint16_t offset;

			E65_TRACE_ENTRY_FORMAT("Memory=%p", &memory);

			if(!e65::interface::singleton<e65::system::video>::initialized()) {
				THROW_E65_SYSTEM_VIDEO_EXCEPTION(E65_SYSTEM_VIDEO_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Video clearing");

			for(offset = E65_VIDEO_ADDRESS_MIN; offset <= E65_VIDEO_ADDRESS_MAX; ++offset) {
				memory.write(offset, E65_COLOR_BLACK);
			}

			m_frame = 0;

			E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Video cleared");

			E65_TRACE_EXIT();
		}

		e65::interface::system::display &
		video::display(void)
		{
			E65_TRACE_ENTRY();

			if(!e65::interface::singleton<e65::system::video>::initialized()) {
				THROW_E65_SYSTEM_VIDEO_EXCEPTION(E65_SYSTEM_VIDEO_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_EXIT();
			return m_display;
		}

		uint32_t
		video::frame(void) const
		{
			E65_TRACE_ENTRY();

			if(!e65::interface::singleton<e65::system::video>::initialized()) {
				THROW_E65_SYSTEM_VIDEO_EXCEPTION(E65_SYSTEM_VIDEO_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_EXIT_FORMAT("Result=%u", m_frame);
			return m_frame;
		}

		bool
		video::on_initialize(
			__in const void *context,
			__in size_t length
			)
		{
			bool result = true;

			E65_TRACE_ENTRY_FORMAT("Context[%u]=%p", length, context);

			E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Video initializing");

			m_display.initialize(context, length);

			E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Video initialized");

			E65_TRACE_EXIT_FORMAT("Result=%x", result);
			return result;
		}

		void
		video::on_uninitialize(void)
		{
			E65_TRACE_ENTRY();

			E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Video uninitializing");

			m_display.uninitialize();

			E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Video uninitialized");

			E65_TRACE_EXIT();
		}

		void
		video::step(
			__in e65::interface::system::memory &memory
			)
		{
			uint16_t offset;

			E65_TRACE_ENTRY_FORMAT("Memory=%p", &memory);

			if(!e65::interface::singleton<e65::system::video>::initialized()) {
				THROW_E65_SYSTEM_VIDEO_EXCEPTION(E65_SYSTEM_VIDEO_EXCEPTION_UNINITIALIZED);
			}

			for(offset = E65_VIDEO_ADDRESS_MIN; offset <= E65_VIDEO_ADDRESS_MAX; ++offset) {
				m_display.set_pixel(offset - E65_VIDEO_ADDRESS_MIN, memory.read(offset));
			}

			m_display.show();

			E65_TRACE_EXIT();
		}

		std::string
		video::to_string(void) const
		{
			std::stringstream result;

			result << E65_SYSTEM_VIDEO_HEADER << "(" << E65_STRING_HEX(uintptr_t, this) << ")"
				<< " Interface=" << e65::interface::singleton<e65::system::video>::to_string();

			if(e65::interface::singleton<e65::system::video>::initialized()) {
				result << ", Display=" << m_display.to_string()
					<< ", Frame=" << m_frame;
			}

			return result.str();
		}
	}
}
