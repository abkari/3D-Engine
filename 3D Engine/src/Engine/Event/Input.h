#pragma once

#include <iostream>
#include <glfw/glfw3.h>
#include "../Math/Glm.h"

namespace Engine
{
	namespace Event
	{
		/*
		enum Keys
		{
			Key_Unknown = -1,
			Key_A = 65,
			Key_B,
			Key_C,
			Key_D,
			Key_E,
			Key_F,
			Key_G,
			Key_H,
			Key_I,
			Key_J,
			Key_K,
			Key_L,
			Key_M,
			Key_N,
			Key_O,
			Key_P,
			Key_Q,
			Key_R,
			Key_S,
			Key_T,
			Key_U,
			Key_V,
			Key_W,
			Key_X,
			Key_Y,
			Key_Z,

			Key_Nump_0 = 48,
			Key_Nump_1,
			Key_Nump_2,
			Key_Nump_3,
			Key_Nump_4,
			Key_Nump_5,
			Key_Nump_6,
			Key_Nump_7,
			Key_Nump_8,
			Key_Nump_9,

			Key_Left_Shift,
			Key_Left_Alt = 342,
			Key_Left_Ctrl,

			Key_Right_Shift = 344,
			Key_Right_Ctrl = 345,
			Key_Right_Alt = 346,

			Key_Enter = 257,
			Key_Tap = 258,
			Key_Echap,
			Key_Space = 32,

			KEY_F1 = 290,
			KEY_F2,
			KEY_F3,
			KEY_F4,
			KEY_F5 ,
			KEY_F6 ,
			KEY_F7,
			KEY_F8,
			KEY_F9,
			KEY_F10,
			KEY_F11,
			KEY_F12,
			KEY_F13,
			KEY_F14,
			KEY_F15,
			KEY_F16,
			KEY_F17,
			KEY_F18,
			KEY_F19,
			KEY_F20,
			KEY_F21,
			KEY_F22,
			KEY_F23,
			KEY_F24,
			KEY_F25
			
		};
		*/

		using namespace Math;

		class Input
		{
		public:

			static void Init(GLFWwindow* m_Window);

			static bool ButtonPress(const short& key);
			static bool ButtonRelease(const short& key);

			inline static Vector2 GetMousePos() { return mousePos; }

			static void ClearInputs();

		private:
			static bool keys_press[1024];
			static bool keys_release[1024];

			static Vector2 mousePos;


			static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);


		};
	}
}


