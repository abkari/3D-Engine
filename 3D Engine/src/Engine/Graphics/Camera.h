#pragma once


#include "../Event/Input.h"
#include "../Math/Glm.h"
#include <cmath>

namespace Engine
{
	namespace Graphics
	{

		using namespace Event;
		using namespace Math;

		class Camera
		{
		public:
			
			Camera();

			void SetParameters(const float& fov, const float& asrectRatio, const float& near, const float& far);
			void SetFov(const float& fov);
			void SetNear(const float& near);
			void SetFar(const float& far);

			void Update(const float& deltaTime, const float& aspectRatio);

			inline Mat4 GetViewMatrix() const { return view; }
			inline Mat4 GetProjMatrix() const { return projection; }

		private:
			Vector3 camPos;
			Vector3 camFront;
			Vector3 camRight;
			Vector3 camUp;

			Mat4 view;
			Mat4 projection;

			float m_Fov = 60.0f;
			float m_Near = 0.1f;
			float m_Far = 100.0f;

			float speed = 2.5f;
			float sensitivity = 0.1f;

			
			float pitch = 0.0f;
			float yaw = -90.0f;
			float lastX, lastY;
			bool firstEnter = true;

			void TransformCalc();
			void HandleMovement(const float& deltaTime);
		};
	}
}


