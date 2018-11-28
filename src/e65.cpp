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

#include <climits>
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

	E65_TRACE_ENTRY_FORMAT("Output=%p", output);

	if(!output) {
		THROW_E65_EXCEPTION_FORMAT(E65_EXCEPTION_ARGUMENT, "%p", output);
	}

	buffer = e65::runtime::acquire().breakpoint_list();

	*output = (char *) std::calloc(buffer.size() + 1, sizeof(char));
	if(!*output) {
		THROW_E65_EXCEPTION_FORMAT(E65_EXCEPTION_ALLOCATION, "%p, %p", *output, *output);
	}

	std::memcpy(*output, &buffer[0], buffer.size());

	E65_TRACE_EXIT_FORMAT("Result=%u(%x)", result, result);
	return result;
}

int
e65_core(
	__inout char **output
	)
{
	uint8_t flags;
	std::string buffer;
	std::stringstream stream;
	int flag, result = EXIT_SUCCESS;

	E65_TRACE_ENTRY_FORMAT("Output=%p", output);

	if(!output) {
		THROW_E65_EXCEPTION_FORMAT(E65_EXCEPTION_ARGUMENT, "%p", output);
	}

	e65::interface::system::processor &processor = e65::runtime::acquire().bus().processor();

	stream << E65_COLUMN_WIDTH(E65_CORE_COLUMN_WIDTH) << "CYC" << processor.cycle() << " (" << (int) processor.cycle_last() << ")"
		<< std::endl << E65_COLUMN_WIDTH(E65_CORE_COLUMN_WIDTH) << "WAI" << processor.waiting()
		<< std::endl << E65_COLUMN_WIDTH(E65_CORE_COLUMN_WIDTH) << "STP" << processor.stopped()
		<< std::endl << E65_COLUMN_WIDTH(E65_CORE_COLUMN_WIDTH) << "IRQ" << processor.interrupted(true)
		<< std::endl << E65_COLUMN_WIDTH(E65_CORE_COLUMN_WIDTH) << "NMI" << processor.interrupted(false);

	stream << std::endl << E65_COLUMN_WIDTH(E65_CORE_COLUMN_WIDTH) << "PC" << E65_STRING_HEX(uint16_t, processor.program_counter())
		<< std::endl << E65_COLUMN_WIDTH(E65_CORE_COLUMN_WIDTH) << "SP" << E65_STRING_HEX(uint8_t, processor.stack_pointer());

	flags = processor.flags();
	stream << std::endl << E65_COLUMN_WIDTH(E65_CORE_COLUMN_WIDTH) << "F" << E65_STRING_HEX(uint8_t, flags) << " [";

	for(flag = E65_PFLAG_MAX; flag >= 0; flag--) {
		stream << ((flags & E65_PFLAG(flag)) ? E65_PFLAG_STRING(flag) : "-");
	}

	stream << "]"
		<< std::endl << E65_COLUMN_WIDTH(E65_CORE_COLUMN_WIDTH) << "A" << E65_STRING_HEX(uint8_t, processor.accumulator())
		<< std::endl << E65_COLUMN_WIDTH(E65_CORE_COLUMN_WIDTH) << "X"  << E65_STRING_HEX(uint8_t, processor.index_x())
		<< std::endl << E65_COLUMN_WIDTH(E65_CORE_COLUMN_WIDTH) << "Y"  << E65_STRING_HEX(uint8_t, processor.index_y());

	buffer = stream.str();
	if(buffer.empty()) {
		buffer = E65_STRING_EMPTY;
	}

	*output = (char *) std::calloc(buffer.size() + 1, sizeof(char));
	if(!*output) {
		THROW_E65_EXCEPTION_FORMAT(E65_EXCEPTION_ALLOCATION, "%p, %p", *output, *output);
	}

	std::memcpy(*output, &buffer[0], buffer.size());

	E65_TRACE_EXIT_FORMAT("Result=%u(%x)", result, result);
	return result;
}

