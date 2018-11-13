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
e65_breakpoint_list(
	__inout char **output
	)
{
	std::string buffer;
	int result = EXIT_SUCCESS;

	if(!output) {
		THROW_E65_EXCEPTION_FORMAT(E65_EXCEPTION_ARGUMENT, "%p", output);
	}

	buffer = e65::runtime::acquire().breakpoint_list();

	*output = (char *) std::calloc(buffer.size() + 1, sizeof(char));
	if(!*output) {
		THROW_E65_EXCEPTION_FORMAT(E65_EXCEPTION_ALLOCATION, "%p, %p", *output, *output);
	}

	std::memcpy(*output, &buffer[0], buffer.size());

	return result;
}

int
e65_dump(
	__inout char **output,
	__in uint16_t address,
	__in uint16_t offset
	)
{
	uint16_t end, iter;
	std::string buffer;
	std::stringstream stream;
	int result = EXIT_SUCCESS;

	if(!output || !offset) {
		THROW_E65_EXCEPTION_FORMAT(E65_EXCEPTION_ARGUMENT, "%p, %u(%04x), %u(%04x)", output, address, address, offset, offset);
	}

	iter = (address % E65_DUMP_BLOCK_SIZE);
	if(iter) {
		end = iter;

		E65_TRACE_MESSAGE_FORMAT(e65::E65_LEVEL_WARNING, "Address is not block-aligned", "%u(%04x) (correction=%u(%04x))", address, address,
			end, end);

		address -= end;
	}

	iter = (offset % E65_DUMP_BLOCK_SIZE);
	if(iter) {
		end = (E65_DUMP_BLOCK_SIZE - iter);

		E65_TRACE_MESSAGE_FORMAT(e65::E65_LEVEL_WARNING, "Offset is not block-aligned", "%u(%04x) (correction=%u(%04x))", offset, offset,
			end, end);

		offset += end;
	}

	if(!offset) {
		THROW_E65_EXCEPTION_FORMAT(E65_EXCEPTION_ARGUMENT, "%p, %u(%04x), %u(%04x)", output, address, address, offset, offset);
	}

	std::cout << "[" << E65_STRING_HEX(uint16_t, address) << "-" << E65_STRING_HEX(uint16_t, address + offset - 1) << "] "
		<< E65_FLOAT_PRECISION(1, offset / E65_BYTES_PER_KBYTE) << " KB (" << offset << " bytes)"
		<< std::endl << std::endl << "      ";

	for(iter = 0; iter < E65_DUMP_BLOCK_SIZE; ++iter) {
		std::cout << " " << E65_STRING_HEX(uint8_t, iter);
	}

	std::cout << std::endl << "---- |";

	for(iter = 0; iter < E65_DUMP_BLOCK_SIZE; ++iter) {
		std::cout << " --";
	}

	end = (address + offset);

	for(iter = address; iter != end; ++iter) {
		uint8_t value;

		if(!(iter % E65_DUMP_BLOCK_SIZE)) {

			if(!buffer.empty()) {
				stream << " | " << buffer;
				buffer.clear();
			}

			stream << std::endl << E65_STRING_HEX(uint16_t, iter) << " |";
		}

		value = e65::runtime::acquire().bus().memory().read(iter);

		stream << " " << E65_STRING_HEX(uint8_t, value);
		buffer += (std::isprint(value) ? value : E65_DUMP_CHARACTER_FILL);
	}

	if(!buffer.empty()) {
		stream << " | " << buffer;
		buffer.clear();
	}

	buffer = stream.str();

	*output = (char *) std::calloc(buffer.size() + 1, sizeof(char));
	if(!*output) {
		THROW_E65_EXCEPTION_FORMAT(E65_EXCEPTION_ALLOCATION, "%p, %p", *output, *output);
	}

	std::memcpy(*output, &buffer[0], buffer.size());

	return result;
}

