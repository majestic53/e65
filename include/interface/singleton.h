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

#ifndef E65_INTERFACE_SINGLETON_H_
#define E65_INTERFACE_SINGLETON_H_

#include "./singleton_type.h"

namespace e65 {

	namespace interface {

		template <class T> class singleton {

			public:

				~singleton(void)
				{
					return;
				}

				static T &acquire(void)
				{
					static T result;

					return result;
				}

				void initialize(
					__in_opt const void *context = nullptr,
					__in_opt size_t length = 0
					)
				{

					if(m_initialized) {
						THROW_E65_INTERFACE_SINGLETON_EXCEPTION_FORMAT(E65_INTERFACE_SINGLETON_EXCEPTION_INITIALIZED,
							"%u(%s), %p", m_type, E65_SINGLETON_STRING(m_type), this);
					}

					m_initialized = true;

					if(!on_initialize(context, length)) {
						uninitialize();
						THROW_E65_INTERFACE_SINGLETON_EXCEPTION_FORMAT(E65_INTERFACE_SINGLETON_EXCEPTION_INITIALIZING,
							"%u(%s), %p", m_type, E65_SINGLETON_STRING(m_type), this);
					}
				}

				bool initialized(void) const
				{
					return m_initialized;
				}

				virtual std::string to_string(void) const
				{
					std::stringstream result;

					result << E65_INTERFACE_SINGLETON_HEADER << "(" << E65_STRING_HEX(uintptr_t, this) << ")"
						<< " Type=" << m_type << "(" << E65_SINGLETON_STRING(m_type) << ")"
						<< ", State=" << m_initialized << "(" << (m_initialized ? "Initialized" : "Uninitialized") << ")";

					return result.str();
				}

				int type(void) const
				{
					return m_type;
				}

				void uninitialize(void)
				{

					if(!m_initialized) {
						THROW_E65_INTERFACE_SINGLETON_EXCEPTION_FORMAT(E65_INTERFACE_SINGLETON_EXCEPTION_UNINITIALIZED,
							"%u(%s), %p", m_type, E65_SINGLETON_STRING(m_type), this);
					}

					on_uninitialize();
					m_initialized = false;
				}

			protected:

				explicit singleton(
					__in int type
					) :
						m_initialized(false),
						m_type(type)
				{
					return;
				}

				singleton(
					__in const singleton &other
					) = delete;

				singleton &operator=(
					__in const singleton &other
					) = delete;

				virtual bool on_initialize(
					__in const void *context,
					__in size_t length
					) = 0;

				virtual void on_uninitialize(void) = 0;

				bool m_initialized;

				int m_type;
		};
	}
}

#endif // E65_INTERFACE_SINGLETON_H_
