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

#ifndef E65_SYSTEM_PROCESSOR_H_
#define E65_SYSTEM_PROCESSOR_H_

#include "../interface/system/processor.h"
#include "./memory.h"

namespace e65 {

	namespace system {

		typedef union {
			struct {
				uint8_t carry : 1;
				uint8_t zero : 1;
				uint8_t irq_disable : 1;
				uint8_t decimal_enable : 1;
				uint8_t breakpoint : 1;
				uint8_t unused : 1;
				uint8_t overflow : 1;
				uint8_t sign : 1;
			};

			uint8_t raw;
		} e65_flag_t;

		class processor :
				public e65::interface::singleton<e65::system::processor>,
				public e65::interface::system::processor {

			public:

				~processor(void);

				uint8_t accumulator(void) const override;

				uint32_t cycle(void) const override;

				uint8_t cycle_last(void) const override;

				uint8_t flags(void) const override;

				uint8_t index_x(void) const override;

				uint8_t index_y(void) const override;

				void interrupt(
					__in bool maskable
					) override;

				bool interrupted(
					__in bool maskable
					) const override;

				bool halted(void) const override;

				uint16_t program_counter(void) const override;

				void reset(
					__in e65::interface::system::memory &memory
					) override;

				void set_accumulator(
					__in uint8_t value
					) override;

				void set_flags(
					__in uint8_t value
					) override;

				void set_halt(
					__in bool value
					) override;

				void set_index_x(
					__in uint8_t value
					) override;

				void set_index_y(
					__in uint8_t value
					) override;

				void set_program_counter(
					__in uint16_t value
					) override;

				void set_stack_pointer(
					__in uint8_t value
					) override;

				void set_stop(
					__in bool value
					) override;

				uint8_t stack_pointer(void) const override;

				uint8_t step(
					__in e65::interface::system::memory &memory
					);

				bool stopped(void) const override;

				std::string to_string(void) const override;

			protected:

				friend class e65::interface::singleton<e65::system::processor>;

				processor(void);

				processor(
					__in const processor &other
					) = delete;

				processor &operator=(
					__in const processor &other
					) = delete;

				bool on_initialize(
					__in const void *context,
					__in size_t length
					) override;

				void on_uninitialize(void) override;

				uint8_t pop(
					__in e65::interface::system::memory &memory
					);

				uint16_t pop_word(
					__in e65::interface::system::memory &memory
					);

				void process(
					__in e65::interface::system::memory &memory
					);

				void push(
					__in e65::interface::system::memory &memory,
					__in uint8_t value
					);

				void push_word(
					__in e65::interface::system::memory &memory,
					__in uint16_t value
					);

				uint8_t read(
					__in e65::interface::system::memory &memory,
					__in uint16_t address
					) const;

				uint16_t read_word(
					__in e65::interface::system::memory &memory,
					__in uint16_t address
					) const;

				void service(
					__in e65::interface::system::memory &memory
					);

				void write(
					__in e65::interface::system::memory &memory,
					__in uint16_t address,
					__in uint8_t value
					);

				void write_word(
					__in e65::interface::system::memory &memory,
					__in uint16_t address,
					__in uint16_t value
					);

				uint8_t m_accumulator;

				uint32_t m_cycle;

				uint8_t m_cycle_last;

				e65::system::e65_flag_t m_flags;

				bool m_halt;

				uint8_t m_index_x;

				uint8_t m_index_y;

				bool m_interrupt_irq;

				bool m_interrupt_nmi;

				uint16_t m_program_counter;

				uint8_t m_stack_pointer;

				bool m_stop;
		};
	}
}

#endif // E65_SYSTEM_PROCESSOR_H_
