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

#include "../include/runtime.h"
#include "./runtime_type.h"

namespace e65 {

	runtime::runtime(void) :
		e65::interface::singleton<e65::runtime>(e65::interface::E65_SINGLETON_RUNTIME),
		m_trace(e65::trace::acquire())
	{
		m_trace.initialize();

		E65_TRACE_ENTRY();

		E65_TRACE_MESSAGE_FORMAT(E65_LEVEL_INFORMATION, "Runtime created", "%s", E65_STRING_CHECK(version()));

		E65_TRACE_EXIT();
	}

	runtime::~runtime(void)
	{
		E65_TRACE_ENTRY();

		E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Runtime destroyed");

		E65_TRACE_EXIT();

		m_trace.uninitialize();
	}

	bool
	runtime::on_initialize(
		__in const void *context,
		__in size_t length
		)
	{
		bool result = true;

		E65_TRACE_ENTRY_FORMAT("Context[%u]=%p", length, context);

		E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Runtime initializing");

		// TODO

		e65::type::thread::start(false, context, length);

		E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Runtime initialized");

		E65_TRACE_EXIT_FORMAT("Result=%x", result);
		return result;
	}

	bool
	runtime::on_run(
		__in const void *context,
		__in size_t length
		)
	{
		bool result = true;

		E65_TRACE_ENTRY_FORMAT("Context[%u]=%p", length, context);

		E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Runtime main loop entry");

		while(e65::type::thread::active()) {

			// TODO
		}

		E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Runtime main loop exit");

		E65_TRACE_EXIT_FORMAT("Result=%x", result);
		return result;
	}

	bool
	runtime::on_start(
		__in const void *context,
		__in size_t length
		)
	{
		bool result = true;

		E65_TRACE_ENTRY_FORMAT("Context[%u]=%p", length, context);

		E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Runtime starting");

		// TODO

		E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Runtime started");

		E65_TRACE_EXIT_FORMAT("Result=%x", result);
		return result;
	}

	void
	runtime::on_stop(void)
	{
		E65_TRACE_ENTRY();

		E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Runtime stopping");

		// TODO

		E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Runtime stopped");

		E65_TRACE_EXIT();
	}

	void
	runtime::on_uninitialize(void)
	{
		E65_TRACE_ENTRY();

		E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Runtime uninitializing");

		e65::type::thread::stop();

		// TODO

		E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Runtime uninitialized");

		E65_TRACE_EXIT();
	}

	std::string
	runtime::to_string(void) const
	{
		std::stringstream result;

		E65_TRACE_ENTRY();

		result << E65_RUNTIME_HEADER << "(" << E65_STRING_HEX(uintptr_t, this) << ")"
			<< " Interface=" << e65::interface::singleton<e65::runtime>::to_string();

		if(m_initialized) {
			result << ", Thread=" << e65::type::thread::to_string()
				<< ", Trace=" << m_trace.to_string();
		}

		E65_TRACE_EXIT();
		return result.str();
	}

	e65::interface::trace &
	runtime::trace(void)
	{
		E65_TRACE_ENTRY();

		if(!e65::interface::singleton<e65::runtime>::initialized()) {
			THROW_E65_RUNTIME_EXCEPTION_FORMAT(E65_RUNTIME_EXCEPTION_UNINITIALIZED, "%p", this);
		}

		E65_TRACE_EXIT();
		return m_trace;
	}

	std::string
	runtime::version(void)
	{
		std::stringstream result;

		result << E65_VERSION_MAJOR << "." << E65_VERSION_MINOR << "." << E65_VERSION_WEEK << "." << E65_VERSION_REVISION
			<< "-" << E65_VERSION_RELEASE;

		return result.str();
	}
}
