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

#include "../../include/system/processor.h"
#include "../../include/trace.h"
#include "./processor_type.h"

namespace e65 {

	namespace system {

		processor::processor(void) :
			e65::interface::singleton<e65::system::processor>(e65::interface::E65_SINGLETON_PROCESSOR)
			// TODO
		{
			E65_TRACE_ENTRY();
			E65_TRACE_EXIT();
		}

		processor::~processor(void)
		{
			E65_TRACE_ENTRY();
			E65_TRACE_EXIT();
		}

		bool
		processor::on_initialize(
			__in const void *context,
			__in size_t length
			)
		{
			bool result = true;

			E65_TRACE_ENTRY_FORMAT("Context[%u]=%p", length, context);

			E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Processor initializing");

			// TODO

			E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Processor initialized");

			E65_TRACE_EXIT_FORMAT("Result=%x", result);
			return result;
		}

		void
		processor::on_uninitialize(void)
		{
			E65_TRACE_ENTRY();

			E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Processor uninitializing");

			E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Processor uninitialized");

			E65_TRACE_EXIT();
		}

		void
		processor::reset(
			__in e65::interface::system::memory &memory
			)
		{
			E65_TRACE_ENTRY_FORMAT("Memory=%p", &memory);

			if(!e65::interface::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Processor resetting");

			// TODO

			E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Processor reset");

			E65_TRACE_EXIT();
		}

		void
		processor::step(
			__in e65::interface::system::memory &memory
			)
		{
			E65_TRACE_ENTRY_FORMAT("Memory=%p", &memory);

			if(!e65::interface::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			// TODO

			E65_TRACE_EXIT();
		}

		std::string
		processor::to_string(void) const
		{
			std::stringstream result;

			result << E65_SYSTEM_PROCESSOR_HEADER << "(" << E65_STRING_HEX(uintptr_t, this) << ")"
				<< " Interface=" << e65::interface::singleton<e65::system::processor>::to_string();

			// TODO

			return result.str();
		}
	}
}
