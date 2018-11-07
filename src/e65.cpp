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

#include <cstring>
#include "../include/e65.h"
#include "../include/runtime.h"
#include "./e65_type.h"

static std::string g_error;

static std::string g_version;

int
e65_command(
	__in const e65_req_t *request,
	__in e65_rsp_t *response
	)
{
	int result = EXIT_SUCCESS;

	try {
		int type;
		uint8_t data;
		uint16_t address;

		if(!request || !response) {
			THROW_E65_EXCEPTION_FORMAT(E65_EXCEPTION_ARGUMENT, "%p, %p", request, response);
		}

		std::memset(response, 0, sizeof(*response));

		type = request->type;
		switch(type) {
			case E65_BREAKPOINT_CLEAR:
				address = request->address;

				E65_TRACE_MESSAGE_FORMAT(e65::E65_LEVEL_INFORMATION, "Clearing breakpoint", "%u(%04x)", address, address);

				response->data.i = e65::runtime::acquire().breakpoint_clear(address);
				break;
			case E65_BREAKPOINT_CLEAR_ALL:
				E65_TRACE_MESSAGE(e65::E65_LEVEL_INFORMATION, "Clearing all breakpoints");

				e65::runtime::acquire().breakpoints_clear();
				break;
			case E65_BREAKPOINT_SET:
				address = request->address;

				E65_TRACE_MESSAGE_FORMAT(e65::E65_LEVEL_INFORMATION, "Setting breakpoint", "%u(%04x)", address, address);

				response->data.i = e65::runtime::acquire().breakpoint_set(address);
				break;
			case E65_MEMORY_READ:
				address = request->address;

				E65_TRACE_MESSAGE_FORMAT(e65::E65_LEVEL_INFORMATION, "Reading memory", "[%u(%04x)]", address, address);

				data = e65::runtime::acquire().bus().memory().read(address);

				E65_TRACE_MESSAGE_FORMAT(e65::E65_LEVEL_INFORMATION, "Read memory", "[%u(%04x)] -> %u(%02x)", address, address,
					data, data);

				response->data.u8 = data;
				break;
			case E65_MEMORY_WRITE:
				data = request->data.u8;
				address = request->address;

				E65_TRACE_MESSAGE_FORMAT(e65::E65_LEVEL_INFORMATION, "Writing memory", "[%u(%04x)] <- %u(%02x)", address, address,
					data, data);

				e65::runtime::acquire().bus().memory().write(address, data);

				data = e65::runtime::acquire().bus().memory().read(address);

				E65_TRACE_MESSAGE_FORMAT(e65::E65_LEVEL_INFORMATION, "Wrote memory", "[%u(%04x)] <- %u(%02x)", address, address,
					data, data);
				break;
			case E65_PROCESSOR_CYCLE:
				response->data.u32 = e65::runtime::acquire().bus().processor().cycle();
				break;
			case E65_VIDEO_FRAME:
				response->data.u32 = e65::runtime::acquire().bus().video().frame();
				break;
			default:
				THROW_E65_EXCEPTION_FORMAT(E65_EXCEPTION_COMMAND, "%u(%s)", type, E65_COMMAND_STRING(type));
		}

		response->type = request->type;
	} catch(e65::exception &exc) {
		g_error = exc.to_string();
		result = EXIT_FAILURE;
	} catch(std::exception &exc) {
		g_error = exc.what();
		result = EXIT_FAILURE;
	}

	E65_TRACE_EXIT_FORMAT("Result=%u(%x)", result, result);
	return result;
}

const char *
e65_error(void)
{
	E65_TRACE_ENTRY();
	E65_TRACE_EXIT();
	return E65_STRING_CHECK(g_error);
}

int
e65_run(
	__in const char *path,
	__in int debug
	)
{
	int result = EXIT_SUCCESS;

	try {

		if(!path) {
			THROW_E65_EXCEPTION_FORMAT(E65_EXCEPTION_ARGUMENT, "%p", path);
		}

		e65::runtime::acquire().run(path, debug);
	} catch(e65::exception &exc) {
		g_error = exc.to_string();
		result = EXIT_FAILURE;
	} catch(std::exception &exc) {
		g_error = exc.what();
		result = EXIT_FAILURE;
	}

	E65_TRACE_EXIT_FORMAT("Result=%u(%x)", result, result);
	return result;
}

int
e65_step(void)
{
	int result = EXIT_SUCCESS;

	try {
		result = e65::runtime::acquire().step();
	} catch(e65::exception &exc) {
		g_error = exc.to_string();
		result = EXIT_FAILURE;
	} catch(std::exception &exc) {
		g_error = exc.what();
		result = EXIT_FAILURE;
	}

	E65_TRACE_EXIT_FORMAT("Result=%u(%x)", result, result);
	return result;
}

void
e65_version(
	__in int *major,
	__in int *minor
	)
{
	E65_TRACE_ENTRY_FORMAT("Major=%p, Minor=%p", major, minor);

	if(major) {
		*major = E65_VERSION_MAJOR;
	}

	if(minor) {
		*minor = E65_VERSION_MINOR;
	}

	E65_TRACE_EXIT();
}

const char *
e65_version_string(void)
{
	E65_TRACE_ENTRY();

	if(g_version.empty()) {
		g_version = e65::runtime::version();
	}

	E65_TRACE_EXIT();
	return E65_STRING_CHECK(g_version);
}
