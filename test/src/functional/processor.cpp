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

#include "../../../include/runtime.h"
#include "../../include/functional/processor.h"
#include "./processor_type.h"

namespace e65 {

	namespace test {

		namespace functional {

			processor::processor(void) :
				e65::test::type::fixture(e65::test::type::E65_FIXTURE_FUNCTIONAL_PROCESSOR)
			{
				return;
			}

			processor::~processor(void)
			{
				return;
			}

			bool
			processor::command_clc_implied(
				__in e65::interface::runtime &runtime,
				__in e65::system::processor &processor,
				__in e65::interface::system::memory &memory
				)
			{
				bool result;

				memory.write(E65_TEST_FUNCTIONAL_PROCESSOR_START_ADDRESS, 0x18);
				processor.step(runtime, memory);

				result = compare(processor, {
					E65_TEST_FUNCTIONAL_PROCESSOR_ACCUMULATOR_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_VALUE + 2,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_LAST_VALUE + 2,
					E65_TEST_FUNCTIONAL_PROCESSOR_FLAGS_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_X_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_Y_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_NON_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_START_ADDRESS + 1,
					E65_TEST_FUNCTIONAL_PROCESSOR_STACK_POINTER_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_STOP_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_WAIT_VALUE
					});

				if(!result) {
					goto exit;
				}

				processor.reset(memory);
				processor.set_flags(processor.flags() | E65_PFLAG(e65::type::E65_PFLAG_CARRY));
				processor.step(runtime, memory);

				result = compare(processor, {
					E65_TEST_FUNCTIONAL_PROCESSOR_ACCUMULATOR_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_VALUE + 2,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_LAST_VALUE + 2,
					E65_TEST_FUNCTIONAL_PROCESSOR_FLAGS_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_X_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_Y_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_NON_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_START_ADDRESS + 1,
					E65_TEST_FUNCTIONAL_PROCESSOR_STACK_POINTER_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_STOP_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_WAIT_VALUE
					});

				if(!result) {
					goto exit;
				}

			exit:
				return result;
			}

			bool
			processor::command_cld_implied(
				__in e65::interface::runtime &runtime,
				__in e65::system::processor &processor,
				__in e65::interface::system::memory &memory
				)
			{
				bool result;

				memory.write(E65_TEST_FUNCTIONAL_PROCESSOR_START_ADDRESS, 0xd8);
				processor.step(runtime, memory);

				result = compare(processor, {
					E65_TEST_FUNCTIONAL_PROCESSOR_ACCUMULATOR_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_VALUE + 2,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_LAST_VALUE + 2,
					E65_TEST_FUNCTIONAL_PROCESSOR_FLAGS_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_X_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_Y_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_NON_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_START_ADDRESS + 1,
					E65_TEST_FUNCTIONAL_PROCESSOR_STACK_POINTER_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_STOP_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_WAIT_VALUE
					});

				if(!result) {
					goto exit;
				}

				processor.reset(memory);
				processor.set_flags(processor.flags() | E65_PFLAG(e65::type::E65_PFLAG_DECIMAL_ENABLE));
				processor.step(runtime, memory);

				result = compare(processor, {
					E65_TEST_FUNCTIONAL_PROCESSOR_ACCUMULATOR_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_VALUE + 2,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_LAST_VALUE + 2,
					E65_TEST_FUNCTIONAL_PROCESSOR_FLAGS_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_X_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_Y_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_NON_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_START_ADDRESS + 1,
					E65_TEST_FUNCTIONAL_PROCESSOR_STACK_POINTER_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_STOP_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_WAIT_VALUE
					});

				if(!result) {
					goto exit;
				}

			exit:
				return result;
			}

