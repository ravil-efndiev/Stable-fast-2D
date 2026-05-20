#include "Layer.hpp"
#include "Application.hpp"

namespace s2f
{
	Layer::Layer() 
		: mSceneRenderer(mScene, Application::get()->renderer()) {}
}
