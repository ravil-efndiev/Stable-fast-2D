#include "Engine.hpp"
#include "GLAPI.hpp"

namespace s2f
{
	Engine::Engine(const WindowInfo& windowInfo, const RenderInfo& renderInfo) 
		: mWindowInfo(windowInfo), mRenderInfo(renderInfo), 
		mWindow(mWindowInfo.size, mWindowInfo.title) {}

	Engine::~Engine()
	{
	}

	void Engine::start()
	{
		glapi::init();
		mTime.lastTime = mWindow.getTime();
	}

	void Engine::startFrame()
	{
		updateTime(mTime, mWindow.getTime());
		glapi::clearScreen(mRenderInfo.clearColor);
	}

	void Engine::endFrame()
	{
		mWindow.swapBuffers();
		mWindow.pollEvents();
	}

	bool Engine::runs() const
	{
		return !mWindow.shouldClose();
	}

	f32 Engine::deltaTime() const
	{
		return static_cast<f32>(mTime.deltaTime);
	}

	Time Engine::time() const
	{
		return mTime;
	}

	RenderInfo& Engine::renderInfo()
	{
		return mRenderInfo;
	}
}
