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

#include "../../include/console/bus.h"
#include "../../include/trace.h"
#include "./bus_type.h"

namespace e65 {

	namespace console {

		bus::bus(void) :
			e65::interface::singleton<e65::console::bus>(e65::interface::E65_SINGLETON_BUS),
			m_display(e65::sdl::display::acquire()),
			m_tick(0)
		{
			E65_TRACE_ENTRY();
			E65_TRACE_EXIT();
		}

		bus::~bus(void)
		{
			E65_TRACE_ENTRY();
			E65_TRACE_EXIT();
		}

		e65::interface::sdl::display &
		bus::display(void)
		{
			E65_TRACE_ENTRY();

			if(!e65::interface::singleton<e65::console::bus>::initialized()) {
				THROW_E65_CONSOLE_BUS_EXCEPTION(E65_CONSOLE_BUS_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_EXIT();
			return m_display;
		}

		void
		bus::input(
			__in int key
			)
		{
			E65_TRACE_ENTRY_FORMAT("Key=%u(%x)", key, key);

			if(!e65::interface::singleton<e65::console::bus>::initialized()) {
				THROW_E65_CONSOLE_BUS_EXCEPTION(E65_CONSOLE_BUS_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_MESSAGE_FORMAT(E65_LEVEL_INFORMATION, "Bus key event", "%u(%x)", key, key);

			// TODO: send input to console::mmu

			E65_TRACE_EXIT();
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

			// TODO: initialize console::cpu, console::mmu, etc.

			E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Bus initialized");

			E65_TRACE_EXIT_FORMAT("Result=%x", result);
			return result;
		}

		void
		bus::on_uninitialize(void)
		{
			E65_TRACE_ENTRY();

			E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Bus uninitializing");

			// TODO: uninitialize console::cpu, console::mmu, etc.

			m_display.uninitialize();

			E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Bus uninitialized");

			E65_TRACE_EXIT();
		}

		void
		bus::step(
			__in e65::interface::runtime &runtime
			)
		{
			E65_TRACE_ENTRY_FORMAT("Runtime=%p", &runtime);

			// TODO: step console::cpu through a single instruction

			E65_TRACE_EXIT();
		}

		void
		bus::step_frame(
			__in e65::interface::runtime &runtime
			)
		{
			E65_TRACE_ENTRY_FORMAT("Runtime=%p", &runtime);

			// TODO: step console::cpu through an entire frame

			m_display.render();

			E65_TRACE_EXIT();
		}

		uint32_t
		bus::tick(void) const
		{
			E65_TRACE_ENTRY();

			if(!e65::interface::singleton<e65::console::bus>::initialized()) {
				THROW_E65_CONSOLE_BUS_EXCEPTION(E65_CONSOLE_BUS_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_EXIT_FORMAT("Result=%u", m_tick);
			return m_tick;
		}

		std::string
		bus::to_string(void) const
		{
			std::stringstream result;

			E65_TRACE_ENTRY();

			result << E65_CONSOLE_BUS_HEADER << "(" << E65_STRING_HEX(uintptr_t, this) << ")"
				<< " Interface=" << e65::interface::singleton<e65::console::bus>::to_string();

			if(e65::interface::singleton<e65::console::bus>::initialized()) {
				result << ", Display=" << m_display.to_string()
					<< ", Tick=" << m_tick;
			}

			E65_TRACE_EXIT();
			return result.str();
		}
	}
}
