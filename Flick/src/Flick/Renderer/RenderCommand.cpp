#include "fipch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Flick
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}