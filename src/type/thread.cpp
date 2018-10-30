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

#include "../../include/type/thread.h"
#include "./thread_type.h"

namespace e65 {

	namespace type {

		thread::thread(void) :
			m_notifiable(false),
			m_state(E65_THREAD_STOP)
		{
			// TODO
		}

		thread::~thread(void)
		{
			// TODO
		}

		bool
		thread::notifiable(void) const
		{
			return m_notifiable;
		}

		void
		thread::notify(
			__in_opt const void *context,
			__in_opt size_t length
			)
		{
			// TODO
		}

		void
		thread::pause(void)
		{
			// TODO
		}

		bool
		thread::run(
			__in const void *context,
			__in size_t length
			)
		{
			bool result;

			// TODO
			result = true;
			// ---

			return result;
		}

		void
		thread::start(
			__in bool notifiable,
			__in_opt const void *context,
			__in_opt size_t length
			)
		{
			// TODO
		}

		int
		thread::state(void) const
		{
			return m_state;
		}

		std::string
		thread::to_string(void) const
		{
			std::stringstream result;

			result << E65_TYPE_THREAD_HEADER << "(" << E65_STRING_HEX(uintptr_t, this) << ")"
				<< " State=" << m_state << "(" << E65_THREAD_STRING(m_state) << ")";

			if(m_state != E65_THREAD_STOP) {
				result << ", Id=" << m_thread.get_id()
					<< ", Mode=" << (m_notifiable ? "Notifiable" : "Non-notifiable");
			}

			return result.str();
		}

		void
		thread::unpause(void)
		{
			// TODO
		}
	}
}
