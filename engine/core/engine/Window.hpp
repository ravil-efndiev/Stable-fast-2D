#pragma once
#include <include.hpp>

namespace s2f 
{
	class Window 
	{
	public:
		Window(const glm::ivec2& size, const char* title);
		~Window();

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		bool shouldClose() const;
		void swapBuffers();
		void pollEvents();
		f64 getTime() const;

	private:
		void initGLFW();
		void initGLAD();
		void setupCallbacks();

	private:
		glm::ivec2 mSize;
		const char* mTitle;
		GLFWwindow* mWindow;
	};

}
