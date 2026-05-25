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
		return Engine::get()->time();
	}

	f32 Time::current()
	{
		return Engine::get()->currentTime();
	}

	f32 Time::delta()
	{
		return Engine::get()->deltaTime();
	}

	f32 Time::fixedDelta()
	{
		return Engine::get()->fixedDeltaTime();
	}
}
