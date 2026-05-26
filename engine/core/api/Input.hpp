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

		static bool mouseButtonPressed(Mouse mouseButton);
		static bool mouseButtonReleased(Mouse mouseButton);
		static bool mouseButtonDown(Mouse mouseButton);

	private:
		static u32 assertInputAndGetKeyCode(Key key);
		static u32 assertInputAndGetMouseCode(Mouse mouseButton);

	private:
		static InputState* sInputState;
	};
}