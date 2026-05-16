#include "Engine.hpp"
#include "GLAPI.hpp"
#include "api/Input.hpp"

namespace s2f
{
	Engine::Engine(const WindowInfo& windowInfo, const RenderInfo& renderInfo) 
		: mWindowInfo(windowInfo), mRenderInfo(renderInfo), 
		mWindow(mWindowInfo.size, mWindowInfo.title, mInputState) 
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
		Input::init(&mInputState);
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
		mInputState.previousKeys = mInputState.keys;
		mInputState.previousMouseButtons = mInputState.mouseButtons;
		mWindow.pollEvents();
	}

	bool Engine::runs() const
	{
		return !mWindow.shouldClose();
	}
}
