#include <Flick.h>
#include <Flick/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "Flick/Core/Core.h"

#include "Sandbox2D.h"

#include "ExampleLayer.h"

class Sandbox : public Flick::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{

	}
};

Flick::Application* Flick::CreateApplication()
{
	return new Sandbox();
}