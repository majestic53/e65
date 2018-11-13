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

#include <algorithm>
#include <fstream>
#include <readline/readline.h>
#include <readline/history.h>
#include "./e65_type.h"

std::string
display_command_usage(void)
{
	std::stringstream result;

	for(int command = 0; command <= E65_COMMAND_MAX; ++command) {
		std::stringstream stream_arguments, stream_command;

		if(command) {
			result << std::endl;
		}

		stream_command << E65_COMMAND_SHORT_STRING(command) << "|" << E65_COMMAND_LONG_STRING(command);

		if(E65_COMMAND_LENGTH(command)) {
			stream_arguments << E65_COMMAND_ARGUMENTS(command);
		} else {
			stream_arguments << " ";
		}

		result << E65_COLUMN_WIDTH(E65_USAGE_COLUMN_LONG_WIDTH) << stream_command.str()
			<< E65_COLUMN_WIDTH(E65_USAGE_COLUMN_SHORT_WIDTH) << stream_arguments.str()
			<< E65_COMMAND_DESCRIPTION(command);
	}

	return result.str();
}

std::string
display_usage(
	__in bool verbose
	)
{
	std::stringstream result;

	result << E65_FLAG_PREFIX << " [";

	for(int flag = 0; flag <= E65_FLAG_MAX; ++flag) {

		if(flag) {
			result << "|";
		}

		result << E65_FLAG_SHORT_STRING(flag);
	}

	result << "] " << E65_FLAG_POSTFIX;

	if(verbose) {
		result << std::endl;

		for(int flag = 0; flag <= E65_FLAG_MAX; ++flag) {
			std::stringstream stream;

			stream << std::endl << E65_FLAG_SHORT_STRING(flag) << "|" << E65_FLAG_LONG_STRING(flag);
			result << E65_COLUMN_WIDTH(E65_USAGE_COLUMN_SHORT_WIDTH) << stream.str() << E65_FLAG_DESCRIPTION(flag);
		}
	}

	return result.str();
}

std::string
display_version(
	__in bool verbose
	)
{
	std::stringstream result;

	if(verbose) {
		result << E65 << " ";
	}

	result << e65_version_string();

	if(verbose) {
		result << std::endl << E65_NOTICE;
	}

	return result.str();
}

int
parse(
	__in const std::vector<std::string> &arguments,
	__inout std::string &path,
	__inout bool &ihex,
	__inout bool &debug,
	__inout bool &help,
	__inout bool &version
	)
{
	int result = EXIT_SUCCESS;
	std::vector<std::string>::const_iterator argument;

	debug = false;
	help = false;
	ihex = false;
	version = false;
	path.clear();

	for(argument = arguments.begin(); argument != arguments.end(); ++argument) {

		if(argument->empty()) {
			continue;
		}

		if(argument->front() == std::string(E65_FLAG_DELIMITER).front()) {

			if(!E65_IS_FLAG(*argument)) {
				std::cerr << display_version(true) << std::endl
					<< std::endl << E65_EXCEPTION_STRING(E65_EXCEPTION_FLAG_UNSUPPORTED) << ": " << *argument
					<< std::endl << std::endl << display_usage(true) << std::endl;
				result = EXIT_FAILURE;
				goto exit;
			}

			switch(E65_FLAG_ID(*argument)) {
				case E65_FLAG_DEBUG:
					debug = true;
					break;
				case E65_FLAG_HELP:
					help = true;
					break;
				case E65_FLAG_HEX:
					ihex = true;
					break;
				case E65_FLAG_VERSION:
					version = true;
					break;
				default:
					std::cerr << display_version(true) << std::endl
						<< std::endl << E65_EXCEPTION_STRING(E65_EXCEPTION_FLAG_INVALID) << ": " << *argument
						<< std::endl << std::endl << display_usage(true) << std::endl;
					result = EXIT_FAILURE;
					goto exit;
					break;
			}
		} else if(!path.empty()) {
			std::cerr << display_version(true) << std::endl
				<< std::endl << E65_EXCEPTION_STRING(E65_EXCEPTION_PATH_REDEFINED) << ": " << *argument
				<< std::endl << std::endl << display_usage(true) << std::endl;
			result = EXIT_FAILURE;
			goto exit;
		} else {
			path = *argument;
		}
	}

	if(!help && !version && path.empty()) {
		std::cerr << display_version(true) << std::endl << std::endl << E65_EXCEPTION_STRING(E65_EXCEPTION_PATH_UNDEFINED)
			<< std::endl << std::endl << display_usage(true) << std::endl;
		result = EXIT_FAILURE;
		goto exit;
	}

exit:
	return result;
}

