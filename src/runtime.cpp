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

#include <fstream>
#include "../include/runtime.h"
#include "./runtime_type.h"

namespace e65 {

	runtime::runtime(void) :
		e65::type::singleton<e65::runtime>(e65::type::E65_SINGLETON_RUNTIME),
		m_bus(e65::system::bus::acquire()),
		m_debug(false),
		m_trace(e65::trace::acquire())
	{
		m_trace.initialize();

		E65_TRACE_ENTRY();

		E65_TRACE_MESSAGE_FORMAT(e65::type::E65_LEVEL_INFORMATION, "Runtime created", "%s", E65_STRING_CHECK(version()));

		E65_TRACE_EXIT();
	}

	runtime::~runtime(void)
	{
		E65_TRACE_ENTRY();

		E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Runtime destroyed");

		E65_TRACE_EXIT();

		m_trace.uninitialize();
	}

	bool
	runtime::breakpoint(
		__in uint16_t address
		)
	{
		bool result;

		E65_TRACE_ENTRY_FORMAT("Address=%u(%04x)", address, address);

		if(!e65::type::singleton<e65::runtime>::initialized()) {
			THROW_E65_RUNTIME_EXCEPTION(E65_RUNTIME_EXCEPTION_UNINITIALIZED);
		}

		result = (m_breakpoint.find(address) != m_breakpoint.end());

		E65_TRACE_EXIT_FORMAT("Result=%x", result);
		return result;
	}

