#pragma once
#include "include.hpp"
#include "inputState.hpp"
#include "events/Event.hpp"
#include "events/inputEvents.hpp"

namespace s2f 
{
	class Window 
	{
	public:
		Window(const glm::ivec2& size, const char* title);
		~Window();

		Window() = delete;
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		bool shouldClose() const;
		void swapBuffers();
		void pollEvents();
		f64 getTime() const;

		glm::ivec2 size() const { return mSize; }

		void setEventFunc(const EventFunc& eventFunc) { mEventFunc = eventFunc; }

	private:
		void initGLFW();
		void setupCallbacks();

		void onEvent(Event& event);

	private:
		glm::ivec2 mSize;
		const char* mTitle;
		GLFWwindow* mWindow;
		EventFunc mEventFunc;
	};
}
