#pragma once
#include "engine/Engine.hpp"
#include "Layer.hpp"

namespace s2f
{
	struct LayerTransition
	{
		Layer* from{ nullptr };
		std::unique_ptr<Layer> to;
	};

	class Application
	{
	public:
		Application(const WindowInfo& windowInfo, const RenderInfo& renderInfo = {});

		void mainLoop();

		template<class LayerT, class... Args>
		void pushLayer(Args&& ...args)
		{
			mLayers.push_back(std::make_unique<LayerT>(std::forward<Args>(args)...));
		}

		RenderInfo& renderInfo() { return mEngine.renderInfo(); }
		Renderer& renderer() { return mEngine.renderer(); }
		Time time() { return mEngine.time(); }

		void stop();

		static Application* get();

	private:
		template <class ToLayerT, class... Args>
		void enqueueLayerTransition(Layer* from, Args&& ...args)
		{
			mLayerTransitions.emplace_back(from, std::make_unique<ToLayerT>(std::forward<Args>(args)...));
		}

		void executeLayerTransitions();

	private:
		Engine mEngine;
		std::vector<std::unique_ptr<Layer>> mLayers;
		std::vector<LayerTransition> mLayerTransitions;

		friend class Layer;
	};
}
