#pragma once
#include "include.hpp"
#include "inputState.hpp"
#include "events/events.hpp"

namespace s2f 
{
	struct WindowInfo
	{
		glm::ivec2 size;
		std::string title;
		bool resizable{ true };
	};

	class Window 
	{
	public:
		Window(const WindowInfo& info);
		~Window();

		Window() = delete;
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		bool shouldClose() const;
		void close();
		void swapBuffers();
		void pollEvents();
		f64 getTime() const;

		glm::ivec2 size() const { return mInfo.size; }
		std::string title() const { return mInfo.title; }
		bool resizable() const { return mInfo.resizable; }

		void setTitle(const std::string& title);
		void setResizable(bool resizable);

		void setEventFunc(const EventFunc& eventFunc) { mEventFunc = eventFunc; }

	private:
		void initGLFW();
		void setupCallbacks();

		void onEvent(Event& event);

	private:
		WindowInfo mInfo;
		GLFWwindow* mWindow;
		EventFunc mEventFunc;
	};
}
