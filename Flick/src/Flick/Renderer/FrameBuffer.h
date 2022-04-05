#pragma once
#include "Flick/Core/Core.h"

namespace Flick {
	struct FrameBufferSpecifications
	{
		uint32_t Width, Height;
		//FrameBufferFormat =
		uint32_t Samples = 1;

		bool SwapchainTarget = false;
	};

	class FrameBuffer {
	public:
		virtual void bind() = 0;
		virtual void unBind() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual uint32_t getColorAttachmentRendererID() const = 0;

		virtual const FrameBufferSpecifications& getSpecifications() const = 0;

		static Ref<FrameBuffer> create(const FrameBufferSpecifications& spec);
	};
}