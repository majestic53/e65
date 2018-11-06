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

#ifndef E65_RUNTIME_H_
#define E65_RUNTIME_H_

#include <set>
#include "./interface/runtime.h"
#include "./system/bus.h"
#include "./trace.h"

namespace e65 {

	class runtime :
			public e65::interface::singleton<e65::runtime>,
			public e65::interface::runtime,
			protected e65::type::thread {

		public:

			~runtime(void);

			bool breakpoint_clear(
				__in uint16_t address
				);

			bool breakpoint_contains(
				__in uint16_t address
				);

			bool breakpoint_set(
				__in uint16_t address
				);

			std::set<uint16_t> breakpoints(void) const;

			void breakpoints_clear(void);

			e65::interface::system::bus &bus(void) override;

			uint32_t frame(void) const override;

			void run(
				__in const std::string &path,
				__in_opt bool debug = false
				);

			bool step(void);

			std::string to_string(void) const override;

			e65::interface::trace &trace(void) override;

			static std::string version(void);

			bool wait(
				__in_opt uint32_t timeout = 0
				);

		protected:

			friend class e65::interface::singleton<e65::runtime>;

			runtime(void);

			runtime(
				__in const runtime &other
				) = delete;

			runtime &operator=(
				__in const runtime &other
				) = delete;

			bool on_initialize(
				__in const void *context,
				__in size_t length
				) override;

			bool on_run(
				__in const void *context,
				__in size_t length
				) override;

			bool on_start(
				__in const void *context,
				__in size_t length
				) override;

			void on_stop(void) override;

			void on_uninitialize(void) override;

			bool poll(void);

			std::set<uint16_t> m_breakpoint;

			e65::system::bus &m_bus;

			bool m_debug;

			uint32_t m_frame;

			e65::trace &m_trace;
	};
}

#endif // E65_RUNTIME_H_
