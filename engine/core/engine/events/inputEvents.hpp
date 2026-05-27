#pragma once
#include "Event.hpp"

namespace s2f
{
	struct KeyPressEvent : public Event
	{
		KeyPressEvent(Key key) : key(key) {}
		S2F_EVENT_BODY(KeyPress)

		Key key;
	};

	struct KeyReleaseEvent : public Event
	{
		KeyReleaseEvent(Key key) : key(key) {}
		S2F_EVENT_BODY(KeyRelease)

		Key key;
	};

	struct MouseButtonPressEvent : public Event
	{
		MouseButtonPressEvent(Mouse button) : button(button) {}
		S2F_EVENT_BODY(MouseButtonPress)

		Mouse button;
	};

	struct MouseButtonReleaseEvent : public Event
	{
		MouseButtonReleaseEvent(Mouse button) : button(button) {}
		S2F_EVENT_BODY(MouseButtonRelease)

		Mouse button;
	};

	struct MouseMoveEvent : public Event
	{
		MouseMoveEvent(f32 mouseX, f32 mouseY) : mouseX(mouseX), mouseY(mouseY) {}
		S2F_EVENT_BODY(MouseMove)

		f32 mouseX, mouseY;
	};
}