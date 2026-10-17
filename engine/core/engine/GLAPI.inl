#pragma once
#include "include.hpp"

namespace s2f
{
	namespace glapi
	{
		template <Callback Func>
		void runCustomUnpackAlignmentBlock(GLint alignment, Func&& block)
		{
			GLint prevAlignment;
			glGetIntegerv(GL_UNPACK_ALIGNMENT, &prevAlignment);
			glPixelStorei(GL_UNPACK_ALIGNMENT, alignment);
			block();
			glPixelStorei(GL_UNPACK_ALIGNMENT, prevAlignment);
		}
	}
}