			bool
			processor::command_cli_implied(
				__in e65::interface::runtime &runtime,
				__in e65::system::processor &processor,
				__in e65::interface::system::memory &memory
				)
			{
				bool result;

				memory.write(E65_TEST_FUNCTIONAL_PROCESSOR_START_ADDRESS, 0x58);
				processor.step(runtime, memory);

				result = compare(processor, {
					E65_TEST_FUNCTIONAL_PROCESSOR_ACCUMULATOR_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_VALUE + 2,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_LAST_VALUE + 2,
					E65_TEST_FUNCTIONAL_PROCESSOR_FLAGS_VALUE & ~E65_PFLAG(e65::type::E65_PFLAG_IRQ_DISABLE),
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_X_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_Y_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_NON_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_START_ADDRESS + 1,
					E65_TEST_FUNCTIONAL_PROCESSOR_STACK_POINTER_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_STOP_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_WAIT_VALUE
					});

				if(!result) {
					goto exit;
				}

				processor.reset(memory);
				processor.set_flags(processor.flags() & ~E65_PFLAG(e65::type::E65_PFLAG_IRQ_DISABLE));
				processor.step(runtime, memory);

				result = compare(processor, {
					E65_TEST_FUNCTIONAL_PROCESSOR_ACCUMULATOR_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_VALUE + 2,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_LAST_VALUE + 2,
					E65_TEST_FUNCTIONAL_PROCESSOR_FLAGS_VALUE & ~E65_PFLAG(e65::type::E65_PFLAG_IRQ_DISABLE),
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_X_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_Y_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_NON_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_START_ADDRESS + 1,
					E65_TEST_FUNCTIONAL_PROCESSOR_STACK_POINTER_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_STOP_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_WAIT_VALUE
					});

				if(!result) {
					goto exit;
				}

			exit:
				return result;
			}

			bool
			processor::command_clv_implied(
				__in e65::interface::runtime &runtime,
				__in e65::system::processor &processor,
				__in e65::interface::system::memory &memory
				)
			{
				bool result;

				memory.write(E65_TEST_FUNCTIONAL_PROCESSOR_START_ADDRESS, 0xb8);
				processor.step(runtime, memory);

				result = compare(processor, {
					E65_TEST_FUNCTIONAL_PROCESSOR_ACCUMULATOR_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_VALUE + 2,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_LAST_VALUE + 2,
					E65_TEST_FUNCTIONAL_PROCESSOR_FLAGS_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_X_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_Y_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_NON_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_START_ADDRESS + 1,
					E65_TEST_FUNCTIONAL_PROCESSOR_STACK_POINTER_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_STOP_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_WAIT_VALUE
					});

				if(!result) {
					goto exit;
				}

				processor.reset(memory);
				processor.set_flags(processor.flags() | E65_PFLAG(e65::type::E65_PFLAG_OVERFLOW));
				processor.step(runtime, memory);

				result = compare(processor, {
					E65_TEST_FUNCTIONAL_PROCESSOR_ACCUMULATOR_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_VALUE + 2,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_LAST_VALUE + 2,
					E65_TEST_FUNCTIONAL_PROCESSOR_FLAGS_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_X_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_Y_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_NON_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_START_ADDRESS + 1,
					E65_TEST_FUNCTIONAL_PROCESSOR_STACK_POINTER_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_STOP_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_WAIT_VALUE
					});

				if(!result) {
					goto exit;
				}

			exit:
				return result;
			}

			bool
			processor::command_nop_implied(
				__in e65::interface::runtime &runtime,
				__in e65::system::processor &processor,
				__in e65::interface::system::memory &memory
				)
			{
				memory.write(E65_TEST_FUNCTIONAL_PROCESSOR_START_ADDRESS, 0xea);
				processor.step(runtime, memory);

				return compare(processor, {
					E65_TEST_FUNCTIONAL_PROCESSOR_ACCUMULATOR_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_VALUE + 2,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_LAST_VALUE + 2,
					E65_TEST_FUNCTIONAL_PROCESSOR_FLAGS_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_X_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_Y_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_NON_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_START_ADDRESS + 1,
					E65_TEST_FUNCTIONAL_PROCESSOR_STACK_POINTER_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_STOP_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_WAIT_VALUE
					});
			}

