#include "Layer.hpp"
#include "Application.hpp"

namespace s2f
{
	Layer::Layer(Application& application)
		: mApplication(application), mSceneRenderer(mScene, mApplication.renderer()) {}
}
