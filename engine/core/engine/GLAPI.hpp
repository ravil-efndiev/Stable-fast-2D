#pragma once
#include "include.hpp"

namespace s2f 
{
	namespace glapi
	{
		void init();
		void setViewport(const glm::ivec2& size);
		void clearScreen(const glm::vec4& color);
		i32 getMaxTextureSlots();
		void drawIndexed(size_t indexCount);
		glm::ivec2 getViewportSize();
	}
}
