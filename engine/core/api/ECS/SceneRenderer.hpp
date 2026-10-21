#pragma once
#include "engine/Renderer.hpp"
#include "engine/TextRenderer.hpp"
#include "Scene.hpp"
#include "Entity.hpp"
#include "UI/StyleLibrary.hpp"

namespace s2f
{
	using SceneRendererDrawFunc = std::function<void(const std::vector<Entity>&, Renderer&)>;
	using SceneRendererUIDrawFunc = std::function<void(const std::vector<Entity>&, Renderer&, TextRenderer&, ui::StyleLibrary&)>;

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
	* @brief Object used to define rendering and oredering logic for UI components for SceneRenderer
	*/
	struct UIRenderLayer
	{
		// Callback used to select components from Scene and call draw methods of Renderer and TextRenderer
		SceneRendererUIDrawFunc drawFunc;

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

		/*
		* @brief Adds a UI render layer, render layers for default UI components (e.g. Text, Button) are present by default
		*
		* Responsible for sorting render layer list by order value of each layer
		* @param layer a UIRenderLayer instance
		*/
		void pushUIRenderLayer(const UIRenderLayer& layer);

		/*
		* @brief Adds a UI render layer by instantiating it from drawFunc and order
		*
		* render layers for default UI components (e.g. Text, Button) are present by default
		*
		* Responsible for sorting render layer list by order value of each layer
		* @param drawFunc callback used to select components from Scene and call draw methods of Renderer and TextRenderer
		* @param order order of rendering, the higher the value, the later drawFunc will be called during rendering
		*/
		void pushUIRenderLayer(const SceneRendererUIDrawFunc& drawFunc, u32 order);

		/*
		* @brief Sets TextRenderer and StyleLibrary references to be used for UI render layers
		* 
		* If not set, UI rendering will not be used during render() call, even if UIRenderLayers are present
		* @param textRenderer TextRenderer reference to be used for UI render layers
		* @param styleLibrary StyleLibrary reference to be used for UI render layers
		*/
		void useUI(TextRenderer& textRenderer, ui::StyleLibrary& styleLibrary);

	private:
		void sortLayers();

	private:
		Scene& mScene;
		Renderer& mRenderer;
		TextRenderer* mTextRenderer{ nullptr };
		ui::StyleLibrary* mStyleLibrary{ nullptr };
		std::vector<RenderLayer> mRenderLayers;
		std::vector<UIRenderLayer> mUIRenderLayers;
	};
}
 