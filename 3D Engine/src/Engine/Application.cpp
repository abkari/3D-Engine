#include "Application.h"


namespace Engine
{

	Camera camera;
	Shader shader;
	Mesh mesh;
	Texture texture;


	Application::Application()
	{
		OnAwake();
	}

	Application::~Application() 
	{

	}

	void Application::Run()
	{
		OnStart();
		MainLoop();
	}

	float lastTime = 0.0f;

	void Application::MainLoop()
	{
		while (window.isOpen())
		{
			float currentTime = glfwGetTime();
			float deltaTime = currentTime - lastTime;
			lastTime = currentTime;

			OnUpdate(deltaTime);
			window.Clear();
			OnDraw();
			window.Refresh();
		}
	}


	void Application::OnAwake()
	{
		WindowSettings settings;
		settings.Width = 800;
		settings.Height = 600;
		settings.Title = "3D Engine!";

		window.Initialize(settings);

	}

	void Application::OnStart()
	{

		Vertices vertices = 
		{
			{
				Vector3(-0.5f, -0.5f, 0.0f),
				Vector3(1.0f, 0.0f, 0.0f),
				Vector2(0.0f, 0.0f)
			},
			{
				Vector3(-0.5f,  0.5f, 0.0f),
				Vector3(0.0f, 1.0f, 0.0f),
				Vector2(0.0f, 1.0f)
			},
			{
				Vector3(0.5f,  0.5f, 0.0f),
				Vector3(0.0f, 0.0f, 1.0f),
				Vector2(1.0f, 1.0f)
			},
			{
				Vector3(0.5f, -0.5f, 0.0f),
				Vector3(1.0f, 1.0f, 1.0f),
				Vector2(1.0f, 0.0f)
			}

		};

		Indices indices = 
		{
			0, 1, 2,
			2, 3, 0
		};

		mesh.SetData(vertices, indices);

		if (!texture.Load("src/Textures/car.jpg"))
		{
			std::cout << "Error: Failed to load texture!" << std::endl;
		}

		if (!shader.Load(
			"src/Engine/Shaders/Default/default.vert",
			"src/Engine/Shaders/Default/default.frag"
		))
		{
			std::cout << "Error: Failed to load shader!" << std::endl;
		}
		
	}


	void Application::OnUpdate(const float& deltaTime)
	{
		camera.Update(deltaTime, window.GetAspectRatio());
	}

	void Application::OnDraw()
	{
		shader.Enable();
		texture.Bind();

		shader.SetMat4("view", camera.GetViewMatrix());
		shader.SetMat4("proj", camera.GetProjMatrix());

		shader.SetInteger("albedo", 0);

		mesh.Bind();
		glDrawElements(GL_TRIANGLES, mesh.GetCount(), GL_UNSIGNED_INT, 0);
		mesh.UnBind();
		texture.UnBind();
		shader.Disable();
	}
}
 