#pragma once

#include <Flick.h>

#include "ParticleSystem.h"

class Sandbox2D : public Flick::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Flick::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Flick::Event& event) override;
private:
	Flick::OrthographicCameraController m_CameraController;

	//Temp
	Flick::Ref<Flick::Texture2D> m_Tex_Checkerbox;
	Flick::Ref<Flick::Texture2D> m_Tex_Bird;
	Flick::Ref<Flick::Texture2D> m_Tile_Map;
	Flick::Ref<Flick::Texture2D> m_Sq;
	Flick::Ref<Flick::SubTexture2D> m_Tile_Door;
	Flick::Ref<Flick::SubTexture2D> m_Tile_Roof;
	Flick::Ref<Flick::SubTexture2D> m_Sq_Panda;

	int m_MapWidth, m_MapHeight;
	std::unordered_map<char, Flick::Ref<Flick::SubTexture2D>> m_TileMap;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

	ParticleSystem m_ParticleSystem;
	ParticleProps m_Particle;
};