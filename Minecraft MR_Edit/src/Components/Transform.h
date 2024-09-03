#pragma once

#include "Math/Vectors.h"
#include "Math/Matrices.h"

namespace Components
{
	class Transform
	{
	public:
		Transform(
			const Vector3f& position = {0.0f, 0.0f, 0.0f},
			const Vector3f& rototion = { 0.0f, 0.0f, 0.0f },
			const Vector3f& scale = { 1.0f, 1.0f, 1.0f }
		)
			: m_Position(position), m_Rotation(rototion), m_Scale(scale) {}
		virtual ~Transform() = default;

		inline const Vector3f& GetPosition() const { return m_Position; }
		inline const Vector3f& GetRotation() const { return m_Rotation; }
		inline const Vector3f& GetScale() const { return m_Scale; }

		inline void SetPosition(const Vector3f& position) { m_Position = position; }
		inline void SetPosition(const float& x, const float& y, const float& z) { m_Position = Vector3f(x, y, z); }

		inline void SetRotation(const Vector3f& rotation) { m_Rotation = rotation; }
		inline void SetRotation(const float& x, const float& y, const float& z) { m_Rotation = Vector3f(x, y, z); }

		inline void SetScale(const Vector3f& scale) { m_Scale = scale; }
		inline void SetScale(const float& x, const float& y, const float& z) { m_Scale = Vector3f(x, y, z); }

		inline void Move(const Vector3f& move) { m_Position += move; }
		inline void Move(const float& x, const float& y, const float& z) { m_Position += Vector3f(x, y, z); }

		inline void Rotate(const Vector3f& rotate) { m_Rotation += rotate; }
		inline void Rotate(const float& x, const float& y, const float& z) { m_Rotation += Vector3f(x, y, z); }

		inline Vector3f Forward() const { return glm::normalize(m_Forward); }
		inline Vector3f Right() const { return glm::normalize(glm::cross(Forward(), Vector3f(0.0f, 1.0f, 0.0f))); }

		Matrix4f GetTransformMatrix();

	private:
		Vector3f m_Position;
		Vector3f m_Rotation;
		Vector3f m_Scale;

		Vector3f m_Forward;
		Vector3f m_Right;

	};
}




