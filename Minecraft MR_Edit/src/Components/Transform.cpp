#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "Transform.h"


namespace Components
{
	Matrix4f Transform::GetTransformMatrix()
	{
		Matrix4f m_Mat4(1.0f);

		m_Mat4 = glm::scale(m_Mat4, m_Scale);
		//m_Mat4 = glm::rotate(m_Mat4, m_Rotation.x, Vector3f(1.0f, 0.0f, 0.0f));
		//m_Mat4 = glm::rotate(m_Mat4, m_Rotation.y, Vector3f(0.0f, 1.0f, 0.0f));
		//m_Mat4 = glm::rotate(m_Mat4, m_Rotation.z, Vector3f(0.0f, 0.0f, 1.0f));
		//m_Forward = Vector3f(std::sin(Deg2Rad(m_Rotation.y)), std::sin(Deg2Rad(90.0f - m_Rotation.x)), std::cos(Deg2Rad(m_Rotation.y)) * std::cos(Deg2Rad(90.0f - m_Rotation.x)));

		Vector3f direction;
		direction.x = std::cos(glm::radians(m_Rotation.y - 90.0f)) * std::cos(glm::radians(-m_Rotation.x));
		direction.y = std::sin(glm::radians(-m_Rotation.x));
		direction.z = std::sin(glm::radians(m_Rotation.y - 90.0f)) * std::cos(glm::radians(-m_Rotation.x));

		m_Forward = glm::normalize(-direction);

		//std::cout << m_Forward.x << ", " << m_Forward.y << ", " << m_Forward.z << "\n";

		m_Mat4 = glm::translate(m_Mat4, m_Position);
		m_Mat4 = glm::lookAt(m_Position, m_Position + m_Forward, Vector3f(0.0f, 1.0f, 0.0f));

		return m_Mat4;
	}
}
