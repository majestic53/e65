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

#ifndef E65_TEST_FUNCTIONAL_PROCESSOR_H_
#define E65_TEST_FUNCTIONAL_PROCESSOR_H_

#include "../../../include/interface/system/memory.h"
#include "../../../include/interface/system/processor.h"
#include "../../include/type/fixture.h"

namespace e65 {

	namespace test {

		namespace functional {

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

					bool command_nop_implied(
						__in e65::interface::system::processor &processor,
						__in e65::interface::system::memory &memory
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
			};
		}
	}
}

#endif // E65_TEST_FUNCTIONAL_PROCESSOR_H_
