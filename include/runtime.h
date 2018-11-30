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
#include "./e65.h"
#include "./trace.h"

namespace e65 {

	class runtime :
			public e65::type::singleton<e65::runtime>,
			public e65::interface::runtime {

		public:

			~runtime(void);

			bool breakpoint(
				__in uint16_t address
				) override;

			bool breakpoint_clear(
				__in uint16_t address
				);

			void breakpoint_clear_all(void);

			std::string breakpoint_list(void) const;

			bool breakpoint_set(
				__in uint16_t address
				);

			e65::interface::system::bus &bus(void) override;

			bool debug(void) const override;

			bool debug_break(void);

			bool debug_run(void);

			bool debug_step(
				__in_opt uint32_t offset = 1
				);

			bool debug_step_frame(
				__in_opt uint32_t offset = 1
				);

			bool register_handler(
				__in e65_cb handler
				);

			bool reset(void);

			void run(
				__in const std::string &path,
				__in bool hex,
				__in_opt bool debug = false
				);

			bool running(void) const;

			void signal_event(
				__in int type,
				__in uint16_t address
				) override;

			bool terminate(void);

			std::string to_string(void) const override;

			static std::string version(void);

		protected:

			friend class e65::type::singleton<e65::runtime>;

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

			void on_uninitialize(void) override;

			bool poll(void);

			bool step_frame(
				__in_opt uint32_t offset = 1
				);

			std::set<uint16_t> m_breakpoint;

			e65::system::bus &m_bus;

			bool m_debug;

			bool m_debug_running;

			e65_cb m_handler;

			bool m_running;

			e65::trace &m_trace;
	};
}

#endif // E65_RUNTIME_H_
