#include "EditorLayer.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

#include "Flick/Scene/SceneSerializer.h"
#include "Flick/Utils/PlatformUtils.h"

//const int s_MapWidth = 24;
//static const char* s_TileMap = 
//"LUUUUUUUUUUUUUUUUUUUUUUR"
//"lDDDDDDDDDDDDDDDDDDDDDDr"
//"lDDCCDDDDDDDDDDDDDDDDDDr"
//"lDDDDDDDDDDDDDDDDDDCCDDr"
//"lDDDDDDDDDDCDDDDDDDDDDDr"
//"lDDDDDDDDDDDDDDDDDDDDDDr"
//"lDDDDDDDCDDDDDDDDCDDDDDr"
//"lDDDDDDDDDDDDDDDDDDDCCDr"
//"lDDDDDDDDDDDDDDDDDDDDDDr"
//"lDDDDDDDDDDCCDDDDDDDDDDr"
//"lDDCDDDDDDDDDDDDDDDDDDDr"
//"TBBBBBBBBBBBBBBBBBBBBBBY";
//

namespace Flick {
	EditorLayer::EditorLayer()
		:Layer("EditorLayer"), m_CameraController(1280.0f / 720.0f, true)
	{}

	void EditorLayer::OnAttach()
	{
		FI_PROFILE_FUNCTION();

		m_Tex_Checkerbox = Texture2D::Create("assets/textures/tex-checkerbox.png");
		//m_Tex_Bird = Texture2D::Create("assets/textures/tex-bird.png");
		//m_Tile_Map = Texture2D::Create("assets/game/textures/tilemap.png");
		m_Sq = Texture2D::Create("assets/game/textures/square_nodetails.png");
		//m_Tile_Door = SubTexture2D::createFromCoords(m_Tile_Map, { 7, 1 }, { 16.875, 16.875 });
		//m_Tile_Roof = SubTexture2D::createFromCoords(m_Tile_Map, { 10, 3 }, { 16.95, 16.875 }, { 1, 2 });
		m_Sq_Panda = SubTexture2D::createFromCoords(m_Sq, { 1, 1 }, { 128.2, 128 });

		//tilemap
		//m_MapWidth = s_MapWidth;
		//m_MapHeight = strlen(s_TileMap) / s_MapWidth;
		//
		//m_TileMap['L'] = SubTexture2D::createFromCoords(m_Tile_Map, { 7, 7 }, { 16.875, 16.875 });
		//m_TileMap['U'] = SubTexture2D::createFromCoords(m_Tile_Map, { 8, 7 }, { 16.875, 16.875 });
		//m_TileMap['R'] = SubTexture2D::createFromCoords(m_Tile_Map, { 9, 7 }, { 16.875, 16.875 });
		//m_TileMap['D'] = SubTexture2D::createFromCoords(m_Tile_Map, { 8, 6 }, { 16.875, 16.875 });
		//m_TileMap['C'] = SubTexture2D::createFromCoords(m_Tile_Map, { 13, 4 }, { 16.9, 16.875 });
		//m_TileMap['T'] = SubTexture2D::createFromCoords(m_Tile_Map, { 7, 5 }, { 16.875, 16.875 });
		//m_TileMap['B'] = SubTexture2D::createFromCoords(m_Tile_Map, { 8, 5 }, { 16.875, 16.875 });
		//m_TileMap['Y'] = SubTexture2D::createFromCoords(m_Tile_Map, { 9, 5 }, { 16.875, 16.875 });
		//m_TileMap['l'] = SubTexture2D::createFromCoords(m_Tile_Map, { 7, 6 }, { 16.875, 16.875 });
		//m_TileMap['r'] = SubTexture2D::createFromCoords(m_Tile_Map, { 9, 6 }, { 16.875, 16.875 });

		Flick::FrameBufferSpecifications fbspec;
		fbspec.Width = 1280;
		fbspec.Height = 720;
		m_FrameBuffer = Flick::FrameBuffer::create(fbspec);

		m_CameraController.SetZoomLevel(1.0f);

		m_ActiveScene = CreateRef<Scene>();
#if 0

		//Entity
		auto square = m_ActiveScene->CreateEntity("Red Square");
		square.AddComponent<SpriteRendererComponent>(glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });

		auto greenSquare = m_ActiveScene->CreateEntity("Green Square");
		greenSquare.AddComponent<SpriteRendererComponent>(glm::vec4{ 0.0f, 1.0f, 0.0f, 1.0f });

