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

#include <climits>
#include "../../include/system/bus.h"
#include "../../include/trace.h"
#include "./bus_type.h"

namespace e65 {

	namespace system {

		bus::bus(void) :
			e65::type::singleton<e65::system::bus>(e65::type::E65_SINGLETON_BUS),
			m_input(e65::system::input::acquire()),
			m_memory(e65::system::memory::acquire()),
			m_processor(e65::system::processor::acquire()),
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

			if(!e65::type::singleton<e65::system::bus>::initialized()) {
				THROW_E65_SYSTEM_BUS_EXCEPTION(E65_SYSTEM_BUS_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Bus clearing");

			m_memory.clear();
			m_input.clear(m_memory);
			m_video.clear(m_memory);

			E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Bus cleared");

			E65_TRACE_EXIT();
		}

		e65::interface::system::input &
		bus::input(void)
		{
			E65_TRACE_ENTRY();

			if(!e65::type::singleton<e65::system::bus>::initialized()) {
				THROW_E65_SYSTEM_BUS_EXCEPTION(E65_SYSTEM_BUS_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_EXIT();
			return m_input;
		}

		void
		bus::load(
			__in const std::vector<uint8_t> &data,
			__in bool hex,
			__in_opt uint16_t origin
			)
		{
			E65_TRACE_ENTRY_FORMAT("Data[%u]=%p, Hex=%x, Origin=%u(%04x)", data.size(), &data, hex, origin, origin);

			clear();

			E65_TRACE_MESSAGE_FORMAT(e65::type::E65_LEVEL_INFORMATION, "Bus loading", "%s, %.1f KB (%u bytes)", hex ? "Hex" : "Binary",
				data.size() / E65_BYTES_PER_KBYTE, data.size());

			if(hex) {
				load_hex(std::string(data.begin(), data.end()));
			} else {
				load_binary(data, origin);
			}

			m_processor.reset(m_memory);

			E65_TRACE_EXIT();
		}

		void
		bus::load_binary(
			__in const std::vector<uint8_t> &data,
			__in uint16_t origin
			)
		{
			E65_TRACE_ENTRY_FORMAT("Data[%u]=%p, Origin=%u(%04x)", data.size(), &data, origin, origin);

			if((data.size() + origin) > E65_MEMORY_LENGTH) {
				THROW_E65_SYSTEM_BUS_EXCEPTION_FORMAT(E65_SYSTEM_BUS_EXCEPTION_LENGTH,
					"%.1f KB (%u bytes) @%u(%04x)", data.size() / E65_BYTES_PER_KBYTE, data.size(), origin, origin);
			}

			m_memory.load(data, origin);

			E65_TRACE_EXIT();
		}

		void
		bus::load_hex(
			__in const std::string &data
			)
		{
			bool end = false;
			size_t count = 1;
			std::string line;
			std::stringstream stream;
			std::vector<std::pair<uint16_t, std::vector<uint8_t>>> section;
			std::vector<std::pair<uint16_t, std::vector<uint8_t>>>::iterator entry;

			E65_TRACE_ENTRY_FORMAT("Data[%u]=%p", data.size(), &data);

			if(data.empty()) {
				THROW_E65_SYSTEM_BUS_EXCEPTION(E65_SYSTEM_BUS_EXCEPTION_EMPTY);
			}

			stream << data;

			while(std::getline(stream, line)) {
				std::vector<uint8_t> data;
				std::stringstream substream;
				uint16_t address, length, type;

				if(line.empty()) {
					continue;
				}

				if(end) {
					THROW_E65_SYSTEM_BUS_EXCEPTION_FORMAT(E65_SYSTEM_BUS_EXCEPTION_END, "(line=%u)", count);
				}

				if(line.size() < E65_HEX_LENGTH_MIN) {
					THROW_E65_SYSTEM_BUS_EXCEPTION_FORMAT(E65_SYSTEM_BUS_EXCEPTION_LENGTH, "%u (minimum=%u) (line=%u)",
						line.size(), E65_HEX_LENGTH_MIN, count);
				}

				if(line.front() != E65_HEX_CHARACTER_START) {
					THROW_E65_SYSTEM_BUS_EXCEPTION_FORMAT(E65_SYSTEM_BUS_EXCEPTION_START,
						"\'%c\'(%02x) (expecting=\'%c\'(%02x)) (line=%u)", line.front(), line.front(),
						E65_HEX_CHARACTER_START, E65_HEX_CHARACTER_START, count);
				}

				substream << std::hex << line.substr(E65_HEX_LENGTH_ORIGIN, E65_HEX_LENGTH_OFFSET);
				substream >> length;

				if(line.size() < (length + E65_HEX_LENGTH_MIN)) {
					THROW_E65_SYSTEM_BUS_EXCEPTION_FORMAT(E65_SYSTEM_BUS_EXCEPTION_LENGTH, "%u (minimum=%u) (line=%u)",
						line.size(), (length + E65_HEX_LENGTH_MIN), count);
				}

				substream.clear();
				substream.str(std::string());
				substream << std::hex << line.substr(E65_HEX_ADDRESS_ORIGIN, E65_HEX_ADDRESS_OFFSET);
				substream >> address;

				substream.clear();
				substream.str(std::string());
				substream << std::hex << line.substr(E65_HEX_TYPE_ORIGIN, E65_HEX_TYPE_OFFSET);
				substream >> type;

				switch(type) {
					case E65_HEX_DATA:
						break;
					case E65_HEX_END:
						end = true;
						break;
					default:
						THROW_E65_SYSTEM_BUS_EXCEPTION_FORMAT(E65_SYSTEM_BUS_EXCEPTION_UNSUPPORTED, "%u(%02x) (line=%u)",
							type, type, count);
				}

				if(length) {
					uint16_t byte, checksum, iter = 0, sum;

					sum = (length + (address >> CHAR_BIT) + (address & UINT8_MAX) + type);

					for(; iter < length; ++iter) {
						substream.clear();
						substream.str(std::string());
						substream << std::hex << line.substr((iter * E65_HEX_DATA_OFFSET) + E65_HEX_DATA_ORIGIN,
							E65_HEX_DATA_OFFSET);
						substream >> byte;
						data.push_back(byte);
						sum += data.back();
					}

					substream.clear();
					substream.str(std::string());
					substream << std::hex << line.substr((length * E65_HEX_DATA_OFFSET) + E65_HEX_DATA_ORIGIN,
						E65_HEX_DATA_OFFSET);
					substream >> checksum;

					checksum &= UINT8_MAX;
					sum = (((~sum) + 1) & UINT8_MAX);

					if(sum != checksum) {
						THROW_E65_SYSTEM_BUS_EXCEPTION_FORMAT(E65_SYSTEM_BUS_EXCEPTION_CHECKSUM,
							"%u(%02x) (expecting=%u(%02x)) (line=%u)", sum, sum, checksum, checksum, count);
					}

					section.push_back(std::make_pair(address, data));
				}

				++count;
			}

			if(!end) {
				THROW_E65_SYSTEM_BUS_EXCEPTION_FORMAT(E65_SYSTEM_BUS_EXCEPTION_END, "(line=%u)", count);
			}

			for(entry = section.begin(); entry != section.end(); ++entry) {
				m_memory.load(entry->second, entry->first);
			}

			E65_TRACE_EXIT();
		}

		e65::interface::system::memory &
		bus::memory(void)
		{
			E65_TRACE_ENTRY();

			if(!e65::type::singleton<e65::system::bus>::initialized()) {
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

			E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Bus initializing");

			m_memory.initialize(context, length);
			m_input.initialize(context, length);
			m_processor.initialize(context, length);
			m_video.initialize(context, length);

			E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Bus initialized");

			E65_TRACE_EXIT_FORMAT("Result=%x", result);
			return result;
		}

		void
		bus::on_uninitialize(void)
		{
			E65_TRACE_ENTRY();

			E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Bus uninitializing");

			m_video.uninitialize();
			m_processor.uninitialize();
			m_input.uninitialize();
			m_memory.uninitialize();

			E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Bus uninitialized");

			E65_TRACE_EXIT();
		}

		e65::interface::system::processor &
		bus::processor(void)
		{
			E65_TRACE_ENTRY();

			if(!e65::type::singleton<e65::system::bus>::initialized()) {
				THROW_E65_SYSTEM_BUS_EXCEPTION(E65_SYSTEM_BUS_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_EXIT();
			return m_processor;
		}

		void
		bus::reset(
			__in e65::interface::runtime &runtime
			)
		{
			E65_TRACE_ENTRY_FORMAT("Runtime=%p", &runtime);

			m_input.step(m_memory);
			m_processor.reset(m_memory);
			m_video.step(m_memory);

			E65_TRACE_EXIT();
		}

		uint8_t
		bus::step(
			__in e65::interface::runtime &runtime
			)
		{
			uint8_t result;

			E65_TRACE_ENTRY_FORMAT("Runtime=%p", &runtime);

			m_input.step(m_memory);
			result = m_processor.step(m_memory);
			m_video.step(m_memory);

			E65_TRACE_EXIT_FORMAT("Result=%u", result);
			return result;
		}

		uint32_t
		bus::step_frame(
			__in e65::interface::runtime &runtime,
			__in_opt uint32_t previous
			)
		{
			int64_t remaining;
			uint32_t result = 0;

			E65_TRACE_ENTRY_FORMAT("Runtime=%p, Previous=%u", &runtime, previous);

			remaining = (E65_PROCESSOR_CYCLES_PER_FRAME - previous);

			E65_TRACE_MESSAGE_FORMAT(e65::type::E65_LEVEL_VERBOSE, "Frame", "[%u] Cycles=%u (Previous=%u)", m_video.frame(), remaining,
				previous);

			while(remaining > 0) {
				m_input.step(m_memory);
				remaining -= m_processor.step(m_memory);
			}

			m_video.step(m_memory);

			if(remaining < 0) {
				result = -remaining;
			}

			E65_TRACE_EXIT_FORMAT("Result=%u", result);
			return result;
		}

		std::string
		bus::to_string(void) const
		{
			std::stringstream result;

			E65_TRACE_ENTRY();

			result << E65_SYSTEM_BUS_HEADER << "(" << E65_STRING_HEX(uintptr_t, this) << ")"
				<< " Interface=" << e65::type::singleton<e65::system::bus>::to_string();

			if(e65::type::singleton<e65::system::bus>::initialized()) {
				result << ", Input=" << m_input.to_string()
					<< ", Memory=" << m_memory.to_string()
					<< ", Processor=" << m_processor.to_string()
					<< ", Video=" << m_video.to_string();
			}

			E65_TRACE_EXIT();
			return result.str();
		}

		e65::interface::system::video &
		bus::video(void)
		{
			E65_TRACE_ENTRY();

			if(!e65::type::singleton<e65::system::bus>::initialized()) {
				THROW_E65_SYSTEM_BUS_EXCEPTION(E65_SYSTEM_BUS_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_EXIT();
			return m_video;
		}
	}
}
