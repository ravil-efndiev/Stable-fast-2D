#include "Engine.hpp"
#include "GLAPI.hpp"

namespace s2f
{
	Engine::Engine(const WindowInfo& windowInfo, const RenderInfo& renderInfo) 
		: mWindowInfo(windowInfo), mRenderInfo(renderInfo), 
		mWindow(mWindowInfo.size, mWindowInfo.title) 
	{
		start();
	}

	Engine::~Engine()
	{
	}

	void Engine::start()
	{
		glapi::init();
		glapi::setViewport(mWindow.size());
		mTime.lastTime = mWindow.getTime();
		mRenderer.init();
	}

	void Engine::startFrame()
	{
		updateTime(mTime, mWindow.getTime());
		glapi::clearScreen(mRenderInfo.clearColor);
		mRenderer.begin();
	}

	void Engine::endFrame()
	{
		mRenderer.end();
		mWindow.swapBuffers();
		mWindow.pollEvents();
	}

	bool Engine::runs() const
	{
		return !mWindow.shouldClose();
	}
}
