#include "Window.hpp"
#include "GLAPI.hpp"

namespace s2f 
{
	Window::Window(const glm::ivec2& size, const char* title, InputState& inputState)
		: mSize(size), mTitle(title), mInputState(inputState)
	{
		initGLFW();
		setupCallbacks();
		S2F_INFO_VERBOSE("Created window with title \"" << mTitle << "\", size (" << mSize.x << ", " << mSize.y << ")");
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
			glapi::setViewport(win->mSize);
		});

		glfwSetKeyCallback(mWindow, [](GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods)
		{
			auto* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
			win->mInputState.keys[key] = action;
		});
	}

	bool Window::shouldClose() const
	{
		return glfwWindowShouldClose(mWindow);
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
