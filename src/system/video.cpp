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
			e65::type::singleton<e65::system::video>(e65::type::E65_SINGLETON_VIDEO),
			m_display(e65::system::display::acquire()),
			m_frame(0),
			m_frame_cycles(0)
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

			if(!e65::type::singleton<e65::system::video>::initialized()) {
				THROW_E65_SYSTEM_VIDEO_EXCEPTION(E65_SYSTEM_VIDEO_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Video clearing");

			for(offset = E65_VIDEO_ADDRESS_MIN; offset <= E65_VIDEO_ADDRESS_MAX; ++offset) {
				memory.write(offset, e65::type::E65_COLOR_BLACK);
			}

			m_frame = 0;

			E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Video cleared");

			E65_TRACE_EXIT();
		}

		e65::interface::system::display &
		video::display(void)
		{
			E65_TRACE_ENTRY();

			if(!e65::type::singleton<e65::system::video>::initialized()) {
				THROW_E65_SYSTEM_VIDEO_EXCEPTION(E65_SYSTEM_VIDEO_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_EXIT();
			return m_display;
		}

		uint32_t
		video::frame(void) const
		{
			E65_TRACE_ENTRY();

			if(!e65::type::singleton<e65::system::video>::initialized()) {
				THROW_E65_SYSTEM_VIDEO_EXCEPTION(E65_SYSTEM_VIDEO_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_EXIT_FORMAT("Result=%u", m_frame);
			return m_frame;
		}

		uint32_t
		video::frame_cycles(void) const
		{
			E65_TRACE_ENTRY();

			if(!e65::type::singleton<e65::system::video>::initialized()) {
				THROW_E65_SYSTEM_VIDEO_EXCEPTION(E65_SYSTEM_VIDEO_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_EXIT_FORMAT("Result=%u", m_frame_cycles);
			return m_frame_cycles;
		}

		bool
		video::on_initialize(
			__in const void *context,
			__in size_t length
			)
		{
			bool result = true;

			E65_TRACE_ENTRY_FORMAT("Context[%u]=%p", length, context);

			E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Video initializing");

			m_display.initialize(context, length);
			m_frame_cycles = (E65_PROCESSOR_FREQUENCY / m_display.frequency());

			E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Video initialized");

			E65_TRACE_EXIT_FORMAT("Result=%x", result);
			return result;
		}

		void
		video::on_uninitialize(void)
		{
			E65_TRACE_ENTRY();

			E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Video uninitializing");

			m_display.uninitialize();

			E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Video uninitialized");

			E65_TRACE_EXIT();
		}

		int
		video::pixel(
			__in e65::interface::system::memory &memory,
			__in uint32_t x,
			__in uint32_t y
			) const
		{
			uint16_t address;
			int result = e65::type::E65_COLOR_BLACK;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Position={%u, %u}", &memory, x, y);

			if(!e65::type::singleton<e65::system::video>::initialized()) {
				THROW_E65_SYSTEM_VIDEO_EXCEPTION(E65_SYSTEM_VIDEO_EXCEPTION_UNINITIALIZED);
			}

			address = (E65_PIXEL_INDEX(x, y) + E65_VIDEO_ADDRESS_MIN);
			if(address > E65_VIDEO_ADDRESS_MAX) {
				THROW_E65_SYSTEM_VIDEO_EXCEPTION_FORMAT(E65_SYSTEM_VIDEO_EXCEPTION_POSITION, "{%u, %u}", x, y);
			}

			result = memory.read(address);

			E65_TRACE_EXIT_FORMAT("Result=%i(%s)", result, E65_COLOR_STRING(result));
			return result;
		}

		void
		video::set_pixel(
			__in e65::interface::system::memory &memory,
			__in uint32_t x,
			__in uint32_t y,
			__in int color
			)
		{
			uint16_t address;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Position={%u, %u}, Color=%u(%s)", &memory, x, y, color, E65_COLOR_STRING(color));

			if(!e65::type::singleton<e65::system::video>::initialized()) {
				THROW_E65_SYSTEM_VIDEO_EXCEPTION(E65_SYSTEM_VIDEO_EXCEPTION_UNINITIALIZED);
			}

			address = (E65_PIXEL_INDEX(x, y) + E65_VIDEO_ADDRESS_MIN);
			if(address > E65_VIDEO_ADDRESS_MAX) {
				THROW_E65_SYSTEM_VIDEO_EXCEPTION_FORMAT(E65_SYSTEM_VIDEO_EXCEPTION_POSITION, "{%u, %u}", x, y);
			}

			memory.write(address, color);

			E65_TRACE_EXIT();
		}

		void
		video::step(
			__in e65::interface::system::memory &memory
			)
		{
			uint16_t offset;

			E65_TRACE_ENTRY_FORMAT("Memory=%p", &memory);

			if(!e65::type::singleton<e65::system::video>::initialized()) {
				THROW_E65_SYSTEM_VIDEO_EXCEPTION(E65_SYSTEM_VIDEO_EXCEPTION_UNINITIALIZED);
			}

			for(offset = E65_VIDEO_ADDRESS_MIN; offset <= E65_VIDEO_ADDRESS_MAX; ++offset) {
				m_display.set_pixel(offset - E65_VIDEO_ADDRESS_MIN, memory.read(offset));
			}

			++m_frame;

			E65_TRACE_EXIT();
		}

		std::string
		video::to_string(void) const
		{
			std::stringstream result;

			result << E65_SYSTEM_VIDEO_HEADER << "(" << E65_STRING_HEX(uintptr_t, this) << ")"
				<< " Interface=" << e65::type::singleton<e65::system::video>::to_string();

			if(e65::type::singleton<e65::system::video>::initialized()) {
				result << ", Display=" << m_display.to_string()
					<< ", Frame=" << m_frame
					<< ", Frame-Cycles=" << m_frame_cycles;
			}

			return result.str();
		}
	}
}
