#pragma once

#include <functional>
#include <GLFW/glfw3.h>

#include "Events/Event.h"
#include "Events/WindowEvents.h"
#include "Events/KeyEvents.h"
#include "Events/MouseEvents.h"

using namespace Events;

namespace Graphics
{

	struct WindowProps
	{
		int Width, Height;
		const char* Title;

		WindowProps(const int& width, const int& height, const char* title)
			: Width(width), Height(height), Title(title) {}
	};

	class Window
	{
		typedef std::function<void(const Event&)> EventFuncCallback;

	public:
		Window(const WindowProps& window_props = {800, 600, "Demo Window!"});
		~Window();

		inline bool IsOpen() const { return m_Open; }
		inline void Refresh() const 
		{
			glfwSwapBuffers(m_Window);
			glfwPollEvents();
		}
		inline void Close() const { m_Open = false; }

		inline int GetWidth() const { return m_Data.Width; }
		inline int GetHeight() const { return m_Data.Height; }

		inline void SetEventFuncCallback(const EventFuncCallback& event_callback) { m_Data.EventCallback = event_callback; }

	private:
		static bool s_GLFWInitialized;
		GLFWwindow* m_Window = nullptr;
		mutable bool m_Open = false;

		

		struct WindowData
		{
			int Width, Height;
			const char* Title;
			EventFuncCallback EventCallback;

		} m_Data;

		bool Init();
		void SetupWindowHints();
		void CenterWindow();
		void SetGLFWEvents();

	};
}


