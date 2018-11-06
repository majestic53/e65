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

#ifndef E65_SYSTEM_INPUT_H_
#define E65_SYSTEM_INPUT_H_

#include "../interface/system/input.h"
#include "./memory.h"

namespace e65 {

	namespace system {

		class input :
				public e65::interface::singleton<e65::system::input>,
				public e65::interface::system::input {

			public:

				~input(void);

				void clear(
					__in e65::interface::system::memory &memory
					) override;

				void key(
					__in e65::interface::system::memory &memory,
					__in int value
					) override;

				std::string to_string(void) const override;

				void update(
					__in e65::interface::system::memory &memory
					) override;

			protected:

				friend class e65::interface::singleton<e65::system::input>;

				input(void);

				input(
					__in const input &other
					) = delete;

				input &operator=(
					__in const input &other
					) = delete;

				bool on_initialize(
					__in const void *context,
					__in size_t length
					) override;

				void on_uninitialize(void) override;
		};
	}
}

#endif // E65_SYSTEM_INPUT_H_
