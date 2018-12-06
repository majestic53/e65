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

#include "../../include/e65.h"
#include "../include/functional/processor.h"
#include "../include/interface/input.h"
#include "../include/interface/memory.h"
#include "../include/interface/processor.h"
#include "../include/interface/video.h"
#include "./e65_test_type.h"

std::string
display_usage(
	__in_opt bool verbose = false
	)
{
	std::stringstream result;

	result << E65_TEST_FLAG_PREFIX << " [";

	for(int flag = 0; flag <= E65_TEST_FLAG_MAX; ++flag) {

		if(flag) {
			result << "|";
		}

		result << E65_TEST_FLAG_SHORT_STRING(flag);
	}

	result << "]";

	if(verbose) {
		result << std::endl;

		for(int flag = 0; flag <= E65_TEST_FLAG_MAX; ++flag) {
			std::stringstream stream;

			stream << std::endl << E65_TEST_FLAG_SHORT_STRING(flag) << "|" << E65_TEST_FLAG_LONG_STRING(flag);
			result << E65_COLUMN_WIDTH(E65_TEST_USAGE_COLUMN_WIDTH) << stream.str() << E65_TEST_FLAG_DESCRIPTION(flag);
		}
	}

	return result.str();
}

std::string
display_version(
	__in_opt bool verbose = false
	)
{
	std::stringstream result;

	if(verbose) {
		result << E65_TEST << " ";
	}

	result << e65_version_string();

	if(verbose) {
		result << std::endl << E65_TEST_NOTICE;
	}

	return result.str();
}

int
parse(
	__in const std::vector<std::string> &arguments,
	__inout bool &help,
	__inout bool &version
	)
{
	int result = EXIT_SUCCESS;
	std::vector<std::string>::const_iterator argument;

	help = false;
	version = false;

	for(argument = arguments.begin(); argument != arguments.end(); ++argument) {

		if(argument->empty()) {
			continue;
		}

		if(argument->front() == std::string(E65_TEST_FLAG_DELIMITER).front()) {

			std::map<std::string, int>::const_iterator entry = E65_TEST_FLAG_MAP.find(*argument);
			if(entry == E65_TEST_FLAG_MAP.end()) {
				std::cerr << display_version(true) << std::endl
					<< std::endl << E65_TEST_EXCEPTION_STRING(E65_TEST_EXCEPTION_FLAG_UNSUPPORTED) << ": " << *argument
					<< std::endl << std::endl << display_usage(true) << std::endl;
				result = EXIT_FAILURE;
			}

			switch(entry->second) {
				case E65_TEST_FLAG_HELP:
					help = true;
					break;
				case E65_TEST_FLAG_VERSION:
					version = true;
					break;
				default:
					std::cerr << display_version(true) << std::endl
						<< std::endl << E65_TEST_EXCEPTION_STRING(E65_TEST_EXCEPTION_FLAG_INVALID) << ": " << *argument
						<< std::endl << std::endl << display_usage(true) << std::endl;
					result = EXIT_FAILURE;
					goto exit;
			}
		}
	}

exit:
	return result;
}

int
run(void)
{
	int fixture = 0, result = EXIT_SUCCESS;

	std::srand(std::time(nullptr));

	for(; fixture <= E65_FIXTURE_MAX; ++fixture) {
		int sub_result = EXIT_SUCCESS;
		std::vector<std::string> failures;
		std::vector<std::string>::iterator failure;

		std::cout << E65_COLUMN_WIDTH(E65_TEST_COLUMN_WIDTH) << E65_FIXTURE_STRING(fixture) << "[";

		switch(fixture) {
			case e65::test::type::E65_FIXTURE_FUNCTIONAL_PROCESSOR: {
					e65::test::functional::processor instance;

					sub_result = (instance.run_all() ? EXIT_SUCCESS : EXIT_FAILURE);
					if(sub_result != EXIT_SUCCESS) {
						failures = instance.failure();
					}
				} break;
			case e65::test::type::E65_FIXTURE_INTERFACE_INPUT: {
					e65::test::interface::input instance;

					sub_result = (instance.run_all() ? EXIT_SUCCESS : EXIT_FAILURE);
					if(sub_result != EXIT_SUCCESS) {
						failures = instance.failure();
					}
				} break;
			case e65::test::type::E65_FIXTURE_INTERFACE_MEMORY: {
					e65::test::interface::memory instance;

					sub_result = (instance.run_all() ? EXIT_SUCCESS : EXIT_FAILURE);
					if(sub_result != EXIT_SUCCESS) {
						failures = instance.failure();
					}
				} break;
			case e65::test::type::E65_FIXTURE_INTERFACE_PROCESSOR: {
					e65::test::interface::processor instance;

					sub_result = (instance.run_all() ? EXIT_SUCCESS : EXIT_FAILURE);
					if(sub_result != EXIT_SUCCESS) {
						failures = instance.failure();
					}
				} break;
			case e65::test::type::E65_FIXTURE_INTERFACE_VIDEO: {
					e65::test::interface::video instance;

					sub_result = (instance.run_all() ? EXIT_SUCCESS : EXIT_FAILURE);
					if(sub_result != EXIT_SUCCESS) {
						failures = instance.failure();
					}
				} break;
			default:
				std::cerr << E65_TEST_EXCEPTION_STRING(E65_TEST_EXCEPTION_TYPE_INVALID) << ": " << fixture << std::endl;
				result = EXIT_FAILURE;
				goto exit;
		}

		if(sub_result != EXIT_SUCCESS) {
#ifdef TRACE_COLOR
			std::cout << E65_LEVEL_COLOR(e65::type::E65_LEVEL_ERROR);
#endif // TRACE_COLOR
			std::cout << "FAIL";
#ifdef TRACE_COLOR
			std::cout << E65_LEVEL_COLOR_RESET;
#endif // TRACE_COLOR
			std::cout << "]";

			for(failure = failures.begin(); failure != failures.end(); ++failure) {
				std::cout << std::endl << "--> " << E65_FIXTURE_STRING(fixture) << "::" << *failure;
			}

			failures.clear();
			result = EXIT_FAILURE;
		} else {
#ifdef TRACE_COLOR
			std::cout << E65_LEVEL_COLOR(e65::type::E65_LEVEL_INFORMATION);
#endif // TRACE_COLOR
			std::cout << "PASS";
#ifdef TRACE_COLOR
			std::cout << E65_LEVEL_COLOR_RESET;
#endif // TRACE_COLOR
			std::cout << "]";
		}

		std::cout << std::endl;
	}

exit:
	return result;
}

int
main(
	__in int argc,
	__in const char *argv[]
	)
{
	int result = EXIT_SUCCESS;
	bool help = false, version = false;

	if(argc < E65_TEST_ARGUMENT_COUNT_MIN) {
		std::cerr << display_usage(false) << std::endl;
		result = EXIT_FAILURE;
		goto exit;
	}

	result = parse(std::vector<std::string>(argv + 1, (argv + 1) + (argc - 1)), help, version);
	if(result != EXIT_SUCCESS) {
		goto exit;
	}

	if(help) {
		std::cout << display_version(true) << std::endl << std::endl << display_usage(true) << std::endl;
	} else if(version) {
		std::cout << display_version(false) << std::endl;
	} else {
		result = run();
	}

exit:
	return result;
}
