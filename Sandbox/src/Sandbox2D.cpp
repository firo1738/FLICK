#include "Sandbox2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{}

void Sandbox2D::OnAttach()
{
	FI_PROFILE_FUNCTION();

	m_Tex_Checkerbox = Flick::Texture2D::Create("assets/textures/tex-checkerbox.png");

	//TODO::add particle system to flick editor 
	m_Particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 1.0f;
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 3.0f, 1.0f };
	m_Particle.Position = { 0.0f, 0.0f };

	m_CameraController.SetZoomLevel(10.0f);
}

void Sandbox2D::OnDetach()
{
	FI_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Flick::Timestep ts)
{
	FI_PROFILE_FUNCTION();

	//update
		m_CameraController.OnUpdate(ts);

	//render
	Flick::Renderer2D::ResetStats();
	{
		FI_PROFILE_SCOPE("Renderer::Prep");
		Flick::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Flick::RenderCommand::Clear();
	}

	{
		static float rotation = 0.0f;
		rotation += ts * -50.0f;

		FI_PROFILE_SCOPE("Renderer::Draw");
		Flick::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Flick::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f), { 0.8f, 0.2f, 0.3f, 1.0f });
		Flick::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Flick::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });

		Flick::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_Tex_Checkerbox, 10.0f);
		

		Flick::Renderer2D::EndScene();

		Flick::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = {(x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f};
				Flick::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		Flick::Renderer2D::EndScene();
	}

	if(Flick::Input::IsMouseButtonPressed(FI_BUTTON_L)) //TODO:change to mouse button left
	{
		auto [x, y] = Flick::Input::GetMousePosition();
		auto width = Flick::Application::Get().GetWindow().GetWidth();
		auto height = Flick::Application::Get().GetWindow().GetHeight();

		auto bounds = m_CameraController.GetBounds();
		auto pos = m_CameraController.GetCamera().GetPosition();
		x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
		y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
		m_Particle.Position = { x + pos.x, y + pos.y };
		for (int i = 0; i < 5; i++)
			m_ParticleSystem.Emit(m_Particle);
	}

	m_ParticleSystem.OnUpdate(ts);
	m_ParticleSystem.OnRender(m_CameraController.GetCamera());

}

void Sandbox2D::OnImGuiRender()
{
	FI_PROFILE_FUNCTION();
	
	{
		ImGui::Begin("Sandbox2D");

		auto stats = Flick::Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quad Count: %d", stats.QuadCount);
		ImGui::Text("Vertex Count: %d", stats.GetTotalVertexCount());
		ImGui::Text("Index Count: %d", stats.GetTotalIndexCount());

		ImGui::End();
	}
}

void Sandbox2D::OnEvent(Flick::Event& e)
{
	m_CameraController.OnEvent(e);
}