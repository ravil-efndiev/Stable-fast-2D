#pragma once
#include "Event.hpp"

namespace s2f
{
	struct ResizeEvent : public Event
	{
		ResizeEvent(i32 width, i32 height) : width(width), height(height) {}

		S2F_EVENT_BODY(FramebufferResize)

		i32 width;
		i32 height;
	};
}