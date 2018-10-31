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

#include "../include/runtime.h"
#include "./runtime_type.h"

namespace e65 {

	runtime::runtime(void) :
		e65::interface::singleton<e65::runtime>(e65::interface::E65_SINGLETON_RUNTIME)
	{
		// TODO
	}

	runtime::~runtime(void)
	{
		// TODO
	}

	bool
	runtime::on_initialize(
		__in const void *context,
		__in size_t length
		)
	{
		bool result;

		// TODO
		std::cout << __FUNCTION__ << "(" << E65_STRING_HEX(uintptr_t, context) << ", " << length << ")" << std::endl;
		result = true;
		// ---

		return result;
	}

	bool
	runtime::on_run(
		__in const void *context,
		__in size_t length
		)
	{
		bool result;

		// TODO
		std::cout << __FUNCTION__ << "(" << E65_STRING_HEX(uintptr_t, context) << ", " << length << ")" << std::endl;
		result = true;
		// ---

		return result;
	}

	bool
	runtime::on_start(
		__in const void *context,
		__in size_t length
		)
	{
		bool result;

		// TODO
		std::cout << __FUNCTION__ << "(" << E65_STRING_HEX(uintptr_t, context) << ", " << length << ")" << std::endl;
		result = true;
		// ---

		return result;
	}

	void
	runtime::on_stop(void)
	{

		// TODO
		std::cout << __FUNCTION__ << std::endl;
		// ---
	}

	void
	runtime::on_uninitialize(void)
	{

		// TODO
		std::cout << __FUNCTION__ << std::endl;
		// ---
	}

	std::string
	runtime::to_string(void) const
	{
		std::stringstream result;

		result << E65_RUNTIME_HEADER << "(" << E65_STRING_HEX(uintptr_t, this) << ")"
			<< " Interface=" << e65::interface::singleton<e65::runtime>::to_string();

		if(m_initialized) {
			result << ", Thread=" << e65::type::thread::to_string();
		}

		return result.str();
	}

	std::string
	runtime::version(void)
	{
		std::stringstream result;

		result << E65_VERSION_MAJOR << "." << E65_VERSION_MINOR << "." << E65_VERSION_WEEK << "." << E65_VERSION_REVISION
			<< "-" << E65_VERSION_RELEASE;

		return result.str();
	}
}
