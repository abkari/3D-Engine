#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

namespace Components
{
	Matrix4f Camera::GetProjectionMatrix(const float& screen_width, const float& screen_height)
	{
		return ((m_CameraType == Perspective) ?
			glm::perspective(glm::radians(PersCamData.Fov), screen_width / screen_height, PersCamData.Near, PersCamData.Far) :
			glm::ortho(0.0f, screen_width, screen_height, 0.0f, OrthoCamData.Near, OrthoCamData.Far));
	}
	
}
