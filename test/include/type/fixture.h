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

#ifndef E65_TEST_TYPE_FIXTURE_H_
#define E65_TEST_TYPE_FIXTURE_H_

#include <set>
#include <vector>
#include "../../../include/define.h"

namespace e65 {

	namespace test {

		namespace type {

			enum {
				E65_FIXTURE_PROCESSOR_INTERFACE = 0,
			};

			#define E65_FIXTURE_MAX e65::test::type::E65_FIXTURE_PROCESSOR_INTERFACE

			static const std::string E65_FIXTURE_STR[] = {
				"Test::Processor::Interface",
				};

			#define E65_FIXTURE_STRING(_TYPE_) \
				(((_TYPE_) > E65_FIXTURE_MAX) ? E65_STRING_UNKNOWN : \
					E65_STRING_CHECK(e65::test::type::E65_FIXTURE_STR[_TYPE_]))

			class fixture {

				public:

					fixture(
						__in int type
						);

					virtual ~fixture(void);

					void clear(void);

					bool failed(void) const;

					std::vector<std::string> failure(void);

					bool run(
						__in int test
						);

					bool run_all(void);

					virtual std::string to_string(void) const;

				protected:

					fixture(
						__in const fixture &other
						) = delete;

					fixture &operator=(
						__in const fixture &other
						) = delete;

					virtual void on_clear(void) = 0;

					virtual std::string on_failure(
						__in int test
						) = 0;

					virtual bool on_run(
						__in int test
						) = 0;

					virtual bool on_run_all(
						__inout std::set<int> &test
						) = 0;

					std::set<int> m_failure;

					int m_type;
			};
		}
	}
}

#endif // E65_TEST_TYPE_FIXTURE_TYPE_H_
