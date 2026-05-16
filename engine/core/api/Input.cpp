#include "Input.hpp"

namespace s2f
{
	InputState* Input::sInputState{ nullptr };

	void Input::init(InputState* inputState)
	{
		sInputState = inputState;
	}

	u32 Input::assertInputAndGetKeyCode(Key key)
	{
		S2F_ASSERT(sInputState, "Input was not initialized when calling its methods, use Input::init()");
		return static_cast<u32>(key);
	}
	
	bool Input::keyPressed(Key key)
	{
		auto keyCode = assertInputAndGetKeyCode(key);
		return sInputState->keys[keyCode] && !sInputState->previousKeys[keyCode];
	}

	bool Input::keyReleased(Key key)
	{
		auto keyCode = assertInputAndGetKeyCode(key);
		return !sInputState->keys[keyCode] && sInputState->previousKeys[keyCode];
	}

	bool Input::keyDown(Key key)
	{
		auto keyCode = assertInputAndGetKeyCode(key);
		return sInputState->keys[keyCode];
	}
}
