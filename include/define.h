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

#ifndef E65_DEFINE_H_
#define E65_DEFINE_H_

#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "./type/color.h"
#include "./type/constant.h"
#include "./type/level.h"
#include "./type/macro.h"
#include "./type/pcommand.h"
#include "./type/pflag.h"

namespace e65 {

#ifndef __in
	#define __in
#endif // __in
#ifndef __in_opt
	#define __in_opt
#endif // __in_opt
#ifndef __inout
	#define __inout
#endif // __inout

	#define E65 "E65"

	#define E65_VERSION_MAJOR 0
	#define E65_VERSION_MINOR 1
	#define E65_VERSION_RELEASE "alpha"
	#define E65_VERSION_REVISION 2
	#define E65_VERSION_WEEK 1848
}

#endif // E65_DEFINE_H_
