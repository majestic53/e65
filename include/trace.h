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

#ifndef E65_TRACE_H_
#define E65_TRACE_H_

#include <ctime>
#include <queue>
#include "./type/singleton.h"
#include "./type/thread.h"

namespace e65 {

	typedef std::tuple<std::string, std::string, int, size_t, std::string, std::time_t> trace_t;

	class trace :
			public e65::type::singleton<e65::trace>,
			protected e65::type::thread {

		public:

			~trace(void);

			bool empty(void) const;

			void flush(void);

			void generate(
				__in int level,
				__in const std::string &prefix,
				__in const std::string &message,
				__in const std::string &file,
				__in const std::string &function,
				__in size_t line,
				__in const char *format,
				...
				);

			size_t size(void) const;

			std::string to_string(void) const override;

		protected:

			friend class e65::type::singleton<e65::trace>;

			trace(void);

			trace(
				__in const trace &other
				) = delete;

			trace &operator=(
				__in const trace &other
				) = delete;

			e65::trace_t dequeue(void);

			void clear(void);

			void enqueue(
				__in const e65::trace_t &entry
				);

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

			void process(
				__in const e65::trace_t &entry
				);

			std::string timestamp(
				__in const std::time_t &time
				);

			std::queue<e65::trace_t> m_queue;

			std::mutex m_queue_mutex;
	};
}

#endif // E65_TRACE_H_