	bool
	runtime::breakpoint_clear(
		__in uint16_t address
		)
	{
		bool result = false;
		std::set<uint16_t>::iterator entry;

		E65_TRACE_ENTRY_FORMAT("Address=%u(%04x)", address, address);

		if(!e65::type::singleton<e65::runtime>::initialized()) {
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

	std::string
	runtime::breakpoint_list(void) const
	{
		std::stringstream result;
		std::set<uint16_t>::const_iterator entry;

		E65_TRACE_ENTRY();

		if(!e65::type::singleton<e65::runtime>::initialized()) {
			THROW_E65_RUNTIME_EXCEPTION(E65_RUNTIME_EXCEPTION_UNINITIALIZED);
		}

		if(!m_breakpoint.empty()) {
			size_t offset = 1;

			for(entry = m_breakpoint.begin(); entry != m_breakpoint.end(); ++entry, ++offset) {

				if(entry != m_breakpoint.begin()) {
					result << std::endl;
				}

				result << "[" << offset << "] " << E65_STRING_HEX(uint16_t, *entry);
			}
		} else {
			result << E65_STRING_EMPTY;
		}

		E65_TRACE_EXIT();
		return result.str();
	}

	bool
	runtime::breakpoint_set(
		__in uint16_t address
		)
	{
		bool result;

		E65_TRACE_ENTRY_FORMAT("Address=%u(%04x)", address, address);

		result = !breakpoint(address);
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

		if(!e65::type::singleton<e65::runtime>::initialized()) {
			THROW_E65_RUNTIME_EXCEPTION(E65_RUNTIME_EXCEPTION_UNINITIALIZED);
		}

		E65_TRACE_EXIT();
		return m_breakpoint;
	}

	void
	runtime::breakpoints_clear(void)
	{
		E65_TRACE_ENTRY();

		if(!e65::type::singleton<e65::runtime>::initialized()) {
			THROW_E65_RUNTIME_EXCEPTION(E65_RUNTIME_EXCEPTION_UNINITIALIZED);
		}

		m_breakpoint.clear();

		E65_TRACE_EXIT();
	}

	e65::interface::system::bus &
	runtime::bus(void)
	{
		E65_TRACE_ENTRY();

		if(!e65::type::singleton<e65::runtime>::initialized()) {
			THROW_E65_RUNTIME_EXCEPTION(E65_RUNTIME_EXCEPTION_UNINITIALIZED);
		}

		E65_TRACE_EXIT();
		return m_bus;
	}

	bool
	runtime::debug(void) const
	{
		E65_TRACE_ENTRY();

		if(!e65::type::singleton<e65::runtime>::initialized()) {
			THROW_E65_RUNTIME_EXCEPTION(E65_RUNTIME_EXCEPTION_UNINITIALIZED);
		}

		E65_TRACE_EXIT_FORMAT("Result=%x", m_debug);
		return m_debug;
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

		E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Runtime initializing");

		m_breakpoint.clear();

		SDL_GetVersion(&version);
		E65_TRACE_MESSAGE_FORMAT(e65::type::E65_LEVEL_INFORMATION, "Runtime library created", "%u.%u.%u", version.major, version.minor,
			version.patch);

		if(SDL_Init(E65_RUNTIME_SDL_FLAGS)) {
			THROW_E65_RUNTIME_EXCEPTION_FORMAT(E65_RUNTIME_EXCEPTION_EXTERNAL, "SDL_Init failed! %s", SDL_GetError());
		}

		m_bus.initialize(context, length);
		e65::type::thread::start(true, context, length);

		E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Runtime initialized");

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
		uint32_t begin = 0, current = 0, previous = 0;

		E65_TRACE_ENTRY_FORMAT("Context[%u]=%p", length, context);

		E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Runtime main loop entry");

		while(e65::type::thread::active()) {
			float delta, rate;
			uint32_t end = SDL_GetTicks();

			rate = (end - begin);
			if(rate >= E65_MILLISECONDS_PER_SECOND) {
				rate = (current - ((rate - E65_MILLISECONDS_PER_SECOND) / E65_RUNTIME_FRAME_RATE));

				E65_TRACE_MESSAGE_FORMAT(e65::type::E65_LEVEL_INFORMATION, "Runtime framerate", "%.1f",
					(rate > 0.f) ? rate : 0.f);

				m_bus.video().display().set_frame_rate((rate > 0.f) ? rate : 0.f);
				begin = end;
				current = 0;
			}

			result = poll();
			if(!result) {
				break;
			}

			if(!m_debug) {
				previous = m_bus.step_frame(*this, previous);
			} else {

				if(!m_bus.video().display().hidden()) {
					m_bus.video().display().show();
				}
			}

			delta = (SDL_GetTicks() - end);
			if(delta < E65_RUNTIME_FRAME_DELTA) {
				SDL_Delay(E65_RUNTIME_FRAME_DELTA - delta);
			}

			++current;
		}

		E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Runtime main loop exit");

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

		E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Runtime starting");

		E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Runtime started");

		E65_TRACE_EXIT_FORMAT("Result=%x", result);
		return result;
	}

	void
	runtime::on_stop(void)
	{
		E65_TRACE_ENTRY();

		E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Runtime stopping");

		E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Runtime stopped");

		E65_TRACE_EXIT();
	}

	void
	runtime::on_uninitialize(void)
	{
		E65_TRACE_ENTRY();

		E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Runtime uninitializing");

		e65::type::thread::stop();

		m_bus.uninitialize();
		SDL_Quit();

		E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Runtime library destroyed");

		E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Runtime uninitialized");

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
						SDL_Scancode value;

						value = event.key.keysym.scancode;
						switch(value) {
							case E65_RUNTIME_SDL_FULLSCREEN_KEY:
								m_bus.video().display().set_fullscreen(!m_bus.video().display().fullscreen());
								break;
							case E65_RUNTIME_SDL_REFRESH_KEY:
								m_bus.video().display().show();
								break;
							default:
								m_bus.input().key(m_bus.memory(), value);
								break;
						}
					}
					break;
				case SDL_QUIT:
					E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Runtime quit event");
					result = false;
					break;
				default:
					break;
			}
		}

