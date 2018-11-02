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
			m_active(false),
			m_notifiable(false)
		{
			return;
		}

		thread::~thread(void)
		{
			return;
		}

		bool
		thread::active(void) const
		{
			return m_active;
		}

		bool
		thread::is_active(void)
		{
			std::lock_guard<std::mutex> lock(m_mutex);

			return m_active;
		}

		bool
		thread::notifiable(void) const
		{
			return m_notifiable;
		}

		void
		thread::notify(void)
		{

			if(is_active() && m_notifiable) {
				m_signal.notify();
			}
		}

		void
		thread::run(
			__in const void *context,
			__in size_t length
			)
		{

			try {

				while(is_active()) {

					if(m_notifiable) {
						m_signal.wait();

						if(!is_active()) {
							break;
						}
					}

					if(!on_run(context, length)) {
						break;
					}
				}
			} catch(e65::exception &exc) {
				m_exception = exc;
			} catch(std::exception &exc) {
				m_exception = E65_EXCEPTION(exc.what());
			}

			m_signal_wait.notify();
		}

		void
		thread::set_active(
			__in bool active
			)
		{
			std::lock_guard<std::mutex> lock(m_mutex);

			m_active = active;
		}

		void
		thread::start(
			__in bool notifiable,
			__in_opt const void *context,
			__in_opt size_t length
			)
		{

			if(is_active()) {
				THROW_E65_TYPE_THREAD_EXCEPTION_FORMAT(E65_TYPE_THREAD_EXCEPTION_STARTED, "%p", this);
			}

			m_exception.clear();
			m_notifiable = notifiable;

			if(!on_start(context, length)) {
				THROW_E65_TYPE_THREAD_EXCEPTION_FORMAT(E65_TYPE_THREAD_EXCEPTION_START, "%p", this);
			}

			set_active(true);
			m_thread = std::thread(&thread::run, this, context, length);
		}

		void
		thread::stop(void)
		{

			if(is_active()) {
				set_active(false);

				if(m_notifiable) {
					m_signal.notify();
				}
			}

			if(m_thread.joinable()) {
				m_thread.join();
			}

			on_stop();

			if(!m_exception.empty()) {
				THROW_E65_TYPE_THREAD_EXCEPTION_FORMAT(E65_TYPE_THREAD_EXCEPTION_INTERNAL,
					"%s", E65_STRING_CHECK(m_exception.to_string()));
			}
		}

		std::string
		thread::to_string(void) const
		{
			std::stringstream result;

			result << E65_TYPE_THREAD_HEADER << "(" << E65_STRING_HEX(uintptr_t, this) << ")"
				<< " State=" << (m_active ? "Running" : "Stopped");

			if(m_active) {
				result << ", Id=" << m_thread.get_id()
					<< ", Mode=" << (m_notifiable ? "Notifiable" : "Non-notifiable");
			}

			return result.str();
		}

		bool
		thread::wait(
			__in_opt uint32_t timeout
			)
		{
			bool result;

			result = is_active();
			if(result) {
				result = m_signal_wait.wait(timeout);
			}

			return result;
		}
	}
}
