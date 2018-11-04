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
		m_bus(e65::console::bus::acquire()),
		m_debug(false),
		m_frame(0),
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
	runtime::breakpoint_clear(
		__in uint16_t address
		)
	{
		bool result = false;
		std::set<uint16_t>::iterator entry;

		E65_TRACE_ENTRY_FORMAT("Address=%u(%04x)", address, address);

		if(!e65::interface::singleton<e65::runtime>::initialized()) {
			THROW_E65_RUNTIME_EXCEPTION(E65_RUNTIME_EXCEPTION_UNINITIALIZED);
		}

		entry = m_breakpoint.find(address);
		if(entry != m_breakpoint.end()) {
			m_breakpoint.erase(entry);
			result = true;
		}

		E65_TRACE_EXIT_FORMAT("Result=%x", result);
		return result;
	}

	bool
	runtime::breakpoint_contains(
		__in uint16_t address
		)
	{
		bool result;

		E65_TRACE_ENTRY_FORMAT("Address=%u(%04x)", address, address);

		if(!e65::interface::singleton<e65::runtime>::initialized()) {
			THROW_E65_RUNTIME_EXCEPTION(E65_RUNTIME_EXCEPTION_UNINITIALIZED);
		}

		result = (m_breakpoint.find(address) != m_breakpoint.end());

		E65_TRACE_EXIT_FORMAT("Result=%x", result);
		return result;
	}

	bool
	runtime::breakpoint_set(
		__in uint16_t address
		)
	{
		bool result;

		E65_TRACE_ENTRY_FORMAT("Address=%u(%04x)", address, address);

		result = !breakpoint_contains(address);
		if(result) {
			m_breakpoint.insert(address);
		}

		E65_TRACE_EXIT_FORMAT("Result=%x", result);
		return result;
	}

	std::set<uint16_t>
	runtime::breakpoints(void) const
	{
		E65_TRACE_ENTRY();

		if(!e65::interface::singleton<e65::runtime>::initialized()) {
			THROW_E65_RUNTIME_EXCEPTION(E65_RUNTIME_EXCEPTION_UNINITIALIZED);
		}

		E65_TRACE_EXIT();
		return m_breakpoint;
	}

	void
	runtime::breakpoints_clear(void)
	{
		E65_TRACE_ENTRY();

		if(!e65::interface::singleton<e65::runtime>::initialized()) {
			THROW_E65_RUNTIME_EXCEPTION(E65_RUNTIME_EXCEPTION_UNINITIALIZED);
		}

		m_breakpoint.clear();

		E65_TRACE_EXIT();
	}

	e65::interface::console::bus &
	runtime::bus(void)
	{
		E65_TRACE_ENTRY();

		if(!e65::interface::singleton<e65::runtime>::initialized()) {
			THROW_E65_RUNTIME_EXCEPTION(E65_RUNTIME_EXCEPTION_UNINITIALIZED);
		}

		E65_TRACE_EXIT();
		return m_bus;
	}

	uint32_t
	runtime::frame(void) const
	{
		E65_TRACE_ENTRY();

		if(!e65::interface::singleton<e65::runtime>::initialized()) {
			THROW_E65_RUNTIME_EXCEPTION(E65_RUNTIME_EXCEPTION_UNINITIALIZED);
		}

		E65_TRACE_EXIT_FORMAT("Result=%u", m_frame);
		return m_frame;
	}

	bool
	runtime::on_initialize(
		__in const void *context,
		__in size_t length
		)
	{
		bool result = true;
		SDL_version version = {};

		E65_TRACE_ENTRY_FORMAT("Context[%u]=%p", length, context);

		E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Runtime initializing");

		m_breakpoint.clear();
		m_frame = 0;

		SDL_GetVersion(&version);
		E65_TRACE_MESSAGE_FORMAT(E65_LEVEL_INFORMATION, "Runtime library created", "%u.%u.%u", version.major, version.minor, version.patch);

		if(SDL_Init(E65_RUNTIME_SDL_FLAGS)) {
			THROW_E65_RUNTIME_EXCEPTION_FORMAT(E65_RUNTIME_EXCEPTION_EXTERNAL, "SDL_Init failed! Error=%s", SDL_GetError());
		}

		m_bus.initialize(context, length);
		e65::type::thread::start(true, context, length);

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

		if(!m_debug) {
			uint32_t begin = 0, current = 0;

			while(e65::type::thread::active()) {
				float delta, rate;
				uint32_t end = SDL_GetTicks();

				rate = (end - begin);
				if(rate >= E65_MILLISECONDS_PER_SECOND) {
					rate = (current - ((rate - E65_MILLISECONDS_PER_SECOND) / E65_RUNTIME_FRAME_RATE));

					E65_TRACE_MESSAGE_FORMAT(E65_LEVEL_INFORMATION, "Runtime framerate", "%.1f", (rate > 0.f) ? rate : 0.f);

					m_bus.display().set_frame_rate((rate > 0.f) ? rate : 0.f);
					begin = end;
					current = 0;
				}

				result = poll();
				if(!result) {
					break;
				}

				m_bus.step_frame(*this);

				delta = (SDL_GetTicks() - end);
				if(delta < E65_RUNTIME_FRAME_DELTA) {
					SDL_Delay(E65_RUNTIME_FRAME_DELTA - delta);
				}

				++current;
				++m_frame;
			}
		} else {

			result = poll();
			if(result) {
				m_bus.step(*this);
			}
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

		E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Runtime started");

		E65_TRACE_EXIT_FORMAT("Result=%x", result);
		return result;
	}

	void
	runtime::on_stop(void)
	{
		E65_TRACE_ENTRY();

		E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Runtime stopping");

		E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Runtime stopped");

		E65_TRACE_EXIT();
	}

	void
	runtime::on_uninitialize(void)
	{
		E65_TRACE_ENTRY();

		E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Runtime uninitializing");

		e65::type::thread::stop();

		m_bus.uninitialize();
		SDL_Quit();

		E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Runtime library destroyed");

		E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Runtime uninitialized");

		E65_TRACE_EXIT();
	}

	bool
	runtime::poll(void)
	{
		bool result = true;
		SDL_Event event = {};

		E65_TRACE_ENTRY();

		while(SDL_PollEvent(&event)) {

			switch(event.type) {
				case SDL_KEYDOWN:

					if(!event.key.repeat) {
						SDL_Scancode key;

						key = event.key.keysym.scancode;
						switch(key) {
							case E65_RUNTIME_SDL_FULLSCREEN_KEY:
								E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Display mode event");
								m_bus.display().set_fullscreen(!m_bus.display().fullscreen());
								break;
							default:
								m_bus.input(key);
								break;
						}
					}
					break;
				case SDL_QUIT:
					E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Runtime quit event");
					result = false;
					break;
				default:
					break;
			}
		}

		E65_TRACE_EXIT_FORMAT("Result=%x", result);
		return result;
	}

	void
	runtime::run(
		__in const std::string &path,
		__in_opt bool debug
		)
	{
		E65_TRACE_ENTRY_FORMAT("Path[%u]=%s, Debug=%x", path.size(), E65_STRING_CHECK(path), debug);

		if(!e65::interface::singleton<e65::runtime>::initialized()) {
			THROW_E65_RUNTIME_EXCEPTION(E65_RUNTIME_EXCEPTION_UNINITIALIZED);
		}

		E65_TRACE_MESSAGE_FORMAT(E65_LEVEL_INFORMATION, "Runtime running", "%s (%s)", E65_STRING_CHECK(path), debug ? "Debug" : "Normal");

		// TODO: reset bus && load input into console::mmu

		m_debug = debug;
		if(!m_debug) {
			e65::type::thread::notify();
		}

		E65_TRACE_EXIT();
	}

	bool
	runtime::step(void)
	{
		bool result;

		E65_TRACE_ENTRY();

		if(!e65::interface::singleton<e65::runtime>::initialized()) {
			THROW_E65_RUNTIME_EXCEPTION(E65_RUNTIME_EXCEPTION_UNINITIALIZED);
		}

		result = m_debug;
		if(result) {
			E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Runtime stepping");

			// TODO
			// result = breakpoint_contains(/* get console::cpu::pc */);
			// if(result) {
				e65::type::thread::notify();
			// }
		}

		E65_TRACE_EXIT_FORMAT("Result=%x", result);
		return result;
	}

	std::string
	runtime::to_string(void) const
	{
		std::stringstream result;

		E65_TRACE_ENTRY();

		result << E65_RUNTIME_HEADER << "(" << E65_STRING_HEX(uintptr_t, this) << ")"
			<< " Interface=" << e65::interface::singleton<e65::runtime>::to_string();

		if(e65::interface::singleton<e65::runtime>::initialized()) {
			result << ", Thread=" << e65::type::thread::to_string()
				<< ", Bus=" << m_bus.to_string()
				<< ", Trace=" << m_trace.to_string()
				<< ", Mode=" << m_debug << "(" << (m_debug ? "Debug" : "Normal") << ")"
				<< ", Frame=" << m_frame;
		}

		E65_TRACE_EXIT();
		return result.str();
	}

	e65::interface::trace &
	runtime::trace(void)
	{
		E65_TRACE_ENTRY();

		if(!e65::interface::singleton<e65::runtime>::initialized()) {
			THROW_E65_RUNTIME_EXCEPTION(E65_RUNTIME_EXCEPTION_UNINITIALIZED);
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

	bool
	runtime::wait(
		__in_opt uint32_t timeout
		)
	{
		bool result;

		E65_TRACE_ENTRY_FORMAT("Timeout=%u", timeout);

		if(!e65::interface::singleton<e65::runtime>::initialized()) {
			THROW_E65_RUNTIME_EXCEPTION(E65_RUNTIME_EXCEPTION_UNINITIALIZED);
		}

		result = e65::type::thread::wait(timeout);

		E65_TRACE_EXIT_FORMAT("Result=%x", result);
		return result;
	}
}
