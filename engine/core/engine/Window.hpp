#pragma once
#include "include.hpp"
#include "inputState.hpp"

namespace s2f 
{
	class Window 
	{
	public:
		Window(const glm::ivec2& size, const char* title, InputState& inputState);
		~Window();

		Window() = delete;
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		bool shouldClose() const;
		void swapBuffers();
		void pollEvents();
		f64 getTime() const;

		glm::ivec2 size() const { return mSize; }

	private:
		void initGLFW();
		void setupCallbacks();

	private:
		glm::ivec2 mSize;
		const char* mTitle;
		GLFWwindow* mWindow;
		InputState& mInputState;
	};

}
