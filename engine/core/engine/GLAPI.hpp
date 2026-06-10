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
		void drawIndexed(u64 indexCount, RenderMode mode);
		void drawIndexedInstanced(u64 indexCount, u64 instanceCount, RenderMode mode);
		glm::ivec2 getViewportSize();
	}
}
