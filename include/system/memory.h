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

#ifndef E65_SYSTEM_MEMORY_H_
#define E65_SYSTEM_MEMORY_H_

#include "../interface/system/memory.h"
#include "../type/singleton.h"

namespace e65 {

	namespace system {

		class memory :
				public e65::type::singleton<e65::system::memory>,
				public e65::interface::system::memory {

			public:

				~memory(void);

				void clear(void);

				void load(
					__in const std::vector<uint8_t> &data,
					__in uint16_t origin
					);

				uint8_t read(
					__in uint16_t address
					) const override;

				uint16_t read_word(
					__in uint16_t address
					) const override;

				std::string to_string(void) const override;

				void write(
					__in uint16_t address,
					__in uint8_t value
					) override;

				void write_word(
					__in uint16_t address,
					__in uint16_t value
					) override;

			protected:

				friend class e65::type::singleton<e65::system::memory>;

				memory(void);

				memory(
					__in const memory &other
					) = delete;

				memory &operator=(
					__in const memory &other
					) = delete;

				bool on_initialize(
					__in const void *context,
					__in size_t length
					) override;

				void on_uninitialize(void) override;

				std::vector<uint8_t> m_memory;
		};
	}
}

#endif // E65_SYSTEM_MEMORY_H_
