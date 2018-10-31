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

#ifndef E65_TYPE_SIGNAL_H_
#define E65_TYPE_SIGNAL_H_

#include <condition_variable>
#include <mutex>
#include "../define.h"

namespace e65 {

	namespace type {

		class signal {

			public:

				signal(void);

				virtual ~signal(void);

				void notify(void);

				virtual std::string to_string(void) const;

				bool timeout(void) const;

				bool valid(void) const;

				bool wait(
					__in_opt uint32_t timeout = 0
					);

			protected:

				signal(
					__in const signal &other
					) = delete;

				signal &operator=(
					__in const signal &other
					) = delete;

				void abandon(void);

				void clear(void);

				std::condition_variable m_condition;

				std::mutex m_mutex;

				int m_state;
		};
	}
}

#endif // E65_TYPE_SIGNAL_H_
