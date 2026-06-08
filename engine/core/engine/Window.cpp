#include "Window.hpp"

namespace s2f 
{
	Window::Window(const WindowInfo& info)
		: mInfo(info)
	{
		initGLFW();
		setupCallbacks();
		Logger::infoVerbose("Created window with title \"{}\", size ({}, {})", mInfo.title, mInfo.size.x, mInfo.size.y);
	}

	Window::~Window() 
	{
		glfwDestroyWindow(mWindow);
		glfwTerminate();
	}

	void Window::initGLFW()
	{
		auto initRes = glfwInit();
		S2F_ASSERT(initRes, "Failed to initialize GLFW");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, mInfo.openglVersion.major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, mInfo.openglVersion.minor);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, mInfo.resizable);
#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
		mWindow = glfwCreateWindow(mInfo.size.x, mInfo.size.y, mInfo.title.c_str(), nullptr, nullptr);
		S2F_ASSERT(mWindow, "Failed to create GLFW window");

		glfwMakeContextCurrent(mWindow);
	}

	void Window::setupCallbacks()
	{
		glfwSetWindowUserPointer(mWindow, this);

		glfwSetFramebufferSizeCallback(mWindow, [](GLFWwindow* window, i32 width, i32 height) 
		{
			auto* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
			win->mInfo.size = { width, height };
			ResizeEvent event(width, height);
			win->onEvent(event);
		});

		glfwSetKeyCallback(mWindow, [](GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods)
		{
			auto* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
			if (action == GLFW_PRESS)
			{
				KeyPressEvent event(static_cast<Key>(key));
				win->onEvent(event);
			}
			else
			{
				KeyReleaseEvent event(static_cast<Key>(key));
				win->onEvent(event);
			}
		});

		glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* window, i32 button, i32 action, i32 mods)
		{
			auto* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
			if (action == GLFW_PRESS)
			{
				MouseButtonPressEvent event(static_cast<Mouse>(button));
				win->onEvent(event);
			}
			else
			{
				MouseButtonReleaseEvent event(static_cast<Mouse>(button));
				win->onEvent(event);
			}
		});

		glfwSetCursorPosCallback(mWindow, [](GLFWwindow* window, f64 mouseX, f64 mouseY)
		{
			auto* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
			MouseMoveEvent event((f32)mouseX, (f32)mouseY);
			win->onEvent(event);
		});
	}

	void Window::onEvent(Event& event)
	{
		if (!mEventFunc) return;
		mEventFunc(event);
	}

	bool Window::shouldClose() const
	{
		return glfwWindowShouldClose(mWindow);
	}

	void Window::close()
	{
		glfwSetWindowShouldClose(mWindow, true);
	}

	void Window::swapBuffers()
	{
		glfwSwapBuffers(mWindow);
	}

	void Window::pollEvents()
	{
		glfwPollEvents();
	}

	f64 Window::getTime() const
	{
		return glfwGetTime();
	}

	void Window::setTitle(std::string_view title)
	{
		mInfo.title = title;
		glfwSetWindowTitle(mWindow, mInfo.title.c_str());
	}

	void Window::setResizable(bool resizable)
	{
		mInfo.resizable = resizable;
		glfwSetWindowAttrib(mWindow, GLFW_RESIZABLE, mInfo.resizable);
	}
}
