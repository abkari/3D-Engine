#pragma once

#include "./Graphics/Window.h"
#include "./Graphics/Camera.h"
#include "./Graphics/Shader.h"
#include "./Graphics/Mesh.h"
#include "./Graphics/Texture.h"



namespace Engine
{

	using namespace Graphics;

	class Application
	{

	public:
		Application();
		~Application();

		void Run();

	private:
		Window window;

		void MainLoop();

		void OnAwake();
		void OnStart();
		void OnUpdate(const float& deltaTime);
		void OnDraw();

	};
}


