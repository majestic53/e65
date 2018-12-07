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

#include "../../../include/system/input.h"
#include "../../../include/system/memory.h"
#include "../../include/interface/input.h"
#include "./input_type.h"

namespace e65 {

	namespace test {

		namespace interface {

			input::input(void) :
				e65::test::type::fixture(e65::test::type::E65_FIXTURE_INTERFACE_INPUT)
			{
				return;
			}

			input::~input(void)
			{
				return;
			}

			bool
			input::key(
				__in e65::interface::system::input &input,
				__in e65::interface::system::memory &memory
				)
			{
				bool result;

				result = (memory.read(E65_TEST_INTERFACE_INPUT_KEY_ADDRESS) == E65_TEST_INTERFACE_INPUT_KEY_VALUE);
				if(result) {
					uint8_t value = std::rand();

					input.key(memory, value);
					result = (memory.read(E65_TEST_INTERFACE_INPUT_KEY_ADDRESS) == value);
				}

				return result;
			}

			void
			input::on_clear(void)
			{
				return;
			}

			std::string
			input::on_failure(
				__in int test
				)
			{
				return E65_TEST_INTERFACE_INPUT_STRING(test);
			}

			bool
			input::on_run(
				__in int test
				)
			{
				bool result = true;

				try {
					e65::system::memory &memory = e65::system::memory::acquire();
					e65::system::input &input = e65::system::input::acquire();

					memory.initialize();
					input.initialize();

					switch(test) {
						case E65_TEST_INTERFACE_INPUT_KEY:
							result = key(input, memory);
							break;
						default:
							break;
					}

					input.uninitialize();
					memory.uninitialize();
				} catch(...) {
					result = false;
				}

				return result;
			}

			bool
			input::on_run_all(
				__inout std::set<int> &test
				)
			{
				int iter = 0;
				bool result = true;

				for(iter = 0; iter <= E65_TEST_INTERFACE_INPUT_MAX; ++iter) {

					if(!on_run(iter)) {
						test.insert(iter);
						result = false;
					}
				}

				return result;
			}

			std::string
			input::to_string(void) const
			{
				std::stringstream result;

				result << E65_TEST_INTERFACE_INPUT_HEADER << "(" << E65_STRING_HEX(uintptr_t, this) << ")"
					<< " Fixture=" << e65::test::type::fixture::to_string();

				return result.str();
			}
		}
	}
}
