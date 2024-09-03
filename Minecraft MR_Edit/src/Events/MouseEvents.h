#pragma once

#include "Event.h"

namespace Events
{
	class MouseButtonPressEvent : public Event
	{
	public:
		MouseButtonPressEvent(const int& button)
			: m_Button(button) {}

		inline int GetButton() const { return m_Button; }

		EVENT_TYPE(MouseButtonPressed)

	private:
		int m_Button;
	};

	class MouseButtonReleaseEvent : public Event
	{
	public:
		MouseButtonReleaseEvent(const int& button)
			: m_Button(button) {}

		inline int GetButton() const { return m_Button; }

		EVENT_TYPE(MouseButtonReleased)

	private:
		int m_Button;
	};

	class MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(const float& xpos, const float& ypos)
			: x_Pos(xpos), y_Pos(ypos) {}

		inline float GetXPos() const { return x_Pos; }
		inline float GetYPos() const { return y_Pos; }

		EVENT_TYPE(MouseMoved)

	private:
		float x_Pos, y_Pos;
	};

	class MouseScrollEvent : public Event
	{
	public:
		MouseScrollEvent(const float& xoffset, const float& yoffset)
			: x_Offset(xoffset), y_Offset(yoffset) {}

		inline float GetXOffset() const { return x_Offset; }
		inline float GetYOffset() const { return y_Offset; }

		EVENT_TYPE(MouseScrolled)

	private:
		float x_Offset, y_Offset;
	};

	class MouseLeaveEvent : public Event
	{
	public:
		MouseLeaveEvent() = default;

		EVENT_TYPE(MouseLeaved)
	};

	class MouseEnterEvent : public Event
	{
	public:
		MouseEnterEvent() = default;

		EVENT_TYPE(MouseLeaved)
	};
}