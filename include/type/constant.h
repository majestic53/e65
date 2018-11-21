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

#ifndef E65_TYPE_CONSTANT_H_
#define E65_TYPE_CONSTANT_H_

namespace e65 {

	namespace type {

		#define E65_BIT_HIGH 0x80
		#define E65_BIT_LOW 0x01

		#define E65_BYTES_PER_KBYTE 1024.f

		#define E65_EXCEPTION_UNKNOWN "Unknown exception"

		#define E65_MEMORY_FILL 0xea
		#define E65_MEMORY_LENGTH 0x10000

		#define E65_MILLISECONDS_PER_SECOND 1000.f

		#define E65_PROCESSOR_CYCLES_PER_FRAME (E65_PROCESSOR_FREQUENCY / E65_VIDEO_FRAME_RATE)
		#define E65_PROCESSOR_FREQUENCY 1000000

		#define E65_STRING_EMPTY "Empty"
		#define E65_STRING_UNKNOWN "Unknown"

		#define E65_VIDEO_FRAME_RATE 60
	}
}

#endif // E65_TYPE_CONSTANT_H_
