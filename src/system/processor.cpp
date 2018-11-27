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
#include "../../include/system/processor.h"
#include "../../include/e65.h"
#include "../../include/trace.h"
#include "./processor_type.h"

namespace e65 {

	namespace system {

		processor::processor(void) :
			e65::type::singleton<e65::system::processor>(e65::type::E65_SINGLETON_PROCESSOR),
			m_accumulator(0),
			m_cycle(0),
			m_cycle_last(0),
			m_flags({}),
			m_index_x(0),
			m_index_y(0),
			m_interrupt_irq(false),
			m_interrupt_nmi(false),
			m_program_counter(0),
			m_stack_pointer(0),
			m_stop(false),
			m_wait(false)
		{
			E65_TRACE_ENTRY();
			E65_TRACE_EXIT();
		}

		processor::~processor(void)
		{
			E65_TRACE_ENTRY();
			E65_TRACE_EXIT();
		}

		uint8_t
		processor::accumulator(void) const
		{
			E65_TRACE_ENTRY();

			if(!e65::type::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_EXIT_FORMAT("Result=%u(%02x)", m_accumulator, m_accumulator);
			return m_accumulator;
		}

		uint16_t
		processor::calculate_address(
			__in e65::interface::system::memory &memory,
			__in int mode,
			__in uint16_t operand
			)
		{
			uint16_t result;
			bool boundary = false;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Mode=%i(%s), Operand=%u(%04x)", &memory, mode, E65_PCOMMAND_MODE_STRING(mode),
				operand, operand);

			result = calculate_address(memory, mode, operand, boundary);

			E65_TRACE_EXIT_FORMAT("Result=%u(%04x)", result, result);
			return result;
		}

		uint16_t
		processor::calculate_address(
			__in e65::interface::system::memory &memory,
			__in int mode,
			__in uint16_t operand,
			__inout bool &boundary
			)
		{
			int8_t relative;
			uint16_t indirect, result = 0;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Mode=%i(%s), Operand=%u(%04x), Boundary=%p", &memory, mode, E65_PCOMMAND_MODE_STRING(mode),
				operand, operand, &boundary);

			boundary = false;

			switch(mode) {
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE:
					result = operand;
					break;
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_INDIRECT:
					result = read_word(memory, operand + m_index_x);
					break;
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_X:
					result = (operand + m_index_x);
					boundary = (((operand & UINT8_MAX) + m_index_x) > UINT8_MAX);
					break;
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_Y:
					result = (operand + m_index_y);
					boundary = (((operand & UINT8_MAX) + m_index_y) > UINT8_MAX);
					break;
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDIRECT:
					result = read_word(memory, operand);
					break;
				case e65::type::E65_PCOMMAND_MODE_RELATIVE:
					relative = (operand & UINT8_MAX);
					result = (m_program_counter + relative);
					indirect = ((m_program_counter - e65::type::E65_PCOMMAND_LENGTH_BYTE) & UINT8_MAX);

					if(relative >= 0) {
						boundary = ((indirect + relative) > UINT8_MAX);
					} else {
						boundary = (indirect < -(relative + e65::type::E65_PCOMMAND_LENGTH_BYTE));
					}
					break;
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE:
					result = (operand & UINT8_MAX);
					break;
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_INDIRECT:

					result = ((operand & UINT8_MAX) + m_index_x);
					if(result > UINT8_MAX) {
						result %= UINT8_MAX;
						--result;
					}

					result = read_word(memory, result);
					break;
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_X:

					result = ((operand & UINT8_MAX) + m_index_x);
					if(result > UINT8_MAX) {
						result %= UINT8_MAX;
						--result;
					}
					break;
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_Y:

					result = ((operand & UINT8_MAX) + m_index_y);
					if(result > UINT8_MAX) {
						result %= UINT8_MAX;
						--result;
					}
					break;
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT:
					result = read_word(memory, operand & UINT8_MAX);
					break;
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT_INDEX:
					indirect = read_word(memory, operand & UINT8_MAX);
					result = (indirect + m_index_y);
					boundary = (((indirect & UINT8_MAX) + m_index_y) > UINT8_MAX);
					break;
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_RELATIVE:
					result = ((m_program_counter - e65::type::E65_PCOMMAND_LENGTH_WORD)
							+ (int8_t) ((operand >> CHAR_BIT) & UINT8_MAX));
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_MODE,
						"%i(%s)", mode, E65_PCOMMAND_MODE_STRING(mode));
			}

