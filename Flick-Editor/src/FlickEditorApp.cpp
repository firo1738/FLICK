#include <Flick.h>
#include <Flick/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "Flick/Core/Core.h"

#include "EditorLayer.h"

namespace Flick {
	class FlickEditor : public Application
	{
	public:
		FlickEditor()
			:Application("Flick Editor")
		{
			PushLayer(new EditorLayer());
		}

		~FlickEditor()
		{

		}
	};

	Application* CreateApplication()
	{
		return new FlickEditor();
	}
}