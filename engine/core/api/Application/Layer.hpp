#pragma once
#include "api/ECS/Scene.hpp"
#include "api/ECS/SceneRenderer.hpp"

namespace s2f
{
	class Application;
	class Layer
	{
	public:
		Layer(Application& application);
		virtual ~Layer() = default;

		virtual void start() = 0;
		virtual void update(f32 dt) = 0;
		virtual void render() = 0;

	private:
		Application& mApplication;

	protected:
		Scene mScene;
		SceneRenderer mSceneRenderer;
	};
}
