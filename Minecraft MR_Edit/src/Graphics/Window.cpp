#include <iostream>
#include <exception>
#include "Window.h"

namespace Graphics
{

	bool Window::s_GLFWInitialized = false;

	Window::Window(const WindowProps& window_props) 
	{
		m_Data.Width = window_props.Width;
		m_Data.Height= window_props.Height;
		m_Data.Title = window_props.Title;

		m_Open = Init();
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_Window);
	}

	bool Window::Init()
	{
		try
		{
			if (!s_GLFWInitialized)
			{
				if (!glfwInit())
					throw std::runtime_error("Failed to initialize glfw!");
				s_GLFWInitialized = true;
			}
		
			SetupWindowHints();

			m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title, NULL, NULL);

			if (!m_Window)
				throw std::runtime_error("Failed to create glfw window!");

			glfwMakeContextCurrent(m_Window);
		}
		catch (const std::runtime_error error)
		{
			std::cerr << "ERROR::" << error.what() << "\n";
			return false;
		}

		CenterWindow();
		SetGLFWEvents();

		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		return true;
	}

	void Window::SetupWindowHints()
	{
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
		glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
		glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
		glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);

		glfwWindowHint(GLFW_FLOATING, GLFW_FALSE);
		glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);
		glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_FALSE);
		
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_OPENGL_ANY_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	}

	void Window::CenterWindow()
	{
		const GLFWvidmode* videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		int xPos = (videoMode->width - m_Data.Width) / 2;
		int yPos = (videoMode->height - m_Data.Height) / 2;
		
		glfwSetWindowPos(m_Window, xPos, yPos);
	}

	void Window::SetGLFWEvents()
	{
		glfwSetWindowUserPointer(m_Window, &m_Data);

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& m_Data = *(WindowData*) glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			m_Data.EventCallback(event);
		});
		glfwSetWindowPosCallback(m_Window, [](GLFWwindow* window, int xpos, int ypos) {
			WindowData& m_Data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowMoveEvent event(xpos, ypos);
			m_Data.EventCallback(event);
		});
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData& m_Data = *(WindowData*)glfwGetWindowUserPointer(window);
			m_Data.Width = width;
			m_Data.Height= height;

			WindowResizeEvent event(width, height);
			m_Data.EventCallback(event);
		});
		glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* window, int focused) {
			WindowData& m_Data = *(WindowData*)glfwGetWindowUserPointer(window);

			if (focused)
			{
				WindowFocusEvent event;
				m_Data.EventCallback(event);
			}
			else
			{
				WindowFocusLostEvent event;
				m_Data.EventCallback(event);
			}
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& m_Data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressEvent event(key, 0);
					m_Data.EventCallback(event);
					break;
				}
				
				case GLFW_REPEAT:
				{
					KeyPressEvent event(key, 1);
					m_Data.EventCallback(event);
					break;
				}

				case GLFW_RELEASE:
				{
					KeyReleaseEvent event(key);
					m_Data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int codepoint) {
			WindowData& m_Data = *(WindowData*)glfwGetWindowUserPointer(window);
			TextEnterEvent event(codepoint);
			m_Data.EventCallback(event);

		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& m_Data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressEvent event(button);
					m_Data.EventCallback(event);
					break;
				}
				
				case GLFW_RELEASE:
				{
					MouseButtonReleaseEvent event(button);
					m_Data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) {
			WindowData& m_Data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMoveEvent event((float) xpos, (float) ypos);
			m_Data.EventCallback(event);
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) {
			WindowData& m_Data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrollEvent event(xoffset, yoffset);
			m_Data.EventCallback(event);
		});

		glfwSetCursorEnterCallback(m_Window, [](GLFWwindow* window, int entered) {
			WindowData& m_Data = *(WindowData*)glfwGetWindowUserPointer(window);

			if (entered)
			{
				MouseEnterEvent event;
				m_Data.EventCallback(event);
			}
			else
			{
				MouseLeaveEvent event;
				m_Data.EventCallback(event);
			}
		});
	}
}