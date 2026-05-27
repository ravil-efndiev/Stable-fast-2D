#include "Window.hpp"

namespace s2f 
{
	Window::Window(const glm::ivec2& size, const char* title)
		: mSize(size), mTitle(title)
	{
		initGLFW();
		setupCallbacks();
		log::infoVerbose("Created window with title \"{}\", size ({}, {})", mTitle, mSize.x, mSize.y);
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

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
		mWindow = glfwCreateWindow(mSize.x, mSize.y, mTitle, nullptr, nullptr);
		S2F_ASSERT(mWindow, "Failed to create GLFW window");

		glfwMakeContextCurrent(mWindow);
	}

	void Window::setupCallbacks()
	{
		glfwSetWindowUserPointer(mWindow, this);

		glfwSetFramebufferSizeCallback(mWindow, [](GLFWwindow* window, i32 width, i32 height) 
		{
			auto* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
			win->mSize = { width, height };
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
}
