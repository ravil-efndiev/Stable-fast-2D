#pragma once
#include "include.hpp"

#define S2F_EVENT_BODY(eventType)  \
	EventType type() const override { return typeStatic(); } \
	const char* typeName() const override { return #eventType; } \
	static EventType typeStatic() { return EventType::eventType; }

#define S2F_EVENT_HANDLED true
#define S2F_EVENT_PROPAGATED false

namespace s2f
{
	enum class EventType : u8
	{
		FramebufferResize,
		KeyPress,
		KeyRelease,
		MouseButtonPress,
		MouseButtonRelease,
		MouseMove,
	};

	struct Event 
	{
		virtual EventType type() const = 0;
		virtual const char* typeName() const = 0;
		bool handled = false;
	};

	using EventFunc = std::function<void(Event&)>;
}
