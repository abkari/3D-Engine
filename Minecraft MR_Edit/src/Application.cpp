#include <iostream>
#include <functional>
#include "Application.h"

#include <glm/gtc/matrix_transform.hpp>


#define BIND_FN(x) std::bind(&x, this, std::placeholders::_1)

bool Application::s_GLADInitialized = false;
	
Application::Application()
{
	Init();
	grid.Init();

	shader.Load("shaders/Default/Default.vert", "shaders/Default/Default.frag");
	texture.Load("textures/d.png");

	mesh.Load({
		Vertex({-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}),
		Vertex({-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}),
		Vertex({ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}),
		Vertex({ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}),

		Vertex({-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}),
		Vertex({-0.5f,  0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}),
		Vertex({-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}),
		Vertex({-0.5f, -0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}),

		Vertex({ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}),
		Vertex({ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}),
		Vertex({-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}),
		Vertex({-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}),

		Vertex({ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}),
		Vertex({ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}),
		Vertex({ 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}),
		Vertex({ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}),

		Vertex({-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}),
		Vertex({-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}),
		Vertex({ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}),
		Vertex({ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}),

		Vertex({-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}),
		Vertex({-0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}),
		Vertex({ 0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}),
		Vertex({ 0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f})

	}, {
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10, 11, 8,

		12, 13, 14,
		14, 15, 12,

		16, 17, 18,
		18, 19, 16,

		20, 21, 22,
		22, 23, 20
	});

	camPos = {0.0f, 0.0f, 5.0f};
	camForward = { 0.0f, 0.0f, -1.0f };
	camRight = glm::normalize(glm::cross(camForward, Vector3f(0.0f, 1.0f, 0.0f)));

	//transform.SetPosition(0.0f, 0.0f, 0.0f);
	camera.SetPosition(0.0f, 0.0f, 5.0f);
}

Application::~Application()
{
	delete m_Window;
	glfwTerminate();
}

void Application::Init()
{
	m_Window = new Window();
	m_Window->SetEventFuncCallback(BIND_FN(Application::OnEvent));

	if (!s_GLADInitialized)
	{
		if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
			std::cerr << "Error::Failed to initialize glad!\n";
		else
		{
			glViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());
			s_GLADInitialized = true;
		}
	}
}

void Application::Run()
{
	if (!s_GLADInitialized)
		return;

	MainLoop();
}

void Application::OnEvent(const Event& event)
{
	EventDispatcher dispatcher((Event&) event);

	dispatcher.LinkEvent<WindowCloseEvent>(BIND_FN(Application::OnWindowClose));
	dispatcher.LinkEvent<WindowResizeEvent>(BIND_FN(Application::OnWindowResize));
	dispatcher.LinkEvent<KeyPressEvent>(BIND_FN(Application::OnKeyPress));
	dispatcher.LinkEvent<KeyReleaseEvent>(BIND_FN(Application::OnKeyRelease));
	dispatcher.LinkEvent<MouseMoveEvent>(BIND_FN(Application::OnMouseMove));
}

