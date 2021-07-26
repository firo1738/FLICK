#include "fipch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Flick
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: FI_CORE_ASSERT(false, "RendererAPI::None is not yet supported by Flick!"); return nullptr;
		case  RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}

		FI_CORE_ASSERT(false, "Unknown RendererAPI!");
		return 0;
	}
}