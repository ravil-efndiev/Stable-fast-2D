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

	Engine::Engine(const EngineInfo& info) 
		: mClearColor(info.clearColor), mWindow(info.windowInfo), mRenderer(info.rendererInfo)
	{
		S2F_ASSERT(!sInstance, "Engine instance can only be created once");
		sInstance = this;
		start();
	}

	bool onWindowResize(ResizeEvent& event);

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
			dispatcher.dispatch<KeyPressEvent>([this](auto& event) { return onKeyEvent(event.key, true); });
			dispatcher.dispatch<KeyReleaseEvent>([this](auto& event) { return onKeyEvent(event.key, false); });
			dispatcher.dispatch<MouseButtonPressEvent>([this](auto& event) { return onMouseEvent(event.button, true); });
			dispatcher.dispatch<MouseButtonReleaseEvent>([this](auto& event) { return onMouseEvent(event.button, false); });
			dispatcher.dispatch<MouseMoveEvent>([this](auto& event) { return onMouseMove(event); });
			dispatcher.dispatch<ResizeEvent>(onWindowResize);

			if (mEventFunc) mEventFunc(event);
		});
	}

	void Engine::startFrame()
	{
		mTime.update(mWindow.getTime());
		glapi::clearScreen(mClearColor);
	}

	void Engine::endFrame()
	{
		mWindow.swapBuffers();
		mInputState.update();
		mWindow.pollEvents();
	}

	bool Engine::runs() const
	{
		return !mWindow.shouldClose();
	}

	void Engine::stop()
	{
		mWindow.close();
	}

	bool Engine::onKeyEvent(Key key, bool press)
	{
		mInputState.keys[static_cast<u32>(key)] = press;
		return S2F_EVENT_PROPAGATED;
	}

	bool Engine::onMouseEvent(Mouse button, bool press)
	{
		mInputState.mouseButtons[static_cast<u32>(button)] = press;
		return S2F_EVENT_PROPAGATED;
	}

	bool Engine::onMouseMove(MouseMoveEvent& event)
	{
		mInputState.mousePosition.x = event.mouseX;
		mInputState.mousePosition.y = event.mouseY;
		return S2F_EVENT_PROPAGATED;
	}

	bool onWindowResize(ResizeEvent& event)
	{
		glapi::setViewport({ event.width, event.height });
		return S2F_EVENT_PROPAGATED;
	}
}
