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

#include "../../include/system/display.h"
#include "../../include/trace.h"
#include "./display_type.h"

namespace e65 {

	namespace system {

		display::display(void) :
			e65::interface::singleton<e65::system::display>(e65::interface::E65_SINGLETON_DISPLAY),
			m_renderer(nullptr),
			m_texture(nullptr),
			m_window(nullptr)
		{
			E65_TRACE_ENTRY();
			E65_TRACE_EXIT();
		}

		display::~display(void)
		{
			E65_TRACE_ENTRY();
			E65_TRACE_EXIT();
		}

		void
		display::clear(void)
		{
			E65_TRACE_ENTRY();

			if(!e65::interface::singleton<e65::system::display>::initialized()) {
				THROW_E65_SYSTEM_DISPLAY_EXCEPTION(E65_SYSTEM_DISPLAY_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Display clearing");

			m_pixel.resize(E65_DISPLAY_WIDTH * E65_DISPLAY_HEIGHT, E65_DISPLAY_COLOR_BACKGROUND.raw);

			E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Display cleared");

			E65_TRACE_EXIT();
		}

		bool
		display::fullscreen(void) const
		{
			bool result;

			E65_TRACE_ENTRY();

			if(!e65::interface::singleton<e65::system::display>::initialized()) {
				THROW_E65_SYSTEM_DISPLAY_EXCEPTION(E65_SYSTEM_DISPLAY_EXCEPTION_UNINITIALIZED);
			}

			result = (SDL_GetWindowFlags(m_window) & E65_DISPLAY_FULLSCREEN_FLAGS);

			E65_TRACE_EXIT_FORMAT("Result=%x", result);
			return result;
		}

		bool
		display::on_initialize(
			__in const void *context,
			__in size_t length
			)
		{
			bool result = true;

			E65_TRACE_ENTRY_FORMAT("Context[%u]=%p", length, context);

			E65_TRACE_MESSAGE_FORMAT(E65_LEVEL_INFORMATION, "Display initializing", "{%u, %u} Scale=%.1f",
				E65_DISPLAY_WIDTH, E65_DISPLAY_HEIGHT, E65_DISPLAY_SCALE);

			m_title = E65;
			m_pixel.resize(E65_DISPLAY_WIDTH * E65_DISPLAY_HEIGHT, E65_DISPLAY_COLOR_BACKGROUND.raw);

			m_window = SDL_CreateWindow(E65_STRING_CHECK(m_title), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
					E65_DISPLAY_WIDTH * E65_DISPLAY_SCALE, E65_DISPLAY_HEIGHT * E65_DISPLAY_SCALE, E65_DISPLAY_FLAGS);

			if(!m_window) {
				THROW_E65_SYSTEM_DISPLAY_EXCEPTION_FORMAT(E65_SYSTEM_DISPLAY_EXCEPTION_EXTERNAL, "SDL_CreateWindow failed! %s",
					SDL_GetError());
			}

			m_renderer = SDL_CreateRenderer(m_window, -1, E65_DISPLAY_RENDERER_FLAGS);
			if(!m_renderer) {
				THROW_E65_SYSTEM_DISPLAY_EXCEPTION_FORMAT(E65_SYSTEM_DISPLAY_EXCEPTION_EXTERNAL, "SDL_CreateRenderer failed! %s",
					SDL_GetError());
			}

			if(SDL_RenderSetLogicalSize(m_renderer, E65_DISPLAY_WIDTH, E65_DISPLAY_HEIGHT)) {
				THROW_E65_SYSTEM_DISPLAY_EXCEPTION_FORMAT(E65_SYSTEM_DISPLAY_EXCEPTION_EXTERNAL,
					"SDL_RenderSetLogicalSize failed! %s", SDL_GetError());
			}

			if(SDL_SetRenderDrawColor(m_renderer, E65_DISPLAY_COLOR_BACKGROUND.red, E65_DISPLAY_COLOR_BACKGROUND.green,
					E65_DISPLAY_COLOR_BACKGROUND.blue, E65_DISPLAY_COLOR_BACKGROUND.alpha)) {
				THROW_E65_SYSTEM_DISPLAY_EXCEPTION_FORMAT(E65_SYSTEM_DISPLAY_EXCEPTION_EXTERNAL,
					"SDL_SetRenderDrawColor failed! %s", SDL_GetError());
			}

			if(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, E65_DISPLAY_RENDERER_QUALITY) == SDL_FALSE) {
				THROW_E65_SYSTEM_DISPLAY_EXCEPTION_FORMAT(E65_SYSTEM_DISPLAY_EXCEPTION_EXTERNAL, "SDL_SetHint failed! %s",
					SDL_GetError());
			}

			m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
					E65_DISPLAY_WIDTH, E65_DISPLAY_HEIGHT);

			if(!m_texture) {
				THROW_E65_SYSTEM_DISPLAY_EXCEPTION_FORMAT(E65_SYSTEM_DISPLAY_EXCEPTION_EXTERNAL, "SDL_CreateTexture failed! %s",
					SDL_GetError());
			}

			if(SDL_RenderClear(m_renderer)) {
				THROW_E65_SYSTEM_DISPLAY_EXCEPTION_FORMAT(E65_SYSTEM_DISPLAY_EXCEPTION_EXTERNAL, "SDL_RenderClear failed! %s",
					SDL_GetError());
			}

			SDL_RenderPresent(m_renderer);

			E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Display initialized");

			E65_TRACE_EXIT_FORMAT("Result=%x", result);
			return result;
		}