int
prompt_command(
	__in int command,
	__in const std::vector<std::string> &arguments,
	__inout bool &terminate
	)
{
	std::stringstream stream;
	int id, result = EXIT_SUCCESS;
	e65_t request = {}, response = {};

	terminate = false;

	switch(command) {
		case E65_COMMAND_BREAKPOINT_CLEAR:
			id = E65_BREAKPOINT_CLEAR;

			if(arguments.front() != E65_ARGUMENT_WILDCARD) {
				stream << std::hex << arguments.front();
				stream >> request.address;
			} else {
				id = E65_BREAKPOINT_CLEAR_ALL;
			}

			result = e65_command(id, &request, &response);
			break;
		case E65_COMMAND_BREAKPOINT_LIST:

			result = e65_command(E65_BREAKPOINT_LIST, &request, &response);
			if(result == EXIT_SUCCESS) {

				char *literal = response.payload.literal;
				if(literal) {
					std::cout << literal << std::endl;
					std::free(response.payload.literal);
					response.payload.literal = nullptr;
					literal = nullptr;
				} else {
					std::cerr << E65_EXCEPTION_STRING(E65_EXCEPTION_COMMAND_RESPONSE) << std::endl;
					result = EXIT_FAILURE;
				}
			}
			break;
		case E65_COMMAND_BREAKPOINT_SET:
			stream << std::hex << arguments.front();
			stream >> request.address;

			result = e65_command(E65_BREAKPOINT_SET, &request, &response);
			break;
		case E65_COMMAND_MEMORY_DUMP:
			stream << std::hex << arguments.front();
			stream >> request.address;

			stream.clear();
			stream.str(std::string());
			stream << std::hex << arguments.back();
			stream >> request.payload.word;

			result = e65_command(E65_MEMORY_DUMP, &request, &response);
			if(result == EXIT_SUCCESS) {

				char *literal = response.payload.literal;
				if(literal) {
					std::cout << literal << std::endl;
					std::free(response.payload.literal);
					response.payload.literal = nullptr;
					literal = nullptr;
				} else {
					std::cerr << E65_EXCEPTION_STRING(E65_EXCEPTION_COMMAND_RESPONSE) << std::endl;
					result = EXIT_FAILURE;
				}
			}
			break;
		case E65_COMMAND_MEMORY_READ:
			stream << std::hex << arguments.front();
			stream >> request.address;

			result = e65_command(E65_MEMORY_READ, &request, &response);
			if(result == EXIT_SUCCESS) {
				std::cout << "[" << E65_STRING_HEX(uint16_t, request.address) << "] --> "
					<< E65_STRING_HEX(uint8_t, response.payload.byte) << std::endl;
			}
			break;
		case E65_COMMAND_MEMORY_WRITE:
			stream << std::hex << arguments.front();
			stream >> request.address;

			stream.clear();
			stream.str(std::string());
			stream << std::hex << arguments.back();
			stream >> request.payload.word;

			result = e65_command(E65_MEMORY_WRITE, &request, &response);
			break;
		case E65_COMMAND_PROCESSOR_ACCUMULATOR:

			result = e65_command(E65_PROCESSOR_ACCUMULATOR, &request, &response);
			if(result == EXIT_SUCCESS) {
				std::cout << "A --> " << E65_STRING_HEX(uint8_t, response.payload.byte) << std::endl;
			}
			break;
		case E65_COMMAND_PROCESSOR_ACCUMULATOR_SET:
			stream << std::hex << arguments.front();
			stream >> request.payload.word;

			result = e65_command(E65_PROCESSOR_ACCUMULATOR_SET, &request, &response);
			break;
		case E65_COMMAND_PROCESSOR_CYCLE:

			result = e65_command(E65_PROCESSOR_CYCLE, &request, &response);
			if(result == EXIT_SUCCESS) {
				std::cout << response.payload.dword << std::endl;
			}
			break;
		case E65_COMMAND_PROCESSOR_FLAGS:

			result = e65_command(E65_PROCESSOR_FLAGS, &request, &response);
			if(result == EXIT_SUCCESS) {
				std::cout << "F --> " << E65_STRING_HEX(uint8_t, response.payload.byte) << std::endl;
			}
			break;
		case E65_COMMAND_PROCESSOR_FLAGS_SET:
			stream << std::hex << arguments.front();
			stream >> request.payload.word;

			result = e65_command(E65_PROCESSOR_FLAGS_SET, &request, &response);
			break;
		case E65_COMMAND_PROCESSOR_HALT:
			result = e65_command(E65_PROCESSOR_HALT, &request, &response);
			break;
		case E65_COMMAND_PROCESSOR_HALT_CLEAR:
			result = e65_command(E65_PROCESSOR_HALT_CLEAR, &request, &response);
			break;
		case E65_COMMAND_PROCESSOR_INDEX_X:

			result = e65_command(E65_PROCESSOR_INDEX_X, &request, &response);
			if(result == EXIT_SUCCESS) {
				std::cout << "X --> " << E65_STRING_HEX(uint8_t, response.payload.byte) << std::endl;
			}
			break;
		case E65_COMMAND_PROCESSOR_INDEX_X_SET:
			stream << std::hex << arguments.front();
			stream >> request.payload.word;

			result = e65_command(E65_PROCESSOR_INDEX_X_SET, &request, &response);
			break;
		case E65_COMMAND_PROCESSOR_INDEX_Y:

			result = e65_command(E65_PROCESSOR_INDEX_Y, &request, &response);
			if(result == EXIT_SUCCESS) {
				std::cout << "Y --> " << E65_STRING_HEX(uint8_t, response.payload.byte) << std::endl;
			}
			break;
		case E65_COMMAND_PROCESSOR_INDEX_Y_SET:
			stream << std::hex << arguments.front();
			stream >> request.payload.word;

			result = e65_command(E65_PROCESSOR_INDEX_Y_SET, &request, &response);
			break;
		case E65_COMMAND_PROCESSOR_IRQ:
		case E65_COMMAND_PROCESSOR_NMI:
			result = e65_interrupt(command == E65_COMMAND_PROCESSOR_IRQ);
			break;
		case E65_COMMAND_PROCESSOR_PROGRAM_COUNTER:

			result = e65_command(E65_PROCESSOR_PROGRAM_COUNTER, &request, &response);
			if(result == EXIT_SUCCESS) {
				std::cout << "PC --> " << E65_STRING_HEX(uint16_t, response.payload.word) << std::endl;
			}
			break;
		case E65_COMMAND_PROCESSOR_PROGRAM_COUNTER_SET:
			stream << std::hex << arguments.front();
			stream >> request.payload.word;

			result = e65_command(E65_PROCESSOR_PROGRAM_COUNTER_SET, &request, &response);
			break;
		case E65_COMMAND_PROCESSOR_STACK_POINTER:

			result = e65_command(E65_PROCESSOR_STACK_POINTER, &request, &response);
			if(result == EXIT_SUCCESS) {
				std::cout << "SP --> " << E65_STRING_HEX(uint8_t, response.payload.byte) << std::endl;
			}
			break;
		case E65_COMMAND_PROCESSOR_STACK_POINTER_SET:
			stream << std::hex << arguments.front();
			stream >> request.payload.word;

			result = e65_command(E65_PROCESSOR_STACK_POINTER_SET, &request, &response);
			break;
		case E65_COMMAND_PROCESSOR_STEP:
			result = e65_step();
			break;
		case E65_COMMAND_PROCESSOR_STOP:
			result = e65_command(E65_PROCESSOR_STOP, &request, &response);
			break;
		case E65_COMMAND_PROCESSOR_STOP_CLEAR:
			result = e65_command(E65_PROCESSOR_STOP_CLEAR, &request, &response);
			break;
		case E65_COMMAND_VIDEO_FRAME:

			result = e65_command(E65_VIDEO_FRAME, &request, &response);
			if(result == EXIT_SUCCESS) {
				std::cout << response.payload.dword << std::endl;
			}
			break;
		case E65_COMMAND_EXIT:
			terminate = true;
			break;
		case E65_COMMAND_HELP:
			std::cout << display_command_usage() << std::endl;
			break;
		case E65_COMMAND_VERSION:
			std::cout << display_version(false) << std::endl;
			break;
		default:
			result = EXIT_FAILURE;
			break;
	}

	return result;
}

