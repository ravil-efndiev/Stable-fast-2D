#include "Layer.hpp"
#include "Application.hpp"

namespace s2f
{
	Layer::Layer() 
		: mRenderer(Application::get()->renderer()), mSceneRenderer(mScene, mRenderer) {}

	void Layer::update(f32 deltaTime)
	{
		onUpdate(deltaTime);
	}

	void Layer::tick(f32 fixedDeltaTime)
	{
		onTick(fixedDeltaTime);
	}

	void Layer::render()
	{
		if (mCamera)
			mRenderer.setProjview(mCamera->projview());
		else
			mRenderer.resetProjview();
		
		mRenderer.begin();
		onRender();
		mRenderer.end();
	}

	void Layer::onFrameEnd()
	{
		mScene.onFrameEnd();
	}
}