		void
		display::on_uninitialize(void)
		{
			E65_TRACE_ENTRY();

			E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Display uninitializing");

			if(m_texture) {
				SDL_DestroyTexture(m_texture);
				m_texture = nullptr;
			}

			if(m_renderer) {
				SDL_DestroyRenderer(m_renderer);
				m_renderer = nullptr;
			}

			if(m_window) {
				SDL_DestroyWindow(m_window);
				m_window = nullptr;
			}

			E65_TRACE_MESSAGE(E65_LEVEL_INFORMATION, "Display uninitialized");

			E65_TRACE_EXIT();
		}

		uint32_t
		display::pixel(
			__in uint32_t x,
			__in uint32_t y
			) const
		{
			uint32_t index, result;

			E65_TRACE_ENTRY_FORMAT("Position={%u, %u}", x, y);

			if(!e65::interface::singleton<e65::system::display>::initialized()) {
				THROW_E65_SYSTEM_DISPLAY_EXCEPTION(E65_SYSTEM_DISPLAY_EXCEPTION_UNINITIALIZED);
			}

			index = E65_DISPLAY_PIXEL_INDEX(x, y);
			if(index >= m_pixel.size()) {
				THROW_E65_SYSTEM_DISPLAY_EXCEPTION_FORMAT(E65_SYSTEM_DISPLAY_EXCEPTION_POSITION, "{%u, %u}", x, y);
			}

			result = m_pixel.at(index);

			E65_TRACE_EXIT_FORMAT("Result=%u(%08x)", result, result);
			return result;
		}

		void
		display::set_frame_rate(
			__in float frame_rate
			)
		{
			std::stringstream result;

			E65_TRACE_ENTRY_FORMAT("Frame-rate=%.1f", frame_rate);

			if(!e65::interface::singleton<e65::system::display>::initialized()) {
				THROW_E65_SYSTEM_DISPLAY_EXCEPTION(E65_SYSTEM_DISPLAY_EXCEPTION_UNINITIALIZED);
			}

			result << m_title << " [" << E65_FLOAT_PRECISION(1, frame_rate) << " fps]";
			SDL_SetWindowTitle(m_window, E65_STRING_CHECK(result.str()));

			E65_TRACE_EXIT();
		}

		void
		display::set_fullscreen(
			__in bool fullscreen
			)
		{
			E65_TRACE_ENTRY_FORMAT("Fullscreen=%x", fullscreen);

			if(!e65::interface::singleton<e65::system::display>::initialized()) {
				THROW_E65_SYSTEM_DISPLAY_EXCEPTION(E65_SYSTEM_DISPLAY_EXCEPTION_UNINITIALIZED);
			}

			if((SDL_GetWindowFlags(m_window) & E65_DISPLAY_FULLSCREEN_FLAGS) != fullscreen) {
				E65_TRACE_MESSAGE_FORMAT(E65_LEVEL_INFORMATION, "Display mode change", "%s", fullscreen ? "Fullscreen" : "Window");

				SDL_ShowCursor(!fullscreen);

				if(SDL_SetWindowFullscreen(m_window, fullscreen ? E65_DISPLAY_FULLSCREEN_FLAGS : 0) < 0) {
					THROW_E65_SYSTEM_DISPLAY_EXCEPTION_FORMAT(E65_SYSTEM_DISPLAY_EXCEPTION_EXTERNAL,
						"SDL_SetWindowFullscreen failed! %s", SDL_GetError());
				}
			}

			E65_TRACE_EXIT();
		}

