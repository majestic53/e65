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

#include <chrono>
#include "../../include/type/signal.h"
#include "./signal_type.h"

namespace e65 {

	namespace type {

		signal::signal(void) :
			m_state(E65_SIGNAL_CLEAR)
		{
			return;
		}

		signal::~signal(void)
		{
			abandon();
		}

		void
		signal::abandon(void)
		{
			std::lock_guard<std::mutex> lock(m_mutex);

			if(m_state != E65_SIGNAL_ABANDON) {
				m_state = E65_SIGNAL_ABANDON;
				m_condition.notify_all();
			}
		}

		void
		signal::clear(void)
		{
			std::lock_guard<std::mutex> lock(m_mutex);

			if(m_state == E65_SIGNAL_ABANDON) {
				THROW_E65_TYPE_SIGNAL_EXCEPTION_FOMAT(E65_TYPE_SIGNAL_EXCEPTION_ABANDONED, "%p", this);
			} else if(m_state != E65_SIGNAL_CLEAR) {
				m_state = E65_SIGNAL_CLEAR;
				m_condition.notify_all();
			}
		}

		void
		signal::notify(void)
		{
			std::lock_guard<std::mutex> lock(m_mutex);

			if(m_state == E65_SIGNAL_ABANDON) {
				THROW_E65_TYPE_SIGNAL_EXCEPTION_FOMAT(E65_TYPE_SIGNAL_EXCEPTION_ABANDONED, "%p", this);
			} else if(m_state == E65_SIGNAL_CLEAR) {
				m_state = E65_SIGNAL_NOTIFY;
				m_condition.notify_all();
			}
		}

		bool
		signal::timeout(void) const
		{
			return (m_state == E65_SIGNAL_TIMEOUT);
		}

		std::string
		signal::to_string(void) const
		{
			std::stringstream result;

			result << E65_TYPE_SIGNAL_HEADER << "(" << E65_STRING_HEX(uintptr_t, this) << ")"
				<< " State=" << m_state << "(" << E65_SIGNAL_STRING(m_state) << ")";

			return result.str();
		}

		bool
		signal::valid(void) const
		{
			return (m_state != E65_SIGNAL_ABANDON);
		}

		bool
		signal::wait(
			__in_opt uint32_t timeout
			)
		{
			bool result;
			std::unique_lock<std::mutex> lock(m_mutex);

			if(m_state == E65_SIGNAL_ABANDON) {
				THROW_E65_TYPE_SIGNAL_EXCEPTION_FOMAT(E65_TYPE_SIGNAL_EXCEPTION_ABANDONED, "%p", this);
			} else if(m_state != E65_SIGNAL_CLEAR) {
				m_state = E65_SIGNAL_CLEAR;
			}

			if(timeout) {
				result = m_condition.wait_for(lock, std::chrono::milliseconds(timeout),
								[this](void) { return (m_state != E65_SIGNAL_CLEAR); });

				if(!result) {
					m_state = E65_SIGNAL_TIMEOUT;
				} else if(m_state != E65_SIGNAL_ABANDON) {
					m_state = E65_SIGNAL_CLEAR;
				}
			} else {
				m_condition.wait(lock, [this](void) { return (m_state != E65_SIGNAL_CLEAR); });

				if(m_state != E65_SIGNAL_ABANDON) {
					m_state = E65_SIGNAL_CLEAR;
				}
			}

			result = (m_state == E65_SIGNAL_CLEAR);
			if(!result && (m_state != E65_SIGNAL_ABANDON) && (m_state != E65_SIGNAL_TIMEOUT)) {
				m_state = E65_SIGNAL_CLEAR;
			}

			return result;
		}
	}
}
