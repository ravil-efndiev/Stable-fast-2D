#include "time.hpp"

namespace s2f
{
	void updateTime(Time& time, f64 currentTime)
	{
		time.currentTime = currentTime;
		time.deltaTime = time.currentTime - time.lastTime;
		time.lastTime = time.currentTime;
	}
}
