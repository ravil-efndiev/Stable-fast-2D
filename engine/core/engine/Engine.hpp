#pragma once
#include "Window.hpp"
#include "time.hpp"
#include "Renderer.hpp"
#include "inputState.hpp"
#include "events/events.hpp"

namespace s2f
{
	struct EngineInfo 
	{
		glm::vec4 clearColor{ 0.f, 0.f, 0.f, 0.f };
		RendererInfo rendererInfo{ RenderMode::Fill, 5000 };
		WindowInfo windowInfo;
	};

	class Engine 
	{
	public:
		Engine(const EngineInfo& info);
		~Engine() = default;

		bool runs() const;
		void stop();

		void startFrame();
		void endFrame();

		void setEventFunc(const EventFunc& eventFunc) { mEventFunc = eventFunc; }

		f32 deltaTime() const { return (f32)mTime.deltaTime; }
		f32 currentTime() const { return (f32)mTime.currentTime; }
		f32 fixedDeltaTime() const { return mTime.fixedDeltaTime; }
		Time time() const { return mTime; }
		Renderer& renderer() { return mRenderer; }

		void setClearColor(const glm::vec4& clearColor) { mClearColor = clearColor; }

		static Engine* get();

	private:
		void start();

		bool onKeyEvent(Key key, bool press);
		bool onMouseEvent(Mouse button, bool press);
		bool onMouseMove(MouseMoveEvent& event);

	private:
		Time mTime;
		Window mWindow;
		Renderer mRenderer;
		InputState mInputState{};
		EventFunc mEventFunc;
		glm::vec4 mClearColor;
	};
}
