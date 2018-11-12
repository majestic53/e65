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
		std::stringstream stream;

		if(command) {
			result << std::endl;
		}

		stream << E65_COMMAND_SHORT_STRING(command) << "|" << E65_COMMAND_LONG_STRING(command);
		result << E65_COLUMN_WIDTH(E65_USAGE_COLUMN_WIDTH) << stream.str() << E65_COMMAND_DESCRIPTION(command);
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
			result << E65_COLUMN_WIDTH(E65_USAGE_COLUMN_WIDTH) << stream.str() << E65_FLAG_DESCRIPTION(flag);
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
prompt(void)
{
	int result = EXIT_SUCCESS;

	while(e65::runtime::acquire().running()) {
		int type;
		char *input;
		size_t length;
		std::string command, input_str;
		std::stringstream prompt, stream;
		e65_t request = {}, response = {};
		std::vector<std::string> arguments;

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

		type = E65_COMMAND_ID(command);

		length = E65_COMMAND_LENGTH(type);
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

		switch(type) {
			case E65_COMMAND_CYCLE:
				result = e65_command(E65_PROCESSOR_CYCLE, &request, &response);
				if(result != EXIT_SUCCESS) {
					goto exit;
				}

				std::cout << response.payload.dword << std::endl;
				break;
			case E65_COMMAND_EXIT:
				goto exit;
			case E65_COMMAND_FRAME:
				result = e65_command(E65_VIDEO_FRAME, &request, &response);
				if(result != EXIT_SUCCESS) {
					goto exit;
				}

				std::cout << response.payload.dword << std::endl;
				break;
			case E65_COMMAND_HELP:
				std::cout << display_command_usage() << std::endl;
				break;
			case E65_COMMAND_IRQ:
			case E65_COMMAND_NMI:
				result = e65_interrupt(type == E65_COMMAND_IRQ);
				break;
			case E65_COMMAND_STEP:
				result = e65_step();
				break;
			case E65_COMMAND_VERSION:
				std::cout << display_version(false) << std::endl;
				break;
			default:
				result = EXIT_FAILURE;
				break;
		}

		if(result != EXIT_SUCCESS) {
#ifdef TRACE_COLOR
			std::cerr << E65_LEVEL_COLOR(e65::E65_LEVEL_ERROR);
#endif // TRACE_COLOR
			std::cerr << E65_EXCEPTION_STRING(E65_EXCEPTION_COMMAND_ERROR) << ": " << E65_STRING_CHECK(command)
				<< ": " << e65_error() << std::endl;
#ifdef TRACE_COLOR
			std::cerr << E65_LEVEL_COLOR_RESET;
#endif // TRACE_COLOR
		}
	}

exit:
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