int
e65_disassemble(
	__inout char **output,
	__in uint16_t address,
	__in uint16_t offset
	)
{
	uint16_t entry = 0;
	std::string buffer;
	std::stringstream stream;
	int result = EXIT_SUCCESS;

	E65_TRACE_ENTRY_FORMAT("Output=%p, Address=%u(%04x), Offset=%u(%04x)", output, address, address, offset, offset);

	if(!output || !offset) {
		THROW_E65_EXCEPTION_FORMAT(E65_EXCEPTION_ARGUMENT, "%p, %u(%04x), %u(%04x)", output, address, address, offset, offset);
	}

	stream << "[" << E65_STRING_HEX(uint16_t, address) << ", " << offset << " instructions]" << std::endl;

	for(; entry < offset; ++entry) {
		std::vector<uint8_t> data;
		std::vector<uint8_t>::iterator byte;
		std::map<uint8_t, std::pair<int, int>>::const_iterator command;

		stream << std::endl << "[" << E65_STRING_HEX(uint16_t, address) << "] ";

		data.push_back(e65::runtime::acquire().bus().memory().read(address++));

		command = e65::type::E65_PCOMMAND_ID_MAP.find(data.back());
		if(command != e65::type::E65_PCOMMAND_ID_MAP.end()) {
			uint16_t operand = 0;
			std::stringstream substream;
			int mode = command->second.second;
			std::map<int, int>::const_iterator length;

			length = e65::type::E65_PCOMMAND_LENGTH_MAP.find(mode);
			if(length != e65::type::E65_PCOMMAND_LENGTH_MAP.end()) {
				stream << E65_PCOMMAND_STRING(command->second.first) << " " << E65_COLUMN_WIDTH(E65_DISASSEMBLE_COLUMN_WIDTH)
					<< E65_PCOMMAND_MODE_STRING(mode);

				switch(length->second) {
					case e65::type::E65_PCOMMAND_LENGTH_NONE:
						break;
					case e65::type::E65_PCOMMAND_LENGTH_BYTE:
						data.push_back(e65::runtime::acquire().bus().memory().read(address++));
						operand = data.back();
						break;
					case e65::type::E65_PCOMMAND_LENGTH_WORD:
						data.push_back(e65::runtime::acquire().bus().memory().read(address++));
						operand = data.back();
						data.push_back(e65::runtime::acquire().bus().memory().read(address++));
						operand |= (data.back() << CHAR_BIT);
						break;
					default:
						break;
				}
			} else {
				stream << E65_COLUMN_WIDTH(E65_DISASSEMBLE_COLUMN_WIDTH) << "<Illegal Mode>";
			}

			switch(mode) {
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_INDIRECT:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_X:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_Y:
				case e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDIRECT:
					substream << "abs=" << E65_STRING_HEX(uint16_t, operand);
					break;
				case e65::type::E65_PCOMMAND_MODE_ACCUMULATOR:
					substream << "a=" << E65_STRING_HEX(uint8_t, operand);
					break;
				case e65::type::E65_PCOMMAND_MODE_IMMEDIATE:
					substream << "#=" << E65_STRING_HEX(uint8_t, operand);
					break;
				case e65::type::E65_PCOMMAND_MODE_RELATIVE:
					substream << "r=" << E65_STRING_HEX(uint8_t, operand);
					break;
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_INDIRECT:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_X:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_Y:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT:
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT_INDEX:
					substream << "zp=" << E65_STRING_HEX(uint8_t, operand);
					break;
				case e65::type::E65_PCOMMAND_MODE_ZEROPAGE_RELATIVE:
					substream << "zp=" << E65_STRING_HEX(uint8_t, operand >> CHAR_BIT)
						<< ", r=" << E65_STRING_HEX(uint8_t, operand);
					break;
				default:
					substream << " ";
					break;
			}

			stream << E65_COLUMN_WIDTH(E65_DISASSEMBLE_COLUMN_WIDTH) << substream.str();
		} else {
			stream << E65_COLUMN_WIDTH(E65_DISASSEMBLE_COLUMN_WIDTH) << "<Illegal Command>";
		}

		stream << "[" << data.size() << "] {";

		for(byte = data.begin(); byte != data.end(); ++byte) {

			if(byte != data.begin()) {
				stream << " ";
			}

			stream << E65_STRING_HEX(uint8_t, *byte);
		}

		stream << "}";
	}

	buffer = stream.str();
	if(buffer.empty()) {
		buffer = E65_STRING_EMPTY;
	}

	*output = (char *) std::calloc(buffer.size() + 1, sizeof(char));
	if(!*output) {
		THROW_E65_EXCEPTION_FORMAT(E65_EXCEPTION_ALLOCATION, "%p, %p", *output, *output);
	}

	std::memcpy(*output, &buffer[0], buffer.size());

	E65_TRACE_EXIT_FORMAT("Result=%u(%x)", result, result);
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

	E65_TRACE_ENTRY_FORMAT("Output=%p, Address=%u(%04x), Offset=%u(%04x)", output, address, address, offset, offset);

	if(!output || !offset) {
		THROW_E65_EXCEPTION_FORMAT(E65_EXCEPTION_ARGUMENT, "%p, %u(%04x), %u(%04x)", output, address, address, offset, offset);
	}

	iter = (address % E65_DUMP_BLOCK_SIZE);
	if(iter) {
		end = iter;

		E65_TRACE_MESSAGE_FORMAT(e65::type::E65_LEVEL_WARNING, "Address is not block-aligned", "%u(%04x) (correction=%u(%04x))",
			address, address, end, end);

		address -= end;
	}

	iter = (offset % E65_DUMP_BLOCK_SIZE);
	if(iter) {
		end = (E65_DUMP_BLOCK_SIZE - iter);

		E65_TRACE_MESSAGE_FORMAT(e65::type::E65_LEVEL_WARNING, "Offset is not block-aligned", "%u(%04x) (correction=%u(%04x))", offset, offset,
			end, end);

		offset += end;
	}

	if(!offset) {
		THROW_E65_EXCEPTION_FORMAT(E65_EXCEPTION_ARGUMENT, "%p, %u(%04x), %u(%04x)", output, address, address, offset, offset);
	}

	stream << "[" << E65_STRING_HEX(uint16_t, address) << "-" << E65_STRING_HEX(uint16_t, address + offset - 1) << "] "
		<< E65_FLOAT_PRECISION(1, offset / E65_BYTES_PER_KBYTE) << " KB (" << offset << " bytes)"
		<< std::endl << std::endl << "      ";

	for(iter = 0; iter < E65_DUMP_BLOCK_SIZE; ++iter) {
		stream << " " << E65_STRING_HEX(uint8_t, iter);
	}

	stream << std::endl << "---- |";

	for(iter = 0; iter < E65_DUMP_BLOCK_SIZE; ++iter) {
		stream << " --";
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
		buffer += ((std::isprint(value) && !std::isspace(value)) ? value : E65_DUMP_CHARACTER_FILL);
	}

	if(!buffer.empty()) {
		stream << " | " << buffer;
		buffer.clear();
	}

	buffer = stream.str();
	if(buffer.empty()) {
		buffer = E65_STRING_EMPTY;
	}

	*output = (char *) std::calloc(buffer.size() + 1, sizeof(char));
	if(!*output) {
		THROW_E65_EXCEPTION_FORMAT(E65_EXCEPTION_ALLOCATION, "%p, %p", *output, *output);
	}

	std::memcpy(*output, &buffer[0], buffer.size());

	E65_TRACE_EXIT_FORMAT("Result=%u(%x)", result, result);
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

	E65_TRACE_ENTRY_FORMAT("Command=%i(%s), Request=%p, Response=%p", command, E65_COMMAND_STRING(command), &request, &response);

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
					E65_TRACE_MESSAGE_FORMAT(e65::type::E65_LEVEL_WARNING, "Failed to clear breakpoint", "%u(%04x)",
						address, address);
				}
				break;
			case E65_BREAKPOINT_CLEAR_ALL:
				e65::runtime::acquire().breakpoint_clear_all();
				break;
			case E65_BREAKPOINT_LIST:
				response->result = e65_breakpoint_list(&response->payload.literal);
				break;
			case E65_BREAKPOINT_SET:
				address = request->address;

				response->result = (e65::runtime::acquire().breakpoint_set(address) ? EXIT_SUCCESS : EXIT_FAILURE);
				if(response->result != EXIT_SUCCESS) {
					E65_TRACE_MESSAGE_FORMAT(e65::type::E65_LEVEL_WARNING, "Failed to set breakpoint", "%u(%04x)",
						address, address);
				}
				break;
			case E65_MEMORY_DUMP:
				response->result = e65_dump(&response->payload.literal, request->address, request->payload.word);
				break;
			case E65_MEMORY_READ:
				response->payload.byte = e65::runtime::acquire().bus().memory().read(request->address);
				break;
			case E65_MEMORY_READ_WORD:
				response->payload.word = e65::runtime::acquire().bus().memory().read_word(request->address);
				break;
			case E65_MEMORY_WRITE:
				e65::runtime::acquire().bus().memory().write(request->address, request->payload.byte);
				break;
			case E65_MEMORY_WRITE_WORD:
				e65::runtime::acquire().bus().memory().write_word(request->address, request->payload.word);
				break;
			case E65_PROCESSOR_ACCUMULATOR:
				response->payload.byte = e65::runtime::acquire().bus().processor().accumulator();
				break;
			case E65_PROCESSOR_ACCUMULATOR_SET:
				e65::runtime::acquire().bus().processor().set_accumulator(request->payload.byte);
				break;
			case E65_PROCESSOR_BREAK:
				result = e65::runtime::acquire().debug_break();
				break;
			case E65_PROCESSOR_CORE:
				response->result = e65_core(&response->payload.literal);
				break;
			case E65_PROCESSOR_CYCLE:
				response->payload.dword = e65::runtime::acquire().bus().processor().cycle();
				break;
			case E65_PROCESSOR_DISASSEMBLE:
				response->result = e65_disassemble(&response->payload.literal, request->address, request->payload.word);
				break;
			case E65_PROCESSOR_FLAGS:
				response->payload.byte = e65::runtime::acquire().bus().processor().flags();
				break;
			case E65_PROCESSOR_FLAGS_SET:
				e65::runtime::acquire().bus().processor().set_flags(request->payload.byte);
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
			case E65_PROCESSOR_RUN:
				result= e65::runtime::acquire().debug_run();
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
			case E65_PROCESSOR_STOPPED:
				response->payload.dword = e65::runtime::acquire().bus().processor().stopped();
				break;
			case E65_PROCESSOR_WAIT:
				e65::runtime::acquire().bus().processor().set_wait(true);
				break;
			case E65_PROCESSOR_WAIT_CLEAR:
				e65::runtime::acquire().bus().processor().set_wait(false);
				break;
			case E65_PROCESSOR_WAITING:
				response->payload.dword = e65::runtime::acquire().bus().processor().waiting();
				break;
			case E65_VIDEO_FRAME:
				response->payload.dword = e65::runtime::acquire().bus().video().frame();
				break;
			case E65_VIDEO_FULLSCREEN:
				e65::runtime::acquire().bus().video().display().set_fullscreen(request->payload.dword);
				break;
			case E65_VIDEO_HIDE:
				e65::runtime::acquire().bus().video().display().set_hidden(request->payload.dword);
				break;
			default:
				THROW_E65_EXCEPTION_FORMAT(E65_EXCEPTION_COMMAND, "%u(%s)", command, E65_COMMAND_STRING(command));
		}

		result = response->result;
	} catch(e65::type::exception &exc) {
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

	E65_TRACE_ENTRY();

	try {
		e65::runtime::acquire().initialize();
	} catch(e65::type::exception &exc) {
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
		e65::runtime::acquire().bus().processor().interrupt(maskable);
	} catch(e65::type::exception &exc) {
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
e65_register_handler(
	__in e65_cb handler
	)
{
	int result = EXIT_SUCCESS;

	E65_TRACE_ENTRY_FORMAT("Handler=%p", handler);

	try {
		result = (e65::runtime::acquire().register_handler(handler) ? EXIT_SUCCESS : EXIT_FAILURE);
	} catch(e65::type::exception &exc) {
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
e65_reset(void)
{
	int result = EXIT_SUCCESS;

	try {
		result = (e65::runtime::acquire().reset() ? EXIT_SUCCESS : EXIT_FAILURE);
	} catch(e65::type::exception &exc) {
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

	E65_TRACE_ENTRY_FORMAT("Path=%p, Hex=%x, Debug=%x", path, hex, debug);

	try {

		if(!path) {
			THROW_E65_EXCEPTION_FORMAT(E65_EXCEPTION_ARGUMENT, "%p", path);
		}

		e65::runtime::acquire().run(path, hex, debug);
	} catch(e65::type::exception &exc) {
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
e65_state(
	__in int *state
	)
{
	int result = EXIT_SUCCESS;

	E65_TRACE_ENTRY_FORMAT("State=%p", state);

	try {

		if(!state) {
			THROW_E65_EXCEPTION_FORMAT(E65_EXCEPTION_ARGUMENT, "%p", state);
		}

		*state = (e65::runtime::acquire().running() ? E65_STATE_ACTIVE : E65_STATE_INACTIVE);
	} catch(e65::type::exception &exc) {
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
e65_step(
	__in int offset
	)
{
	int result = EXIT_SUCCESS;

	E65_TRACE_ENTRY_FORMAT("Offset=%i", offset);

	try {
		result = (e65::runtime::acquire().step(offset) ? EXIT_SUCCESS : EXIT_FAILURE);
	} catch(e65::type::exception &exc) {
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
e65_step_frame(
	__in int offset
	)
{
	int result = EXIT_SUCCESS;

	E65_TRACE_ENTRY_FORMAT("Offset=%i", offset);

	try {
		result = (e65::runtime::acquire().step_frame(offset) ? EXIT_SUCCESS : EXIT_FAILURE);
	} catch(e65::type::exception &exc) {
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
e65_terminate(void)
{
	int result = EXIT_SUCCESS;

	E65_TRACE_ENTRY();

	try {
		result = (e65::runtime::acquire().terminate() ? EXIT_SUCCESS : EXIT_FAILURE);
	} catch(e65::type::exception &exc) {
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
	E65_TRACE_ENTRY();

	try {
		e65::runtime::acquire().uninitialize();
	} catch(e65::type::exception &exc) {
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
