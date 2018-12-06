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

#include "../../../include/system/memory.h"
#include "../../../include/system/processor.h"
#include "../../include/interface/processor.h"
#include "./processor_type.h"

namespace e65 {

	namespace test {

		namespace interface {

			processor::processor(void) :
				e65::test::type::fixture(e65::test::type::E65_FIXTURE_INTERFACE_PROCESSOR)
			{
				return;
			}

			processor::~processor(void)
			{
				return;
			}

			bool
			processor::accumulator(
				__in e65::interface::system::processor &processor,
				__in e65::interface::system::memory &memory
				)
			{
				bool result = true;

				try {
					processor.reset(memory);

					result = (processor.accumulator() == E65_TEST_INTERFACE_PROCESSOR_ACCUMULATOR_VALUE);
					if(result) {
						uint8_t value = std::rand();

						processor.set_accumulator(value);
						result = (processor.accumulator() == value);
					}
				} catch(...) {
					result = false;
				}

				return result;
			}

			bool
			processor::cycle(
				__in e65::interface::system::processor &processor,
				__in e65::interface::system::memory &memory
				)
			{
				bool result = true;

				try {
					processor.reset(memory);

					result = (processor.cycle() == E65_TEST_INTERFACE_PROCESSOR_CYCLE_VALUE);
				} catch(...) {
					result = false;
				}

				return result;
			}

			bool
			processor::cycle_last(
				__in e65::interface::system::processor &processor,
				__in e65::interface::system::memory &memory
				)
			{
				bool result = true;

				try {
					processor.reset(memory);

					result = (processor.cycle_last() == E65_TEST_INTERFACE_PROCESSOR_CYCLE_LAST_VALUE);
				} catch(...) {
					result = false;
				}

				return result;
			}

			bool
			processor::flags(
				__in e65::interface::system::processor &processor,
				__in e65::interface::system::memory &memory
				)
			{
				bool result = true;

				try {
					processor.reset(memory);

					result = (processor.flags() == E65_TEST_INTERFACE_PROCESSOR_FLAGS_VALUE);
					if(result) {
						uint8_t value = std::rand();

						processor.set_flags(value);
						result = (processor.flags() == value);
					}
				} catch(...) {
					result = false;
				}

				return result;
			}

			bool
			processor::index_x(
				__in e65::interface::system::processor &processor,
				__in e65::interface::system::memory &memory
				)
			{
				bool result = true;

				try {
					processor.reset(memory);

					result = (processor.index_x() == E65_TEST_INTERFACE_PROCESSOR_INDEX_X_VALUE);
					if(result) {
						uint8_t value = std::rand();

						processor.set_index_x(value);
						result = (processor.index_x() == value);
					}
				} catch(...) {
					result = false;
				}

				return result;
			}

			bool
			processor::index_y(
				__in e65::interface::system::processor &processor,
				__in e65::interface::system::memory &memory
				)
			{
				bool result = true;

				try {
					processor.reset(memory);

					result = (processor.index_y() == E65_TEST_INTERFACE_PROCESSOR_INDEX_Y_VALUE);
					if(result) {
						uint8_t value = std::rand();

						processor.set_index_y(value);
						result = (processor.index_y() == value);
					}
				} catch(...) {
					result = false;
				}

				return result;
			}

