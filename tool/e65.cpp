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

#include "./e65_type.h"

// TODO
#include "../include/trace.h"
// ---

int
main(
	__in int argc,
	__in const char *argv[]
	)
{
	int result = EXIT_SUCCESS;

	try {

		// TODO
		e65::runtime &instance = e65::runtime::acquire();

		instance.initialize();

		instance.run(std::string(), false);

		instance.wait();

		instance.uninitialize();
		// ---

	} catch(e65::exception &exc) {
		std::cerr << exc.to_string() << std::endl;
		result = EXIT_FAILURE;
	} catch(std::exception &exc) {
		std::cerr << exc.what() << std::endl;
		result = EXIT_FAILURE;
	}

	return result;
}