int
prompt(void)
{
	int result = EXIT_SUCCESS;

	while(e65::runtime::acquire().running()) {
		int id;
		char *input;
		size_t length;
		bool terminate = false;
		std::string command, input_str;
		std::stringstream prompt, stream;
		std::vector<std::string> arguments;
		std::vector<std::string>::iterator argument;

#ifdef TRACE_COLOR
		prompt << E65_LEVEL_COLOR(e65::E65_LEVEL_INFORMATION);
#endif // TRACE_COLOR
		prompt << E65;
#ifdef TRACE_COLOR
		prompt << E65_LEVEL_COLOR(e65::E65_LEVEL_WARNING);
#endif // TRACE_COLOR
		prompt << E65_PROMPT;
#ifdef TRACE_COLOR
		prompt << E65_LEVEL_COLOR_RESET;
#endif // TRACE_COLOR

		input = readline(prompt.str().c_str());
		if(!input) {
			continue;
		}

		input_str = input;
		std::transform(input_str.begin(), input_str.end(), input_str.begin(), ::tolower);

		add_history(input);

		free(input);
		input = nullptr;

		stream << input_str;
		stream >> command;

		if(command.empty()) {
			continue;
		}

		while(stream) {
			arguments.push_back(std::string());
			stream >> arguments.back();

			if(arguments.back().empty()) {
				arguments.erase(arguments.end());
			}
		}

		if(!E65_IS_COMMAND(command)) {
#ifdef TRACE_COLOR
			std::cerr << E65_LEVEL_COLOR(e65::E65_LEVEL_WARNING);
#endif // TRACE_COLOR
			std::cerr << E65_EXCEPTION_STRING(E65_EXCEPTION_COMAMND_UNSUPPORTED) << ": " << E65_STRING_CHECK(command)
				<< std::endl;
#ifdef TRACE_COLOR
			std::cerr << E65_LEVEL_COLOR_RESET;
#endif // TRACE_COLOR
			continue;
		}

		id = E65_COMMAND_ID(command);

		length = E65_COMMAND_LENGTH(id);
		if(length != arguments.size()) {
#ifdef TRACE_COLOR
			std::cerr << E65_LEVEL_COLOR(e65::E65_LEVEL_WARNING);
#endif // TRACE_COLOR
			std::cerr << E65_EXCEPTION_STRING(E65_EXCEPTION_COMMAND_ARGUMENT) << ": " << input_str
				<< std::endl;
#ifdef TRACE_COLOR
			std::cerr << E65_LEVEL_COLOR_RESET;
#endif // TRACE_COLOR
			continue;
		}

		result = prompt_command(id, arguments, terminate);
		if(result != EXIT_SUCCESS) {
			std::string error_str;

#ifdef TRACE_COLOR
			std::cerr << E65_LEVEL_COLOR(e65::E65_LEVEL_ERROR);
#endif // TRACE_COLOR
			std::cerr << E65_EXCEPTION_STRING(E65_EXCEPTION_COMMAND_ERROR) << ": " << E65_STRING_CHECK(command);

			for(argument = arguments.begin(); argument != arguments.end(); ++argument) {
				std::cerr << " " << *argument;
			}

			error_str = e65_error();
			if(!error_str.empty() && (error_str != E65_STRING_EMPTY)) {
				std::cerr << " (" << error_str << ")";
			}

			std::cerr << std::endl;
#ifdef TRACE_COLOR
			std::cerr << E65_LEVEL_COLOR_RESET;
#endif // TRACE_COLOR
		}

		if(terminate) {
			break;
		}
	}

	return result;
}

