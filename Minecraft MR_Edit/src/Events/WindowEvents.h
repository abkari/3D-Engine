#pragma once

#include "Event.h"

namespace Events
{
	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		EVENT_TYPE(WindowClosed)
	};

	class WindowMoveEvent : public Event
	{
	public:
		WindowMoveEvent(const int& xpos, const int& ypos) 
			: x_Pos(xpos), y_Pos(ypos) {}

		inline int GetXPos() const { return x_Pos; }
		inline int GetYPos() const { return y_Pos; }

		EVENT_TYPE(WindowMoved)

	private:
		int x_Pos, y_Pos;
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(const int& width, const int& height)
			: m_Width(width), m_Height(height) {}

		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }

		EVENT_TYPE(WindowResized)

	private:
		int m_Width, m_Height;
	};

	class WindowFocusLostEvent : public Event
	{
	public:
		WindowFocusLostEvent() = default;

		EVENT_TYPE(WindowFocusLosted)
	};

	class WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent() = default;

		EVENT_TYPE(WindowFocused)
	};
}