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

#include <cstdarg>
#include "../include/trace.h"
#include "./trace_type.h"

namespace e65 {

	trace::trace(void) :
		e65::interface::singleton<e65::trace>(e65::interface::E65_SINGLETON_TRACE)
	{
		return;
	}

	trace::~trace(void)
	{
		return;
	}

	void
	trace::clear(void)
	{

		while(!m_queue.empty()) {
			dequeue();
		}
	}

	e65::trace_t
	trace::dequeue(void)
	{
		e65::trace_t result;
		std::lock_guard<std::mutex> lock(m_queue_mutex);

		if(m_queue.empty()) {
			THROW_E65_TRACE_EXCEPTION(E65_TRACE_EXCEPTION_EMPTY);
		}

		result = m_queue.front();
		m_queue.pop();

		return result;
	}

	bool
	trace::empty(void) const
	{

		if(!e65::interface::singleton<e65::trace>::initialized()) {
			THROW_E65_TRACE_EXCEPTION(E65_TRACE_EXCEPTION_UNINITIALIZED);
		}

		return m_queue.empty();
	}

	void
	trace::enqueue(
		__in const e65::trace_t &entry
		)
	{
		std::lock_guard<std::mutex> lock(m_queue_mutex);

		while(m_queue.size() >= E65_TRACE_QUEUE_MAX) {
			m_queue.pop();
		}

		m_queue.push(entry);
		e65::type::thread::notify();
	}

	void
	trace::flush(void)
	{

		if(!e65::interface::singleton<e65::trace>::initialized()) {
			THROW_E65_TRACE_EXCEPTION(E65_TRACE_EXCEPTION_UNINITIALIZED);
		}

		while(!m_queue.empty()) {
			process(dequeue());
		}
	}

	void
	trace::generate(
		__in int level,
		__in const std::string &prefix,
		__in const std::string &message,
		__in const std::string &file,
		__in const std::string &function,
		__in size_t line,
		__in const char *format,
		...
		)
	{
		std::time_t timestamp;
		std::stringstream result;

		timestamp = std::time(nullptr);

		result << prefix << message;

		if(format) {
			int length;
			va_list arguments;
			std::string buffer;

			va_start(arguments, format);
			length = std::vsnprintf(nullptr, 0, format, arguments);
			va_end(arguments);

			if(length > 0) {
				buffer.resize(++length);
				va_start(arguments, format);
				length = std::vsnprintf((char *) &buffer[0], buffer.size(), format, arguments);
				va_end(arguments);
			}

			if(length < 0) {
				buffer = E65_TRACE_EXCEPTION_STRING(E65_TRACE_EXCEPTION_MALFORMED);
			} else if(length > 0) {
				buffer.resize(length);
			}

			if(!buffer.empty()) {

				if(!result.str().empty()) {
					result << ": ";
				}

				result << buffer;
			}
		}

		enqueue(std::make_tuple(file, function, level, line, result.str(), timestamp));
	}

	bool
	trace::on_initialize(
		__in const void *context,
		__in size_t length
		)
	{
		bool result = true;

		e65::type::thread::start(true, context, length);

		return result;
	}

	bool
	trace::on_run(
		__in const void *context,
		__in size_t length
		)
	{
		bool result = true;

		flush();

		return result;
	}

	bool
	trace::on_start(
		__in const void *context,
		__in size_t length
		)
	{
		bool result = true;

		clear();

		return result;
	}

	void
	trace::on_stop(void)
	{
		flush();
	}

	void
	trace::on_uninitialize(void)
	{
		e65::type::thread::stop();
	}

	void
	trace::process(
		__in const e65::trace_t &entry
		)
	{
		int level;
		std::string buffer;
		std::stringstream result;

		level = E65_TRACE_VALUE(E65_TRACE_LEVEL, entry);

#ifdef TRACE_COLOR
		result << E65_LEVEL_COLOR(level);
#endif // TRACE_COLOR

		result << "[" << timestamp(E65_TRACE_VALUE(E65_TRACE_TIMESTAMP, entry)) << "] {" << E65_LEVEL_STRING(level) << "}";

		buffer = E65_TRACE_VALUE(E65_TRACE_MESSAGE, entry);
		if(!buffer.empty()) {
			result << " " << buffer;
		}

#ifndef NDEBUG
		result << " (";

		buffer = E65_TRACE_VALUE(E65_TRACE_FUNCTION, entry);
		if(!buffer.empty()) {
			result << buffer << ":";
		}

		buffer = E65_TRACE_VALUE(E65_TRACE_FILE, entry);
		if(!buffer.empty()) {
			result << buffer << ":";
		}

		result << E65_TRACE_VALUE(E65_TRACE_LINE, entry) << ")";
#endif // NDEBUG

#ifdef TRACE_COLOR
		result << E65_LEVEL_COLOR_RESET;
#endif // TRACE_COLOR

		switch(level) {
			case e65::type::E65_LEVEL_ERROR:
			case e65::type::E65_LEVEL_WARNING:
				std::cerr << result.str() << std::endl;
				break;
			default:
				std::cout << result.str() << std::endl;
				break;
		}
	}

	size_t
	trace::size(void) const
	{
		return m_queue.size();
	}

	std::string
	trace::timestamp(
		__in const std::time_t &time
		)
	{
		int length;
		std::string result;

		result.resize(E65_TRACE_TIMESTAMP_LENGTH);
		length = std::strftime((char *) &result[0], result.size(), E65_TRACE_TIMESTAMP_FORMAT, std::localtime(&time));

		if(length > 0) {
			result = result.substr(0, length);
		} else {
			result = E65_TRACE_EXCEPTION_STRING(E65_TRACE_EXCEPTION_MALFORMED);
		}

		return result;
	}

	std::string
	trace::to_string(void) const
	{
		std::stringstream result;

		result << E65_TRACE_HEADER << "(" << E65_STRING_HEX(uintptr_t, this) << ")"
			<< " Interface=" << e65::interface::singleton<e65::trace>::to_string();

		if(m_initialized) {
			result << ", Thread=" << e65::type::thread::to_string()
				<< ", Queue[" << m_queue.size() << "]=" << E65_STRING_HEX(uintptr_t, &m_queue);
		}

		return result.str();
	}
}
