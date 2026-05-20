#pragma once
#include "api/ECS/Scene.hpp"
#include "api/ECS/SceneRenderer.hpp"

namespace s2f
{
	class Application;
	class Layer
	{
	public:
		Layer();
		virtual ~Layer() = default;

		virtual void start() = 0;
		virtual void update(f32 dt) = 0;
		virtual void render() = 0;

		template <class ToLayerT, class... Args>
		void transitionTo(Args&& ...args)
		{
			Application::get()->template enqueueLayerTransition<ToLayerT>(this, std::forward<Args>(args)...);
		}

	protected:
		Scene mScene;
		SceneRenderer mSceneRenderer;
	};
}
