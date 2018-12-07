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
#include "../../include/interface/memory.h"
#include "./memory_type.h"

namespace e65 {

	namespace test {

		namespace interface {

			memory::memory(void) :
				e65::test::type::fixture(e65::test::type::E65_FIXTURE_INTERFACE_MEMORY)
			{
				return;
			}

			memory::~memory(void)
			{
				return;
			}

			void
			memory::on_clear(void)
			{
				return;
			}

			std::string
			memory::on_failure(
				__in int test
				)
			{
				return E65_TEST_INTERFACE_MEMORY_STRING(test);
			}

			bool
			memory::on_run(
				__in int test
				)
			{
				bool result = true;

				try {
					e65::system::memory &memory = e65::system::memory::acquire();

					memory.initialize();

					switch(test) {
						case E65_TEST_INTERFACE_MEMORY_READ:
							result = read(memory);
							break;
						case E65_TEST_INTERFACE_MEMORY_READ_WORD:
							result = read_word(memory);
							break;
						case E65_TEST_INTERFACE_MEMORY_WRITE:
							result = write(memory);
							break;
						case E65_TEST_INTERFACE_MEMORY_WRITE_WORD:
							result = write_word(memory);
							break;
						default:
							break;
					}

					memory.uninitialize();
				} catch(...) {
					result = false;
				}

				return result;
			}

			bool
			memory::on_run_all(
				__inout std::set<int> &test
				)
			{
				int iter = 0;
				bool result = true;

				for(iter = 0; iter <= E65_TEST_INTERFACE_MEMORY_MAX; ++iter) {

					if(!on_run(iter)) {
						test.insert(iter);
						result = false;
					}
				}

				return result;
			}

			bool
			memory::read(
				__in e65::interface::system::memory &memory
				)
			{
				bool result;
				uint8_t value;
				uint16_t address = std::rand();

				switch(address) {
					case E65_TEST_INTERFACE_MEMORY_KEY_ADDRESS_LOW ... E65_TEST_INTERFACE_MEMORY_KEY_ADDRESS_HIGH:
					case E65_TEST_INTERFACE_MEMORY_VIDEO_ADDRESS_LOW ... E65_TEST_INTERFACE_MEMORY_VIDEO_ADDRESS_HIGH:
						value = E65_TEST_INTERFACE_MEMORY_VALUE_ZERO;
						break;
					default:
						value = E65_TEST_INTERFACE_MEMORY_VALUE;
						break;
				}

				result = (memory.read(address) == value);
				if(result) {
					address = std::rand();
					value = std::rand();

					memory.write(address, value);
					result = (memory.read(address) == value);
				}

				return result;
			}

			bool
			memory::read_word(
				__in e65::interface::system::memory &memory
				)
			{
				bool result;
				uint16_t address = std::rand(), value = std::rand();

				if(address == UINT16_MAX) {
					--address;
				}

				memory.write_word(address, value);

				result = (memory.read_word(address) == value);
				if(result) {
					address = UINT16_MAX;
					value = std::rand();

					memory.write_word(address, value);
					result = (memory.read_word(address) == value);
				}

				return result;
			}

			std::string
			memory::to_string(void) const
			{
				std::stringstream result;

				result << E65_TEST_INTERFACE_MEMORY_HEADER << "(" << E65_STRING_HEX(uintptr_t, this) << ")"
					<< " Fixture=" << e65::test::type::fixture::to_string();

				return result.str();
			}

			bool
			memory::write(
				__in e65::interface::system::memory &memory
				)
			{
				bool result;
				uint8_t value = std::rand();
				uint16_t address = std::rand();

				memory.write(address, value);
				result = (memory.read(address) == value);

				return result;
			}

			bool
			memory::write_word(
				__in e65::interface::system::memory &memory
				)
			{
				bool result;
				uint16_t address = std::rand(), value = std::rand();

				if(address == UINT16_MAX) {
					--address;
				}

				memory.write_word(address, value);

				result = (memory.read_word(address) == value);
				if(result) {
					address = UINT16_MAX;
					value = std::rand();

					memory.write_word(address, value);
					result = (memory.read_word(address) == value);
				}

				return result;
			}
		}
	}
}
