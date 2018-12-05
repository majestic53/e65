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

#ifndef E65_TEST_INTERFACE_PROCESSOR_H_
#define E65_TEST_INTERFACE_PROCESSOR_H_

#include "../../../include/interface/system/memory.h"
#include "../../../include/interface/system/processor.h"
#include "../../include/type/fixture.h"

namespace e65 {

	namespace test {

		namespace interface {

			class processor :
					public e65::test::type::fixture {

				public:

					processor(void);

					virtual ~processor(void);

					virtual std::string to_string(void) const override;

				protected:

					processor(
						__in const processor &other
						) = delete;

					processor &operator=(
						__in const processor &other
						) = delete;

					bool accumulator(
						__in e65::interface::system::processor &processor
						);

					bool cycle(
						__in e65::interface::system::processor &processor
						);

					bool cycle_last(
						__in e65::interface::system::processor &processor
						);

					bool flags(
						__in e65::interface::system::processor &processor
						);

					bool index_x(
						__in e65::interface::system::processor &processor
						);

					bool index_y(
						__in e65::interface::system::processor &processor
						);

					bool interrupt(
						__in e65::interface::system::processor &processor
						);

					void on_clear(void) override;

					std::string on_failure(
						__in int test
						) override;

					bool on_run(
						__in int test
						) override;

					bool on_run_all(
						__inout std::set<int> &test
						) override;

					bool program_counter(
						__in e65::interface::system::processor &processor
						);

					bool reset(
						__in e65::interface::system::processor &processor,
						__in e65::interface::system::memory &memory
						);

					bool stack_pointer(
						__in e65::interface::system::processor &processor
						);

					bool stop(
						__in e65::interface::system::processor &processor
						);

					bool wait(
						__in e65::interface::system::processor &processor
						);

			};
		}
	}
}

#endif // E65_TEST_INTERFACE_PROCESSOR_H_
