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
			processor::command_nop_implied(
				__in e65::interface::system::processor &processor,
				__in e65::interface::system::memory &memory
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
				return E65_TEST_FUNCTIONAL_PROCESSOR_STRING(test);
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
					case E65_TEST_FUNCTIONAL_PROCESSOR_COMMAND_NOP_IMPLIED:
						result = command_nop_implied(processor, memory);
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
