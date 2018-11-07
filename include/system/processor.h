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

#ifndef E65_SYSTEM_PROCESSOR_H_
#define E65_SYSTEM_PROCESSOR_H_

#include "../interface/system/processor.h"
#include "./memory.h"

namespace e65 {

	namespace system {

		class processor :
				public e65::interface::singleton<e65::system::processor>,
				public e65::interface::system::processor {

			public:

				~processor(void);

				uint32_t cycle(void) const override;

				void reset(
					__in e65::interface::system::memory &memory
					) override;

				void step(
					__in e65::interface::system::memory &memory
					);

				std::string to_string(void) const override;

				// TODO

			protected:

				friend class e65::interface::singleton<e65::system::processor>;

				processor(void);

				processor(
					__in const processor &other
					) = delete;

				processor &operator=(
					__in const processor &other
					) = delete;

				bool on_initialize(
					__in const void *context,
					__in size_t length
					) override;

				void on_uninitialize(void) override;

				// TODO

				uint32_t m_cycle;
		};
	}
}

#endif // E65_SYSTEM_PROCESSOR_H_
