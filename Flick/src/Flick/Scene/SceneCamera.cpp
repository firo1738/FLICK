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
		m_ProjectionType = ProjectionType::Orthographic;
		m_OrthographicSize = size;
		m_OrthographicNear = nearclip;
		m_OrthographicFar = farclip;

		RecalculateProjection();
	}

	void SceneCamera::SetPerspective(float fov, float nearclip, float farclip)
	{
		m_ProjectionType = ProjectionType::Perspective;
		m_PerspectiveFov = fov;
		m_PerspectiveNear = nearclip;
		m_PerspectiveFar = farclip;

		RecalculateProjection();
	}

	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		m_AspectRatio = (float)width / (float)height;

		RecalculateProjection();
	}

	void SceneCamera::RecalculateProjection()
	{
		if (m_ProjectionType == ProjectionType::Perspective)
		{
			m_Projection = glm::perspective(m_PerspectiveFov, m_AspectRatio, m_PerspectiveNear, m_PerspectiveFar);
		}
		else
		{
			double orthoLeft = -m_OrthographicSize * m_AspectRatio * 0.5;
			double orthoRight = m_OrthographicSize * m_AspectRatio * 0.5;
			double orthoBottom = -m_OrthographicSize * 0.5;
			double orthoTop = m_OrthographicSize * 0.5;

			m_Projection = glm::ortho((float)orthoLeft, (float)orthoRight, (float)orthoBottom, (float)orthoTop, m_OrthographicNear, m_OrthographicFar);
		}
	}

}