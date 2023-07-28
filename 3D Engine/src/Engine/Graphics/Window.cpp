#include "Window.h"


namespace Engine
{
	namespace Graphics
	{
		void Window::Initialize(WindowSettings windowSettings)
		{
			m_WindowSettnigs = windowSettings;

			if (!glfwInit())
			{
				std::cout << "Error: Failed to intialize glfw!" << std::endl;
				return;
			}

			

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

			m_Window = glfwCreateWindow(
				windowSettings.Width, 
				windowSettings.Height,
				windowSettings.Title,
				NULL,
				NULL
			);

			if (!m_Window)
			{
				std::cout << "Error: Failed to create glfw window!" << std::endl;
				glfwTerminate();
				return;
			}

			
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			glfwMakeContextCurrent(m_Window);

			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				std::cout << "Error: Failed to initialize glad!" << std::endl;
				glfwDestroyWindow(m_Window);
				glfwTerminate();
				return;
			}


			glfwSetWindowUserPointer(m_Window, this);
			glfwSetWindowSizeCallback(m_Window, window_size_callback);

			Input::Init(m_Window);

		}

		void Window::DestroySelf() const
		{
			glfwDestroyWindow(m_Window);
			glfwTerminate();
		}

		Window::~Window()
		{
			DestroySelf();
		}

		bool Window::isOpen() const
		{
			return (!m_Window)? false : !glfwWindowShouldClose(m_Window);
		}

		void Window::Clear(float r, float g, float b, float a)
		{
			glClearColor(r, g, b, a);
			glClear(GL_COLOR_BUFFER_BIT);
		}

		void Window::Refresh()
		{
			glfwSwapBuffers(m_Window);
			
			if (Input::ButtonRelease(GLFW_KEY_ESCAPE))
			{
				glfwSetInputMode(
					m_Window, 
					GLFW_CURSOR,
					((cursorLock)? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED)
				);

				cursorLock = !cursorLock;
			}

			Input::ClearInputs();
			glfwPollEvents();
		}

		void Window::Close() const
		{
			glfwSetWindowShouldClose(m_Window, true);
		}

		void window_size_callback(GLFWwindow* m_Window, int width, int height)
		{
			Window* window = static_cast<Window*>(glfwGetWindowUserPointer(m_Window));

			window->m_WindowSettnigs.Width = width;
			window->m_WindowSettnigs.Height = height;

			glViewport(0, 0, width, height);
		}
	}
}