			bool
			processor::command_sec_implied(
				__in e65::interface::runtime &runtime,
				__in e65::system::processor &processor,
				__in e65::interface::system::memory &memory
				)
			{
				bool result;

				memory.write(E65_TEST_FUNCTIONAL_PROCESSOR_START_ADDRESS, 0x38);
				processor.step(runtime, memory);

				result = compare(processor, {
					E65_TEST_FUNCTIONAL_PROCESSOR_ACCUMULATOR_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_VALUE + 2,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_LAST_VALUE + 2,
					E65_TEST_FUNCTIONAL_PROCESSOR_FLAGS_VALUE | E65_PFLAG(e65::type::E65_PFLAG_CARRY),
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_X_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_Y_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_NON_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_START_ADDRESS + 1,
					E65_TEST_FUNCTIONAL_PROCESSOR_STACK_POINTER_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_STOP_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_WAIT_VALUE
					});

				if(!result) {
					goto exit;
				}

				processor.reset(memory);
				processor.set_flags(processor.flags() | E65_PFLAG(e65::type::E65_PFLAG_CARRY));
				processor.step(runtime, memory);

				result = compare(processor, {
					E65_TEST_FUNCTIONAL_PROCESSOR_ACCUMULATOR_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_VALUE + 2,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_LAST_VALUE + 2,
					E65_TEST_FUNCTIONAL_PROCESSOR_FLAGS_VALUE | E65_PFLAG(e65::type::E65_PFLAG_CARRY),
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_X_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_Y_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_NON_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_START_ADDRESS + 1,
					E65_TEST_FUNCTIONAL_PROCESSOR_STACK_POINTER_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_STOP_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_WAIT_VALUE
					});

				if(!result) {
					goto exit;
				}

			exit:
				return result;
			}

			bool
			processor::command_sed_implied(
				__in e65::interface::runtime &runtime,
				__in e65::system::processor &processor,
				__in e65::interface::system::memory &memory
				)
			{
				bool result;

				memory.write(E65_TEST_FUNCTIONAL_PROCESSOR_START_ADDRESS, 0xf8);
				processor.step(runtime, memory);

				result = compare(processor, {
					E65_TEST_FUNCTIONAL_PROCESSOR_ACCUMULATOR_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_VALUE + 2,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_LAST_VALUE + 2,
					E65_TEST_FUNCTIONAL_PROCESSOR_FLAGS_VALUE | E65_PFLAG(e65::type::E65_PFLAG_DECIMAL_ENABLE),
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_X_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_Y_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_NON_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_START_ADDRESS + 1,
					E65_TEST_FUNCTIONAL_PROCESSOR_STACK_POINTER_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_STOP_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_WAIT_VALUE
					});

				if(!result) {
					goto exit;
				}

				processor.reset(memory);
				processor.set_flags(processor.flags() | E65_PFLAG(e65::type::E65_PFLAG_DECIMAL_ENABLE));
				processor.step(runtime, memory);

				result = compare(processor, {
					E65_TEST_FUNCTIONAL_PROCESSOR_ACCUMULATOR_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_VALUE + 2,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_LAST_VALUE + 2,
					E65_TEST_FUNCTIONAL_PROCESSOR_FLAGS_VALUE | E65_PFLAG(e65::type::E65_PFLAG_DECIMAL_ENABLE),
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_X_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_Y_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_NON_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_START_ADDRESS + 1,
					E65_TEST_FUNCTIONAL_PROCESSOR_STACK_POINTER_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_STOP_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_WAIT_VALUE
					});

				if(!result) {
					goto exit;
				}

			exit:
				return result;
			}

