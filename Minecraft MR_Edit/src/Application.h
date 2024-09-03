#pragma once

#include <glad/glad.h>

#include "Graphics/Window.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"

#include "Events/Event.h"
#include "Events/WindowEvents.h"
#include "Events/KeyEvents.h"
#include "Events/MouseEvents.h"

#include "Components/Mesh.h"
#include "Components/Transform.h"
#include "Components/Camera.h"

#include "Grid.h"


using namespace Graphics;
using namespace Events;
using namespace Components;


class Application
{
public:
	Application();
	~Application();

	void Run();

private:
	static bool s_GLADInitialized;
	Window* m_Window = nullptr;

	Grid grid;

	Shader shader;
	Texture texture;
	Mesh mesh;
	Transform transform;
	Camera camera;

	Vector3f camPos;
	Vector3f camForward;
	Vector3f camRight;

	bool keyW = false;
	bool keyA = false;
	bool keyS = false;
	bool keyD = false;
	bool keyE = false;
	bool keyQ = false;

	float yaw = 180.0f;
	float pitch = 0.0f;

	float lastX = 0.0f;
	float lastY = 0.0f;

	float xOffset = 0.0f;
	float yOffset = 0.0f;

	bool firstEnter = true;


	void Init();
	void MainLoop();

	void OnEvent(const Event& event);
	bool OnWindowClose(const WindowCloseEvent& event);
	bool OnWindowResize(const WindowResizeEvent& event);
	bool OnKeyPress(const KeyPressEvent& event);
	bool OnKeyRelease(const KeyReleaseEvent& event);
	bool OnMouseMove(const MouseMoveEvent& event);
};



