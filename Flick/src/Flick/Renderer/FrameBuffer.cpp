#include "fipch.h"
#include "FrameBuffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace Flick {
	Ref<FrameBuffer> FrameBuffer::create(const FrameBufferSpecifications& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: FI_CORE_ASSERT(false, "RendererAPi::None is not yet supported by Flick!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLFrameBuffer>(spec);
		}

		FI_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}