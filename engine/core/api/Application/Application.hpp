#pragma once
#include "engine/Engine.hpp"
#include "Layer.hpp"

namespace s2f
{
	/*
	* @brief Object representing transition between layers
	*/
	struct LayerTransition
	{
		// raw pointer from layer stack inside Application
		Layer* from{ nullptr };

		// newly created unique_ptr that will be moved into Application's layer stack on transition
		std::unique_ptr<Layer> to;
	};

	/*
	* @brief Higher-level abstraction over Engine class, owns Engine instance
	* adds layer stack, layer transitioning and abstracts away some internal object creation code
	*/
	class Application
	{
	public:
		/*
		* @brief Constructor of Aplication
		* 
		* sets static instance of Application, only one application instance can exist
		* 
		* @param engineInfo initialization struct for Engine, same as when creating Engine instance
		*/
		Application(const EngineInfo& engineInfo);

		/*
		* @brief Method to run application's main runtime loop
		* 
		* handles engine frame start/end and is responsible for manging layer initializations, updates and rendering
		*/
		void mainLoop();

		/*
		 * @brief Pushes a layer into the layer stack
		 * @tparam LayerT User-defined type derived from Layer
		 * @param ...args Arguments for constructor of user-defined LayerT type
		 */
		template<std::derived_from<Layer> LayerT, class... Args>
		void pushLayer(Args&& ...args)
		{
			mLayers.push_back(std::make_unique<LayerT>(std::forward<Args>(args)...));
		}

		Engine& engine() { return mEngine; }
		Renderer& renderer() { return mEngine.renderer(); }
		Time time() { return mEngine.time(); }

		void stop();

		/*
		* @brief Static method that returns Application instance
		* @return Application instance pointer
		*/
		static Application* get();

	private:
		template <std::derived_from<Layer> ToLayerT, class... Args>
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

#include "Layer.inl"
