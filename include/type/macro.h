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

#ifndef E65_TYPE_MACRO_H_
#define E65_TYPE_MACRO_H_

namespace e65 {

	namespace type {

		#define E65_COLUMN_WIDTH(_WIDTH_) \
			std::left << std::setw(_WIDTH_)

		#define E65_EXCEPTION(_MESSAGE_) \
			e65::exception(_MESSAGE_, __FILE__, __FUNCTION__, __LINE__)

		#define E65_EXCEPTION_GENERATE(_MESSAGE_, _FILE_, _FUNCTION_, _LINE_, _FORMAT_, ...) \
			e65::exception::generate(_MESSAGE_, _FILE_, _FUNCTION_, _LINE_, _FORMAT_, __VA_ARGS__)

		#define E65_EXCEPTION_THROW(_MESSAGE_) \
			E65_EXCEPTION_THROW_FORMAT(_MESSAGE_, "", "")
		#define E65_EXCEPTION_THROW_FORMAT(_MESSAGE_, _FORMAT_, ...) \
			E65_EXCEPTION_GENERATE(_MESSAGE_, __FILE__, __FUNCTION__, __LINE__, _FORMAT_, __VA_ARGS__)

		#define E65_FLOAT_PRECISION(_PRECISION_, _VALUE_) \
			std::right << std::setprecision(_PRECISION_) << std::fixed << (_VALUE_) << std::defaultfloat

		#define E65_STRING_CHECK(_STRING_) \
			((_STRING_).empty() ? E65_STRING_EMPTY : (_STRING_).c_str())

		#define E65_STRING_HEX(_TYPE_, _VALUE_) \
			std::right << std::setw(sizeof(_TYPE_) * 2) << std::setfill('0') << std::hex << (uintmax_t) ((_TYPE_) (_VALUE_)) \
				<< std::dec << std::setfill(' ')

		#define E65_TRACE_ENTRY() \
			E65_TRACE_ENTRY_FORMAT("", "")
		#define E65_TRACE_ENTRY_FORMAT(_FORMAT_, ...) \
			E65_TRACE_GENERATE(e65::type::E65_LEVEL_VERBOSE, "+", __FUNCTION__, _FORMAT_, __VA_ARGS__)

		#define E65_TRACE_ERROR(_MESSAGE_, _FILE_, _FUNCTION_, _LINE_) \
			E65_TRACE_GENERATE_FORMAT(e65::type::E65_LEVEL_ERROR, "", _MESSAGE_, _FILE_, _FUNCTION_, _LINE_, "", "")

		#define E65_TRACE_EXIT() \
			E65_TRACE_EXIT_FORMAT("", "")
		#define E65_TRACE_EXIT_FORMAT(_FORMAT_, ...) \
			E65_TRACE_GENERATE(e65::type::E65_LEVEL_VERBOSE, "-", __FUNCTION__, _FORMAT_, __VA_ARGS__)

		#define E65_TRACE_GENERATE(_LEVEL_, _PREFIX_, _MESSAGE_, _FORMAT_, ...) \
			E65_TRACE_GENERATE_FORMAT(_LEVEL_, _PREFIX_, _MESSAGE_, __FILE__, __FUNCTION__, __LINE__, _FORMAT_, __VA_ARGS__)
#ifndef NDEBUG
		#define E65_TRACE_GENERATE_FORMAT(_LEVEL_, _PREFIX_, _MESSAGE_, _FILE_, _FUNCTION_, _LINE_, _FORMAT_, ...) \
			try { \
				if((TRACE) >= (_LEVEL_)) { \
					e65::trace::acquire().generate(_LEVEL_, _PREFIX_, _MESSAGE_, _FILE_, _FUNCTION_, _LINE_, _FORMAT_, __VA_ARGS__); \
				} \
			} catch(...) { }
#else
		#define E65_TRACE_GENERATE_FORMAT(_LEVEL_, _PREFIX_, _MESSAGE_, _FILE_, _FUNCTION_, _LINE_, _FORMAT_, ...)
#endif // NDEBUG

		#define E65_TRACE_MESSAGE(_LEVEL_, _MESSAGE_) \
			E65_TRACE_MESSAGE_FORMAT(_LEVEL_, _MESSAGE_, "", "")
		#define E65_TRACE_MESSAGE_FORMAT(_LEVEL_, _MESSAGE_, _FORMAT_, ...) \
			E65_TRACE_GENERATE(_LEVEL_, "", _MESSAGE_, _FORMAT_, __VA_ARGS__)
	}
}

#endif // E65_TYPE_MACRO_H_
