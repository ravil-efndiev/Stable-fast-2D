#pragma once
#include "engine/Renderer.hpp"
#include "Scene.hpp"
#include "Entity.hpp"

namespace s2f
{
	using SceneRendererDrawFunc = std::function<void(const std::vector<Entity>&, Renderer&)>;
	struct RenderLayer
	{
		SceneRendererDrawFunc drawFunc;
		u32 order;
	};

	class SceneRenderer
	{
	public:
		SceneRenderer(Scene& scene, Renderer& renderer);

		void render();

		void pushRenderLayer(const RenderLayer& layer);
		void pushRenderLayer(SceneRendererDrawFunc drawFunc, u32 order);

	private:
		void sortLayers();

	private:
		Scene& mScene;
		Renderer& mRenderer;
		std::vector<RenderLayer> mRenderLayers;
	};
}
