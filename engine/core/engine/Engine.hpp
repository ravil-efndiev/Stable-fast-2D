#pragma once
#include "Window.hpp"
#include "time.hpp"
#include "Renderer.hpp"
#include "inputState.hpp"

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
		~Engine();

		bool runs() const;

		void startFrame();
		void endFrame();

		f32 deltaTime() const { return (f32)mTime.deltaTime; }
		Time time() const { return mTime; }
		RenderInfo& renderInfo() { return mRenderInfo; }
		Renderer& renderer() { return mRenderer; }

	private:
		void start();

	private:
		WindowInfo mWindowInfo;
		RenderInfo mRenderInfo;
		Time mTime;
		Window mWindow;
		Renderer mRenderer;
		InputState mInputState{};
	};
}
