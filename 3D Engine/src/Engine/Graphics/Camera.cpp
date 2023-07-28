#include "Camera.h"


namespace Engine
{
	namespace Graphics
	{


		Camera::Camera()
		{
			camPos = Vector3(0.0f, 0.0f, 5.0f);
			camUp = Vector3(0.0f, 1.0f, 0.0f);
		}

		void Camera::SetParameters(const float& fov, const float& asrectRatio, const float& near, const float& far)
		{
			m_Fov = fov;
			m_Near = near;
			m_Far = far;
		}

		void Camera::SetFov(const float& fov)
		{
			m_Fov = fov;
		}

		void Camera::SetNear(const float& near)
		{
			m_Near = near;
		}

		void Camera::SetFar(const float& far)
		{
			m_Far = far;
		}

		void Camera::Update(const float& deltaTime, const float& aspectRatio)
		{
			view = Mat4(1.0f);
			projection = Mat4(1.0f);

			projection = glm::perspective( glm::radians(m_Fov), aspectRatio, m_Near, m_Far);

			TransformCalc();
			HandleMovement(deltaTime);

			view = glm::lookAt(camPos, camPos + camFront, camUp);
		}

		void Camera::TransformCalc()
		{
			Vector2 mousePos = Input::GetMousePos();

			//std::cout << mousePos.x << " / " << mousePos.y << std::endl;

			if (firstEnter)
			{
				lastX = mousePos.x;
				lastY = mousePos.y;
				firstEnter = false;
			}

			float xoffset = mousePos.x - lastX;
			float yoffset = lastY - mousePos.y;

			lastX = mousePos.x;
			lastY = mousePos.y;

			xoffset *= sensitivity;
			yoffset *= sensitivity;

			yaw += xoffset;
			pitch += yoffset;

			//std::cout << "Yaw : " << yaw << std::endl;

			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;

			glm::vec3 direction;
			direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
			direction.y = sin(glm::radians(pitch));
			direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

			camFront = glm::normalize(direction);
			camRight = glm::normalize(glm::cross(camFront, camUp));
		}

		void Camera::HandleMovement(const float& deltaTime)
		{
			if (Input::ButtonPress(GLFW_KEY_D))
				camPos += camRight * speed * deltaTime;

			if (Input::ButtonPress(GLFW_KEY_A))
				camPos -= camRight * speed * deltaTime;

			if (Input::ButtonPress(GLFW_KEY_W))
				camPos += camFront * speed * deltaTime;

			if (Input::ButtonPress(GLFW_KEY_S))
				camPos -= camFront * speed * deltaTime;

			if (Input::ButtonPress(GLFW_KEY_E))
				camPos += camUp * speed * deltaTime;

			if (Input::ButtonPress(GLFW_KEY_LEFT_SHIFT))
				camPos -= camUp * speed * deltaTime;
		}

	}
}
