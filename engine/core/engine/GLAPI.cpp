#include "GLAPI.hpp"

namespace s2f
{
	namespace glapi
	{
		void init()
		{
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
		}

		void clearScreen(const glm::vec4& color)
		{
			glClearColor(color.r, color.g, color.b, color.a);
			glClear(GL_COLOR_BUFFER_BIT);
		}
	}
}
