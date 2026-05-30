#pragma once
#include "Event.hpp"

namespace s2f
{
	template <std::derived_from<Event> EventT>
	using EventDispatcherFunc = std::function<bool(EventT&)>;

	template <class T, std::derived_from<Event> EventT>
	using EventDispatcherMemFunc = bool (T::*)(EventT&);

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event) : mEvent(event) {}

		template <std::derived_from<Event> EventT>
		void dispatch(const EventDispatcherFunc<EventT>& eventFunc)
		{
			if (mEvent.type() == EventT::typeStatic() && !mEvent.handled)
			{
				mEvent.handled = eventFunc(static_cast<EventT&>(mEvent));
			}
		}

		template <std::derived_from<Event> EventT, class T>
		void dispatchMember(T* obj, EventDispatcherMemFunc<T, EventT> eventFunc)
		{
			dispatch<EventT>([obj, eventFunc](EventT& event)
			{
				return (obj->*eventFunc)(event);
			});
		}

	private:
		Event& mEvent;
	};
}
