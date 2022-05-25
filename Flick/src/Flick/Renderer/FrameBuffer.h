#pragma once
#include "Flick/Core/Core.h"

namespace Flick {
	enum class FrameBufferTextureFormat
	{
		None = 0,

		//color
		RGBA8,

		//depth/stencil
		DEPTH24STENCIL8,

		//defaults
		Depth = DEPTH24STENCIL8
	};

	struct FrameBufferTextureSpecifications
	{
		FrameBufferTextureSpecifications() = default;
		FrameBufferTextureSpecifications(FrameBufferTextureFormat format)
			:TextureFormat(format) {}

		FrameBufferTextureFormat TextureFormat;
		//TODO: filtering/wrap
	};

	struct FrameBufferSpecifications
	{
		uint32_t Width, Height;
		//FrameBufferFormat =
		uint32_t Samples = 1;

		bool SwapchainTarget = false;
	};

	class FrameBuffer {
	public:
		virtual ~FrameBuffer() = default;

		virtual void bind() = 0;
		virtual void unBind() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual uint32_t getColorAttachmentRendererID() const = 0;

		virtual const FrameBufferSpecifications& getSpecifications() const = 0;

		static Ref<FrameBuffer> create(const FrameBufferSpecifications& spec);
	};
}