		E65_TRACE_EXIT_FORMAT("Result=%x", result);
		return result;
	}

	bool
	runtime::reset(void)
	{
		bool result = true;

		E65_TRACE_ENTRY();

		if(!e65::type::singleton<e65::runtime>::initialized()) {
			THROW_E65_RUNTIME_EXCEPTION(E65_RUNTIME_EXCEPTION_UNINITIALIZED);
		}

		m_bus.reset(*this);

		E65_TRACE_EXIT_FORMAT("Result=%x", result);
		return result;
	}

	void
	runtime::run(
		__in const std::string &path,
		__in bool hex,
		__in_opt bool debug
		)
	{
		int length;
		std::ifstream file;
		std::stringstream title;
		std::vector<uint8_t> data;

		E65_TRACE_ENTRY_FORMAT("Path[%u]=%s, Hex=%x, Debug=%x", path.size(), E65_STRING_CHECK(path), hex, debug);

		if(!e65::type::singleton<e65::runtime>::initialized()) {
			THROW_E65_RUNTIME_EXCEPTION(E65_RUNTIME_EXCEPTION_UNINITIALIZED);
		}

		E65_TRACE_MESSAGE_FORMAT(e65::type::E65_LEVEL_INFORMATION, "Runtime running", "%s, %s", debug ? "Debug" : "Normal",
			E65_STRING_CHECK(path));

		file = std::ifstream(path.c_str(), std::ios::binary | std::ios::in);
		if(!file) {
			THROW_E65_RUNTIME_EXCEPTION_FORMAT(E65_RUNTIME_EXCEPTION_FILE_NOT_FOUND, "%s", E65_STRING_CHECK(path));
		}

		file.seekg(0, std::ios::end);
		length = file.tellg();
		file.seekg(0, std::ios::beg);

		if(length >= 0) {
			data.resize(length);
			file.read((char *) &data[0], data.size());
		}

		file.close();

		if(length < 0) {
			THROW_E65_RUNTIME_EXCEPTION_FORMAT(E65_RUNTIME_EXCEPTION_FILE_MALFORMED, "%s", E65_STRING_CHECK(path));
		}

		m_bus.load(data, hex);

		m_debug = debug;
		title << E65 << " -- " << path << (m_debug ? " [Debug]" : "");
		m_bus.video().display().set_title(title.str());

		if(m_debug) {
			m_bus.video().display().set_hidden(true);
		}

		e65::type::thread::notify();

		E65_TRACE_EXIT();
	}

	bool
	runtime::running(void) const
	{
		bool result;

		E65_TRACE_ENTRY();

		if(!e65::type::singleton<e65::runtime>::initialized()) {
			THROW_E65_RUNTIME_EXCEPTION(E65_RUNTIME_EXCEPTION_UNINITIALIZED);
		}

		result = e65::type::thread::active();

		E65_TRACE_EXIT_FORMAT("Result=%x", result);
		return result;
	}

	bool
	runtime::step(
		__in uint32_t offset
		)
	{
		bool result;

		E65_TRACE_ENTRY_FORMAT("Offset=%u", offset);

		if(!e65::type::singleton<e65::runtime>::initialized()) {
			THROW_E65_RUNTIME_EXCEPTION(E65_RUNTIME_EXCEPTION_UNINITIALIZED);
		}

		result = m_debug;
		if(result) {
			uint32_t iter = 0;

			if(!offset) {
				offset = 1;
			}

			for(; iter < offset; ++iter) {

				result = (m_bus.step(*this) > 0);
				if(!result) {
					break;
				}
			}
		}

		E65_TRACE_EXIT_FORMAT("Result=%x", result);
		return result;
	}

	bool
	runtime::step_frame(
		__in uint32_t offset
		)
	{
		bool result;

		E65_TRACE_ENTRY_FORMAT("Offset=%u", offset);

		if(!e65::type::singleton<e65::runtime>::initialized()) {
			THROW_E65_RUNTIME_EXCEPTION(E65_RUNTIME_EXCEPTION_UNINITIALIZED);
		}

		result = m_debug;
		if(result) {
			uint32_t iter = 0;

			if(!offset) {
				offset = 1;
			}

			for(; iter < offset; ++iter) {

				result = (m_bus.step_frame(*this) != EXIT_FAILURE);
				if(!result) {
					break;
				}
			}
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
			<< " Interface=" << e65::type::singleton<e65::runtime>::to_string();

		if(e65::type::singleton<e65::runtime>::initialized()) {
			result << ", Thread=" << e65::type::thread::to_string()
				<< ", Bus=" << m_bus.to_string()
				<< ", Trace=" << m_trace.to_string()
				<< ", Mode=" << m_debug << "(" << (m_debug ? "Debug" : "Normal") << ")";
		}

		E65_TRACE_EXIT();
		return result.str();
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

		if(!e65::type::singleton<e65::runtime>::initialized()) {
			THROW_E65_RUNTIME_EXCEPTION(E65_RUNTIME_EXCEPTION_UNINITIALIZED);
		}

		result = !m_debug;
		if(result) {
			result = e65::type::thread::wait(timeout);
		}

		E65_TRACE_EXIT_FORMAT("Result=%x", result);
		return result;
	}
}
