#include "fipch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Flick
{
	///////////////////Index Buffer///////////////////

	VertexBuffer* VertexBuffer::Create(float* verticies, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: FI_CORE_ASSERT(false, "RendererAPi::None is not yet supported by Flick!"); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(verticies, size);
		}

		FI_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	///////////////////Index Buffer///////////////////

	IndexBuffer* IndexBuffer::Create(uint32_t* indicies, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: FI_CORE_ASSERT(false, "RendererAPi::None is not yet supported by Flick!"); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indicies, count);
		}

		FI_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}