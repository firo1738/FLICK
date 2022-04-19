#pragma once

#include "Flick/Renderer/Camera.h"

namespace Flick {
	class SceneCamera : public Camera
	{
	public:
		enum class ProjectionType { Perspective = 0, Orthographic = 1 };
	public:
		SceneCamera();

		virtual ~SceneCamera() = default;

		void SetOrthographic(float size, float nearclip, float farclip);

		void SetPerspective(float fov, float nearclip, float farclip);

		void SetViewportSize(uint32_t width, uint32_t height);

		float GetPerspectiveVerticalFov() const { return m_PerspectiveFov; }
		void SetPerspectiveVerticalFov(float verticalfov) { m_PerspectiveFov = verticalfov; RecalculateProjection(); }
		float GetPerspectiveNearClip() const { return m_PerspectiveNear; }
		void SetPerspectiveNearClip(float nearclip) { m_PerspectiveNear = nearclip; RecalculateProjection(); }
		float GetPerspectiveFarClip() const { return m_PerspectiveFar; }
		void SetPerspectiveFarClip(float farclip) { m_PerspectiveFar = farclip; RecalculateProjection(); }

		float GetOrthographicSize() const { return m_OrthographicSize; }
		void SetOrthographicSize(float size) { m_OrthographicSize = size; RecalculateProjection(); }
		float GetOrthoNearClip() const { return m_OrthographicNear; }
		void SetOrthoNearClip(float nearclip) { m_OrthographicNear = nearclip; RecalculateProjection();}
		float GetOrthoFarClip() const { return m_OrthographicFar; }
		void SetOrthoFarClip(float farclip) { m_OrthographicFar = farclip; RecalculateProjection();}

		ProjectionType GetProjectionType() const { return m_ProjectionType;}

		void SetProjectionType(ProjectionType proj) { m_ProjectionType = proj; RecalculateProjection();}
	private:
		void RecalculateProjection();
	private:
		ProjectionType m_ProjectionType = ProjectionType::Orthographic;

		float m_PerspectiveFov = glm::radians(45.0f);
		float m_PerspectiveNear = 0.01f, m_PerspectiveFar = 1000.0f;

		float m_OrthographicSize = 10.0f;
		float m_OrthographicNear = -1.0f, m_OrthographicFar = 1.0f;

		float m_AspectRatio = 0.0f;
	};
}