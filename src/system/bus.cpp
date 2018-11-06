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

#include "../../include/system/bus.h"
#include "../../include/trace.h"
#include "./bus_type.h"

namespace e65 {

	namespace system {

		bus::bus(void) :
			e65::interface::singleton<e65::system::bus>(e65::interface::E65_SINGLETON_BUS),
			m_display(e65::system::display::acquire()),
			m_input(e65::system::input::acquire()),
			m_memory(e65::system::memory::acquire()),
			m_processor(e65::system::processor::acquire()),
			m_tick(0),
			m_video(e65::system::video::acquire())
		{
			E65_TRACE_ENTRY();
			E65_TRACE_EXIT();
		}

		bus::~bus(void)
		{
			E65_TRACE_ENTRY();
			E65_TRACE_EXIT();
		}

		void
		bus::clear(void)
		{
			E65_TRACE_ENTRY();

			if(!e65::interface::singleton<e65::system::bus>::initialized()) {
				THROW_E65_SYSTEM_BUS_EXCEPTION(E65_SYSTEM_BUS_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Bus clearing");

			m_memory.clear();
			m_input.clear(m_memory);
			m_video.clear(m_memory);
			m_tick = 0;

			E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Bus cleared");

			E65_TRACE_EXIT();
		}

		e65::interface::system::display &
		bus::display(void)
		{
			E65_TRACE_ENTRY();

			if(!e65::interface::singleton<e65::system::bus>::initialized()) {
				THROW_E65_SYSTEM_BUS_EXCEPTION(E65_SYSTEM_BUS_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_EXIT();
			return m_display;
		}

		e65::interface::system::input &
		bus::input(void)
		{
			E65_TRACE_ENTRY();

			if(!e65::interface::singleton<e65::system::bus>::initialized()) {
				THROW_E65_SYSTEM_BUS_EXCEPTION(E65_SYSTEM_BUS_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_EXIT();
			return m_input;
		}

		void
		bus::load(
			__in const std::string &path
			)
		{
			E65_TRACE_ENTRY_FORMAT("Path[%u]=%s", path.size(), E65_STRING_CHECK(path));

			E65_TRACE_MESSAGE_FORMAT(E65_LEVEL_INFORMATION, "Bus loading", "%s", E65_STRING_CHECK(path));

			clear();

			// TODO: load file at path into memory

			m_processor.reset(m_memory);

			E65_TRACE_EXIT();
		}

		e65::interface::system::memory &
		bus::memory(void)
		{
			E65_TRACE_ENTRY();

			if(!e65::interface::singleton<e65::system::bus>::initialized()) {
				THROW_E65_SYSTEM_BUS_EXCEPTION(E65_SYSTEM_BUS_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_EXIT();
			return m_memory;
		}

		bool
		bus::on_initialize(
			__in const void *context,
			__in size_t length
			)
		{
			bool result = true;

			E65_TRACE_ENTRY_FORMAT("Context[%u]=%p", length, context);

			E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Bus initializing");

			m_tick = 0;
			m_display.initialize(context, length);
			m_memory.initialize(context, length);
			m_input.initialize(context, length);
			m_processor.initialize(context, length);
			m_video.initialize(context, length);

			E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Bus initialized");

			E65_TRACE_EXIT_FORMAT("Result=%x", result);
			return result;
		}

		void
		bus::on_uninitialize(void)
		{
			E65_TRACE_ENTRY();

			E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Bus uninitializing");

			m_video.uninitialize();
			m_processor.uninitialize();
			m_input.uninitialize();
			m_memory.uninitialize();
			m_display.uninitialize();

			E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Bus uninitialized");

			E65_TRACE_EXIT();
		}

		e65::interface::system::processor &
		bus::processor(void)
		{
			E65_TRACE_ENTRY();

			if(!e65::interface::singleton<e65::system::bus>::initialized()) {
				THROW_E65_SYSTEM_BUS_EXCEPTION(E65_SYSTEM_BUS_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_EXIT();
			return m_processor;
		}

		void
		bus::step(
			__in e65::interface::runtime &runtime
			)
		{
			E65_TRACE_ENTRY_FORMAT("Runtime=%p", &runtime);

			m_input.update(m_memory);

			// TODO: step processor through a single instruction

			E65_TRACE_EXIT();
		}

		void
		bus::step_frame(
			__in e65::interface::runtime &runtime
			)
		{
			E65_TRACE_ENTRY_FORMAT("Runtime=%p", &runtime);

			// TODO: step processor through an entire frame
			step(runtime);
			// ---

			m_video.update(m_display, m_memory);
			m_display.show();

			E65_TRACE_EXIT();
		}

		uint32_t
		bus::tick(void) const
		{
			E65_TRACE_ENTRY();

			if(!e65::interface::singleton<e65::system::bus>::initialized()) {
				THROW_E65_SYSTEM_BUS_EXCEPTION(E65_SYSTEM_BUS_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_EXIT_FORMAT("Result=%u", m_tick);
			return m_tick;
		}

		std::string
		bus::to_string(void) const
		{
			std::stringstream result;

			E65_TRACE_ENTRY();

			result << E65_SYSTEM_BUS_HEADER << "(" << E65_STRING_HEX(uintptr_t, this) << ")"
				<< " Interface=" << e65::interface::singleton<e65::system::bus>::to_string();

			if(e65::interface::singleton<e65::system::bus>::initialized()) {
				result << ", Display=" << m_display.to_string()
					<< ", Input=" << m_input.to_string()
					<< ", Memory=" << m_memory.to_string()
					<< ", Video=" << m_video.to_string()
					<< ", Tick=" << m_tick;
			}

			E65_TRACE_EXIT();
			return result.str();
		}

		e65::interface::system::video &
		bus::video(void)
		{
			E65_TRACE_ENTRY();

			if(!e65::interface::singleton<e65::system::bus>::initialized()) {
				THROW_E65_SYSTEM_BUS_EXCEPTION(E65_SYSTEM_BUS_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_EXIT();
			return m_video;
		}
	}
}
