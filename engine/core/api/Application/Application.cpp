#include "Application.hpp"

namespace s2f
{
	std::unique_ptr<Application> Application::sInstance;

	Application::Application(const WindowInfo& windowInfo, const RenderInfo& renderInfo)
		: mEngine(windowInfo, renderInfo) {}

	void Application::mainLoop()
	{
		mLayers.top()->start();
		while (mEngine.runs())
		{
			mEngine.startFrame();
			mLayers.top()->update(mEngine.deltaTime());
			mLayers.top()->render();
			mEngine.endFrame();
		}
	}
}
