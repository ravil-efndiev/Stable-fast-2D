#pragma once
#include "Event.hpp"

namespace s2f
{
	template <std::derived_from<Event> EventT>
	using EventDispatcherFunc = std::function<bool(EventT&)>;

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event) : mEvent(event) {}

		template <std::derived_from<Event> EventT>
		void dispatch(const EventDispatcherFunc<EventT>& eventFunc)
		{
			if (mEvent.type() == EventT::typeStatic() && !mEvent.handled)
			{
				mEvent.handled = eventFunc(*(EventT*)&mEvent);
			}
		}

	private:
		Event& mEvent;
	};
}