			bool
			processor::command_sei_implied(
				__in e65::interface::runtime &runtime,
				__in e65::system::processor &processor,
				__in e65::interface::system::memory &memory
				)
			{
				bool result;

				memory.write(E65_TEST_FUNCTIONAL_PROCESSOR_START_ADDRESS, 0x78);
				processor.step(runtime, memory);

				result = compare(processor, {
					E65_TEST_FUNCTIONAL_PROCESSOR_ACCUMULATOR_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_VALUE + 2,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_LAST_VALUE + 2,
					E65_TEST_FUNCTIONAL_PROCESSOR_FLAGS_VALUE | E65_PFLAG(e65::type::E65_PFLAG_IRQ_DISABLE),
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_X_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_Y_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_NON_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_START_ADDRESS + 1,
					E65_TEST_FUNCTIONAL_PROCESSOR_STACK_POINTER_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_STOP_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_WAIT_VALUE
					});

				if(!result) {
					goto exit;
				}

				processor.reset(memory);
				processor.set_flags(processor.flags() & ~E65_PFLAG(e65::type::E65_PFLAG_IRQ_DISABLE));
				processor.step(runtime, memory);

				result = compare(processor, {
					E65_TEST_FUNCTIONAL_PROCESSOR_ACCUMULATOR_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_VALUE + 2,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_LAST_VALUE + 2,
					E65_TEST_FUNCTIONAL_PROCESSOR_FLAGS_VALUE | E65_PFLAG(e65::type::E65_PFLAG_IRQ_DISABLE),
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_X_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_Y_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_NON_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_START_ADDRESS + 1,
					E65_TEST_FUNCTIONAL_PROCESSOR_STACK_POINTER_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_STOP_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_WAIT_VALUE
					});

				if(!result) {
					goto exit;
				}

			exit:
				return result;
			}

			bool
			processor::command_stp_implied(
				__in e65::interface::runtime &runtime,
				__in e65::system::processor &processor,
				__in e65::interface::system::memory &memory
				)
			{
				bool result;

				memory.write(E65_TEST_FUNCTIONAL_PROCESSOR_START_ADDRESS, 0xdb);
				processor.step(runtime, memory);

				result = compare(processor, {
					E65_TEST_FUNCTIONAL_PROCESSOR_ACCUMULATOR_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_VALUE + 3,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_LAST_VALUE + 3,
					E65_TEST_FUNCTIONAL_PROCESSOR_FLAGS_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_X_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_Y_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_NON_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_START_ADDRESS + 1,
					E65_TEST_FUNCTIONAL_PROCESSOR_STACK_POINTER_VALUE,
					true,
					E65_TEST_FUNCTIONAL_PROCESSOR_WAIT_VALUE
					});

				if(!result) {
					goto exit;
				}

				processor.reset(memory);
				processor.set_stop(true);
				processor.step(runtime, memory);

				result = compare(processor, {
					E65_TEST_FUNCTIONAL_PROCESSOR_ACCUMULATOR_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_VALUE + 2,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_LAST_VALUE + 2,
					E65_TEST_FUNCTIONAL_PROCESSOR_FLAGS_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_X_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_Y_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_NON_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_START_ADDRESS,
					E65_TEST_FUNCTIONAL_PROCESSOR_STACK_POINTER_VALUE,
					true,
					E65_TEST_FUNCTIONAL_PROCESSOR_WAIT_VALUE
					});

				if(!result) {
					goto exit;
				}

				processor.reset(memory);
				processor.interrupt(false);
				processor.set_stop(true);
				processor.step(runtime, memory);

				result = compare(processor, {
					E65_TEST_FUNCTIONAL_PROCESSOR_ACCUMULATOR_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_VALUE + 2,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_LAST_VALUE + 2,
					E65_TEST_FUNCTIONAL_PROCESSOR_FLAGS_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_X_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_Y_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_MASKABLE,
					true,
					E65_TEST_FUNCTIONAL_PROCESSOR_START_ADDRESS,
					E65_TEST_FUNCTIONAL_PROCESSOR_STACK_POINTER_VALUE,
					true,
					E65_TEST_FUNCTIONAL_PROCESSOR_WAIT_VALUE
					});

				if(!result) {
					goto exit;
				}

			exit:
				return result;
			}

