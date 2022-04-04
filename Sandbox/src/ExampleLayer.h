#pragma once

#include "Flick.h"

class ExampleLayer : public Flick::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Flick::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Flick::Event& e) override;
private:
	Flick::ShaderLibrary m_ShaderLibrary;
	Flick::Ref<Flick::Shader> m_TriangleShader;
	Flick::Ref<Flick::VertexArray> m_VA;

	Flick::Ref<Flick::Shader> m_FlatColorShader;
	Flick::Ref<Flick::VertexArray> m_SqVA;

	Flick::Ref<Flick::Texture2D> m_Texture1, m_Texture2;

	Flick::OrthographicCameraController m_CameraController;
	glm::vec3 m_SqColor = {0.2f, 0.3f, 0.8f};
};