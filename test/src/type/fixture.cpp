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

#include "../../include/type/fixture.h"
#include "./fixture_type.h"

namespace e65 {

	namespace test {

		namespace type {

			fixture::fixture(
				__in int type
				) :
					m_type(type)
			{
				return;
			}

			fixture::~fixture(void)
			{
				return;
			}

			void
			fixture::clear(void)
			{
				m_failure.clear();
			}

			bool
			fixture::failed(void) const
			{
				return !m_failure.empty();
			}

			std::vector<std::string>
			fixture::failure(void)
			{
				std::set<int>::iterator failure;
				std::vector<std::string> result;

				for(failure = m_failure.begin(); failure != m_failure.end(); ++failure) {
					result.push_back(on_failure(*failure));
				}

				return result;
			}

			bool
			fixture::run(
				__in int test
				)
			{
				bool result;

				m_failure.clear();

				result = on_run(test);
				if(!result) {
					m_failure.insert(test);
				}

				return result;
			}

			bool
			fixture::run_all(void)
			{
				bool result;
				std::set<int> test;

				result = on_run_all(test);
				if(!result) {
					m_failure = test;
				}

				return result;
			}

			std::string
			fixture::to_string(void) const
			{
				std::stringstream result;

				result << E65_TEST_TYPE_FIXTURE_HEADER << "(" << E65_STRING_HEX(uintptr_t, this) << ")"
					<< " Type=" << m_type << "(" << E65_FIXTURE_STRING(m_type) << ")"
					<< ", Failure[" << m_failure.size() << "]=" << E65_STRING_HEX(uintptr_t, &m_failure);

				return result.str();
			}
		}
	}
}
