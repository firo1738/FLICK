#pragma once

#include <Flick.h>

#include "Panels/SceneHierarchyPanel.h"
#include "Panels/Panel.h"

#include "Flick/Renderer/EditorCamera.h"

namespace Flick {
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& event) override;
	private:
		bool OnKeyPressed(KeyPressedEvent& e);

		void NewScene();
		void OpenScene();
		void SaveCurrentScene();
		void SaveSceneAs();
	private:
		Flick::OrthographicCameraController m_CameraController;

		Ref<Scene> m_ActiveScene;
		Entity m_SquareEntity;
		Entity m_CameraEntity;
		Entity m_SecondCamera;

		bool m_PrimaryCamera = true;

		//Temp
		Ref<Texture2D> m_Tex_Checkerbox;
		Ref<Texture2D> m_Tex_Bird;
		Ref<Texture2D> m_Tile_Map;
		Ref<Texture2D> m_Sq;
		Ref<SubTexture2D> m_Tile_Door;
		Ref<SubTexture2D> m_Tile_Roof;
		Ref<SubTexture2D> m_Sq_Panda;

		int m_MapWidth, m_MapHeight;
		std::unordered_map<char, Ref<SubTexture2D>> m_TileMap;

		bool m_ViewportFocus = false;
		bool m_ViewportHover = false;
		glm::vec2 m_Viewport;

		Ref<FrameBuffer> m_FrameBuffer;

		EditorCamera m_EditorCamera;

		//panels
		Panel m_NewPanel;
		SceneHierarchyPanel m_SceneHierarchyPanel;

		int m_GizmoType = -1;

		//scene filepath
		std::string m_Filepath;
	};
}