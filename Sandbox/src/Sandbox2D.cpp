#include "Sandbox2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

const int s_MapWidth = 24;
static const char* s_TileMap = 
"LUUUUUUUUUUUUUUUUUUUUUUR"
"lDDDDDDDDDDDDDDDDDDDDDDr"
"lDDCCDDDDDDDDDDDDDDDDDDr"
"lDDDDDDDDDDDDDDDDDDCCDDr"
"lDDDDDDDDDDCDDDDDDDDDDDr"
"lDDDDDDDDDDDDDDDDDDDDDDr"
"lDDDDDDDCDDDDDDDDCDDDDDr"
"lDDDDDDDDDDDDDDDDDDDCCDr"
"lDDDDDDDDDDDDDDDDDDDDDDr"
"lDDDDDDDDDDCCDDDDDDDDDDr"
"lDDCDDDDDDDDDDDDDDDDDDDr"
"TBBBBBBBBBBBBBBBBBBBBBBY";

float rotation;

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{}

void Sandbox2D::OnAttach()
{
	FI_PROFILE_FUNCTION();

	m_Tex_Checkerbox= Flick::Texture2D::Create("assets/textures/tex-checkerbox.png");
	m_Tex_Bird = Flick::Texture2D::Create("assets/textures/tex-bird.png");
	m_Tile_Map = Flick::Texture2D::Create("assets/game/textures/tilemap.png");
	m_Sq = Flick::Texture2D::Create("assets/game/textures/square_nodetails.png");
	m_Tile_Door = Flick::SubTexture2D::createFromCoords(m_Tile_Map, { 7, 1 }, {16.875, 16.875});
	m_Tile_Roof = Flick::SubTexture2D::createFromCoords(m_Tile_Map, { 10, 3 }, { 16.95, 16.875 }, {1, 2});
	m_Sq_Panda = Flick::SubTexture2D::createFromCoords(m_Sq, { 1, 1 }, { 128.2, 128 });

	//tilemap
	m_MapWidth = s_MapWidth;
	m_MapHeight = strlen(s_TileMap) / s_MapWidth;

	m_TileMap['L'] = Flick::SubTexture2D::createFromCoords(m_Tile_Map, { 7, 7 }, { 16.875, 16.875 });
	m_TileMap['U'] = Flick::SubTexture2D::createFromCoords(m_Tile_Map, { 8, 7 }, { 16.875, 16.875 });
	m_TileMap['R'] = Flick::SubTexture2D::createFromCoords(m_Tile_Map, { 9, 7 }, { 16.875, 16.875 });
	m_TileMap['D'] = Flick::SubTexture2D::createFromCoords(m_Tile_Map, { 8, 6 }, { 16.875, 16.875 });
	m_TileMap['C'] = Flick::SubTexture2D::createFromCoords(m_Tile_Map, { 13, 4 }, { 16.9, 16.875 });
	m_TileMap['T'] = Flick::SubTexture2D::createFromCoords(m_Tile_Map, { 7, 5 }, { 16.875, 16.875 });
	m_TileMap['B'] = Flick::SubTexture2D::createFromCoords(m_Tile_Map, { 8, 5 }, { 16.875, 16.875 });
	m_TileMap['Y'] = Flick::SubTexture2D::createFromCoords(m_Tile_Map, { 9, 5 }, { 16.875, 16.875 });
	m_TileMap['l'] = Flick::SubTexture2D::createFromCoords(m_Tile_Map, { 7, 6 }, { 16.875, 16.875 });
	m_TileMap['r'] = Flick::SubTexture2D::createFromCoords(m_Tile_Map, { 9, 6 }, { 16.875, 16.875 });
	
	Flick::FrameBufferSpecifications fbspec;
	fbspec.Width = 1280;
	fbspec.Height = 720;
	m_FrameBuffer = Flick::FrameBuffer::create(fbspec);

	//Particle attached by particleprops
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
		m_FrameBuffer->bind();
		Flick::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Flick::RenderCommand::Clear();
	}

#if 0
	{
		static float rotation = 0.0f;
		rotation += ts * -50.0f;

		FI_PROFILE_SCOPE("Renderer::Draw");
		Flick::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Flick::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f), { 0.8f, 0.2f, 0.3f, 1.0f });
		Flick::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Flick::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });

		Flick::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_Tex_Checkerbox, 10.0f);
		
		Flick::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, glm::radians(rotation), m_Tex_Bird, 20.0f);

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
#endif

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

	Flick::Renderer2D::BeginScene(m_CameraController.GetCamera());
	//Flick::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.5f }, { 1.0f, 1.0f }, m_Tile_Door);
	//Flick::Renderer2D::DrawQuad({ 1.0f, 0.0f, 0.5f }, { 1.0f, 2.0f }, m_Tile_Roof);
	//Flick::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.5f }, { 10.0f, 10.0f }, m_Sq_Panda);

	//tilemap
	for (uint32_t y = 0; y < m_MapHeight; y++) {
		for (uint32_t x = 0; x < m_MapWidth; x++)
		{
			char tiletype = s_TileMap[x + y * m_MapWidth];
			Flick::Ref<Flick::SubTexture2D> texture;
			if (m_TileMap.find(tiletype) != m_TileMap.end()) {
				texture = m_TileMap[tiletype];
			}
			else
			{
				texture = m_Sq_Panda;
			}
	
			Flick::Renderer2D::DrawQuad({ x - m_MapWidth / 2.0f, m_MapHeight - y - m_MapHeight / 2.0f, 0.5f }, { 1.0f, 1.0f },
			texture);
		}
	}

	Flick::Renderer2D::EndScene();
	m_FrameBuffer->unBind();
}

void Sandbox2D::OnImGuiRender()
{
	FI_PROFILE_FUNCTION();
	
	static bool dockspaceEnable = true;
	if (dockspaceEnable) {
		bool dockspaceOpen = true;
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->GetWorkPos());
			ImGui::SetNextWindowSize(viewport->GetWorkSize());
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit")) Flick::Application::Get().Close();

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::Begin("Settings");

		auto stats = Flick::Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quad Count: %d", stats.QuadCount);
		ImGui::Text("Vertex Count: %d", stats.GetTotalVertexCount());
		ImGui::Text("Index Count: %d", stats.GetTotalIndexCount());

		m_CameraController.setRotation(rotation);

		ImGui::SliderAngle("rotation", &rotation);

		uint32_t textureID = m_FrameBuffer->getColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ 1280, 720 }, { 1, 1 }, { 0, 0 });

		ImGui::End();
		
		//dockspace end()
		ImGui::End();
	}
	else
	{
		ImGui::Begin("Sandbox2D");

		auto stats = Flick::Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quad Count: %d", stats.QuadCount);
		ImGui::Text("Vertex Count: %d", stats.GetTotalVertexCount());
		ImGui::Text("Index Count: %d", stats.GetTotalIndexCount());

		uint32_t textureID = m_Tex_Bird->getRendererID();
		ImGui::Image((void*)textureID, ImVec2{ 1280, 720 }, { 1, 1 }, {0, 0});

		ImGui::End();
	}
}

void Sandbox2D::OnEvent(Flick::Event& e)
{
	m_CameraController.OnEvent(e);
}