void Application::MainLoop()
{
	while (m_Window->IsOpen())
	{

		/*float speed = 0.005f;

		if (keyD) camPos += camRight * speed;
		if (keyA) camPos -= camRight * speed;

		if (keyW) camPos += camForward * speed;
		if (keyS) camPos -= camForward * speed;

		if (keyE) camPos += Vector3f(0.0f, 1.0f, 0.0f) * speed;
		if (keyQ) camPos -= Vector3f(0.0f, 1.0f, 0.0f) * speed;*/

		float speed = 0.005f;

		if (keyD) camPos += camera.Right() * speed;
		if (keyA) camPos -= camera.Right() * speed;

		if (keyW) camPos += camera.Forward() * speed;
		if (keyS) camPos -= camera.Forward() * speed;

		if (keyE) camPos += Vector3f(0.0f, 1.0f, 0.0f) * speed;
		if (keyQ) camPos -= Vector3f(0.0f, 1.0f, 0.0f) * speed;

		//camera.Move(-0.001f, 0.0f, 0.0f);
		//camera.Rotate(0.0f, 0.001f, 0.0f);

		Vector3f direction;
		direction.x = std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch));
		direction.y = std::sin(glm::radians(pitch));
		direction.z = std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch));

		camForward = glm::normalize(direction);
		camRight = glm::normalize(glm::cross(camForward, Vector3f(0.0f, 1.0f, 0.0f)));

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDepthFunc(GL_LESS);
		glFrontFace(GL_CW);
		glCullFace(GL_BACK);
			
			
		Matrix4f view = glm::translate(Matrix4f(1.0f), camPos);
		view = glm::lookAt(camPos, camPos + camForward, Vector3f(0.0f, 1.0f, 0.0f));
		
		//transform.Move(0.01f, 0.0f, 0.0f);
		transform.SetRotation(10.0f, 30.0f, 0.0f);
		camera.SetPosition(camPos);
		camera.SetRotation(pitch, yaw, 0.0f);

		grid.Draw(camera.GetTransformMatrix(), camera.GetProjectionMatrix((float)m_Window->GetWidth(), (float)m_Window->GetHeight()));

		shader.Enable();

		shader.SetUniform("albedo", 0);
		// SET MVP
		shader.SetUniform("model", transform.GetTransformMatrix());
		shader.SetUniform("view", camera.GetTransformMatrix());
		shader.SetUniform("proj", camera.GetProjectionMatrix((float) m_Window->GetWidth(), (float)m_Window->GetHeight()));

		texture.Bind();
		mesh.Bind();
		glDrawElements(GL_TRIANGLES, mesh.GetIndicesCount(), GL_UNSIGNED_INT, NULL);
		mesh.Unbind();
		texture.Unbind();
		shader.Disable();

		// Disable
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);

		m_Window->Refresh();
	}
}

bool Application::OnWindowClose(const WindowCloseEvent& event)
{
	m_Window->Close();
	return true;
}

bool Application::OnWindowResize(const WindowResizeEvent& event)
{
	glViewport(0, 0, event.GetWidth(), event.GetHeight());
	return true;
}

bool Application::OnKeyPress(const KeyPressEvent& event)
{
	if (event.GetKey() == KeyCode::D) keyD = true;
	if (event.GetKey() == KeyCode::A) keyA = true;

	if (event.GetKey() == KeyCode::W) keyW = true;
	if (event.GetKey() == KeyCode::S) keyS = true;

	if (event.GetKey() == KeyCode::SPACE) keyE = true;
	if (event.GetKey() == KeyCode::LEFT_SHIFT) keyQ = true;

	if (event.GetKey() == KeyCode::ESCAPE) m_Window->Close();

	return true;
}

bool Application::OnKeyRelease(const KeyReleaseEvent& event)
{
	if (event.GetKey() == KeyCode::D) keyD = false;
	if (event.GetKey() == KeyCode::A) keyA = false;
												 
	if (event.GetKey() == KeyCode::W) keyW = false;
	if (event.GetKey() == KeyCode::S) keyS = false;
												 
	if (event.GetKey() == KeyCode::SPACE) keyE = false;
	if (event.GetKey() == KeyCode::LEFT_SHIFT) keyQ = false;

	return true;
}

bool Application::OnMouseMove(const MouseMoveEvent& event)
{
	float sensitivity = 0.1f;

	if (firstEnter)
	{
		lastX = event.GetXPos();
		lastY = event.GetYPos();

		firstEnter = false;
	}

	xOffset = (event.GetXPos() - lastX) * sensitivity;
	yOffset = (lastY - event.GetYPos()) * sensitivity;

	lastX = event.GetXPos();
	lastY = event.GetYPos();

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;

	return true;
}