			bool
			processor::command_wai_implied(
				__in e65::interface::runtime &runtime,
				__in e65::system::processor &processor,
				__in e65::interface::system::memory &memory
				)
			{
				bool result;

				memory.write(E65_TEST_FUNCTIONAL_PROCESSOR_START_ADDRESS, 0xcb);
				processor.step(runtime, memory);

				result = compare(processor, {
					E65_TEST_FUNCTIONAL_PROCESSOR_ACCUMULATOR_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_VALUE + 3,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_LAST_VALUE + 3,
					E65_TEST_FUNCTIONAL_PROCESSOR_FLAGS_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_X_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_Y_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_NON_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_START_ADDRESS + 1,
					E65_TEST_FUNCTIONAL_PROCESSOR_STACK_POINTER_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_STOP_VALUE,
					true
					});

				if(!result) {
					goto exit;
				}

				processor.reset(memory);
				processor.set_wait(true);
				processor.step(runtime, memory);

				result = compare(processor, {
					E65_TEST_FUNCTIONAL_PROCESSOR_ACCUMULATOR_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_VALUE + 2,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_LAST_VALUE + 2,
					E65_TEST_FUNCTIONAL_PROCESSOR_FLAGS_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_X_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_Y_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_NON_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_START_ADDRESS,
					E65_TEST_FUNCTIONAL_PROCESSOR_STACK_POINTER_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_STOP_VALUE,
					true
					});

				if(!result) {
					goto exit;
				}

				memory.write_word(E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_NON_MASKABLE_ADDRESS, 0x1000);
				memory.write(0x1000, 0xea);
				processor.reset(memory);
				processor.interrupt(false);
				processor.set_wait(true);
				processor.step(runtime, memory);

				result = compare(processor, {
					E65_TEST_FUNCTIONAL_PROCESSOR_ACCUMULATOR_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_VALUE + 9,
					E65_TEST_FUNCTIONAL_PROCESSOR_CYCLE_LAST_VALUE + 9,
					E65_TEST_FUNCTIONAL_PROCESSOR_FLAGS_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_X_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INDEX_Y_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_MASKABLE,
					E65_TEST_FUNCTIONAL_PROCESSOR_INTERRUPT_NON_MASKABLE,
					0x1001,
					E65_TEST_FUNCTIONAL_PROCESSOR_STACK_POINTER_VALUE - 3,
					E65_TEST_FUNCTIONAL_PROCESSOR_STOP_VALUE,
					E65_TEST_FUNCTIONAL_PROCESSOR_WAIT_VALUE
					});

				if(!result) {
					goto exit;
				}

			exit:
				return result;
			}

			bool
			processor::compare(
				__in e65::interface::system::processor &processor,
				__in const e65::test::functional::processor_state_t &expected
				)
			{
				bool result = true;

				result = (processor.accumulator() == expected.accumulator);
				if(!result) {
					goto exit;
				}

				result = (processor.cycle() == expected.cycle);
				if(!result) {
					goto exit;
				}

				result = (processor.cycle_last() == expected.cycle_last);
				if(!result) {
					goto exit;
				}

				result = (processor.flags() == expected.flags);
				if(!result) {
					goto exit;
				}

				result = (processor.index_x() == expected.index_x);
				if(!result) {
					goto exit;
				}

				result = (processor.index_y() == expected.index_y);
				if(!result) {
					goto exit;
				}

				result = (processor.interrupted(true) == expected.interrupt_maskable);
				if(!result) {
					goto exit;
				}

				result = (processor.interrupted(false) == expected.interrupt_non_maskable);
				if(!result) {
					goto exit;
				}

				result = (processor.program_counter() == expected.program_counter);
				if(!result) {
					goto exit;
				}

				result = (processor.stack_pointer() == expected.stack_pointer);
				if(!result) {
					goto exit;
				}

				result = (processor.stopped() == expected.stopped);
				if(!result) {
					goto exit;
				}

				result = (processor.waiting() == expected.waiting);
				if(!result) {
					goto exit;
				}

			exit:
				return result;
			}

