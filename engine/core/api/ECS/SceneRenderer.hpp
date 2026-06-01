#pragma once
#include "engine/Renderer.hpp"
#include "Scene.hpp"
#include "Entity.hpp"

namespace s2f
{
	using SceneRendererDrawFunc = std::function<void(const std::vector<Entity>&, Renderer&)>;

	/*
	* @brief Object used to define rendering and oredering logic for SceneRenderer
	*/
	struct RenderLayer
	{
		// Callback used to select components from Scene and call Renderer's draw methods
		SceneRendererDrawFunc drawFunc;

		// Order of rendering, the higher the value, the later drawFunc will be called during rendering
		u32 order;
	};

	/*
	* @brief Higher-level abstraction to simplify drawing components inside a Scene
	* 
	* Allows to add custom render functions to draw custom renderable components and sort them via render layers
	* 
	* Creates and manages render layers for default compoenents (e.g. Sprite)
	*/
	class SceneRenderer
	{
	public:
		/*
		* @param scene Scene reference from which components will be used for rendering
		* @param renderer Renderer reference which will be used for actual draw calls
		* 
		* SceneRenderer is not responsible for calling begin/end of a Renderer
		*/
		SceneRenderer(Scene& scene, Renderer& renderer);

		/*
		* @brief Goes through render layers and performs draw operations
		* 
		* Should be called during rendering stage (between begin/end methods of a Renderer)
		*/
		void render();

		/*
		* @brief Adds a render layer, render layers for default components (e.g. Sprite) are present by default
		* 
		* Responsible for sorting render layer list by order value of each layer
		* @param layer a RenderLayer instance
		*/
		void pushRenderLayer(const RenderLayer& layer);

		/*
		* @brief Adds a render layer by instantiating it from drawFunc and order
		*	
		* render layers for default components (e.g. Sprite) are present by default
		* 
		* Responsible for sorting render layer list by order value of each layer
		* @param drawFunc callback used to select components from Scene and call Renderer's draw methods
		* @param order order of rendering, the higher the value, the later drawFunc will be called during rendering
		*/
		void pushRenderLayer(const SceneRendererDrawFunc& drawFunc, u32 order);

	private:
		void sortLayers();

	private:
		Scene& mScene;
		Renderer& mRenderer;
		std::vector<RenderLayer> mRenderLayers;
	};
}
