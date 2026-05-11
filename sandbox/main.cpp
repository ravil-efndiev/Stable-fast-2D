#include "sf2d.hpp"

int main()
{
	s2f::Engine engine({ {1000, 700}, "Sandbox" });

	while (engine.runs()) 
	{
		engine.startFrame();
		
		engine.endFrame();
	}

	return 0;
}
