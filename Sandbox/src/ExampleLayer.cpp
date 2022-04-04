#include "ExampleLayer.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ExampleLayer::ExampleLayer()
	:Layer("ExampleLayer"), m_CameraController(1280.0f / 720.0f)
{
	m_VA = Flick::VertexArray::Create();

	float verticies[3 * 7] = {
		-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
		 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
	};

	Flick::Ref<Flick::VertexBuffer> vb = Flick::VertexBuffer::Create(verticies, sizeof(verticies));

	Flick::BufferLayout layout = {
		{Flick::ShaderDataType::Float3, "a_Position"},
		{Flick::ShaderDataType::Float4, "a_Color"}
	};

	vb->SetLayout(layout);
	m_VA->AddVertexBuffer(vb);

	uint32_t indicies[3] = { 0, 1, 2 };
	Flick::Ref<Flick::IndexBuffer> ib = Flick::IndexBuffer::Create(indicies, sizeof(indicies) / sizeof(uint32_t));
	m_VA->SetIndexBuffer(ib);

	m_SqVA = Flick::VertexArray::Create();

	float sqverticies[4 * 5] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};

	Flick::Ref<Flick::VertexBuffer> sqvb = Flick::VertexBuffer::Create(sqverticies, sizeof(sqverticies));

	sqvb->SetLayout({
		{ Flick::ShaderDataType::Float3, "a_Position" },
		{ Flick::ShaderDataType::Float2, "a_TexCoord" }
		});
	m_SqVA->AddVertexBuffer(sqvb);

	uint32_t sqindicies[6] = { 0, 1, 2, 2, 3, 0 };
	Flick::Ref<Flick::IndexBuffer> sqib = Flick::IndexBuffer::Create(sqindicies, sizeof(sqindicies) / sizeof(uint32_t));
	m_SqVA->SetIndexBuffer(sqib);

	std::string vertexsrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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

	m_TriangleShader = Flick::Shader::Create("VertexPosColor", vertexsrc, fragmentsrc);

	std::string flatcolorvertexsrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

	std::string flatcolorfragmentsrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

	m_FlatColorShader = Flick::Shader::Create("FlatColor", flatcolorvertexsrc, flatcolorfragmentsrc);

	auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

	m_Texture1 = Flick::Texture2D::Create("assets/textures/texture1.png");
	m_Texture2 = Flick::Texture2D::Create("assets/textures/texture2.png");

	textureShader->Bind();
	textureShader->SetInt("u_Texture", 0);
}

void ExampleLayer::OnAttach()
{}

void ExampleLayer::OnDetach()
{}

void ExampleLayer::OnUpdate(Flick::Timestep ts)
{
	//Update
	m_CameraController.OnUpdate(ts);

	//Render
	Flick::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Flick::RenderCommand::Clear();

	Flick::Renderer::BeginScene(m_CameraController.GetCamera());

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	m_FlatColorShader->Bind();
	m_FlatColorShader->SetFloat3("u_Color", m_SqColor);

	for (int j = 0; j < 10; j++) {
		for (int i = 0; i < 10; i++) {
			glm::vec3 pos(i * 0.11f, j * 0.11f, 0.0f);
			glm::mat4 Sqtransform = glm::translate(glm::mat4(1.0f), pos) * scale;
			Flick::Renderer::Submit(m_FlatColorShader, m_SqVA, Sqtransform);
			Flick::Renderer::Submit(m_TriangleShader, m_VA, Sqtransform);
		}
	}

	auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

	m_Texture1->Bind();
	Flick::Renderer::Submit(textureShader, m_SqVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));

	m_Texture2->Bind();
	Flick::Renderer::Submit(textureShader, m_SqVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));

	Flick::Renderer::EndScene();
}

void ExampleLayer::OnImGuiRender()
{
	ImGui::Begin("IMGUI Window");
	ImGui::Text("ExampleLayer!");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SqColor));
	ImGui::End();
}

void ExampleLayer::OnEvent(Flick::Event & e)
{ 
	m_CameraController.OnEvent(e);
}