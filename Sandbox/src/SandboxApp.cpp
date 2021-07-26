#include <Flick.h>

#include "imgui/imgui.h"

class ExampleLayer : public Flick::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CamPosition(0.0f)
	{
		m_VA.reset(Flick::VertexArray::Create());

		float verticies[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Flick::VertexBuffer> vb;
		vb.reset(Flick::VertexBuffer::Create(verticies, sizeof(verticies)));

		Flick::BufferLayout layout = {
			{Flick::ShaderDataType::Float3, "a_Position"},
			{Flick::ShaderDataType::Float4, "a_Color"}
		};

		vb->SetLayout(layout);
		m_VA->AddVertexBuffer(vb);

		uint32_t indicies[3] = { 0, 1, 2 };
		std::shared_ptr<Flick::IndexBuffer> ib;
		ib.reset(Flick::IndexBuffer::Create(indicies, sizeof(indicies) / sizeof(uint32_t)));
		m_VA->SetIndexBuffer(ib);

		m_SqVA.reset(Flick::VertexArray::Create());

		float sqverticies[4 * 3] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<Flick::VertexBuffer> sqvb;
		sqvb.reset(Flick::VertexBuffer::Create(sqverticies, sizeof(sqverticies)));

		sqvb->SetLayout({ { Flick::ShaderDataType::Float3, "a_Position" } });
		m_SqVA->AddVertexBuffer(sqvb);

		uint32_t sqindicies[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Flick::IndexBuffer> sqib;
		sqib.reset(Flick::IndexBuffer::Create(sqindicies, sizeof(sqindicies) / sizeof(uint32_t)));
		m_SqVA->SetIndexBuffer(sqib);

		std::string vertexsrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentsrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Flick::Shader(vertexsrc, fragmentsrc));

		std::string sqvertexsrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			
			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string sqfragmentsrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;

			void main()
			{
				color = vec4(1.0, 1.0, 1.0, 1.0);
			}
		)";

		m_WhiteShader.reset(new Flick::Shader(sqvertexsrc, sqfragmentsrc));
	}

	void OnUpdate() override
	{
		if (Flick::Input::IsKeyPressed(FI_KEY_UP))
			m_CamPosition.y -= m_CamMoveSpeed;
		else if (Flick::Input::IsKeyPressed(FI_KEY_DOWN))
			m_CamPosition.y += m_CamMoveSpeed;

		if (Flick::Input::IsKeyPressed(FI_KEY_LEFT))
			m_CamPosition.x += m_CamMoveSpeed;
		else if (Flick::Input::IsKeyPressed(FI_KEY_RIGHT))
			m_CamPosition.x -= m_CamMoveSpeed;

		if (Flick::Input::IsKeyPressed(FI_KEY_A))
			m_CamRotation -= m_CamRotationSpeed;
		else if (Flick::Input::IsKeyPressed(FI_KEY_D))
			m_CamRotation += m_CamRotationSpeed;

		Flick::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Flick::RenderCommand::Clear();

		m_Camera.SetPosition(m_CamPosition);
		m_Camera.SetRotation(m_CamRotation);

		Flick::Renderer::BeginScene(m_Camera);

		Flick::Renderer::Submit(m_WhiteShader, m_SqVA);
		Flick::Renderer::Submit(m_Shader, m_VA);

		Flick::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		
	}

	void OnEvent(Flick::Event& event) override
	{

	}
private:
	std::shared_ptr<Flick::Shader> m_Shader;
	std::shared_ptr<Flick::VertexArray> m_VA;

	std::shared_ptr<Flick::Shader> m_WhiteShader;
	std::shared_ptr<Flick::VertexArray> m_SqVA;

	Flick::OrthographicCamera m_Camera;

	glm::vec3 m_CamPosition;
	float m_CamMoveSpeed = 0.05f;

	float m_CamRotation = 0.0f;
	float m_CamRotationSpeed = 1.0f;
};


class Sandbox : public Flick::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Flick::Application* Flick::CreateApplication()
{
	return new Sandbox();
}