int
run(
	__in const std::string &path,
	__in bool ihex,
	__in bool debug
	)
{
	int result = EXIT_SUCCESS;

	result = e65_initialize();
	if(result != EXIT_SUCCESS) {
		goto exit;
	}

	result = e65_run(path.c_str(), ihex, debug);
	if(result != EXIT_SUCCESS) {
		goto exit;
	}

	if(!debug) {

		result = e65_wait();
		if(result != EXIT_SUCCESS) {
			goto exit;
		}
	} else {
		result = prompt();
	}

exit:
	e65_uninitialize();

	return result;
}

int
main(
	__in int argc,
	__in const char *argv[]
	)
{
	std::string path;
	int result = EXIT_SUCCESS;
	bool debug = false, help = false, ihex = false, version = false;

	if(argc < E65_ARGUMENT_COUNT_MIN) {
		std::cerr << display_usage(false) << std::endl;
		result = EXIT_FAILURE;
		goto exit;
	}

	result = parse(std::vector<std::string>(argv + 1, (argv + 1) + (argc - 1)), path, ihex, debug, help, version);
	if(result != EXIT_SUCCESS) {
		goto exit;
	}

	if(help) {
		std::cout << display_version(true) << std::endl << std::endl << display_usage(true) << std::endl;
	} else if(version) {
		std::cout << display_version(false) << std::endl;
	} else {

		result = run(path, ihex, debug);
		if(result != EXIT_SUCCESS) {
			std::cerr << E65 << ": " << e65_error() << std::endl;
			goto exit;
		}
	}

exit:
	return result;
}