			void
			processor::on_clear(void)
			{
				return;
			}

			std::string
			processor::on_failure(
				__in int test
				)
			{
				return E65_TEST_FUNCTIONAL_PROCESSOR_STRING(test);
			}

			bool
			processor::on_run(
				__in int test
				)
			{
				bool result = true;

				try {
					e65::runtime &runtime = e65::runtime::acquire();

					runtime.initialize();

					e65::system::memory &memory = e65::system::memory::acquire();
					e65::system::processor &processor = e65::system::processor::acquire();

					memory.write_word(E65_TEST_FUNCTIONAL_PROCESSOR_RESET_ADDRESS, E65_TEST_FUNCTIONAL_PROCESSOR_START_ADDRESS);
					processor.reset(memory);

					switch(test) {
						case E65_TEST_FUNCTIONAL_PROCESSOR_COMMAND_CLC_IMPLIED:
							result = command_clc_implied(runtime, processor, memory);
							break;
						case E65_TEST_FUNCTIONAL_PROCESSOR_COMMAND_CLD_IMPLIED:
							result = command_cld_implied(runtime, processor, memory);
							break;
						case E65_TEST_FUNCTIONAL_PROCESSOR_COMMAND_CLI_IMPLIED:
							result = command_cli_implied(runtime, processor, memory);
							break;
						case E65_TEST_FUNCTIONAL_PROCESSOR_COMMAND_CLV_IMPLIED:
							result = command_clv_implied(runtime, processor, memory);
							break;
						case E65_TEST_FUNCTIONAL_PROCESSOR_COMMAND_NOP_IMPLIED:
							result = command_nop_implied(runtime, processor, memory);
							break;
						case E65_TEST_FUNCTIONAL_PROCESSOR_COMMAND_SEC_IMPLIED:
							result = command_sec_implied(runtime, processor, memory);
							break;
						case E65_TEST_FUNCTIONAL_PROCESSOR_COMMAND_SED_IMPLIED:
							result = command_sed_implied(runtime, processor, memory);
							break;
						case E65_TEST_FUNCTIONAL_PROCESSOR_COMMAND_SEI_IMPLIED:
							result = command_sei_implied(runtime, processor, memory);
							break;
						case E65_TEST_FUNCTIONAL_PROCESSOR_COMMAND_STP_IMPLIED:
							result = command_stp_implied(runtime, processor, memory);
							break;
						case E65_TEST_FUNCTIONAL_PROCESSOR_COMMAND_WAI_IMPLIED:
							result = command_wai_implied(runtime, processor, memory);
							break;
						default:
							break;
					}

					runtime.uninitialize();
				} catch(...) {
					result = false;
				}

				return result;
			}

			bool
			processor::on_run_all(
				__inout std::set<int> &test
				)
			{
				int iter = 0;
				bool result = true;

				for(iter = 0; iter <= E65_TEST_FUNCTIONAL_PROCESSOR_MAX; ++iter) {

					if(!on_run(iter)) {
						test.insert(iter);
						result = false;
					}
				}

				return result;
			}

			std::string
			processor::to_string(void) const
			{
				std::stringstream result;

				result << E65_TEST_FUNCTIONAL_PROCESSOR_HEADER << "(" << E65_STRING_HEX(uintptr_t, this) << ")"
					<< " Fixture=" << e65::test::type::fixture::to_string();

				return result.str();
			}
		}
	}
}
