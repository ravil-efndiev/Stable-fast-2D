#include "Layer.hpp"
#include "Application.hpp"

namespace s2f
{
	Layer::Layer() 
		: mRenderer(Application::get()->renderer()), mSceneRenderer(mScene, mRenderer) {}

	void Layer::update(f32 deltaTime)
	{
		mScene.update(deltaTime);
		onUpdate(deltaTime);
	}

	void Layer::render()
	{
		if (mCamera)
			mRenderer.setProjview(mCamera->projview());
		
		onRender();
	}
}
