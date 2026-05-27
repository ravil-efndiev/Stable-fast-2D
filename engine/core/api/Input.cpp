#include "Input.hpp"

#define ASSERT_INPUT_INITIALIZED S2F_ASSERT(sInputState, "Input was not initialized when calling its methods, use Input::init()")

namespace s2f
{
	InputState* Input::sInputState{ nullptr };

	void Input::init(InputState* inputState)
	{
		sInputState = inputState;
	}

	u32 Input::assertInputAndGetKeyCode(Key key)
	{
		ASSERT_INPUT_INITIALIZED;
		return static_cast<u32>(key);
	}

	u32 Input::assertInputAndGetMouseCode(Mouse mouseButton)
	{
		ASSERT_INPUT_INITIALIZED;
		return static_cast<u32>(mouseButton);
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

	bool Input::mouseButtonPressed(Mouse mouseButton)
	{
		auto mouseCode = assertInputAndGetMouseCode(mouseButton);
		return sInputState->mouseButtons[mouseCode] && !sInputState->previousMouseButtons[mouseCode];
	}

	bool Input::mouseButtonReleased(Mouse mouseButton)
	{
		auto mouseCode = assertInputAndGetMouseCode(mouseButton);
		return !sInputState->mouseButtons[mouseCode] && sInputState->previousMouseButtons[mouseCode];
	}

	bool Input::mouseButtonDown(Mouse mouseButton)
	{
		auto mouseCode = assertInputAndGetMouseCode(mouseButton);
		return sInputState->mouseButtons[mouseCode];
	}

	glm::vec2 Input::mousePosition()
	{
		ASSERT_INPUT_INITIALIZED;
		return sInputState->mousePosition;
	}
}
