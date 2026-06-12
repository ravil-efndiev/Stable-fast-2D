#include "GLAPI.hpp"

namespace s2f
{
	namespace glapi
	{
		static i32 maxTextureSlotsCached{ -1 };

		void init()
		{
			auto res = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
			S2F_ASSERT(res, "Failed to initialize GLAD");

			glEnable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			auto version = (const char*)glGetString(GL_VERSION);
			auto glslVersion = (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
			Logger::info("OpenGL Version: {}", version);
			Logger::info("GLSL Version: {}", glslVersion);
		}

		void setViewport(const glm::ivec2& size)
		{
			Logger::infoVerbose("glapi::setViewport() size = ({}, {})", size.x, size.y);
			glViewport(0, 0, size.x, size.y);
		}

		void clearScreen(const glm::vec4& color)
		{
			glClearColor(color.r, color.g, color.b, color.a);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		i32 getMaxTextureSlots()
		{
			if (maxTextureSlotsCached != -1) return maxTextureSlotsCached;
			GLint maxTextureUnits = 0;
			glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnits);
			return std::min(maxTextureUnits, 32);
		}

		void drawIndexed(u64 indexCount, RenderMode mode)
		{
			glPolygonMode(GL_FRONT_AND_BACK, mode == RenderMode::Fill ? GL_FILL : GL_LINE);
			glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
		}

		void drawIndexedInstanced(u64 indexCount, u64 instanceCount, RenderMode mode)
		{
			glPolygonMode(GL_FRONT_AND_BACK, mode == RenderMode::Fill ? GL_FILL : GL_LINE);
			glDrawElementsInstanced(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr, instanceCount);
		}

		glm::ivec2 getViewportSize()
		{
			int viewport[4];
			glGetIntegerv(GL_VIEWPORT, viewport);
			return { viewport[2], viewport[3] };
		}

		void setDepthFuncLequal()
		{
			glDepthFunc(GL_LEQUAL);
			glDepthMask(GL_FALSE);
		}

		void setDepthFuncLess()
		{
			glDepthFunc(GL_LESS);
			glDepthMask(GL_TRUE);
		}

		void toggleAdditiveBlend(bool flag)
		{
			if (flag)
				glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			else
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
	}
}
