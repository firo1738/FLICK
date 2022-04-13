#include "fipch.h"
#include "SceneCamera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Flick {

	SceneCamera::SceneCamera()
	{
		RecalculateProjection();
	}

	void SceneCamera::SetOrthographic(float size, float nearclip, float farclip)
	{
		m_OrthographicSize = size;
		m_OrthographicNear = nearclip;
		m_OrthographicFar = farclip;

		RecalculateProjection();
	}

	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		m_AspectRatio = (float)width / (float)height;

		RecalculateProjection();
	}

	void SceneCamera::RecalculateProjection()
	{
		float orthoLeft = -m_OrthographicSize * m_AspectRatio * 0.5;
		float orthoRight = m_OrthographicSize * m_AspectRatio * 0.5;
		float orthoBottom = -m_OrthographicSize * 0.5;
		float orthoTop = m_OrthographicSize * 0.5;

		m_Projection = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, m_OrthographicNear, m_OrthographicFar);
	}

}