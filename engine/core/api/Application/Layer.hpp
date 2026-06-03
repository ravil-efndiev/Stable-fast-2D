#pragma once
#include "api/ECS/Scene.hpp"
#include "api/ECS/SceneRenderer.hpp"
#include "engine/events/Event.hpp"
#include "api/objects/Camera.hpp"

namespace s2f
{
	class Application;

	/*
	* @brief Abstract class used to define application layer
	* 
	* has its own Scene and SceneRenderer objects created from base constructor
	* 
	* provides virtual methods for user to define layer-specific behavior
	*/
	class Layer
	{
	public:
		Layer();
		virtual ~Layer() = default;

		/*
		* @brief Virtual method that is called once on layer creation
		* 
		* should be used to set up initialization and setup code
		* 
		* must be implemented
		*/
		virtual void start() = 0;

		/*
		* @brief Virtual method that is called every frame before rendering stage
		* 
		* must be implemented
		* @param deltaTime time difference between frames, also accessible staticly via Time::delta()
		*/
		virtual void onUpdate(f32 deltaTime) = 0;

		/*
		* @brief Virtual method that is called every frame in rendering stage
		* 
		* use to draw scene via SceneRenderer or call draw methods of Renderer
		* 
		* must be implemented
		*/
		virtual void onRender() = 0;

		/*
		* @brief Virtual method that is called when event gets raised inside Engine via its event func
		* @param event generic event object, must be cast to a specific Event subtype, you might want to use EventDispatcher
		*/
		virtual void onEvent(Event& event) {}

		/*
		* @brief Called from Application, calls virtual onUpdate and handles extra update code
		*/
		void update(f32 deltaTime);

		/*
		* @brief Called from Application, calls virtual onRender and handles extra rendering code
		* 
		* manages renderer's render stage (begin, end)
		*/
		void render();

		/*
		* @brief Enqueues layer transition from current to a different layer inside Application
		* @tparam ToLayerT User-defined type derived from Layer that will be transitioned to
		* @param ...args Arguments for constructor of user-defined ToLayerT type
		*/
		template <std::derived_from<Layer> ToLayerT, class... Args>
		void transitionTo(Args&& ...args);

		/*
		* @brief Sets camera pointer to a user-defined camera object
		* 
		* camera will be used to set up view projection in Renderer
		*/
		void useCamera(Camera& camera) { mCamera = &camera; }

	protected:
		Renderer& mRenderer;
		Scene mScene;
		SceneRenderer mSceneRenderer;
	
	private:
		Camera* mCamera{ nullptr };
	};
}
