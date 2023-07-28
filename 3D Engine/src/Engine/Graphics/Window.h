#pragma once

#include <iostream>
#include <glfw/glfw3.h>
#include <glad/glad.h>

#include "../Event/Input.h"


namespace Engine
{
	namespace Graphics
	{

		using namespace Event;

		struct WindowSettings
		{
			int Width;
			int Height;
			const char* Title;
		};


		void window_size_callback(GLFWwindow* m_Window, int width, int height);

		class Window
		{
		public:
			Window() = default;
			~Window();

			void Initialize(WindowSettings windowSettings = { 800, 600, "Demo Window!"});
			
			bool isOpen() const;
			void Clear(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);
			void Refresh();
			void Close() const;

			inline float GetAspectRatio() const 
			{ 
				return  float(m_WindowSettnigs.Width) / float(m_WindowSettnigs.Height);
			};

			inline int GetWidth() const
			{
				return m_WindowSettnigs.Width;
			};

			inline int GetHeight() const
			{
				return m_WindowSettnigs.Height;
			};
			
		private: 
			WindowSettings m_WindowSettnigs;
			GLFWwindow* m_Window;
			bool cursorLock = true;

			void DestroySelf() const;

			friend void window_size_callback(GLFWwindow* m_Window, int width, int height);
		};

		void window_size_callback(GLFWwindow* m_Window, int width, int height);

		

	}
}


