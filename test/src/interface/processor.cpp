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
				e65::test::type::fixture(e65::test::type::E65_FIXTURE_PROCESSOR_INTERFACE)
			{
				return;
			}

			processor::~processor(void)
			{
				return;
			}

			bool
			processor::accumulator(
				__in e65::interface::system::processor &processor
				)
			{
				bool result = true;

				// TODO

				return result;
			}

			bool
			processor::cycle(
				__in e65::interface::system::processor &processor
				)
			{
				bool result = true;

				// TODO

				return result;
			}

			bool
			processor::cycle_last(
				__in e65::interface::system::processor &processor
				)
			{
				bool result = true;

				// TODO

				return result;
			}

			bool
			processor::flags(
				__in e65::interface::system::processor &processor
				)
			{
				bool result = true;

				// TODO

				return result;
			}

			bool
			processor::index_x(
				__in e65::interface::system::processor &processor
				)
			{
				bool result = true;

				// TODO

				return result;
			}

			bool
			processor::index_y(
				__in e65::interface::system::processor &processor
				)
			{
				bool result = true;

				// TODO

				return result;
			}

			bool
			processor::interrupt(
				__in e65::interface::system::processor &processor
				)
			{
				bool result = true;

				// TODO

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
				return E65_SUBTEST_INTERFACE_PROCESSOR_STRING(test);
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
					case E65_SUBTEST_INTERFACE_PROCESSOR_ACCUMULATOR:
						result = accumulator(processor);
						break;
					case E65_SUBTEST_INTERFACE_PROCESSOR_CYCLE:
						result = cycle(processor);
						break;
					case E65_SUBTEST_INTERFACE_PROCESSOR_CYCLE_LAST:
						result = cycle_last(processor);
						break;
					case E65_SUBTEST_INTERFACE_PROCESSOR_FLAGS:
						result = flags(processor);
						break;
					case E65_SUBTEST_INTERFACE_PROCESSOR_INDEX_X:
						result = index_x(processor);
						break;
					case E65_SUBTEST_INTERFACE_PROCESSOR_INDEX_Y:
						result = index_y(processor);
						break;
					case E65_SUBTEST_INTERFACE_PROCESSOR_INTERRUPT:
						result = interrupt(processor);
						break;
					case E65_SUBTEST_INTERFACE_PROCESSOR_PROGRAM_COUNTER:
						result = program_counter(processor);
						break;
					case E65_SUBTEST_INTERFACE_PROCESSOR_RESET:
						result = reset(processor, memory);
						break;
					case E65_SUBTEST_INTERFACE_PROCESSOR_STACK_POINTER:
						result = stack_pointer(processor);
						break;
					case E65_SUBTEST_INTERFACE_PROCESSOR_STOP:
						result = stop(processor);
						break;
					case E65_SUBTEST_INTERFACE_PROCESSOR_WAIT:
						result = wait(processor);
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

				for(iter = 0; iter <= E65_SUBTEST_INTERFACE_PROCESSOR_MAX; ++iter) {

					if(!on_run(iter)) {
						test.insert(iter);
						result = false;
					}
				}

				return result;
			}

			bool
			processor::program_counter(
				__in e65::interface::system::processor &processor
				)
			{
				bool result = true;

				// TODO

				return result;
			}

			bool
			processor::reset(
				__in e65::interface::system::processor &processor,
				__in e65::interface::system::memory &memory
				)
			{
				bool result = true;

				// TODO

				return result;
			}

			bool
			processor::stack_pointer(
				__in e65::interface::system::processor &processor
				)
			{
				bool result = true;

				// TODO

				return result;
			}

			bool
			processor::stop(
				__in e65::interface::system::processor &processor
				)
			{
				bool result = true;

				// TODO

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
				__in e65::interface::system::processor &processor
				)
			{
				bool result = true;

				// TODO

				return result;
			}
		}
	}
}
