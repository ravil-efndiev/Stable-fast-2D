#pragma once
#include "engine/Engine.hpp"
#include "Layer.hpp"

namespace s2f
{
	class Application
	{
	public:
		Application(const WindowInfo& windowInfo, const RenderInfo& renderInfo = {});

		void mainLoop();

		template<class LayerT>
		void pushLayer()
		{
			mLayers.push(std::make_shared<LayerT>(*this));
		}

		RenderInfo& renderInfo() { return mEngine.renderInfo(); }
		Renderer& renderer() { return mEngine.renderer(); }
		Time time() { return mEngine.time(); }

	private:
		static std::unique_ptr<Application> sInstance;

		Engine mEngine;
		std::stack<std::shared_ptr<Layer>> mLayers;
	};
}
