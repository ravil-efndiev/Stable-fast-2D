#pragma once
#include "engine/inputState.hpp"

namespace s2f
{
	class Input
	{
	public:
		static void init(InputState* inputState);
		static bool keyPressed(Key key);
		static bool keyReleased(Key key);
		static bool keyDown(Key key);

	private:
		static u32 assertInputAndGetKeyCode(Key key);

	private:
		static InputState* sInputState;
	};
}