		void
		display::set_pixel(
			__in uint32_t index,
			__in uint8_t color
			)
		{
			E65_TRACE_ENTRY_FORMAT("Index=%u, Color=%u(%s)", index, color, E65_DISPLAY_COLOR_STRING(color));

			if(!e65::interface::singleton<e65::system::display>::initialized()) {
				THROW_E65_SYSTEM_DISPLAY_EXCEPTION(E65_SYSTEM_DISPLAY_EXCEPTION_UNINITIALIZED);
			}

			if(index >= m_pixel.size()) {
				THROW_E65_SYSTEM_DISPLAY_EXCEPTION_FORMAT(E65_SYSTEM_DISPLAY_EXCEPTION_INDEX, "%u", index);
			}

			m_pixel.at(index) = E65_DISPLAY_COLOR(color).raw;

			E65_TRACE_EXIT();
		}

		void
		display::set_pixel(
			__in uint32_t x,
			__in uint32_t y,
			__in uint8_t color
			)

		{
			E65_TRACE_ENTRY_FORMAT("Position={%u, %u}, Color=%u(%s)", x, y, color, E65_DISPLAY_COLOR_STRING(color));

			set_pixel(E65_DISPLAY_PIXEL_INDEX(x, y), color);

			E65_TRACE_EXIT();
		}

		void
		display::set_title(
			__in const std::string &title
			)
		{
			E65_TRACE_ENTRY_FORMAT("Title[%u]=%s", title.size(), E65_STRING_CHECK(title));

			if(!e65::interface::singleton<e65::system::display>::initialized()) {
				THROW_E65_SYSTEM_DISPLAY_EXCEPTION(E65_SYSTEM_DISPLAY_EXCEPTION_UNINITIALIZED);
			}

			m_title = title;
			SDL_SetWindowTitle(m_window, E65_STRING_CHECK(m_title));

			E65_TRACE_EXIT();
		}

		void
		display::show(void) const
		{
			E65_TRACE_ENTRY();

			if(!e65::interface::singleton<e65::system::display>::initialized()) {
				THROW_E65_SYSTEM_DISPLAY_EXCEPTION(E65_SYSTEM_DISPLAY_EXCEPTION_UNINITIALIZED);
			}

			if(SDL_UpdateTexture(m_texture, nullptr, &m_pixel[0], E65_DISPLAY_WIDTH * sizeof(uint32_t))) {
				THROW_E65_SYSTEM_DISPLAY_EXCEPTION_FORMAT(E65_SYSTEM_DISPLAY_EXCEPTION_EXTERNAL, "SDL_UpdateTexture failed! %s",
					SDL_GetError());
			}

			if(SDL_RenderClear(m_renderer)) {
				THROW_E65_SYSTEM_DISPLAY_EXCEPTION_FORMAT(E65_SYSTEM_DISPLAY_EXCEPTION_EXTERNAL, "SDL_RenderClear failed! %s",
					SDL_GetError());
			}

			if(SDL_RenderCopy(m_renderer, m_texture, nullptr, nullptr)) {
				THROW_E65_SYSTEM_DISPLAY_EXCEPTION_FORMAT(E65_SYSTEM_DISPLAY_EXCEPTION_EXTERNAL, "SDL_RenderCopy failed! %s",
					SDL_GetError());
			}

			SDL_RenderPresent(m_renderer);

			E65_TRACE_EXIT();
		}

		std::string
		display::title(void) const
		{
			E65_TRACE_ENTRY();

			if(!e65::interface::singleton<e65::system::display>::initialized()) {
				THROW_E65_SYSTEM_DISPLAY_EXCEPTION(E65_SYSTEM_DISPLAY_EXCEPTION_UNINITIALIZED);
			}

			E65_TRACE_EXIT_FORMAT("Result[%u]=%s", m_title.size(), E65_STRING_CHECK(m_title));
			return m_title;
		}

		std::string
		display::to_string(void) const
		{
			std::stringstream result;

			result << E65_SYSTEM_DISPLAY_HEADER << "(" << E65_STRING_HEX(uintptr_t, this) << ")"
				<< " Interface=" << e65::interface::singleton<e65::system::display>::to_string();

			if(e65::interface::singleton<e65::system::display>::initialized()) {
				result << ", Title[" << m_title.size() << "]=" << E65_STRING_CHECK(m_title)
					<< ", Pixel[" << m_pixel.size() << "]=" << E65_STRING_HEX(uintptr_t, &m_pixel)
					<< ", Window=" << E65_STRING_HEX(uintptr_t, m_window)
					<< ", Renderer=" << E65_STRING_HEX(uintptr_t, m_renderer)
					<< ", Texture=" << E65_STRING_HEX(uintptr_t, m_texture);
			}

			return result.str();
		}
	}
}
