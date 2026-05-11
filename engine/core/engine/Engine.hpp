#pragma once
#include "Window.hpp"
#include "time.hpp"

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

		f32 deltaTime() const;
		Time time() const;

		RenderInfo& renderInfo();

	private:
		void start();

	private:
		WindowInfo mWindowInfo;
		RenderInfo mRenderInfo;
		Window mWindow;
		Time mTime;
	};
}
