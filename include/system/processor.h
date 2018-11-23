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

#include "../interface/runtime.h"
#include "./memory.h"

namespace e65 {

	namespace system {

		class processor :
				public e65::type::singleton<e65::system::processor>,
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

				uint16_t program_counter(void) const override;

				void reset(
					__in e65::interface::system::memory &memory
					) override;

				void set_accumulator(
					__in uint8_t accumulator
					) override;

				void set_flags(
					__in uint8_t flags
					) override;

				void set_index_x(
					__in uint8_t index_x
					) override;

				void set_index_y(
					__in uint8_t index_y
					) override;

				void set_program_counter(
					__in uint16_t program_counter
					) override;

				void set_stack_pointer(
					__in uint8_t stack_pointer
					) override;

				void set_stop(
					__in bool stop
					) override;

				void set_wait(
					__in bool wait
					) override;

				uint8_t stack_pointer(void) const override;

				uint8_t step(
					__in e65::interface::runtime &runtime,
					__in e65::interface::system::memory &memory
					);

				bool stopped(void) const override;

				std::string to_string(void) const override;

				bool waiting(void) const override;

			protected:

				friend class e65::type::singleton<e65::system::processor>;

				processor(void);

				processor(
					__in const processor &other
					) = delete;

				processor &operator=(
					__in const processor &other
					) = delete;

				uint16_t address_in(
					__in e65::interface::system::memory &memory,
					__in int mode,
					__in uint16_t operand,
					__inout bool &boundary
					);

				uint16_t address_out(
					__in e65::interface::system::memory &memory,
					__in int mode,
					__in uint16_t operand
					);

				uint8_t cycles(
					__in int command,
					__in int mode,
					__in_opt bool secondary = false
					) const;

				bool decode(
					__in uint8_t code,
					__inout int &command,
					__inout int &mode,
					__inout int &length
					);

				void execute_brk(
					__in e65::interface::runtime &runtime,
					__in e65::interface::system::memory &memory
					);

				void execute_adc(
					__in e65::interface::system::memory &memory,
					__in int mode,
					__in uint16_t operand
					);

				void execute_and(
					__in e65::interface::system::memory &memory,
					__in int mode,
					__in uint16_t operand
					);

				void execute_clc(void);

				void execute_cld(void);

				void execute_cli(void);

				void execute_clv(void);

				void execute_cmp(
					__in e65::interface::system::memory &memory,
					__in int mode,
					__in uint16_t operand
					);

				void execute_dex(void);

				void execute_dey(void);

				void execute_eor(
					__in e65::interface::system::memory &memory,
					__in int mode,
					__in uint16_t operand
					);

				void execute_inx(void);

				void execute_iny(void);

				void execute_lda(
					__in e65::interface::system::memory &memory,
					__in int mode,
					__in uint16_t operand
					);

				void execute_nop(void);

				void execute_ora(
					__in e65::interface::system::memory &memory,
					__in int mode,
					__in uint16_t operand
					);

				void execute_pha(
					__in e65::interface::system::memory &memory
					);

				void execute_php(
					__in e65::interface::system::memory &memory
					);

				void execute_phx(
					__in e65::interface::system::memory &memory
					);

				void execute_phy(
					__in e65::interface::system::memory &memory
					);

				void execute_pla(
					__in e65::interface::system::memory &memory
					);

				void execute_plp(
					__in e65::interface::system::memory &memory
					);

				void execute_plx(
					__in e65::interface::system::memory &memory
					);

				void execute_ply(
					__in e65::interface::system::memory &memory
					);

				void execute_rti(
					__in e65::interface::system::memory &memory
					);

				void execute_rts(
					__in e65::interface::system::memory &memory
					);

				void execute_sbc(
					__in e65::interface::system::memory &memory,
					__in int mode,
					__in uint16_t operand
					);

				void execute_sec(void);

				void execute_sed(void);

				void execute_sei(void);

				void execute_sta(
					__in e65::interface::system::memory &memory,
					__in int mode,
					__in uint16_t operand
					);

				void execute_stp(void);

				void execute_tax(void);

				void execute_tay(void);

				void execute_tsx(void);

				void execute_txa(void);

				void execute_txs(void);

				void execute_tya(void);

				void execute_wai(void);

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
					__in e65::interface::runtime &runtime,
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
					__in e65::interface::runtime &runtime,
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

				e65::type::pflag_t m_flags;

				uint8_t m_index_x;

				uint8_t m_index_y;

				bool m_interrupt_irq;

				bool m_interrupt_nmi;

				uint16_t m_program_counter;

				uint8_t m_stack_pointer;

				bool m_stop;

				bool m_wait;
		};
	}
}

#endif // E65_SYSTEM_PROCESSOR_H_
