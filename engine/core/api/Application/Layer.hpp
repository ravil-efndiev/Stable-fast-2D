#pragma once
#include "api/ECS/Scene.hpp"
#include "api/ECS/SceneRenderer.hpp"
#include "api/objects/Camera.hpp"

namespace s2f
{
	class Application;
	class Layer
	{
	public:
		Layer();
		virtual ~Layer() = default;

		virtual void start() = 0;
		virtual void onUpdate(f32 dt) = 0;
		virtual void onRender() = 0;

		void update(f32 deltaTime);
		void render();

		template <class ToLayerT, class... Args>
		void transitionTo(Args&& ...args)
		{
			Application::get()->template enqueueLayerTransition<ToLayerT>(this, std::forward<Args>(args)...);
		}

		void useCamera(Camera& camera) { mCamera = &camera; }

	protected:
		Renderer& mRenderer;
		Scene mScene;
		SceneRenderer mSceneRenderer;
	
	private:
		Camera* mCamera{ nullptr };
	};
}
