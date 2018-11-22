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

#include "../../include/system/input.h"
#include "../../include/trace.h"
#include "./input_type.h"

namespace e65 {

	namespace system {

		input::input(void) :
			e65::type::singleton<e65::system::input>(e65::type::E65_SINGLETON_INPUT)
		{
			E65_TRACE_ENTRY();

			std::srand(std::time(nullptr));

			E65_TRACE_EXIT();
		}

		input::~input(void)
		{
			E65_TRACE_ENTRY();
			E65_TRACE_EXIT();
		}

		void
		input::clear(
			__in e65::interface::system::memory &memory
			)
		{
			E65_TRACE_ENTRY_FORMAT("Memory=%p", &memory);

			if(!e65::type::singleton<e65::system::input>::initialized()) {
				THROW_E65_SYSTEM_INPUT_EXCEPTION(E65_SYSTEM_INPUT_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Input clearing");

			memory.write(E65_INPUT_ADDRESS_KEY, 0);
			memory.write(E65_INPUT_ADDRESS_RANDOM, 0);

			E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Input cleared");

			E65_TRACE_EXIT();
		}

		void
		input::key(
			__in e65::interface::system::memory &memory,
			__in int value
			)
		{
			E65_TRACE_ENTRY_FORMAT("Memory=%p, Value=%u(%x)", &memory, value, value);

			if(!e65::type::singleton<e65::system::input>::initialized()) {
				THROW_E65_SYSTEM_INPUT_EXCEPTION(E65_SYSTEM_INPUT_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_MESSAGE_FORMAT(e65::type::E65_LEVEL_INFORMATION, "Input key event", "%u(%x)", value, value);

			memory.write(E65_INPUT_ADDRESS_KEY, value);

			E65_TRACE_EXIT();
		}

		bool
		input::on_initialize(
			__in const void *context,
			__in size_t length
			)
		{
			bool result = true;

			E65_TRACE_ENTRY_FORMAT("Context[%u]=%p", length, context);

			E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Input initializing");

			E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Input initialized");

			E65_TRACE_EXIT_FORMAT("Result=%x", result);
			return result;
		}

		void
		input::on_uninitialize(void)
		{
			E65_TRACE_ENTRY();

			E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Input uninitializing");

			E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Input uninitialized");

			E65_TRACE_EXIT();
		}

		void
		input::step(
			__in e65::interface::system::memory &memory
			)
		{
			E65_TRACE_ENTRY_FORMAT("Memory=%p", &memory);

			if(!e65::type::singleton<e65::system::input>::initialized()) {
				THROW_E65_SYSTEM_INPUT_EXCEPTION(E65_SYSTEM_INPUT_EXCEPTION_UNINITIALIZED);
			}

			memory.write(E65_INPUT_ADDRESS_RANDOM, std::rand());

			E65_TRACE_EXIT();
		}

		std::string
		input::to_string(void) const
		{
			std::stringstream result;

			result << E65_SYSTEM_INPUT_HEADER << "(" << E65_STRING_HEX(uintptr_t, this) << ")"
				<< " Interface=" << e65::type::singleton<e65::system::input>::to_string();

			return result.str();
		}
	}
}
