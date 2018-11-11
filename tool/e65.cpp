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

// TODO: DEBUG
#include <unistd.h>
// ---

int
main(
	__in int argc,
	__in const char *argv[]
	)
{
	int result;

	// TODO: DEBUG
	e65_t req = {}, rsp = {};
	// ---

	result = e65_initialize();
	if(result != EXIT_SUCCESS) {
		goto exit;
	}

	result = e65_run("./test/test.bin", false, false);
	//result = e65_run("./test/test.hex", true, false);
	if(result != EXIT_SUCCESS) {
		goto exit;
	}

	// TODO: DEBUG
	sleep(1);

	req.address = 0x0600;
	req.payload.word = 0x0140; // offset

	result = e65_command(E65_MEMORY_DUMP, &req, &rsp);
	if(result != EXIT_SUCCESS) {
		goto exit;
	}

	if(rsp.payload.literal) {
		std::cout << rsp.payload.literal << std::endl << std::endl;

		std::free(rsp.payload.literal);
		rsp.payload.literal = nullptr;
	} else {
		std::cout << E65_STRING_EMPTY << std::endl << std::endl;
	}

	// ---

	req.address = 0xfff0;
	req.payload.word = 0x0010; // offset

	result = e65_command(E65_MEMORY_DUMP, &req, &rsp);
	if(result != EXIT_SUCCESS) {
		goto exit;
	}

	if(rsp.payload.literal) {
		std::cout << rsp.payload.literal << std::endl;

		std::free(rsp.payload.literal);
		rsp.payload.literal = nullptr;
	} else {
		std::cout << E65_STRING_EMPTY << std::endl;
	}
	// ---

	result = e65_wait();
	if(result != EXIT_SUCCESS) {
		goto exit;
	}

exit:
	e65_uninitialize();

	return result;
}
