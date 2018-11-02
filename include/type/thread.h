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

#ifndef E65_TYPE_THREAD_H_
#define E65_TYPE_THREAD_H_

#include <thread>
#include "../exception.h"
#include "./signal.h"

namespace e65 {

	namespace type {

		class thread {

			public:

				thread(void);

				virtual ~thread(void);

				bool active(void) const;

				bool notifiable(void) const;

				void notify(void);

				void start(
					__in bool notifiable,
					__in_opt const void *context = nullptr,
					__in_opt size_t length = 0
					);

				void stop(void);

				virtual std::string to_string(void) const;

				bool wait(
					__in_opt uint32_t timeout = 0
					);

			protected:

				thread(
					__in const thread &other
					) = delete;

				thread &operator=(
					__in const thread &other
					) = delete;

				bool is_active(void);

				virtual bool on_run(
					__in const void *context,
					__in size_t length
					) = 0;

				virtual bool on_start(
					__in const void *context,
					__in size_t length
					) = 0;

				virtual void on_stop(void) = 0;

				void run(
					__in const void *context,
					__in size_t length
					);

				void set_active(
					__in bool active
					);

				bool m_active;

				e65::exception m_exception;

				std::mutex m_mutex;

				bool m_notifiable;

				e65::type::signal m_signal;

				e65::type::signal m_signal_wait;

				std::thread m_thread;
		};
	}
}

#endif // E65_TYPE_THREAD_H_
