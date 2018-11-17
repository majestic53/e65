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
#include "../../include/trace.h"
#include "./processor_type.h"

namespace e65 {

	namespace system {

		processor::processor(void) :
			e65::interface::singleton<e65::system::processor>(e65::interface::E65_SINGLETON_PROCESSOR),
			m_accumulator(0),
			m_cycle(0),
			m_cycle_last(0),
			m_flags({}),
			m_halt(false),
			m_index_x(0),
			m_index_y(0),
			m_interrupt_irq(false),
			m_interrupt_nmi(false),
			m_program_counter(0),
			m_stack_pointer(0),
			m_stop(false)
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

			if(!e65::interface::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_EXIT_FORMAT("Result=%u(%02x)", m_accumulator, m_accumulator);
			return m_accumulator;
		}

		uint32_t
		processor::cycle(void) const
		{
			E65_TRACE_ENTRY();

			if(!e65::interface::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_EXIT_FORMAT("Result=%u", m_cycle);
			return m_cycle;
		}

		uint8_t
		processor::cycle_last(void) const
		{
			E65_TRACE_ENTRY();

			if(!e65::interface::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_EXIT_FORMAT("Result=%u", m_cycle_last);
			return m_cycle_last;
		}

		uint8_t
		processor::flags(void) const
		{
			E65_TRACE_ENTRY();

			if(!e65::interface::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_EXIT_FORMAT("Result=%u(%02x)", m_flags.raw, m_flags.raw);
			return m_flags.raw;
		}

		bool
		processor::halted(void) const
		{
			E65_TRACE_ENTRY();

			if(!e65::interface::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_EXIT_FORMAT("Result=%x", m_halt);
			return m_halt;
		}

		uint8_t
		processor::index_x(void) const
		{
			E65_TRACE_ENTRY();

			if(!e65::interface::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_EXIT_FORMAT("Result=%u(%02x)", m_index_x, m_index_x);
			return m_index_x;
		}

		uint8_t
		processor::index_y(void) const
		{
			E65_TRACE_ENTRY();

			if(!e65::interface::singleton<e65::system::processor>::initialized()) {
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

			if(!e65::interface::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			if(!maskable || !m_flags.irq_disable) {

				if(maskable) {
					E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Processor IRQ interrupt request");
					m_interrupt_irq = true;
				} else {
					E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Processor NMI interrupt request");
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

			if(!e65::interface::singleton<e65::system::processor>::initialized()) {
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

			E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Processor initializing");

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
			__in e65::interface::system::memory &memory
			)
		{
			E65_TRACE_ENTRY_FORMAT("Memory=%p", &memory);

			if(!m_halt && !m_stop) {

				// TODO: step processor through a single instruction
				m_cycle_last += (std::rand() % 10 + 2);
				// ---

			}

			E65_TRACE_EXIT();
		}

		uint16_t
		processor::program_counter(void) const
		{
			E65_TRACE_ENTRY();

			if(!e65::interface::singleton<e65::system::processor>::initialized()) {
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

			if(!e65::interface::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Processor resetting");

			m_accumulator = E65_PROCESSOR_REGISTER_ACCUMULATOR;
			m_cycle = E65_PROCESSOR_INTERRUPT_CYCLES;
			m_cycle_last = E65_PROCESSOR_INTERRUPT_CYCLES;
			m_flags.raw = E65_PROCESSOR_REGISTER_FLAGS;
			m_halt = false;
			m_index_x = E65_PROCESSOR_REGISTER_INDEX_X;
			m_index_y = E65_PROCESSOR_REGISTER_INDEX_Y;
			m_interrupt_irq = false;
			m_interrupt_nmi = false;
			m_program_counter = read_word(memory, E65_PROCESSOR_ADDRESS_RESET_INTERRUPT);
			m_stack_pointer = E65_PROCESSOR_REGISTER_STACK_POINTER;
			m_stop = false;

			E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Processor reset");

			E65_TRACE_EXIT();
		}

		void
		processor::service(
			__in e65::interface::system::memory &memory
			)
		{
			E65_TRACE_ENTRY_FORMAT("Memory=%p", &memory);

			if(m_interrupt_irq || m_interrupt_nmi) {

				if(m_interrupt_nmi) {
					E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Processor servicing NMI interrupt");
				} else if(m_interrupt_irq) {
					E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Processor servicing IRQ interrupt");
				}

				push_word(memory, m_program_counter);
				push(memory, m_flags.raw & ~E65_PFLAG(E65_PFLAG_BREAKPOINT));

				if(m_interrupt_nmi) {
					m_interrupt_nmi = false;
					m_program_counter = read_word(memory, E65_PROCESSOR_ADDRESS_NON_MASKABLE_INTERRUPT);
				} else if(m_interrupt_irq) {
					m_interrupt_irq = false;
					m_program_counter = read_word(memory, E65_PROCESSOR_ADDRESS_MASKABLE_INTERRUPT);
				}

				m_cycle_last += E65_PROCESSOR_INTERRUPT_CYCLES;
				m_halt = false;
			}

			E65_TRACE_EXIT();
		}

		void
		processor::set_accumulator(
			__in uint8_t value
			)
		{
			E65_TRACE_ENTRY_FORMAT("Value=%u(%02x)", value, value);

			if(!e65::interface::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			m_accumulator = value;

			E65_TRACE_EXIT();
		}

		void
		processor::set_flags(
			__in uint8_t value
			)
		{
			E65_TRACE_ENTRY_FORMAT("Value=%u(%02x)", value, value);

			if(!e65::interface::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			m_flags.raw = value;

			E65_TRACE_EXIT();
		}

		void
		processor::set_halt(
			__in bool value
			)
		{
			E65_TRACE_ENTRY_FORMAT("Value=%x", value);

			if(!e65::interface::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			m_halt = value;

			E65_TRACE_EXIT();
		}

		void
		processor::set_index_x(
			__in uint8_t value
			)
		{
			E65_TRACE_ENTRY_FORMAT("Value=%u(%02x)", value, value);

			if(!e65::interface::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			m_index_x = value;

			E65_TRACE_EXIT();
		}

		void
		processor::set_index_y(
			__in uint8_t value
			)
		{
			E65_TRACE_ENTRY_FORMAT("Value=%u(%02x)", value, value);

			if(!e65::interface::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			m_index_y = value;

			E65_TRACE_EXIT();
		}

		void
		processor::set_program_counter(
			__in uint16_t value
			)
		{
			E65_TRACE_ENTRY_FORMAT("Value=%u(%04x)", value, value);

			if(!e65::interface::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			m_program_counter = value;

			E65_TRACE_EXIT();
		}

		void
		processor::set_stack_pointer(
			__in uint8_t value
			)
		{
			E65_TRACE_ENTRY_FORMAT("Value=%u(%02x)", value, value);

			if(!e65::interface::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			m_stack_pointer = value;

			E65_TRACE_EXIT();
		}

		void
		processor::set_stop(
			__in bool value
			)
		{
			E65_TRACE_ENTRY_FORMAT("Value=%x", value);

			if(!e65::interface::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			m_stop = value;

			E65_TRACE_EXIT();
		}

		uint8_t
		processor::stack_pointer(void) const
		{
			E65_TRACE_ENTRY();

			if(!e65::interface::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_EXIT_FORMAT("Result=%u(%02x)", m_stack_pointer, m_stack_pointer);
			return m_stack_pointer;
		}

		uint8_t
		processor::step(
			__in e65::interface::system::memory &memory
			)
		{
			E65_TRACE_ENTRY_FORMAT("Memory=%p", &memory);

			if(!e65::interface::singleton<e65::system::processor>::initialized()) {
				THROW_E65_SYSTEM_PROCESSOR_EXCEPTION(E65_SYSTEM_PROCESSOR_EXCEPTION_UNINITIALIZED);
			}

			m_cycle_last = 0;

			service(memory);
			process(memory);

			m_cycle += m_cycle_last;

			E65_TRACE_EXIT_FORMAT("Result=%u", m_cycle_last);
			return m_cycle_last;
		}

		bool
		processor::stopped(void) const
		{
			E65_TRACE_ENTRY();

			if(!e65::interface::singleton<e65::system::processor>::initialized()) {
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
				<< " Interface=" << e65::interface::singleton<e65::system::processor>::to_string();

			if(e65::interface::singleton<e65::system::processor>::initialized()) {
				result << ", Cycle=" << m_cycle << " (Last=" << (int) m_cycle_last << ")"
					<< ", Halt=" << m_halt
					<< ", Stop=" << m_stop
					<< ", IRQ=" << m_interrupt_irq
					<< ", NMI=" << m_interrupt_nmi
					<< ", PC=" << (int) m_program_counter << "(" << E65_STRING_HEX(uint16_t, m_program_counter) << ")"
					<< ", SP=" << (int) m_stack_pointer << "(" << E65_STRING_HEX(uint8_t, m_stack_pointer) << ")"
					<< ", F=" << (int) m_flags.raw << "(" << E65_STRING_HEX(uint8_t, m_flags.raw) << ")"
					<< " [" << (m_flags.sign ? E65_PFLAG_STRING(E65_PFLAG_SIGN) : "-")
						<< (m_flags.overflow ? E65_PFLAG_STRING(E65_PFLAG_OVERFLOW) : "-")
						<< E65_PFLAG_STRING(E65_PFLAG_UNUSED)
						<< (m_flags.breakpoint ? E65_PFLAG_STRING(E65_PFLAG_BREAKPOINT) : "-")
						<< (m_flags.decimal_enable ? E65_PFLAG_STRING(E65_PFLAG_DECIMAL_ENABLE) : "-")
						<< (m_flags.irq_disable ? E65_PFLAG_STRING(E65_PFLAG_IRQ_DISABLE) : "-")
						<< (m_flags.zero ? E65_PFLAG_STRING(E65_PFLAG_ZERO) : "-")
						<< (m_flags.carry ? E65_PFLAG_STRING(E65_PFLAG_CARRY) : "-") << "]"
					<< ", A=" << (int) m_accumulator << "(" << E65_STRING_HEX(uint8_t, m_accumulator) << ")"
					<< ", X=" << (int) m_index_x << "(" << E65_STRING_HEX(uint8_t, m_index_x) << ")"
					<< ", Y=" << (int) m_index_y << "(" << E65_STRING_HEX(uint8_t, m_index_y) << ")";
			}

			return result.str();
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
