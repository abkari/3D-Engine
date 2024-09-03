#pragma once

#include "Transform.h"
#include "Math/Matrices.h"

namespace Components
{
	enum CameraType
	{
		Perspective,
		Orthographic
	};

	class Camera : public Transform
	{
	public:
		Camera() : m_CameraType(Perspective) {}

		inline const float& GetFiledOfView() const { return PersCamData.Fov; }
		inline const float& GetNear() const 
		{
			if (m_CameraType == Perspective)
				return PersCamData.Near;
			else return OrthoCamData.Near;
		}
		inline const float& GetFar() const 
		{ 
			if (m_CameraType == Perspective)
				return PersCamData.Far;
			else return OrthoCamData.Far;
		}

		inline void SetFiledOfView(const float& fov) { PersCamData.Fov = fov; }
		inline void SetNear(const float& near) 
		{
			if (m_CameraType == Perspective)
				PersCamData.Near = near;
			else OrthoCamData.Near = near;
		}
		inline void SetFar(const float& far) 
		{
			if (m_CameraType == Perspective)
				PersCamData.Far = far;
			else OrthoCamData.Far = far;
		}
		inline void SetCameraType(CameraType camera_type) { m_CameraType = camera_type; }

		Matrix4f GetProjectionMatrix(const float& screen_width, const float& screen_height);

	private:
		CameraType m_CameraType;

		struct
		{
			float Fov = 70.0f;
			float Near = 0.1f;
			float Far = 100.0f;

		} PersCamData;

		struct
		{
			float Near = 0.0f;
			float Far = 100.0f;

		} OrthoCamData;
	};
}