			E65_TRACE_EXIT_FORMAT("Result=%u(%04x)", result, result);
			return result;
		}

		uint8_t
		processor::calculate_cycles(
			__in int command,
			__in int mode,
			__in_opt bool secondary
			) const
		{
			uint8_t result;
			std::map<int, std::pair<uint8_t, uint8_t>>::const_iterator entry_command;
			std::map<int, std::map<int, std::pair<uint8_t, uint8_t>>>::const_iterator entry_mode;

			E65_TRACE_ENTRY_FORMAT("Command=%i(%s), Mode=%i(%s), Part=%x(%s)", command, E65_PCOMMAND_STRING(command),
				mode, E65_PCOMMAND_MODE_STRING(mode), secondary, secondary ? "Secondary" : "Primary");

			entry_mode = e65::type::E65_PCOMMAND_CYCLE_MAP.find(mode);
			if(entry_mode == e65::type::E65_PCOMMAND_CYCLE_MAP.end()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_MODE,
					"%i(%s) %i(%s)", command, E65_PCOMMAND_STRING(command), mode, E65_PCOMMAND_MODE_STRING(mode));
			}

			entry_command = entry_mode->second.find(command);
			if(entry_command == entry_mode->second.end()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_COMMAND,
					"%i(%s) %i(%s)", command, E65_PCOMMAND_STRING(command), mode, E65_PCOMMAND_MODE_STRING(mode));
			}

			result = (secondary ? entry_command->second.second : entry_command->second.first);

			E65_TRACE_EXIT_FORMAT("Result=%u(%02x)", result, result);
			return result;
		}

		uint32_t
		processor::cycle(void) const
		{
			E65_TRACE_ENTRY();

			if(!e65::type::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_EXIT_FORMAT("Result=%u", m_cycle);
			return m_cycle;
		}

		uint8_t
		processor::cycle_last(void) const
		{
			E65_TRACE_ENTRY();

			if(!e65::type::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_EXIT_FORMAT("Result=%u", m_cycle_last);
			return m_cycle_last;
		}

		bool
		processor::decode(
			__in uint8_t code,
			__inout int &command,
			__inout int &mode,
			__inout int &length
			)
		{
			bool result = false;
			std::map<uint8_t, std::pair<int, int>>::const_iterator entry_command;

			E65_TRACE_ENTRY_FORMAT("Code=%u(%02x), Command=%p, Mode=%p, Length=%p", code, code, &command, &mode, &length);

			entry_command = e65::type::E65_PCOMMAND_ID_MAP.find(code);
			if(entry_command != e65::type::E65_PCOMMAND_ID_MAP.end()) {
				std::map<int, int>::const_iterator entry_length;

				command = entry_command->second.first;
				mode = entry_command->second.second;

				entry_length = e65::type::E65_PCOMMAND_LENGTH_MAP.find(mode);
				if(entry_length != e65::type::E65_PCOMMAND_LENGTH_MAP.end()) {
					length = entry_length->second;
					result = true;
				}
			}

			E65_TRACE_EXIT_FORMAT("Result=%x", result);
			return result;
		}

		void
		processor::execute_adc(
			__in e65::interface::system::memory &memory,
			__in int mode,
			__in uint16_t operand
			)
		{
			uint8_t value = 0;
			bool boundary = false;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Mode=%i(%s), Operand=%u(%04x)", &memory, mode, E65_PCOMMAND_MODE_STRING(mode),
				operand, operand);

			switch(mode) {
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_X:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_Y:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_INDIRECT:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_X:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT_INDEX:
					value = read(memory, calculate_address(memory, mode, operand, boundary));
					break;
				case e65::type::E65_PCOMMAND_MODE_IMMEDIATE:
					value = operand;
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_MODE,
						"%s %s", E65_PCOMMAND_STRING(e65::type::E65_PCOMMAND_ADC), E65_PCOMMAND_MODE_STRING(mode));
			}

			// TODO: perform operation and set flags (also handle decimal mode)

			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_ADC, mode, boundary);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_and(
			__in e65::interface::system::memory &memory,
			__in int mode,
			__in uint16_t operand
			)
		{
			uint8_t value = 0;
			bool boundary = false;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Mode=%i(%s), Operand=%u(%04x)", &memory, mode, E65_PCOMMAND_MODE_STRING(mode),
				operand, operand);

			switch(mode) {
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_X:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_Y:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_INDIRECT:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_X:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT_INDEX:
					value = read(memory, calculate_address(memory, mode, operand, boundary));
					break;
				case e65::type::E65_PCOMMAND_MODE_IMMEDIATE:
					value = operand;
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_MODE,
						"%s %s", E65_PCOMMAND_STRING(e65::type::E65_PCOMMAND_AND), E65_PCOMMAND_MODE_STRING(mode));
			}

			m_accumulator &= value;
			m_flags.sign = (m_accumulator & E65_BIT_HIGH);
			m_flags.zero = (m_accumulator == 0);
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_AND, mode, boundary);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_asl(
			__in e65::interface::system::memory &memory,
			__in int mode,
			__in uint16_t operand
			)
		{
			uint8_t value = 0;
			uint16_t address = 0;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Mode=%i(%s), Operand=%u(%04x)", &memory, mode, E65_PCOMMAND_MODE_STRING(mode),
				operand, operand);

			switch(mode) {
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_X:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_X:
					address = calculate_address(memory, mode, operand);
					value = read(memory, address);
					break;
				case e65::type::E65_PCOMMAND_MODE_ACCUMULATOR:
					value = m_accumulator;
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_MODE,
						"%s %s", E65_PCOMMAND_STRING(e65::type::E65_PCOMMAND_ASL), E65_PCOMMAND_MODE_STRING(mode));
			}

			m_flags.carry = (value & E65_BIT_HIGH);
			value <<= 1;
			m_flags.sign = (value & E65_BIT_HIGH);
			m_flags.zero = (value == 0);

			switch(mode) {
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_X:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_X:
					write(memory, address, value);
					break;
				case e65::type::E65_PCOMMAND_MODE_ACCUMULATOR:
					m_accumulator = value;
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_MODE,
						"%s %s", E65_PCOMMAND_STRING(e65::type::E65_PCOMMAND_ASL), E65_PCOMMAND_MODE_STRING(mode));
			}

			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_ASL, mode);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_bbr(
			__in e65::interface::system::memory &memory,
			__in int command,
			__in uint16_t operand
			)
		{
			E65_TRACE_ENTRY_FORMAT("Memory=%p, Command=%i(%s), Operand=%u(%04x)", &memory, command, E65_PCOMMAND_STRING(command),
				operand, operand);

			switch(command) {
				case e65::type::E65_PCOMMAND_BBR0:
				case e65::type::E65_PCOMMAND_BBR1:
				case e65::type::E65_PCOMMAND_BBR2:
				case e65::type::E65_PCOMMAND_BBR3:
				case e65::type::E65_PCOMMAND_BBR4:
				case e65::type::E65_PCOMMAND_BBR5:
				case e65::type::E65_PCOMMAND_BBR6:
				case e65::type::E65_PCOMMAND_BBR7:

					if(!(read(memory, operand & UINT8_MAX) & E65_BIT(command - e65::type::E65_PCOMMAND_BBR0))) {
						m_program_counter = calculate_address(memory, e65::type::E65_PCOMMAND_MODE_ZEROPAGE_RELATIVE, operand);
					}
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_COMMAND,
						"%s %s", E65_PCOMMAND_STRING(command), e65::type::E65_PCOMMAND_MODE_ZEROPAGE_RELATIVE);
			}

			m_cycle_last += calculate_cycles(command, e65::type::E65_PCOMMAND_MODE_ZEROPAGE_RELATIVE);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_bbs(
			__in e65::interface::system::memory &memory,
			__in int command,
			__in uint16_t operand
			)
		{
			E65_TRACE_ENTRY_FORMAT("Memory=%p, Command=%i(%s), Operand=%u(%04x)", &memory, command, E65_PCOMMAND_STRING(command),
				operand, operand);

			switch(command) {
				case e65::type::E65_PCOMMAND_BBS0:
				case e65::type::E65_PCOMMAND_BBS1:
				case e65::type::E65_PCOMMAND_BBS2:
				case e65::type::E65_PCOMMAND_BBS3:
				case e65::type::E65_PCOMMAND_BBS4:
				case e65::type::E65_PCOMMAND_BBS5:
				case e65::type::E65_PCOMMAND_BBS6:
				case e65::type::E65_PCOMMAND_BBS7:

					if(read(memory, operand & UINT8_MAX) & E65_BIT(command - e65::type::E65_PCOMMAND_BBS0)) {
						m_program_counter = calculate_address(memory, e65::type::E65_PCOMMAND_MODE_ZEROPAGE_RELATIVE, operand);
					}
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_COMMAND,
						"%s %s", E65_PCOMMAND_STRING(command), e65::type::E65_PCOMMAND_MODE_ZEROPAGE_RELATIVE);
			}

			m_cycle_last += calculate_cycles(command, e65::type::E65_PCOMMAND_MODE_ZEROPAGE_RELATIVE);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_bcc(
			__in e65::interface::system::memory &memory,
			__in int8_t operand
			)
		{
			uint16_t address;
			bool boundary = false;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Operand=%i(%02x)", &memory, operand, operand);

			address = calculate_address(memory, e65::type::E65_PCOMMAND_MODE_RELATIVE, operand, boundary);

			if(!m_flags.carry) {
				m_program_counter = address;
				m_cycle_last += E65_PCOMMAND_RELATIVE_CYCLES_TAKEN;
			}

			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_BCC, e65::type::E65_PCOMMAND_MODE_RELATIVE, boundary);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_bcs(
			__in e65::interface::system::memory &memory,
			__in int8_t operand
			)
		{
			uint16_t address;
			bool boundary = false;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Operand=%i(%02x)", &memory, operand, operand);

			address = calculate_address(memory, e65::type::E65_PCOMMAND_MODE_RELATIVE, operand, boundary);

			if(m_flags.carry) {
				m_program_counter = address;
				m_cycle_last += E65_PCOMMAND_RELATIVE_CYCLES_TAKEN;
			}

			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_BCS, e65::type::E65_PCOMMAND_MODE_RELATIVE, boundary);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_beq(
			__in e65::interface::system::memory &memory,
			__in int8_t operand
			)
		{
			uint16_t address;
			bool boundary = false;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Operand=%i(%02x)", &memory, operand, operand);

			address = calculate_address(memory, e65::type::E65_PCOMMAND_MODE_RELATIVE, operand, boundary);

			if(m_flags.zero) {
				m_program_counter = address;
				m_cycle_last += E65_PCOMMAND_RELATIVE_CYCLES_TAKEN;
			}

			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_BEQ, e65::type::E65_PCOMMAND_MODE_RELATIVE, boundary);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_bit(
			__in e65::interface::system::memory &memory,
			__in int mode,
			__in uint16_t operand
			)
		{
			uint8_t value = 0;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Mode=%i(%s), Operand=%u(%04x)", &memory, mode, E65_PCOMMAND_MODE_STRING(mode),
				operand, operand);

			switch(mode) {
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_X:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_X:
					value = read(memory, calculate_address(memory, mode, operand));
					break;
				case e65::type::E65_PCOMMAND_MODE_IMMEDIATE:
					value = operand;
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_MODE,
						"%s %s", E65_PCOMMAND_STRING(e65::type::E65_PCOMMAND_BIT), E65_PCOMMAND_MODE_STRING(mode));
			}

			value &= m_accumulator;
			m_flags.overflow = (value & (E65_BIT_HIGH >> 1));
			m_flags.sign = (value & E65_BIT_HIGH);
			m_flags.zero = (value == 0);
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_BIT, mode);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_bmi(
			__in e65::interface::system::memory &memory,
			__in int8_t operand
			)
		{
			uint16_t address;
			bool boundary = false;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Operand=%i(%02x)", &memory, operand, operand);

			address = calculate_address(memory, e65::type::E65_PCOMMAND_MODE_RELATIVE, operand, boundary);

			if(m_flags.sign) {
				m_program_counter = address;
				m_cycle_last += E65_PCOMMAND_RELATIVE_CYCLES_TAKEN;
			}

			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_BMI, e65::type::E65_PCOMMAND_MODE_RELATIVE, boundary);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_bne(
			__in e65::interface::system::memory &memory,
			__in int8_t operand
			)
		{
			uint16_t address;
			bool boundary = false;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Operand=%i(%02x)", &memory, operand, operand);

			address = calculate_address(memory, e65::type::E65_PCOMMAND_MODE_RELATIVE, operand, boundary);

			if(!m_flags.zero) {
				m_program_counter = address;
				m_cycle_last += E65_PCOMMAND_RELATIVE_CYCLES_TAKEN;
			}

			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_BNE, e65::type::E65_PCOMMAND_MODE_RELATIVE, boundary);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_bpl(
			__in e65::interface::system::memory &memory,
			__in int8_t operand
			)
		{
			uint16_t address;
			bool boundary = false;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Operand=%i(%02x)", &memory, operand, operand);

			address = calculate_address(memory, e65::type::E65_PCOMMAND_MODE_RELATIVE, operand, boundary);

			if(!m_flags.sign) {
				m_program_counter = address;
				m_cycle_last += E65_PCOMMAND_RELATIVE_CYCLES_TAKEN;
			}

			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_BPL, e65::type::E65_PCOMMAND_MODE_RELATIVE, boundary);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_bra(
			__in e65::interface::system::memory &memory,
			__in int8_t operand
			)
		{
			bool boundary = false;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Operand=%i(%02x)", &memory, operand, operand);

			m_program_counter = calculate_address(memory, e65::type::E65_PCOMMAND_MODE_RELATIVE, operand, boundary);

			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_BRA, e65::type::E65_PCOMMAND_MODE_RELATIVE, boundary);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_brk(
			__in e65::interface::runtime &runtime,
			__in e65::interface::system::memory &memory
			)
		{
			E65_TRACE_ENTRY_FORMAT("Runtime=%p, Memory=%p", &runtime, &memory);

			m_flags.breakpoint = 1;
			push_word(memory, m_program_counter);
			push(memory, m_flags.raw);
			m_program_counter = read_word(memory, E65_PROCESSOR_ADDRESS_MASKABLE_INTERRUPT);
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_BRK, e65::type::E65_PCOMMAND_MODE_IMPLIED);
			runtime.signal_event(E65_EVENT_BREAK, m_program_counter);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_bvc(
			__in e65::interface::system::memory &memory,
			__in int8_t operand
			)
		{
			uint16_t address;
			bool boundary = false;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Operand=%i(%02x)", &memory, operand, operand);

			address = calculate_address(memory, e65::type::E65_PCOMMAND_MODE_RELATIVE, operand, boundary);

			if(!m_flags.overflow) {
				m_program_counter = address;
				m_cycle_last += E65_PCOMMAND_RELATIVE_CYCLES_TAKEN;
			}

			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_BVC, e65::type::E65_PCOMMAND_MODE_RELATIVE, boundary);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_bvs(
			__in e65::interface::system::memory &memory,
			__in int8_t operand
			)
		{
			uint16_t address;
			bool boundary = false;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Operand=%i(%02x)", &memory, operand, operand);

			address = calculate_address(memory, e65::type::E65_PCOMMAND_MODE_RELATIVE, operand, boundary);

			if(m_flags.overflow) {
				m_program_counter = address;
				m_cycle_last += E65_PCOMMAND_RELATIVE_CYCLES_TAKEN;
			}

			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_BVS, e65::type::E65_PCOMMAND_MODE_RELATIVE, boundary);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_clc(void)
		{
			E65_TRACE_ENTRY();

			m_flags.carry = 0;
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_CLC, e65::type::E65_PCOMMAND_MODE_IMPLIED);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_cld(void)
		{
			E65_TRACE_ENTRY();

			m_flags.decimal_enable = 0;
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_CLD, e65::type::E65_PCOMMAND_MODE_IMPLIED);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_cli(void)
		{
			E65_TRACE_ENTRY();

			m_flags.irq_disable = 0;
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_CLI, e65::type::E65_PCOMMAND_MODE_IMPLIED);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_clv(void)
		{
			E65_TRACE_ENTRY();

			m_flags.overflow = 0;
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_CLV, e65::type::E65_PCOMMAND_MODE_IMPLIED);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_cmp(
			__in e65::interface::system::memory &memory,
			__in int mode,
			__in uint16_t operand
			)
		{
			uint8_t value = 0;
			bool boundary = false;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Mode=%i(%s), Operand=%u(%04x)", &memory, mode, E65_PCOMMAND_MODE_STRING(mode),
				operand, operand);

			switch(mode) {
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_X:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_Y:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_INDIRECT:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_X:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT_INDEX:
					value = read(memory, calculate_address(memory, mode, operand, boundary));
					break;
				case e65::type::E65_PCOMMAND_MODE_IMMEDIATE:
					value = operand;
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_MODE,
						"%s %s", E65_PCOMMAND_STRING(e65::type::E65_PCOMMAND_CMP), E65_PCOMMAND_MODE_STRING(mode));
			}

			m_flags.carry = (m_accumulator >= value);
			m_flags.sign = ((m_accumulator - value) & E65_BIT_HIGH);
			m_flags.zero = (m_accumulator == value);
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_CMP, mode, boundary);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_cpx(
			__in e65::interface::system::memory &memory,
			__in int mode,
			__in uint16_t operand
			)
		{
			uint8_t value = 0;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Mode=%i(%s), Operand=%u(%04x)", &memory, mode, E65_PCOMMAND_MODE_STRING(mode),
				operand, operand);

			switch(mode) {
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE:
					value = read(memory, calculate_address(memory, mode, operand));
					break;
				case e65::type::E65_PCOMMAND_MODE_IMMEDIATE:
					value = operand;
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_MODE,
						"%s %s", E65_PCOMMAND_STRING(e65::type::E65_PCOMMAND_CPX), E65_PCOMMAND_MODE_STRING(mode));
			}

			m_flags.carry = (m_index_x >= value);
			m_flags.sign = ((m_index_x - value) & E65_BIT_HIGH);
			m_flags.zero = (m_index_x == value);
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_CPX, mode);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_cpy(
			__in e65::interface::system::memory &memory,
			__in int mode,
			__in uint16_t operand
			)
		{
			uint8_t value = 0;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Mode=%i(%s), Operand=%u(%04x)", &memory, mode, E65_PCOMMAND_MODE_STRING(mode),
				operand, operand);

			switch(mode) {
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE:
					value = read(memory, calculate_address(memory, mode, operand));
					break;
				case e65::type::E65_PCOMMAND_MODE_IMMEDIATE:
					value = operand;
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_MODE,
						"%s %s", E65_PCOMMAND_STRING(e65::type::E65_PCOMMAND_CPY), E65_PCOMMAND_MODE_STRING(mode));
			}

			m_flags.carry = (m_index_y >= value);
			m_flags.sign = ((m_index_y - value) & E65_BIT_HIGH);
			m_flags.zero = (m_index_y == value);
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_CPY, mode);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_dec(
			__in e65::interface::system::memory &memory,
			__in int mode,
			__in uint16_t operand
			)
		{
			uint8_t value = 0;
			uint16_t address = 0;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Mode=%i(%s), Operand=%u(%04x)", &memory, mode, E65_PCOMMAND_MODE_STRING(mode),
				operand, operand);

			switch(mode) {
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_X:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_X:
					address = calculate_address(memory, mode, operand);
					value = read(memory, address);
					break;
				case e65::type::E65_PCOMMAND_MODE_ACCUMULATOR:
					value = m_accumulator;
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_MODE,
						"%s %s", E65_PCOMMAND_STRING(e65::type::E65_PCOMMAND_DEC), E65_PCOMMAND_MODE_STRING(mode));
			}

			--value;
			m_flags.sign = (value & E65_BIT_HIGH);
			m_flags.zero = (value == 0);

			switch(mode) {
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_X:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_X:
					write(memory, address, value);
					break;
				case e65::type::E65_PCOMMAND_MODE_ACCUMULATOR:
					m_accumulator = value;
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_MODE,
						"%s %s", E65_PCOMMAND_STRING(e65::type::E65_PCOMMAND_DEC), E65_PCOMMAND_MODE_STRING(mode));
			}

			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_DEC, mode);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_dex(void)
		{
			E65_TRACE_ENTRY();

			--m_index_x;
			m_flags.sign = (m_index_x & E65_BIT_HIGH);
			m_flags.zero = (m_index_x == 0);
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_DEX, e65::type::E65_PCOMMAND_MODE_IMPLIED);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_dey(void)
		{
			E65_TRACE_ENTRY();

			--m_index_y;
			m_flags.sign = (m_index_y & E65_BIT_HIGH);
			m_flags.zero = (m_index_y == 0);
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_DEY, e65::type::E65_PCOMMAND_MODE_IMPLIED);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_eor(
			__in e65::interface::system::memory &memory,
			__in int mode,
			__in uint16_t operand
			)
		{
			uint8_t value = 0;
			bool boundary = false;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Mode=%i(%s), Operand=%u(%04x)", &memory, mode, E65_PCOMMAND_MODE_STRING(mode),
				operand, operand);

			switch(mode) {
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_X:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_Y:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_INDIRECT:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_X:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT_INDEX:
					value = read(memory, calculate_address(memory, mode, operand, boundary));
					break;
				case e65::type::E65_PCOMMAND_MODE_IMMEDIATE:
					value = operand;
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_MODE,
						"%s %s", E65_PCOMMAND_STRING(e65::type::E65_PCOMMAND_EOR), E65_PCOMMAND_MODE_STRING(mode));
			}

			m_accumulator ^= value;
			m_flags.sign = (m_accumulator & E65_BIT_HIGH);
			m_flags.zero = (m_accumulator == 0);
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_EOR, mode, boundary);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_inc(
			__in e65::interface::system::memory &memory,
			__in int mode,
			__in uint16_t operand
			)
		{
			uint8_t value = 0;
			uint16_t address = 0;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Mode=%i(%s), Operand=%u(%04x)", &memory, mode, E65_PCOMMAND_MODE_STRING(mode),
				operand, operand);

			switch(mode) {
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_X:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_X:
					address = calculate_address(memory, mode, operand);
					value = read(memory, address);
					break;
				case e65::type::E65_PCOMMAND_MODE_ACCUMULATOR:
					value = m_accumulator;
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_MODE,
						"%s %s", E65_PCOMMAND_STRING(e65::type::E65_PCOMMAND_INC), E65_PCOMMAND_MODE_STRING(mode));
			}

			++value;
			m_flags.sign = (value & E65_BIT_HIGH);
			m_flags.zero = (value == 0);

			switch(mode) {
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_X:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_X:
					write(memory, address, value);
					break;
				case e65::type::E65_PCOMMAND_MODE_ACCUMULATOR:
					m_accumulator = value;
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_MODE,
						"%s %s", E65_PCOMMAND_STRING(e65::type::E65_PCOMMAND_INC), E65_PCOMMAND_MODE_STRING(mode));
			}

			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_INC, mode);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_inx(void)
		{
			E65_TRACE_ENTRY();

			++m_index_x;
			m_flags.sign = (m_index_x & E65_BIT_HIGH);
			m_flags.zero = (m_index_x == 0);
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_INX, e65::type::E65_PCOMMAND_MODE_IMPLIED);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_iny(void)
		{
			E65_TRACE_ENTRY();

			++m_index_y;
			m_flags.sign = (m_index_y & E65_BIT_HIGH);
			m_flags.zero = (m_index_y == 0);
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_INY, e65::type::E65_PCOMMAND_MODE_IMPLIED);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_jmp(
			__in e65::interface::system::memory &memory,
			__in int mode,
			__in uint16_t operand
			)
		{
			uint16_t address = 0;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Mode=%i(%s), Operand=%u(%04x)", &memory, mode, E65_PCOMMAND_MODE_STRING(mode),
				operand, operand);

			switch(mode) {
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_INDIRECT:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDIRECT:
					address = calculate_address(memory, mode, operand);
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_MODE,
						"%s %s", E65_PCOMMAND_STRING(e65::type::E65_PCOMMAND_JMP), E65_PCOMMAND_MODE_STRING(mode));
			}

			m_program_counter = address;
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_JMP, mode);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_jsr(
			__in e65::interface::system::memory &memory,
			__in int mode,
			__in uint16_t operand
			)
		{
			uint16_t address = 0;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Mode=%i(%s), Operand=%u(%04x)", &memory, mode, E65_PCOMMAND_MODE_STRING(mode),
				operand, operand);

			switch(mode) {
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE:
					address = calculate_address(memory, mode, operand);
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_MODE,
						"%s %s", E65_PCOMMAND_STRING(e65::type::E65_PCOMMAND_JSR), E65_PCOMMAND_MODE_STRING(mode));
			}

			push_word(memory, m_program_counter - 1);
			m_program_counter = address;
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_JSR, mode);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_lda(
			__in e65::interface::system::memory &memory,
			__in int mode,
			__in uint16_t operand
			)
		{
			uint8_t value = 0;
			bool boundary = false;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Mode=%i(%s), Operand=%u(%04x)", &memory, mode, E65_PCOMMAND_MODE_STRING(mode),
				operand, operand);

			switch(mode) {
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_X:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_Y:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_INDIRECT:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_X:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT_INDEX:
					value = read(memory, calculate_address(memory, mode, operand, boundary));
					break;
				case e65::type::E65_PCOMMAND_MODE_IMMEDIATE:
					value = operand;
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_MODE,
						"%s %s", E65_PCOMMAND_STRING(e65::type::E65_PCOMMAND_LDA), E65_PCOMMAND_MODE_STRING(mode));
			}

			m_accumulator = value;
			m_flags.sign = (m_accumulator & E65_BIT_HIGH);
			m_flags.zero = (m_accumulator == 0);
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_LDA, mode, boundary);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_ldx(
			__in e65::interface::system::memory &memory,
			__in int mode,
			__in uint16_t operand
			)
		{
			uint8_t value = 0;
			bool boundary = false;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Mode=%i(%s), Operand=%u(%04x)", &memory, mode, E65_PCOMMAND_MODE_STRING(mode),
				operand, operand);

			switch(mode) {
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_Y:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_Y:
					value = read(memory, calculate_address(memory, mode, operand, boundary));
					break;
				case e65::type::E65_PCOMMAND_MODE_IMMEDIATE:
					value = operand;
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_MODE,
						"%s %s", E65_PCOMMAND_STRING(e65::type::E65_PCOMMAND_LDX), E65_PCOMMAND_MODE_STRING(mode));
			}

			m_index_x = value;
			m_flags.sign = (m_index_x & E65_BIT_HIGH);
			m_flags.zero = (m_index_x == 0);
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_LDX, mode, boundary);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_ldy(
			__in e65::interface::system::memory &memory,
			__in int mode,
			__in uint16_t operand
			)
		{
			uint8_t value = 0;
			bool boundary = false;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Mode=%i(%s), Operand=%u(%04x)", &memory, mode, E65_PCOMMAND_MODE_STRING(mode),
				operand, operand);

			switch(mode) {
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_X:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_X:
					value = read(memory, calculate_address(memory, mode, operand, boundary));
					break;
				case e65::type::E65_PCOMMAND_MODE_IMMEDIATE:
					value = operand;
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_MODE,
						"%s %s", E65_PCOMMAND_STRING(e65::type::E65_PCOMMAND_LDY), E65_PCOMMAND_MODE_STRING(mode));
			}

			m_index_y = value;
			m_flags.sign = (m_index_y & E65_BIT_HIGH);
			m_flags.zero = (m_index_y == 0);
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_LDY, mode, boundary);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_lsr(
			__in e65::interface::system::memory &memory,
			__in int mode,
			__in uint16_t operand
			)
		{
			uint8_t value = 0;
			uint16_t address = 0;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Mode=%i(%s), Operand=%u(%04x)", &memory, mode, E65_PCOMMAND_MODE_STRING(mode),
				operand, operand);

			switch(mode) {
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_X:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_X:
					address = calculate_address(memory, mode, operand);
					value = read(memory, address);
					break;
				case e65::type::E65_PCOMMAND_MODE_ACCUMULATOR:
					value = m_accumulator;
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_MODE,
						"%s %s", E65_PCOMMAND_STRING(e65::type::E65_PCOMMAND_LSR), E65_PCOMMAND_MODE_STRING(mode));
			}

			m_flags.carry = (value & E65_BIT_LOW);
			value >>= 1;
			m_flags.sign = (value & E65_BIT_HIGH);
			m_flags.zero = (value == 0);

			switch(mode) {
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_X:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_X:
					write(memory, address, value);
					break;
				case e65::type::E65_PCOMMAND_MODE_ACCUMULATOR:
					m_accumulator = value;
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_MODE,
						"%s %s", E65_PCOMMAND_STRING(e65::type::E65_PCOMMAND_LSR), E65_PCOMMAND_MODE_STRING(mode));
			}

			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_LSR, mode);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_nop(void)
		{
			E65_TRACE_ENTRY();

			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_NOP, e65::type::E65_PCOMMAND_MODE_IMPLIED);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_ora(
			__in e65::interface::system::memory &memory,
			__in int mode,
			__in uint16_t operand
			)
		{
			uint8_t value = 0;
			bool boundary = false;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Mode=%i(%s), Operand=%u(%04x)", &memory, mode, E65_PCOMMAND_MODE_STRING(mode),
				operand, operand);

			switch(mode) {
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_X:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_Y:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_INDIRECT:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_X:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT_INDEX:
					value = read(memory, calculate_address(memory, mode, operand, boundary));
					break;
				case e65::type::E65_PCOMMAND_MODE_IMMEDIATE:
					value = operand;
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_MODE,
						"%s %s", E65_PCOMMAND_STRING(e65::type::E65_PCOMMAND_ORA), E65_PCOMMAND_MODE_STRING(mode));
			}

			m_accumulator |= value;
			m_flags.sign = (m_accumulator & E65_BIT_HIGH);
			m_flags.zero = (m_accumulator == 0);
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_ORA, mode, boundary);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_pha(
			__in e65::interface::system::memory &memory
			)
		{
			E65_TRACE_ENTRY_FORMAT("Memory=%p", &memory);

			push(memory, m_accumulator);
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_PHA, e65::type::E65_PCOMMAND_MODE_IMPLIED);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_php(
			__in e65::interface::system::memory &memory
			)
		{
			E65_TRACE_ENTRY_FORMAT("Memory=%p", &memory);

			push(memory, m_flags.raw);
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_PHP, e65::type::E65_PCOMMAND_MODE_IMPLIED);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_phx(
			__in e65::interface::system::memory &memory
			)
		{
			E65_TRACE_ENTRY_FORMAT("Memory=%p", &memory);

			push(memory, m_index_x);
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_PHX, e65::type::E65_PCOMMAND_MODE_IMPLIED);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_phy(
			__in e65::interface::system::memory &memory
			)
		{
			E65_TRACE_ENTRY_FORMAT("Memory=%p", &memory);

			push(memory, m_index_y);
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_PHY, e65::type::E65_PCOMMAND_MODE_IMPLIED);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_pla(
			__in e65::interface::system::memory &memory
			)
		{
			E65_TRACE_ENTRY_FORMAT("Memory=%p", &memory);

			m_accumulator = pop(memory);
			m_flags.sign = (m_accumulator & E65_BIT_HIGH);
			m_flags.zero = (m_accumulator == 0);
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_PLA, e65::type::E65_PCOMMAND_MODE_IMPLIED);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_plp(
			__in e65::interface::system::memory &memory
			)
		{
			E65_TRACE_ENTRY_FORMAT("Memory=%p", &memory);

			m_flags.raw = pop(memory);
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_PLP, e65::type::E65_PCOMMAND_MODE_IMPLIED);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_plx(
			__in e65::interface::system::memory &memory
			)
		{
			E65_TRACE_ENTRY_FORMAT("Memory=%p", &memory);

			m_index_x = pop(memory);
			m_flags.sign = (m_index_x & E65_BIT_HIGH);
			m_flags.zero = (m_index_x == 0);
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_PLX, e65::type::E65_PCOMMAND_MODE_IMPLIED);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_ply(
			__in e65::interface::system::memory &memory
			)
		{
			E65_TRACE_ENTRY_FORMAT("Memory=%p", &memory);

			m_index_y = pop(memory);
			m_flags.sign = (m_index_y & E65_BIT_HIGH);
			m_flags.zero = (m_index_y == 0);
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_PLY, e65::type::E65_PCOMMAND_MODE_IMPLIED);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_rmb(
			__in e65::interface::system::memory &memory,
			__in int command,
			__in uint16_t operand
			)
		{
			uint8_t address, value;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Command=%i(%s), Operand=%u(%04x)", &memory, command, E65_PCOMMAND_STRING(command),
				operand, operand);

			address = (operand & UINT8_MAX);
			value = read(memory, address);

			switch(command) {
				case e65::type::E65_PCOMMAND_RMB0:
				case e65::type::E65_PCOMMAND_RMB1:
				case e65::type::E65_PCOMMAND_RMB2:
				case e65::type::E65_PCOMMAND_RMB3:
				case e65::type::E65_PCOMMAND_RMB4:
				case e65::type::E65_PCOMMAND_RMB5:
				case e65::type::E65_PCOMMAND_RMB6:
				case e65::type::E65_PCOMMAND_RMB7:
					value &= ~E65_BIT(command - e65::type::E65_PCOMMAND_RMB0);
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_COMMAND,
						"%s %s", E65_PCOMMAND_STRING(command), e65::type::E65_PCOMMAND_MODE_ZEROPAGE);
			}

			write(memory, address, value);
			m_cycle_last += calculate_cycles(command, e65::type::E65_PCOMMAND_MODE_ZEROPAGE);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_rol(
			__in e65::interface::system::memory &memory,
			__in int mode,
			__in uint16_t operand
			)
		{
			uint16_t address = 0;
			uint8_t carry, value = 0;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Mode=%i(%s), Operand=%u(%04x)", &memory, mode, E65_PCOMMAND_MODE_STRING(mode),
				operand, operand);

			switch(mode) {
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_X:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_X:
					address = calculate_address(memory, mode, operand);
					value = read(memory, address);
					break;
				case e65::type::E65_PCOMMAND_MODE_ACCUMULATOR:
					value = m_accumulator;
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_MODE,
						"%s %s", E65_PCOMMAND_STRING(e65::type::E65_PCOMMAND_ROL), E65_PCOMMAND_MODE_STRING(mode));
			}

			carry = m_flags.carry;
			m_flags.carry = (value & E65_BIT_HIGH);
			value <<= 1;

			if(carry) {
				value |= E65_BIT_LOW;
			}

			m_flags.sign = (value & E65_BIT_HIGH);
			m_flags.zero = (value == 0);

			switch(mode) {
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_X:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_X:
					write(memory, address, value);
					break;
				case e65::type::E65_PCOMMAND_MODE_ACCUMULATOR:
					m_accumulator = value;
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_MODE,
						"%s %s", E65_PCOMMAND_STRING(e65::type::E65_PCOMMAND_ROL), E65_PCOMMAND_MODE_STRING(mode));
			}

			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_ROL, mode);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_ror(
			__in e65::interface::system::memory &memory,
			__in int mode,
			__in uint16_t operand
			)
		{
			uint16_t address = 0;
			uint8_t carry, value = 0;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Mode=%i(%s), Operand=%u(%04x)", &memory, mode, E65_PCOMMAND_MODE_STRING(mode),
				operand, operand);

			switch(mode) {
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_X:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_X:
					address = calculate_address(memory, mode, operand);
					value = read(memory, address);
					break;
				case e65::type::E65_PCOMMAND_MODE_ACCUMULATOR:
					value = m_accumulator;
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_MODE,
						"%s %s", E65_PCOMMAND_STRING(e65::type::E65_PCOMMAND_ROR), E65_PCOMMAND_MODE_STRING(mode));
			}

			carry = m_flags.carry;
			m_flags.carry = (value & E65_BIT_LOW);
			value >>= 1;

			if(carry) {
				value |= E65_BIT_HIGH;
			}

			m_flags.sign = (value & E65_BIT_HIGH);
			m_flags.zero = (value == 0);

			switch(mode) {
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_X:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_X:
					write(memory, address, value);
					break;
				case e65::type::E65_PCOMMAND_MODE_ACCUMULATOR:
					m_accumulator = value;
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_MODE,
						"%s %s", E65_PCOMMAND_STRING(e65::type::E65_PCOMMAND_ROR), E65_PCOMMAND_MODE_STRING(mode));
			}

			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_ROR, mode);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_rti(
			__in e65::interface::system::memory &memory
			)
		{
			E65_TRACE_ENTRY_FORMAT("Memory=%p", &memory);

			m_flags.raw = pop(memory);
			m_program_counter = pop_word(memory);
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_RTI, e65::type::E65_PCOMMAND_MODE_IMPLIED);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_rts(
			__in e65::interface::system::memory &memory
			)
		{
			E65_TRACE_ENTRY_FORMAT("Memory=%p", &memory);

			m_program_counter = (pop_word(memory) + 1);
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_RTS, e65::type::E65_PCOMMAND_MODE_IMPLIED);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_sbc(
			__in e65::interface::system::memory &memory,
			__in int mode,
			__in uint16_t operand
			)
		{
			uint8_t value = 0;
			bool boundary = false;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Mode=%i(%s), Operand=%u(%04x)", &memory, mode, E65_PCOMMAND_MODE_STRING(mode),
				operand, operand);

			switch(mode) {
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_X:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_Y:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_INDIRECT:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_X:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT_INDEX:
					value = read(memory, calculate_address(memory, mode, operand, boundary));
					break;
				case e65::type::E65_PCOMMAND_MODE_IMMEDIATE:
					value = operand;
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_MODE,
						"%s %s", E65_PCOMMAND_STRING(e65::type::E65_PCOMMAND_SBC), E65_PCOMMAND_MODE_STRING(mode));
			}

			// TODO: perform operation and set flags (also handle decimal mode)

			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_SBC, mode, boundary);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_sec(void)
		{
			E65_TRACE_ENTRY();

			m_flags.carry = 1;
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_SEC, e65::type::E65_PCOMMAND_MODE_IMPLIED);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_sed(void)
		{
			E65_TRACE_ENTRY();

			m_flags.decimal_enable = 1;
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_SED, e65::type::E65_PCOMMAND_MODE_IMPLIED);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_sei(void)
		{
			E65_TRACE_ENTRY();

			m_flags.irq_disable = 1;
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_SEI, e65::type::E65_PCOMMAND_MODE_IMPLIED);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_smb(
			__in e65::interface::system::memory &memory,
			__in int command,
			__in uint16_t operand
			)
		{
			uint8_t address, value;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Command=%i(%s), Operand=%u(%04x)", &memory, command, E65_PCOMMAND_STRING(command),
				operand, operand);

			address = (operand & UINT8_MAX);
			value = read(memory, address);

			switch(command) {
				case e65::type::E65_PCOMMAND_SMB0:
				case e65::type::E65_PCOMMAND_SMB1:
				case e65::type::E65_PCOMMAND_SMB2:
				case e65::type::E65_PCOMMAND_SMB3:
				case e65::type::E65_PCOMMAND_SMB4:
				case e65::type::E65_PCOMMAND_SMB5:
				case e65::type::E65_PCOMMAND_SMB6:
				case e65::type::E65_PCOMMAND_SMB7:
					value |= E65_BIT(command - e65::type::E65_PCOMMAND_SMB0);
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_COMMAND,
						"%s %s", E65_PCOMMAND_STRING(command), e65::type::E65_PCOMMAND_MODE_ZEROPAGE);
			}

			write(memory, address, value);
			m_cycle_last += calculate_cycles(command, e65::type::E65_PCOMMAND_MODE_ZEROPAGE);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_sta(
			__in e65::interface::system::memory &memory,
			__in int mode,
			__in uint16_t operand
			)
		{
			E65_TRACE_ENTRY_FORMAT("Memory=%p, Mode=%i(%s), Operand=%u(%04x)", &memory, mode, E65_PCOMMAND_MODE_STRING(mode),
				operand, operand);

			switch(mode) {
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_X:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_Y:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_INDIRECT:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_X:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT_INDEX:
					write(memory, calculate_address(memory, mode, operand), m_accumulator);
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_MODE,
						"%s %s", E65_PCOMMAND_STRING(e65::type::E65_PCOMMAND_STA), E65_PCOMMAND_MODE_STRING(mode));
			}

			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_STA, mode);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_stp(void)
		{
			E65_TRACE_ENTRY();

			E65_TRACE_MESSAGE(e65::type::E65_LEVEL_WARNING, "Processor stopped");

			m_stop = true;
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_STP, e65::type::E65_PCOMMAND_MODE_IMPLIED);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_stx(
			__in e65::interface::system::memory &memory,
			__in int mode,
			__in uint16_t operand
			)
		{
			E65_TRACE_ENTRY_FORMAT("Memory=%p, Mode=%i(%s), Operand=%u(%04x)", &memory, mode, E65_PCOMMAND_MODE_STRING(mode),
				operand, operand);

			switch(mode) {
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_Y:
					write(memory, calculate_address(memory, mode, operand), m_index_x);
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_MODE,
						"%s %s", E65_PCOMMAND_STRING(e65::type::E65_PCOMMAND_STX), E65_PCOMMAND_MODE_STRING(mode));
			}

			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_STX, mode);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_sty(
			__in e65::interface::system::memory &memory,
			__in int mode,
			__in uint16_t operand
			)
		{
			E65_TRACE_ENTRY_FORMAT("Memory=%p, Mode=%i(%s), Operand=%u(%04x)", &memory, mode, E65_PCOMMAND_MODE_STRING(mode),
				operand, operand);

			switch(mode) {
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_X:
					write(memory, calculate_address(memory, mode, operand), m_index_y);
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_MODE,
						"%s %s", E65_PCOMMAND_STRING(e65::type::E65_PCOMMAND_STY), E65_PCOMMAND_MODE_STRING(mode));
			}

			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_STY, mode);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_stz(
			__in e65::interface::system::memory &memory,
			__in int mode,
			__in uint16_t operand
			)
		{
			E65_TRACE_ENTRY_FORMAT("Memory=%p, Mode=%i(%s), Operand=%u(%04x)", &memory, mode, E65_PCOMMAND_MODE_STRING(mode),
				operand, operand);

			switch(mode) {
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_X:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_X:
					write(memory, calculate_address(memory, mode, operand), 0);
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_MODE,
						"%s %s", E65_PCOMMAND_STRING(e65::type::E65_PCOMMAND_STZ), E65_PCOMMAND_MODE_STRING(mode));
			}

			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_STZ, mode);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_tax(void)
		{
			E65_TRACE_ENTRY();

			m_index_x = m_accumulator;
			m_flags.sign = (m_index_x & E65_BIT_HIGH);
			m_flags.zero = (m_index_x == 0);
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_TAX, e65::type::E65_PCOMMAND_MODE_IMPLIED);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_tay(void)
		{
			E65_TRACE_ENTRY();

			m_index_y = m_accumulator;
			m_flags.sign = (m_index_y & E65_BIT_HIGH);
			m_flags.zero = (m_index_y == 0);
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_TAY, e65::type::E65_PCOMMAND_MODE_IMPLIED);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_trb(
			__in e65::interface::system::memory &memory,
			__in int mode,
			__in uint16_t operand
			)
		{
			uint8_t value = 0;
			uint16_t address = 0;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Mode=%i(%s), Operand=%u(%04x)", &memory, mode, E65_PCOMMAND_MODE_STRING(mode),
				operand, operand);

			switch(mode) {
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE:
					address = calculate_address(memory, mode, operand);
					value = read(memory, address);
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_MODE,
						"%s %s", E65_PCOMMAND_STRING(e65::type::E65_PCOMMAND_TRB), E65_PCOMMAND_MODE_STRING(mode));
			}

			m_flags.zero = (m_accumulator & value);
			value &= ~m_accumulator;

			switch(mode) {
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE:
					write(memory, address, value);
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_MODE,
						"%s %s", E65_PCOMMAND_STRING(e65::type::E65_PCOMMAND_TRB), E65_PCOMMAND_MODE_STRING(mode));
			}

			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_TRB, mode);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_tsb(
			__in e65::interface::system::memory &memory,
			__in int mode,
			__in uint16_t operand
			)
		{
			uint8_t value = 0;
			uint16_t address = 0;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Mode=%i(%s), Operand=%u(%04x)", &memory, mode, E65_PCOMMAND_MODE_STRING(mode),
				operand, operand);

			switch(mode) {
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE:
					address = calculate_address(memory, mode, operand);
					value = read(memory, address);
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_MODE,
						"%s %s", E65_PCOMMAND_STRING(e65::type::E65_PCOMMAND_TSB), E65_PCOMMAND_MODE_STRING(mode));
			}

			m_flags.zero = (m_accumulator & value);
			value |= m_accumulator;

			switch(mode) {
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE:
					write(memory, address, value);
					break;
				default:
					THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_MODE,
						"%s %s", E65_PCOMMAND_STRING(e65::type::E65_PCOMMAND_TSB), E65_PCOMMAND_MODE_STRING(mode));
			}

			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_TSB, mode);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_tsx(void)
		{
			E65_TRACE_ENTRY();

			m_index_x = m_stack_pointer;
			m_flags.sign = (m_index_x & E65_BIT_HIGH);
			m_flags.zero = (m_index_x == 0);
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_TSX, e65::type::E65_PCOMMAND_MODE_IMPLIED);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_txa(void)
		{
			E65_TRACE_ENTRY();

			m_accumulator = m_index_x;
			m_flags.sign = (m_accumulator & E65_BIT_HIGH);
			m_flags.zero = (m_accumulator == 0);
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_TXA, e65::type::E65_PCOMMAND_MODE_IMPLIED);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_txs(void)
		{
			E65_TRACE_ENTRY();

			m_stack_pointer = m_index_x;
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_TXS, e65::type::E65_PCOMMAND_MODE_IMPLIED);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_tya(void)
		{
			E65_TRACE_ENTRY();

			m_accumulator = m_index_y;
			m_flags.sign = (m_accumulator & E65_BIT_HIGH);
			m_flags.zero = (m_accumulator == 0);
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_TYA, e65::type::E65_PCOMMAND_MODE_IMPLIED);

			E65_TRACE_EXIT();
		}

		void
		processor::execute_wai(void)
		{
			E65_TRACE_ENTRY();

			E65_TRACE_MESSAGE(e65::type::E65_LEVEL_WARNING, "Processor waiting for interrupt");

			m_wait = true;
			m_cycle_last += calculate_cycles(e65::type::E65_PCOMMAND_WAI, e65::type::E65_PCOMMAND_MODE_IMPLIED);

			E65_TRACE_EXIT();
		}

		uint8_t
		processor::flags(void) const
		{
			E65_TRACE_ENTRY();

			if(!e65::type::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_EXIT_FORMAT("Result=%u(%02x)", m_flags.raw, m_flags.raw);
			return m_flags.raw;
		}

		uint8_t
		processor::index_x(void) const
		{
			E65_TRACE_ENTRY();

			if(!e65::type::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_EXIT_FORMAT("Result=%u(%02x)", m_index_x, m_index_x);
			return m_index_x;
		}

		uint8_t
		processor::index_y(void) const
		{
			E65_TRACE_ENTRY();

			if(!e65::type::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_EXIT_FORMAT("Result=%u(%02x)", m_index_y, m_index_y);
			return m_index_y;
		}

		void
		processor::interrupt(
			__in bool maskable
			)
		{
			E65_TRACE_ENTRY_FORMAT("Type=%s", maskable ? "IRQ" : "NMI");

			if(!e65::type::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			if(!maskable || !m_flags.irq_disable) {

				if(maskable) {
					E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Processor IRQ interrupt request");
					m_interrupt_irq = true;
				} else {
					E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Processor NMI interrupt request");
					m_interrupt_nmi = true;
				}
			}

			E65_TRACE_EXIT();
		}

		bool
		processor::interrupted(
			__in bool maskable
			) const
		{
			bool result;

			E65_TRACE_ENTRY_FORMAT("Type=%s", maskable ? "IRQ" : "NMI");

			if(!e65::type::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			if(maskable) {
				result = m_interrupt_irq;
			} else {
				result = m_interrupt_nmi;
			}

			E65_TRACE_EXIT_FORMAT("Result=%x", result);
			return result;
		}

		bool
		processor::on_initialize(
			__in const void *context,
			__in size_t length
			)
		{
			bool result = true;

			E65_TRACE_ENTRY_FORMAT("Context[%u]=%p", length, context);

			E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Processor initializing");

			E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Processor initialized");

			E65_TRACE_EXIT_FORMAT("Result=%x", result);
			return result;
		}

		void
		processor::on_uninitialize(void)
		{
			E65_TRACE_ENTRY();

			E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Processor uninitializing");

			E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Processor uninitialized");

			E65_TRACE_EXIT();
		}

		uint8_t
		processor::pop(
			__in e65::interface::system::memory &memory
			)
		{
			uint8_t result;

			E65_TRACE_ENTRY_FORMAT("Memory=%p", &memory);

			result = read(memory, E65_PROCESSOR_REGISTER_STACK_POINTER_BASE + ++m_stack_pointer);

			E65_TRACE_EXIT_FORMAT("Result=%u(%02x)", result, result);
			return result;
		}

		uint16_t
		processor::pop_word(
			__in e65::interface::system::memory &memory
			)
		{
			uint16_t result = 0;

			E65_TRACE_ENTRY_FORMAT("Memory=%p", &memory);

			result |= read(memory, E65_PROCESSOR_REGISTER_STACK_POINTER_BASE + ++m_stack_pointer);
			result |= (read(memory, E65_PROCESSOR_REGISTER_STACK_POINTER_BASE + ++m_stack_pointer) << CHAR_BIT);

			E65_TRACE_EXIT_FORMAT("Result=%u(%04x)", result, result);
			return result;
		}

		void
		processor::process(
			__in e65::interface::runtime &runtime,
			__in e65::interface::system::memory &memory
			)
		{
			E65_TRACE_ENTRY_FORMAT("Runtime=%p, Memory=%p", &runtime, &memory);

			if(!m_stop && !m_wait) {
				uint8_t code;
				uint16_t address = m_program_counter, operand = 0;
				int command, length = 0, mode = e65::type::E65_PCOMMAND_MODE_IMPLIED;

				code = read(memory, m_program_counter++);
				if(decode(code, command, mode, length)) {

					switch(length) {
						case e65::type::E65_PCOMMAND_LENGTH_NONE:
							break;
						case e65::type::E65_PCOMMAND_LENGTH_BYTE:
							operand = read(memory, m_program_counter++);
							break;
						case e65::type::E65_PCOMMAND_LENGTH_WORD:
							operand = read_word(memory, m_program_counter);
							m_program_counter += sizeof(uint16_t);
							break;
						default:
							THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_LENGTH,
								"[%04x] %u(%02x)=%i", address, code, code, command);
					}

					E65_TRACE_MESSAGE_FORMAT(e65::type::E65_LEVEL_VERBOSE, "Command", "[%04x] %s %s {%u(%04x)}", address,
						E65_PCOMMAND_STRING(command), E65_PCOMMAND_MODE_STRING(mode), operand, operand);
				} else {
					E65_TRACE_MESSAGE_FORMAT(e65::type::E65_LEVEL_WARNING, "Illegal command", "[%04x] %u(%02x)", address,
						code, code);
					command = e65::type::E65_PCOMMAND_NOP;
				}

				switch(command) {
					case e65::type::E65_PCOMMAND_ADC:
						execute_adc(memory, mode, operand);
						break;
					case e65::type::E65_PCOMMAND_AND:
						execute_and(memory, mode, operand);
						break;
					case e65::type::E65_PCOMMAND_ASL:
						execute_asl(memory, mode, operand);
						break;
					case e65::type::E65_PCOMMAND_BBR0:
					case e65::type::E65_PCOMMAND_BBR1:
					case e65::type::E65_PCOMMAND_BBR2:
					case e65::type::E65_PCOMMAND_BBR3:
					case e65::type::E65_PCOMMAND_BBR4:
					case e65::type::E65_PCOMMAND_BBR5:
					case e65::type::E65_PCOMMAND_BBR6:
					case e65::type::E65_PCOMMAND_BBR7:
						execute_bbr(memory, command, operand);
						break;
					case e65::type::E65_PCOMMAND_BBS0:
					case e65::type::E65_PCOMMAND_BBS1:
					case e65::type::E65_PCOMMAND_BBS2:
					case e65::type::E65_PCOMMAND_BBS3:
					case e65::type::E65_PCOMMAND_BBS4:
					case e65::type::E65_PCOMMAND_BBS5:
					case e65::type::E65_PCOMMAND_BBS6:
					case e65::type::E65_PCOMMAND_BBS7:
						execute_bbs(memory, command, operand);
						break;
					case e65::type::E65_PCOMMAND_BCC:
						execute_bcc(memory, operand);
						break;
					case e65::type::E65_PCOMMAND_BCS:
						execute_bcs(memory, operand);
						break;
					case e65::type::E65_PCOMMAND_BEQ:
						execute_beq(memory, operand);
						break;
					case e65::type::E65_PCOMMAND_BIT:
						execute_bit(memory, mode, operand);
						break;
					case e65::type::E65_PCOMMAND_BMI:
						execute_bmi(memory, operand);
						break;
					case e65::type::E65_PCOMMAND_BNE:
						execute_bne(memory, operand);
						break;
					case e65::type::E65_PCOMMAND_BPL:
						execute_bpl(memory, operand);
						break;
					case e65::type::E65_PCOMMAND_BRA:
						execute_bra(memory, operand);
						break;
					case e65::type::E65_PCOMMAND_BRK:
						execute_brk(runtime, memory);
						break;
					case e65::type::E65_PCOMMAND_BVC:
						execute_bvc(memory, operand);
						break;
					case e65::type::E65_PCOMMAND_BVS:
						execute_bvs(memory, operand);
						break;
					case e65::type::E65_PCOMMAND_CLC:
						execute_clc();
						break;
					case e65::type::E65_PCOMMAND_CLD:
						execute_cld();
						break;
					case e65::type::E65_PCOMMAND_CLI:
						execute_cli();
						break;
					case e65::type::E65_PCOMMAND_CLV:
						execute_clv();
						break;
					case e65::type::E65_PCOMMAND_CMP:
						execute_cmp(memory, mode, operand);
						break;
					case e65::type::E65_PCOMMAND_CPX:
						execute_cpx(memory, mode, operand);
						break;
					case e65::type::E65_PCOMMAND_CPY:
						execute_cpy(memory, mode, operand);
						break;
					case e65::type::E65_PCOMMAND_DEC:
						execute_dec(memory, mode, operand);
						break;
					case e65::type::E65_PCOMMAND_DEX:
						execute_dex();
						break;
					case e65::type::E65_PCOMMAND_DEY:
						execute_dey();
						break;
					case e65::type::E65_PCOMMAND_EOR:
						execute_eor(memory, mode, operand);
						break;
					case e65::type::E65_PCOMMAND_INC:
						execute_inc(memory, mode, operand);
						break;
					case e65::type::E65_PCOMMAND_INX:
						execute_inx();
						break;
					case e65::type::E65_PCOMMAND_INY:
						execute_iny();
						break;
					case e65::type::E65_PCOMMAND_JMP:
						execute_jmp(memory, mode, operand);
						break;
					case e65::type::E65_PCOMMAND_JSR:
						execute_jsr(memory, mode, operand);
						break;
					case e65::type::E65_PCOMMAND_LDA:
						execute_lda(memory, mode, operand);
						break;
					case e65::type::E65_PCOMMAND_LDX:
						execute_ldx(memory, mode, operand);
						break;
					case e65::type::E65_PCOMMAND_LDY:
						execute_ldy(memory, mode, operand);
						break;
					case e65::type::E65_PCOMMAND_LSR:
						execute_lsr(memory, mode, operand);
						break;
					case e65::type::E65_PCOMMAND_NOP:
						execute_nop();
						break;
					case e65::type::E65_PCOMMAND_ORA:
						execute_ora(memory, mode, operand);
						break;
					case e65::type::E65_PCOMMAND_PHA:
						execute_pha(memory);
						break;
					case e65::type::E65_PCOMMAND_PHP:
						execute_php(memory);
						break;
					case e65::type::E65_PCOMMAND_PHX:
						execute_phx(memory);
						break;
					case e65::type::E65_PCOMMAND_PHY:
						execute_phy(memory);
						break;
					case e65::type::E65_PCOMMAND_PLA:
						execute_pla(memory);
						break;
					case e65::type::E65_PCOMMAND_PLP:
						execute_plp(memory);
						break;
					case e65::type::E65_PCOMMAND_PLX:
						execute_plx(memory);
						break;
					case e65::type::E65_PCOMMAND_PLY:
						execute_ply(memory);
						break;
					case e65::type::E65_PCOMMAND_RMB0:
					case e65::type::E65_PCOMMAND_RMB1:
					case e65::type::E65_PCOMMAND_RMB2:
					case e65::type::E65_PCOMMAND_RMB3:
					case e65::type::E65_PCOMMAND_RMB4:
					case e65::type::E65_PCOMMAND_RMB5:
					case e65::type::E65_PCOMMAND_RMB6:
					case e65::type::E65_PCOMMAND_RMB7:
						execute_rmb(memory, command, operand);
						break;
					case e65::type::E65_PCOMMAND_ROL:
						execute_rol(memory, mode, operand);
						break;
					case e65::type::E65_PCOMMAND_ROR:
						execute_ror(memory, mode, operand);
						break;
					case e65::type::E65_PCOMMAND_RTI:
						execute_rti(memory);
						break;
					case e65::type::E65_PCOMMAND_RTS:
						execute_rts(memory);
						break;
					case e65::type::E65_PCOMMAND_SBC:
						execute_sbc(memory, mode, operand);
						break;
					case e65::type::E65_PCOMMAND_SEC:
						execute_sec();
						break;
					case e65::type::E65_PCOMMAND_SED:
						execute_sed();
						break;
					case e65::type::E65_PCOMMAND_SEI:
						execute_sei();
						break;
					case e65::type::E65_PCOMMAND_SMB0:
					case e65::type::E65_PCOMMAND_SMB1:
					case e65::type::E65_PCOMMAND_SMB2:
					case e65::type::E65_PCOMMAND_SMB3:
					case e65::type::E65_PCOMMAND_SMB4:
					case e65::type::E65_PCOMMAND_SMB5:
					case e65::type::E65_PCOMMAND_SMB6:
					case e65::type::E65_PCOMMAND_SMB7:
						execute_smb(memory, command, operand);
						break;
					case e65::type::E65_PCOMMAND_STA:
						execute_sta(memory, mode, operand);
						break;
					case e65::type::E65_PCOMMAND_STP:
						execute_stp();
						break;
					case e65::type::E65_PCOMMAND_STX:
						execute_stx(memory, mode, operand);
						break;
					case e65::type::E65_PCOMMAND_STY:
						execute_sty(memory, mode, operand);
						break;
					case e65::type::E65_PCOMMAND_STZ:
						execute_stz(memory, mode, operand);
						break;
					case e65::type::E65_PCOMMAND_TAX:
						execute_tax();
						break;
					case e65::type::E65_PCOMMAND_TAY:
						execute_tay();
						break;
					case e65::type::E65_PCOMMAND_TRB:
						execute_trb(memory, mode, operand);
						break;
					case e65::type::E65_PCOMMAND_TSB:
						execute_tsb(memory, mode, operand);
						break;
					case e65::type::E65_PCOMMAND_TSX:
						execute_tsx();
						break;
					case e65::type::E65_PCOMMAND_TXA:
						execute_txa();
						break;
					case e65::type::E65_PCOMMAND_TXS:
						execute_txs();
						break;
					case e65::type::E65_PCOMMAND_TYA:
						execute_tya();
						break;
					case e65::type::E65_PCOMMAND_WAI:
						execute_wai();
						break;
					default:
						THROW_E65_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(E65_SYSTEM_PROCESSOR_EXCEPTION_INVALID_CODE,
							"[%04x] %u(%02x)=%i", address, code, code, command);
				}
			} else {

				if(m_stop) {
					runtime.signal_event(E65_EVENT_STOP, m_program_counter);
				}

				if(m_wait) {
					runtime.signal_event(E65_EVENT_WAIT, m_program_counter);
				}

				execute_nop();
			}

			E65_TRACE_EXIT();
		}

		uint16_t
		processor::program_counter(void) const
		{
			E65_TRACE_ENTRY();

			if(!e65::type::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_EXIT_FORMAT("Result=%u(%04x)", m_program_counter, m_program_counter);
			return m_program_counter;
		}

		void
		processor::push(
			__in e65::interface::system::memory &memory,
			__in uint8_t value
			)
		{
			E65_TRACE_ENTRY_FORMAT("Memory=%p, Value=%u(%02x)", &memory, value, value);

			write(memory, E65_PROCESSOR_REGISTER_STACK_POINTER_BASE + m_stack_pointer--, value);

			E65_TRACE_EXIT();
		}

		void
		processor::push_word(
			__in e65::interface::system::memory &memory,
			__in uint16_t value
			)
		{
			E65_TRACE_ENTRY_FORMAT("Memory=%p, Value=%u(%04x)", &memory, value, value);

			write(memory, E65_PROCESSOR_REGISTER_STACK_POINTER_BASE + m_stack_pointer--, value >> CHAR_BIT);
			write(memory, E65_PROCESSOR_REGISTER_STACK_POINTER_BASE + m_stack_pointer--, value);

			E65_TRACE_EXIT();
		}

		uint8_t
		processor::read(
			__in e65::interface::system::memory &memory,
			__in uint16_t address
			) const
		{
			uint8_t result;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Address=%u(%04x)", &memory, address, address);

			result = memory.read(address);

			E65_TRACE_EXIT_FORMAT("Result=%u(%02x)", result, result);
			return result;
		}

		uint16_t
		processor::read_word(
			__in e65::interface::system::memory &memory,
			__in uint16_t address
			) const
		{
			uint16_t result;

			E65_TRACE_ENTRY_FORMAT("Memory=%p, Address=%u(%04x)", &memory, address, address);

			result = memory.read_word(address);

			E65_TRACE_EXIT_FORMAT("Result=%u(%04x)", result, result);
			return result;
		}

		void
		processor::reset(
			__in e65::interface::system::memory &memory
			)
		{
			E65_TRACE_ENTRY_FORMAT("Memory=%p", &memory);

			if(!e65::type::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Processor resetting");

			m_accumulator = E65_PROCESSOR_REGISTER_ACCUMULATOR_RESET;
			m_cycle = E65_PROCESSOR_INTERRUPT_CYCLES;
			m_cycle_last = E65_PROCESSOR_INTERRUPT_CYCLES;
			m_flags.raw = E65_PROCESSOR_REGISTER_FLAGS_RESET;
			m_index_x = E65_PROCESSOR_REGISTER_INDEX_X_RESET;
			m_index_y = E65_PROCESSOR_REGISTER_INDEX_Y_RESET;
			m_interrupt_irq = false;
			m_interrupt_nmi = false;
			m_program_counter = read_word(memory, E65_PROCESSOR_ADDRESS_RESET_INTERRUPT);
			m_stack_pointer = E65_PROCESSOR_REGISTER_STACK_POINTER_RESET;
			m_stop = false;
			m_wait = false;

			push_word(memory, m_program_counter);

			E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Processor reset");

			E65_TRACE_EXIT();
		}

		void
		processor::service(
			__in e65::interface::runtime &runtime,
			__in e65::interface::system::memory &memory
			)
		{
			E65_TRACE_ENTRY_FORMAT("Runtime=%p, Memory=%p", &runtime, &memory);

			if(m_interrupt_irq || m_interrupt_nmi) {

				if(m_interrupt_nmi) {
					E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Processor servicing NMI interrupt");
					runtime.signal_event(E65_EVENT_NON_MASKABLE_INTERRUPT, m_program_counter);
				} else if(m_interrupt_irq) {
					E65_TRACE_MESSAGE(e65::type::E65_LEVEL_INFORMATION, "Processor servicing IRQ interrupt");
					runtime.signal_event(E65_EVENT_MASKABLE_INTERRUPT, m_program_counter);
				}

				push_word(memory, m_program_counter);
				push(memory, m_flags.raw & ~E65_PFLAG(e65::type::E65_PFLAG_BREAKPOINT));

				if(m_interrupt_nmi) {
					m_interrupt_nmi = false;
					m_program_counter = read_word(memory, E65_PROCESSOR_ADDRESS_NON_MASKABLE_INTERRUPT);
				} else if(m_interrupt_irq) {
					m_interrupt_irq = false;
					m_program_counter = read_word(memory, E65_PROCESSOR_ADDRESS_MASKABLE_INTERRUPT);
				}

				m_cycle_last += E65_PROCESSOR_INTERRUPT_CYCLES;
				m_wait = false;
			}

			E65_TRACE_EXIT();
		}

		void
		processor::set_accumulator(
			__in uint8_t accumulator
			)
		{
			E65_TRACE_ENTRY_FORMAT("Accumulator=%u(%02x)", accumulator, accumulator);

			if(!e65::type::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			m_accumulator = accumulator;

			E65_TRACE_EXIT();
		}

		void
		processor::set_flags(
			__in uint8_t flags
			)
		{
			E65_TRACE_ENTRY_FORMAT("Flags=%u(%02x)", flags, flags);

			if(!e65::type::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			m_flags.raw = flags;

			E65_TRACE_EXIT();
		}

		void
		processor::set_index_x(
			__in uint8_t index_x
			)
		{
			E65_TRACE_ENTRY_FORMAT("Index-X=%u(%02x)", index_x, index_x);

			if(!e65::type::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			m_index_x = index_x;

			E65_TRACE_EXIT();
		}

		void
		processor::set_index_y(
			__in uint8_t index_y
			)
		{
			E65_TRACE_ENTRY_FORMAT("Index-Y=%u(%02x)", index_y, index_y);

			if(!e65::type::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			m_index_y = index_y;

			E65_TRACE_EXIT();
		}

		void
		processor::set_program_counter(
			__in uint16_t program_counter
			)
		{
			E65_TRACE_ENTRY_FORMAT("Program-Counter=%u(%04x)", program_counter, program_counter);

			if(!e65::type::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			m_program_counter = program_counter;

			E65_TRACE_EXIT();
		}

		void
		processor::set_stack_pointer(
			__in uint8_t stack_pointer
			)
		{
			E65_TRACE_ENTRY_FORMAT("Stack-Pointer=%u(%02x)", stack_pointer, stack_pointer);

			if(!e65::type::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			m_stack_pointer = stack_pointer;

			E65_TRACE_EXIT();
		}

		void
		processor::set_stop(
			__in bool stop
			)
		{
			E65_TRACE_ENTRY_FORMAT("Stop=%x", stop);

			if(!e65::type::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			m_stop = stop;

			E65_TRACE_EXIT();
		}

		void
		processor::set_wait(
			__in bool wait
			)
		{
			E65_TRACE_ENTRY_FORMAT("Wait=%x", wait);

			if(!e65::type::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			m_wait = wait;

			E65_TRACE_EXIT();
		}

		uint8_t
		processor::stack_pointer(void) const
		{
			E65_TRACE_ENTRY();

			if(!e65::type::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_EXIT_FORMAT("Result=%u(%02x)", m_stack_pointer, m_stack_pointer);
			return m_stack_pointer;
		}

		uint8_t
		processor::step(
			__in e65::interface::runtime &runtime,
			__in e65::interface::system::memory &memory
			)
		{
			E65_TRACE_ENTRY_FORMAT("Runtime=%p, Memory=%p", &runtime, &memory);

			if(!e65::type::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			m_cycle_last = 0;

			service(runtime, memory);
			process(runtime, memory);

			m_cycle += m_cycle_last;

			E65_TRACE_EXIT_FORMAT("Result=%u", m_cycle_last);
			return m_cycle_last;
		}

		bool
		processor::stopped(void) const
		{
			E65_TRACE_ENTRY();

			if(!e65::type::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_EXIT_FORMAT("Result=%x", m_stop);
			return m_stop;
		}

		std::string
		processor::to_string(void) const
		{
			std::stringstream result;

			result << E65_SYSTEM_PROCESSOR_HEADER << "(" << E65_STRING_HEX(uintptr_t, this) << ")"
				<< " Interface=" << e65::type::singleton<e65::system::processor>::to_string();

			if(e65::type::singleton<e65::system::processor>::initialized()) {
				result << ", Cycle=" << m_cycle << " (Last=" << (int) m_cycle_last << ")"
					<< ", WAI=" << m_wait
					<< ", STP=" << m_stop
					<< ", IRQ=" << m_interrupt_irq
					<< ", NMI=" << m_interrupt_nmi
					<< ", PC=" << (int) m_program_counter << "(" << E65_STRING_HEX(uint16_t, m_program_counter) << ")"
					<< ", SP=" << (int) m_stack_pointer << "(" << E65_STRING_HEX(uint8_t, m_stack_pointer) << ")"
					<< ", F=" << (int) m_flags.raw << "(" << E65_STRING_HEX(uint8_t, m_flags.raw) << ")"
					<< " [" << (m_flags.sign ? E65_PFLAG_STRING(e65::type::E65_PFLAG_SIGN) : "-")
						<< (m_flags.overflow ? E65_PFLAG_STRING(e65::type::E65_PFLAG_OVERFLOW) : "-")
						<< E65_PFLAG_STRING(e65::type::E65_PFLAG_UNUSED)
						<< (m_flags.breakpoint ? E65_PFLAG_STRING(e65::type::E65_PFLAG_BREAKPOINT) : "-")
						<< (m_flags.decimal_enable ? E65_PFLAG_STRING(e65::type::E65_PFLAG_DECIMAL_ENABLE) : "-")
						<< (m_flags.irq_disable ? E65_PFLAG_STRING(e65::type::E65_PFLAG_IRQ_DISABLE) : "-")
						<< (m_flags.zero ? E65_PFLAG_STRING(e65::type::E65_PFLAG_ZERO) : "-")
						<< (m_flags.carry ? E65_PFLAG_STRING(e65::type::E65_PFLAG_CARRY) : "-") << "]"
					<< ", A=" << (int) m_accumulator << "(" << E65_STRING_HEX(uint8_t, m_accumulator) << ")"
					<< ", X=" << (int) m_index_x << "(" << E65_STRING_HEX(uint8_t, m_index_x) << ")"
					<< ", Y=" << (int) m_index_y << "(" << E65_STRING_HEX(uint8_t, m_index_y) << ")";
			}

			return result.str();
		}

		bool
		processor::waiting(void) const
		{
			E65_TRACE_ENTRY();

			if(!e65::type::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_EXIT_FORMAT("Result=%x", m_wait);
			return m_wait;
		}

		void
		processor::write(
			__in e65::interface::system::memory &memory,
			__in uint16_t address,
			__in uint8_t value
			)
		{
			E65_TRACE_ENTRY_FORMAT("Memory=%p, Address=%u(%04x), Value=%u(%02x)", &memory, address, address, value, value);

			memory.write(address, value);

			E65_TRACE_EXIT();
		}

		void
		processor::write_word(
			__in e65::interface::system::memory &memory,
			__in uint16_t address,
			__in uint16_t value
			)
		{
			E65_TRACE_ENTRY_FORMAT("Memory=%p, Address=%u(%04x), Value=%u(%04x)", &memory, address, address, value, value);

			memory.write_word(address, value);

			E65_TRACE_EXIT();
		}
	}
}
