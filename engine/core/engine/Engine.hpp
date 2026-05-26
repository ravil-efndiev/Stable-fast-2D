#pragma once
#include "Window.hpp"
#include "time.hpp"
#include "Renderer.hpp"
#include "inputState.hpp"
#include "events/Event.hpp"
#include "events/EventDispatcher.hpp"

namespace s2f
{
	struct WindowInfo 
	{
		glm::ivec2 size;
		const char* title;
	};

	struct RenderInfo 
	{
		glm::vec4 clearColor{ 0.f, 0.f, 0.f, 0.f };
	};

	class Engine 
	{
	public:
		Engine(const WindowInfo& windowInfo, const RenderInfo& renderInfo = {});
		~Engine() = default;

		bool runs() const;

		void startFrame();
		void endFrame();

		void setEventFunc(const EventFunc& eventFunc) { mEventFunc = eventFunc; }

		f32 deltaTime() const { return (f32)mTime.deltaTime; }
		f32 currentTime() const { return (f32)mTime.currentTime; }
		f32 fixedDeltaTime() const { return mTime.fixedDeltaTime; }
		Time time() const { return mTime; }
		RenderInfo& renderInfo() { return mRenderInfo; }
		Renderer& renderer() { return mRenderer; }

		static Engine* get();

	private:
		void start();

		bool onKeyEvent(Key key, bool press);

	private:
		WindowInfo mWindowInfo;
		RenderInfo mRenderInfo;
		Time mTime;
		Window mWindow;
		Renderer mRenderer;
		InputState mInputState{};
		EventFunc mEventFunc;
	};
}
