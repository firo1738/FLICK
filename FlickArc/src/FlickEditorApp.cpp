#include <Flick.h>
#include <Flick/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "Flick/Core/Core.h"

#include "EditorLayer.h"

namespace Flick {
	class FlickArc : public Application
	{
	public:
		FlickArc()
			:Application("FlickArc")
		{
			PushLayer(new EditorLayer());
		}

		~FlickArc()
		{

		}
	};

	Application* CreateApplication()
	{
		return new FlickArc();
	}
}