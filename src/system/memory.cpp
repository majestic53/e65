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
#include "../../include/system/memory.h"
#include "../../include/trace.h"
#include "./memory_type.h"

namespace e65 {

	namespace system {

		memory::memory(void) :
			e65::type::singleton<e65::system::memory>(e65::type::E65_SINGLETON_MEMORY)
		{
			E65_TRACE_ENTRY();
			E65_TRACE_EXIT();
		}

		memory::~memory(void)
		{
			E65_TRACE_ENTRY();
			E65_TRACE_EXIT();
		}

		void
		memory::clear(void)
		{
			E65_TRACE_ENTRY();

			if(!e65::type::singleton<e65::system::memory>::initialized()) {
				THROW_E65_SYSTEM_MEMORY_EXCEPTION(E65_SYSTEM_MEMORY_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Memory clearing");

			m_memory.resize(E65_MEMORY_LENGTH, E65_MEMORY_FILL);

			E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Memory cleared");

			E65_TRACE_EXIT();
		}

		void
		memory::load(
			__in const std::vector<uint8_t> &data,
			__in uint16_t origin
			)
		{
			size_t offset;

			E65_TRACE_ENTRY_FORMAT("Data[%u]=%p, Origin=%u(%04x)", data.size(), &data, origin, origin);

			if(!e65::type::singleton<e65::system::memory>::initialized()) {
				THROW_E65_SYSTEM_MEMORY_EXCEPTION(E65_SYSTEM_MEMORY_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_MESSAGE_FORMAT(e65::type::E65_LEVEL_INFORMATION, "Memory load", "%u(%04x), %.1f KB (%u bytes)", origin, origin,
				data.size() / E65_BYTES_PER_KBYTE, data.size());

			offset = (origin + data.size());
			if(offset > m_memory.size()) {
				THROW_E65_SYSTEM_MEMORY_EXCEPTION_FORMAT(E65_SYSTEM_MEMORY_EXCEPTION_OFFSET, "%u(%x)", offset, offset);
			}

			for(offset = 0; offset < data.size(); ++offset) {
				m_memory.at(origin + offset) = data.at(offset);
			}

			E65_TRACE_EXIT();
		}

		bool
		memory::on_initialize(
			__in const void *context,
			__in size_t length
			)
		{
			bool result = true;

			E65_TRACE_ENTRY_FORMAT("Context[%u]=%p", length, context);

			E65_TRACE_MESSAGE_FORMAT(e65::type::E65_LEVEL_INFORMATION, "Memory initializing", "%.1f KB (%u bytes)",
				E65_MEMORY_LENGTH / E65_BYTES_PER_KBYTE, E65_MEMORY_LENGTH);

			m_memory.resize(E65_MEMORY_LENGTH, E65_MEMORY_FILL);

			E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Memory initialized");

			E65_TRACE_EXIT_FORMAT("Result=%x", result);
			return result;
		}

		void
		memory::on_uninitialize(void)
		{
			E65_TRACE_ENTRY();

			E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Memory uninitializing");

			E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Memory uninitialized");

			E65_TRACE_EXIT();
		}

		uint8_t
		memory::read(
			__in uint16_t address
			) const
		{
			uint8_t result;

			E65_TRACE_ENTRY_FORMAT("%u(%04x)", address, address);

			if(!e65::type::singleton<e65::system::memory>::initialized()) {
				THROW_E65_SYSTEM_MEMORY_EXCEPTION(E65_SYSTEM_MEMORY_EXCEPTION_UNINITIALIZED);
			}

			if(address >= m_memory.size()) {
				THROW_E65_SYSTEM_MEMORY_EXCEPTION_FORMAT(E65_SYSTEM_MEMORY_EXCEPTION_ADDRESS, "%u(%04x)", address, address);
			}

			result = m_memory.at(address);

			E65_TRACE_EXIT_FORMAT("Result=%u(%02x)", result, result);
			return result;
		}

		uint16_t
		memory::read_word(
			__in uint16_t address
			) const
		{
			uint16_t result;

			E65_TRACE_ENTRY_FORMAT("%u(%04x)", address, address);

			if(!e65::type::singleton<e65::system::memory>::initialized()) {
				THROW_E65_SYSTEM_MEMORY_EXCEPTION(E65_SYSTEM_MEMORY_EXCEPTION_UNINITIALIZED);
			}

			if(address >= (m_memory.size() - 1)) {
				THROW_E65_SYSTEM_MEMORY_EXCEPTION_FORMAT(E65_SYSTEM_MEMORY_EXCEPTION_ADDRESS, "%u(%04x)", address, address);
			}

			result = m_memory.at(address);
			result |= (m_memory.at(address + 1) << CHAR_BIT);

			E65_TRACE_EXIT_FORMAT("Result=%u(%04x)", result, result);
			return result;
		}

		std::string
		memory::to_string(void) const
		{
			std::stringstream result;

			E65_TRACE_ENTRY();

			result << E65_SYSTEM_MEMORY_HEADER << "(" << E65_STRING_HEX(uintptr_t, this) << ")"
				<< " Interface=" << e65::type::singleton<e65::system::memory>::to_string();

			if(e65::type::singleton<e65::system::memory>::initialized()) {
				result << ", Memory[" << m_memory.size() << "]=" << E65_STRING_HEX(uintptr_t, &m_memory);
			}

			E65_TRACE_EXIT();
			return result.str();
		}

		void
		memory::write(
			__in uint16_t address,
			__in uint8_t value
			)
		{
			E65_TRACE_ENTRY_FORMAT("Address=%u(%04x), Value=%u(%02x)", address, address, value, value);

			if(!e65::type::singleton<e65::system::memory>::initialized()) {
				THROW_E65_SYSTEM_MEMORY_EXCEPTION(E65_SYSTEM_MEMORY_EXCEPTION_UNINITIALIZED);
			}

			if(address >= m_memory.size()) {
				THROW_E65_SYSTEM_MEMORY_EXCEPTION_FORMAT(E65_SYSTEM_MEMORY_EXCEPTION_ADDRESS, "%u(%04x)", address, address);
			}

			m_memory.at(address) = value;

			E65_TRACE_EXIT();
		}

		void
		memory::write_word(
			__in uint16_t address,
			__in uint16_t value
			)
		{
			E65_TRACE_ENTRY_FORMAT("Address=%u(%04x), Value=%u(%04x)", address, address, value, value);

			if(!e65::type::singleton<e65::system::memory>::initialized()) {
				THROW_E65_SYSTEM_MEMORY_EXCEPTION(E65_SYSTEM_MEMORY_EXCEPTION_UNINITIALIZED);
			}

			if(address >= (m_memory.size() - 1)) {
				THROW_E65_SYSTEM_MEMORY_EXCEPTION_FORMAT(E65_SYSTEM_MEMORY_EXCEPTION_ADDRESS, "%u(%04x)", address, address);
			}

			m_memory.at(address) = value;
			m_memory.at(address + 1) = (value >> CHAR_BIT);

			E65_TRACE_EXIT();
		}
	}
}
