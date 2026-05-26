#include "Engine.hpp"
#include "GLAPI.hpp"
#include "api/Input.hpp"

namespace s2f
{
	static Engine* sInstance{ nullptr };

	Engine* Engine::get()
	{
		S2F_ASSERT(sInstance, "Engine::get() Engine was not initialized");
		return sInstance;
	}

	Engine::Engine(const WindowInfo& windowInfo, const RenderInfo& renderInfo) 
		: mWindowInfo(windowInfo), mRenderInfo(renderInfo), 
		mWindow(mWindowInfo.size, mWindowInfo.title) 
	{
		S2F_ASSERT(!sInstance, "Engine instance can only be created once");
		sInstance = this;
		start();
	}

	void Engine::start()
	{
		glapi::init();
		glapi::setViewport(mWindow.size());
		mTime.lastTime = mWindow.getTime();
		mRenderer.init();
		Input::init(&mInputState);

		mWindow.setEventFunc([this](Event& event)
		{
			EventDispatcher dispatcher(event);
			dispatcher.dispatch<KeyPressEvent>([this](KeyPressEvent& event) { return onKeyEvent(event.key, true); });
			dispatcher.dispatch<KeyReleaseEvent>([this](KeyReleaseEvent& event) { return onKeyEvent(event.key, false); });

			if (mEventFunc) mEventFunc(event);
		});
	}

	bool Engine::onKeyEvent(Key key, bool press)
	{
		mInputState.keys[static_cast<u32>(key)] = press;
		return S2F_EVENT_PROPAGATED;
	}

	void Engine::startFrame()
	{
		mTime.update(mWindow.getTime());
		glapi::clearScreen(mRenderInfo.clearColor);
		mRenderer.begin();
	}

	void Engine::endFrame()
	{
		mRenderer.end();
		mWindow.swapBuffers();
		mInputState.update();
		mWindow.pollEvents();
	}

	bool Engine::runs() const
	{
		return !mWindow.shouldClose();
	}
}
