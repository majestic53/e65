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

#ifndef E65_TYPE_PFLAG_H_
#define E65_TYPE_PFLAG_H_

namespace e65 {

	namespace type {

		enum {
			E65_PFLAG_CARRY = 0,
			E65_PFLAG_ZERO,
			E65_PFLAG_IRQ_DISABLE,
			E65_PFLAG_DECIMAL_ENABLE,
			E65_PFLAG_BREAKPOINT,
			E65_PFLAG_UNUSED,
			E65_PFLAG_OVERFLOW,
			E65_PFLAG_SIGN,
		};

		#define E65_PFLAG_MAX e65::type::E65_PFLAG_SIGN

		#define E65_PFLAG(_TYPE_) (1 << (_TYPE_))

		static const std::string E65_PFLAG_STR[] = {
			"C", "Z", "I", "D", "B", "-", "V", "N",
			};

		#define E65_PFLAG_STRING(_TYPE_) \
			(((_TYPE_) > E65_PFLAG_MAX) ? E65_STRING_UNKNOWN : \
				E65_STRING_CHECK(e65::type::E65_PFLAG_STR[_TYPE_]))

		typedef union {

			struct {
				uint8_t carry : 1;
				uint8_t zero : 1;
				uint8_t irq_disable : 1;
				uint8_t decimal_enable : 1;
				uint8_t breakpoint : 1;
				uint8_t unused : 1;
				uint8_t overflow : 1;
				uint8_t sign : 1;
			};

			uint8_t raw;
		} pflag_t;
	}
}

#endif // E65_TYPE_PFLAG_H_
