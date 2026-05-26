#include "inputState.hpp"

namespace s2f
{
	void InputState::update()
	{
		previousKeys = keys;
		previousMouseButtons = mouseButtons;
	}
}
