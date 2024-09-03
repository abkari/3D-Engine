#pragma once

#include <functional>

namespace Events
{
	enum class EventType
	{
		WindowClosed, WindowMoved, WindowResized, WindowFocusLosted, WindowFocused,
		KeyPressed, KeyReleased, TextEntered,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled, MouseLeaved, MouseEntered
	};

	#define EVENT_TYPE(x) static EventType GetStaticType() { return EventType::x; }\
	                      EventType GetEventType() const { return GetStaticType(); }\
                          const char* GetName() const { return #x; }

	class Event
	{
	public:
		bool Handled = false;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event) {}
	
		template <typename T>
		using EventFn = std::function<bool(const T&)>;

		template <typename T>
		void LinkEvent(EventFn<T> fn)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
				m_Event.Handled = fn(static_cast<const T&>(m_Event));
		}

	private:
		Event& m_Event;
	};

	

	

}