int
e65_command(
	__in int command,
	__in const e65_t *request,
 	__in e65_t *response
	)
{
	int result = EXIT_SUCCESS;

	try {
		uint16_t address;

		if(!request || !response) {
			THROW_E65_EXCEPTION_FORMAT(E65_EXCEPTION_ARGUMENT, "%p, %p", request, response);
		}

		std::memset(response, 0, sizeof(*response));

		switch(command) {
			case E65_BREAKPOINT_CLEAR:
				address = request->address;

				response->result = (e65::runtime::acquire().breakpoint_clear(address) ? EXIT_SUCCESS : EXIT_FAILURE);
				if(response->result != EXIT_SUCCESS) {
					E65_TRACE_MESSAGE_FORMAT(e65::E65_LEVEL_WARNING, "Failed to clear breakpoint", "%u(%04x)", address, address);
				}
				break;
			case E65_BREAKPOINT_CLEAR_ALL:
				e65::runtime::acquire().breakpoints_clear();
				break;
			case E65_BREAKPOINT_LIST:
				response->result = e65_breakpoint_list(&response->payload.literal);
				break;
			case E65_BREAKPOINT_SET:
				address = request->address;

				response->result = (e65::runtime::acquire().breakpoint_set(address) ? EXIT_SUCCESS : EXIT_FAILURE);
				if(response->result != EXIT_SUCCESS) {
					E65_TRACE_MESSAGE_FORMAT(e65::E65_LEVEL_WARNING, "Failed to set breakpoint", "%u(%04x)", address, address);
				}
				break;
			case E65_MEMORY_DUMP:
				response->result = e65_dump(&response->payload.literal, request->address, request->payload.word);
				break;
			case E65_MEMORY_READ:
				response->payload.byte = e65::runtime::acquire().bus().memory().read(request->address);
				break;
			case E65_MEMORY_WRITE:
				e65::runtime::acquire().bus().memory().write(request->address, request->payload.byte);
				break;
			case E65_PROCESSOR_ACCUMULATOR:
				response->payload.byte = e65::runtime::acquire().bus().processor().accumulator();
				break;
			case E65_PROCESSOR_ACCUMULATOR_SET:
				e65::runtime::acquire().bus().processor().set_accumulator(request->payload.byte);
				break;
			case E65_PROCESSOR_CYCLE:
				response->payload.dword = e65::runtime::acquire().bus().processor().cycle();
				break;
			case E65_PROCESSOR_FLAGS:
				response->payload.byte = e65::runtime::acquire().bus().processor().flags();
				break;
			case E65_PROCESSOR_FLAGS_SET:
				e65::runtime::acquire().bus().processor().set_flags(request->payload.byte);
				break;
			case E65_PROCESSOR_HALT:
				e65::runtime::acquire().bus().processor().set_halt(true);
				break;
			case E65_PROCESSOR_HALT_CLEAR:
				e65::runtime::acquire().bus().processor().set_halt(false);
				break;
			case E65_PROCESSOR_INDEX_X:
				response->payload.byte = e65::runtime::acquire().bus().processor().index_x();
				break;
			case E65_PROCESSOR_INDEX_X_SET:
				e65::runtime::acquire().bus().processor().set_index_x(request->payload.byte);
				break;
			case E65_PROCESSOR_INDEX_Y:
				response->payload.byte = e65::runtime::acquire().bus().processor().index_y();
				break;
			case E65_PROCESSOR_INDEX_Y_SET:
				e65::runtime::acquire().bus().processor().set_index_y(request->payload.byte);
				break;
			case E65_PROCESSOR_PROGRAM_COUNTER:
				response->payload.word = e65::runtime::acquire().bus().processor().program_counter();
				break;
			case E65_PROCESSOR_PROGRAM_COUNTER_SET:
				e65::runtime::acquire().bus().processor().set_program_counter(request->payload.word);
				break;
			case E65_PROCESSOR_STACK_POINTER:
				response->payload.byte = e65::runtime::acquire().bus().processor().stack_pointer();
				break;
			case E65_PROCESSOR_STACK_POINTER_SET:
				e65::runtime::acquire().bus().processor().set_stack_pointer(request->payload.byte);
				break;
			case E65_PROCESSOR_STOP:
				e65::runtime::acquire().bus().processor().set_stop(true);
				break;
			case E65_PROCESSOR_STOP_CLEAR:
				e65::runtime::acquire().bus().processor().set_stop(false);
				break;
			case E65_VIDEO_FRAME:
				response->payload.dword = e65::runtime::acquire().bus().video().frame();
				break;
			default:
				THROW_E65_EXCEPTION_FORMAT(E65_EXCEPTION_COMMAND, "%u(%s)", command, E65_COMMAND_STRING(command));
		}

		result = response->result;
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
e65_initialize(void)
{
	int result = EXIT_SUCCESS;

	try {
		e65::runtime::acquire().initialize();
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
e65_interrupt(
	__in int maskable
	)
{
	int result = EXIT_SUCCESS;

	try {
		result = (e65::runtime::acquire().interrupt(maskable) ? EXIT_SUCCESS : EXIT_FAILURE);
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
e65_run(
	__in const char *path,
	__in int hex,
	__in int debug
	)
{
	int result = EXIT_SUCCESS;

	try {

		if(!path) {
			THROW_E65_EXCEPTION_FORMAT(E65_EXCEPTION_ARGUMENT, "%p", path);
		}

		e65::runtime::acquire().run(path, hex, debug);
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
		result = (e65::runtime::acquire().step() ? EXIT_SUCCESS : EXIT_FAILURE);
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
e65_uninitialize(void)
{

	try {
		e65::runtime::acquire().uninitialize();
	} catch(e65::exception &exc) {
		g_error = exc.to_string();
	} catch(std::exception &exc) {
		g_error = exc.what();
	}

	E65_TRACE_EXIT();
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

int
e65_wait(void)
{
	int result = EXIT_SUCCESS;

	try {
		result = (e65::runtime::acquire().wait() ? EXIT_SUCCESS : EXIT_FAILURE);
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
