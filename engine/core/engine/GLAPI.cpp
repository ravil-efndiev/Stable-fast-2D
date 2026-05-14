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

			const GLubyte* version = glGetString(GL_VERSION);
			const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
			S2F_INFO("OpenGL Version: " << version);
			S2F_INFO("GLSL Version: " << glslVersion);
		}

		void setViewport(const glm::ivec2& size)
		{
			S2F_INFO("glapi::setViewport() size = (" << size.x << ", " << size.y << ")");
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

		void drawIndexed(size_t indexCount)
		{
			glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
		}
	}
}
