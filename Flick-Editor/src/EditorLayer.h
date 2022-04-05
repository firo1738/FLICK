#pragma once

#include <Flick.h>

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
		Flick::OrthographicCameraController m_CameraController;

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

		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

		glm::vec2 m_viewport;

		Ref<FrameBuffer> m_FrameBuffer;
	};
}