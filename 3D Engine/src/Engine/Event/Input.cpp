#include "Input.h"


namespace Engine
{
	namespace Event
	{

		bool Input::keys_press[1024];
		bool Input::keys_release[1024];
		Vector2 Input::mousePos;

		void Input::Init(GLFWwindow* m_Window)
		{
			ClearInputs();
			glfwSetKeyCallback(m_Window, key_callback);
			glfwSetCursorPosCallback(m_Window, cursor_position_callback);
		}

		void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			keys_press[key]   = (action != GLFW_RELEASE);
			keys_release[key] = (action == GLFW_RELEASE);
		}

		void Input::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
		{
			mousePos.x = xpos;
			mousePos.y = ypos;
		}

		bool Input::ButtonPress(const short& key)
		{
			return keys_press[key];
		}

		bool Input::ButtonRelease(const short& key)
		{
			return keys_release[key];
		}

		void Input::ClearInputs()
		{
			for (int i = 0; i < 1024; i++)
				keys_release[i] = false;
		}

	}
}