		m_SquareEntity = square;

		m_CameraEntity = m_ActiveScene->CreateEntity("Camera A");
		m_CameraEntity.AddComponent<CameraComponent>();

		m_SecondCamera = m_ActiveScene->CreateEntity("Camera B");
		auto& cc = m_SecondCamera.AddComponent<CameraComponent>();
		cc.Primary = false;

		class CameraController : public ScriptableEntity 
		{
		public:
			void OnCreate()
			{
				auto& translation = GetComponent<TransformComponent>().Translation;
				translation.x = rand() % 10 - 5.0f;
			}

			void OnDestroy()
			{
			}

			void OnUpdate(Timestep ts) {
				auto& translation = GetComponent<TransformComponent>().Translation;
				float speed = 5.0f;

				if (Input::IsKeyPressed(KeyCode::A))
					translation.x -= speed * ts;
				if (Input::IsKeyPressed(KeyCode::D))
					translation.x += speed * ts;
				if (Input::IsKeyPressed(KeyCode::W))
					translation.y += speed * ts;
				if (Input::IsKeyPressed(KeyCode::S))
					translation.y -= speed * ts;
			}
		};

		m_CameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();//bind intanciates all the fns for the cameracontroller class, that is create as a native script.
		m_SecondCamera.AddComponent<NativeScriptComponent>().Bind<CameraController>();
#endif
		m_SceneHierarchyPanel.SetContext(m_ActiveScene);
		//TODO: Give the abilites to create properties on new panels
		//m_NewPanel.SetContext(m_ActiveScene);
	}

	void EditorLayer::OnDetach()
	{
		FI_PROFILE_FUNCTION();
	}

	void EditorLayer::OnUpdate(Timestep ts)
	{
		FI_PROFILE_FUNCTION();

		//Resize
		if (FrameBufferSpecifications spec = m_FrameBuffer->getSpecifications();
			m_Viewport.x > 0.0f && m_Viewport.y > 0.0f && //frame buffer with size 0 invalid
			(spec.Width != m_Viewport.x || spec.Height != m_Viewport.y)) 
		{
			m_FrameBuffer->Resize((uint32_t)m_Viewport.x, (uint32_t)m_Viewport.y);
			m_CameraController.OnResize(m_Viewport.x, m_Viewport.y);
		
			m_ActiveScene->OnViewportResize((uint32_t)m_Viewport.x, (uint32_t)m_Viewport.y);
		}

		//update
		if (m_ViewportFocus)
			m_CameraController.OnUpdate(ts);

		//render
		Renderer2D::ResetStats();
		m_FrameBuffer->bind();
		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RenderCommand::Clear();

		//Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.5f }, { 1.0f, 1.0f }, m_Tile_Door);
		//Renderer2D::DrawQuad({ 1.0f, 0.0f, 0.5f }, { 1.0f, 2.0f }, m_Tile_Roof);
		//
		//Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f, 0.5f }, { 10.0f, 10.0f }, glm::radians(-45.0f), { 0.8f, 0.2f, 0.3f, 1.0f });
		//Renderer2D::DrawQuad({ -10.0f, -0.5f, 0.5f }, { 10.0f, 10.0f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		//
		////Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.5f }, { 10.0f, 10.0f }, m_Sq_Panda);
		//Renderer2D::DrawQuad({ 12.0f, 0.0f, 0.5f }, { 10.0f, 10.0f }, m_Tex_Checkerbox);
		//
		//tilemap
		//for (uint32_t y = 0; y < m_MapHeight; y++) {
		//	for (uint32_t x = 0; x < m_MapWidth; x++)
		//	{
		//		char tiletype = s_TileMap[x + y * m_MapWidth];
		//		Ref<SubTexture2D> texture;
		//		if (m_TileMap.find(tiletype) != m_TileMap.end()) {
		//			texture = m_TileMap[tiletype];
		//		}
		//		else
		//		{
		//			texture = m_Sq_Panda;
		//		}
		//
		//		Renderer2D::DrawQuad({ x - m_MapWidth / 2.0f, m_MapHeight - y - m_MapHeight / 2.0f, 0.5f }, { 1.0f, 1.0f },
		//			texture);
		//	}
		//}

		//update scene
		m_ActiveScene->OnUpdate(ts);

		m_FrameBuffer->unBind();
	}

	void EditorLayer::OnImGuiRender()
	{
		FI_PROFILE_FUNCTION();

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
			ImGuiStyle& style = ImGui::GetStyle();
			float minWinSize = style.WindowMinSize.x;
			style.WindowMinSize.x = 420.0f;
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			}
			style.WindowMinSize.x = minWinSize;

			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					if (ImGui::MenuItem("New", "Ctrl+N"))
					{
						NewScene();
					}

					ImGui::Separator();

					if (ImGui::MenuItem("Open...", "Ctrl+O"))
					{
						OpenScene();
					}

					ImGui::Separator();

					if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
					{
						SaveSceneAs();
					}

					ImGui::Separator();

					if (ImGui::MenuItem("Exit")) Application::Get().Close();

					ImGui::EndMenu();
				}

				ImGui::EndMenuBar();
			}

			//panels
			//m_NewPanel.CreatePanel("New Panel");
			m_SceneHierarchyPanel.OnImGuiRender();

			ImGui::Begin("Stats");

			auto stats = Renderer2D::GetStats();
			ImGui::Text("Renderer2D Stats:");
			ImGui::Text("Draw Calls: %d", stats.DrawCalls);
			ImGui::Text("Quad Count: %d", stats.QuadCount);
			ImGui::Text("Vertex Count: %d", stats.GetTotalVertexCount());
			ImGui::Text("Index Count: %d", stats.GetTotalIndexCount());

			ImGui::End();

			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
			ImGui::Begin("Viewport");

			m_ViewportFocus = ImGui::IsWindowFocused();
			m_ViewportHover = ImGui::IsWindowHovered();
			Application::Get().GetImguiLayer()->BlockEvents(!m_ViewportFocus || !m_ViewportHover);

			ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
			m_Viewport = {viewportPanelSize.x, viewportPanelSize.y};
			uint32_t textureID = m_FrameBuffer->getColorAttachmentRendererID();
			ImGui::Image((void*)textureID, ImVec2{ m_Viewport.x, m_Viewport.y }, { 0, 1 }, { 1, 0 });

			ImGui::End();
			ImGui::PopStyleVar();

			//dockspace end()
			ImGui::End();
	}

	void EditorLayer::OnEvent(Event& e)
	{
		m_CameraController.OnEvent(e);

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(FI_BIND_EVENT_FN(EditorLayer::OnKeyPressed));
	}

	bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
	{
		//file shotcuts
		if (e.GetRepeatCount() > 0)
			return false;

		bool control = Input::IsKeyPressed(FI_KEY_LEFT_CONTROL) || Input::IsKeyPressed(FI_KEY_RIGHT_CONTROL);
		bool shift = Input::IsKeyPressed(FI_KEY_LEFT_SHIFT) || Input::IsKeyPressed(FI_KEY_RIGHT_SHIFT);

		switch (e.GetKeyCode())
		{
		case FI_KEY_N:
		{
			NewScene();
			break;
		}
		case FI_KEY_O:
		{
			if (control)
				OpenScene();
			break;
		}
		case FI_KEY_S:
		{
			if (control && shift)
				SaveSceneAs();
			break;
		}
		}
	}
	void EditorLayer::NewScene()
	{
		m_ActiveScene = CreateRef<Scene>();
		m_ActiveScene->OnViewportResize((uint32_t)m_Viewport.x, (uint32_t)m_Viewport.y);
		m_SceneHierarchyPanel.SetContext(m_ActiveScene);
	}

	void EditorLayer::OpenScene()
	{
		std::string filepath = FileDialogs::OpenFile("Flick Scene(*.flick)\0 * .flick\0");
		if (!filepath.empty())
		{
			m_ActiveScene = CreateRef<Scene>();
			m_ActiveScene->OnViewportResize((uint32_t)m_Viewport.x, (uint32_t)m_Viewport.y);
			m_SceneHierarchyPanel.SetContext(m_ActiveScene);

			SceneSerializer Serializer(m_ActiveScene);
			Serializer.DeSerialize(filepath);
		}
	}

	void EditorLayer::SaveSceneAs()
	{
		std::string filepath = FileDialogs::SaveFile("Flick Scene(*.flick)\0 * .flick\0");
		if (!filepath.empty())
		{
			SceneSerializer Serializer(m_ActiveScene);
			Serializer.Serialize(filepath);
		}
	}
}