#include "time.hpp"
#include "Engine.hpp"

namespace s2f
{
	void Time::update(f64 currentTime)
	{
		this->currentTime = currentTime;
		deltaTime = this->currentTime - lastTime;
		lastTime = this->currentTime;
	}

	Time Time::get() 
	{
		Engine::get()->time();
	}

	f32 Time::current()
	{
		Engine::get()->currentTime();
	}

	f32 Time::delta()
	{
		Engine::get()->deltaTime();
	}

	f32 Time::fixedDelta()
	{
		Engine::get()->fixedDeltaTime();
	}
}