			bool
			processor::interrupt(
				__in e65::interface::system::processor &processor,
				__in e65::interface::system::memory &memory
				)
			{
				bool result = true;

				try {
					processor.reset(memory);

					result = !processor.interrupted(false);
					if(!result) {
						goto exit;
					}

					processor.interrupt(false);

					result = processor.interrupted(false);
					if(!result) {
						goto exit;
					}

					result = !processor.interrupted(true);
					if(!result) {
						goto exit;
					}

					processor.interrupt(true);

					result = !processor.interrupted(true);
					if(!result) {
						goto exit;
					}

					processor.set_flags(processor.flags() & ~E65_PFLAG(e65::type::E65_PFLAG_IRQ_DISABLE));
					processor.interrupt(true);

					result = processor.interrupted(true);
					if(!result) {
						goto exit;
					}
				} catch(...) {
					result = false;
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
				return E65_TEST_INTERFACE_PROCESSOR_STRING(test);
			}

			bool
			processor::on_run(
				__in int test
				)
			{
				bool result = true;

				e65::system::memory &memory = e65::system::memory::acquire();
				e65::system::processor &processor = e65::system::processor::acquire();

				memory.initialize();
				processor.initialize();

				switch(test) {
					case E65_TEST_INTERFACE_PROCESSOR_ACCUMULATOR:
						result = accumulator(processor, memory);
						break;
					case E65_TEST_INTERFACE_PROCESSOR_CYCLE:
						result = cycle(processor, memory);
						break;
					case E65_TEST_INTERFACE_PROCESSOR_CYCLE_LAST:
						result = cycle_last(processor, memory);
						break;
					case E65_TEST_INTERFACE_PROCESSOR_FLAGS:
						result = flags(processor, memory);
						break;
					case E65_TEST_INTERFACE_PROCESSOR_INDEX_X:
						result = index_x(processor, memory);
						break;
					case E65_TEST_INTERFACE_PROCESSOR_INDEX_Y:
						result = index_y(processor, memory);
						break;
					case E65_TEST_INTERFACE_PROCESSOR_INTERRUPT:
						result = interrupt(processor, memory);
						break;
					case E65_TEST_INTERFACE_PROCESSOR_PROGRAM_COUNTER:
						result = program_counter(processor, memory);
						break;
					case E65_TEST_INTERFACE_PROCESSOR_RESET:
						result = reset(processor, memory);
						break;
					case E65_TEST_INTERFACE_PROCESSOR_STACK_POINTER:
						result = stack_pointer(processor, memory);
						break;
					case E65_TEST_INTERFACE_PROCESSOR_STOP:
						result = stop(processor, memory);
						break;
					case E65_TEST_INTERFACE_PROCESSOR_WAIT:
						result = wait(processor, memory);
						break;
					default:
						break;
				}

				processor.uninitialize();
				memory.uninitialize();

				return result;
			}

			bool
			processor::on_run_all(
				__inout std::set<int> &test
				)
			{
				int iter = 0;
				bool result = true;

				for(iter = 0; iter <= E65_TEST_INTERFACE_PROCESSOR_MAX; ++iter) {

					if(!on_run(iter)) {
						test.insert(iter);
						result = false;
					}
				}

				return result;
			}

			bool
			processor::program_counter(
				__in e65::interface::system::processor &processor,
				__in e65::interface::system::memory &memory
				)
			{
				bool result = true;

				try {
					uint16_t address = std::rand();

					memory.write_word(E65_TEST_INTERFACE_PROCESSOR_RESET_ADDRESS, address);
					processor.reset(memory);

					result = (processor.program_counter() == address);
					if(result) {
						address = std::rand();

						processor.set_program_counter(address);
						result = (processor.program_counter() == address);
					}
				} catch(...) {
					result = false;
				}

				return result;
			}

			bool
			processor::reset(
				__in e65::interface::system::processor &processor,
				__in e65::interface::system::memory &memory
				)
			{
				bool result = true;

				try {
					uint16_t address = std::rand();

					memory.write_word(E65_TEST_INTERFACE_PROCESSOR_RESET_ADDRESS, address);
					processor.reset(memory);

					result = (processor.accumulator() == E65_TEST_INTERFACE_PROCESSOR_ACCUMULATOR_VALUE);
					if(!result) {
						goto exit;
					}

					result = (processor.cycle() == E65_TEST_INTERFACE_PROCESSOR_CYCLE_VALUE);
					if(!result) {
						goto exit;
					}

					result = (processor.cycle_last() == E65_TEST_INTERFACE_PROCESSOR_CYCLE_LAST_VALUE);
					if(!result) {
						goto exit;
					}

					result = (processor.flags() == E65_TEST_INTERFACE_PROCESSOR_FLAGS_VALUE);
					if(!result) {
						goto exit;
					}

					result = (processor.index_x() == E65_TEST_INTERFACE_PROCESSOR_INDEX_X_VALUE);
					if(!result) {
						goto exit;
					}

					result = (processor.index_y() == E65_TEST_INTERFACE_PROCESSOR_INDEX_Y_VALUE);
					if(!result) {
						goto exit;
					}

					result = (processor.program_counter() == address);
					if(!result) {
						goto exit;
					}

					result = (processor.stack_pointer() == E65_TEST_INTERFACE_PROCESSOR_STACK_POINTER_VALUE);
					if(!result) {
						goto exit;
					}

					result = (processor.stopped() == E65_TEST_INTERFACE_PROCESSOR_STOP_VALUE);
					if(!result) {
						goto exit;
					}

					result = (processor.waiting() == E65_TEST_INTERFACE_PROCESSOR_WAIT_VALUE);
					if(!result) {
						goto exit;
					}
				} catch(...) {
					result = false;
				}

			exit:
				return result;
			}

			bool
			processor::stack_pointer(
				__in e65::interface::system::processor &processor,
				__in e65::interface::system::memory &memory
				)
			{
				bool result = true;

				try {
					processor.reset(memory);

					result = (processor.stack_pointer() == E65_TEST_INTERFACE_PROCESSOR_STACK_POINTER_VALUE);
					if(result) {
						uint8_t value = std::rand();

						processor.set_stack_pointer(value);
						result = (processor.stack_pointer() == value);
					}
				} catch(...) {
					result = false;
				}

				return result;
			}

			bool
			processor::stop(
				__in e65::interface::system::processor &processor,
				__in e65::interface::system::memory &memory
				)
			{
				bool result = true;

				try {
					processor.reset(memory);

					result = (processor.stopped() == E65_TEST_INTERFACE_PROCESSOR_STOP_VALUE);
					if(result) {
						processor.set_stop(true);

						result = processor.stopped();
						if(result) {
							processor.set_stop(false);
							result = !processor.stopped();
						}
					}
				} catch(...) {
					result = false;
				}

				return result;
			}

			std::string
			processor::to_string(void) const
			{
				std::stringstream result;

				result << E65_TEST_INTERFACE_PROCESSOR_HEADER << "(" << E65_STRING_HEX(uintptr_t, this) << ")"
					<< " Fixture=" << e65::test::type::fixture::to_string();

				return result.str();
			}

			bool
			processor::wait(
				__in e65::interface::system::processor &processor,
				__in e65::interface::system::memory &memory
				)
			{
				bool result = true;

				try {
					processor.reset(memory);

					result = (processor.waiting() == E65_TEST_INTERFACE_PROCESSOR_WAIT_VALUE);
					if(result) {
						processor.set_wait(true);

						result = processor.waiting();
						if(result) {
							processor.set_wait(false);
							result = !processor.waiting();
						}
					}
				} catch(...) {
					result = false;
				}

				return result;
			}
		}
	}
}
