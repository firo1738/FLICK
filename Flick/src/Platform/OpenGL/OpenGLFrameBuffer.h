#pragma once
#include "Renderer/FrameBuffer.h"

namespace Flick {
	class OpenGLFrameBuffer : public FrameBuffer 
	{
	public:
		OpenGLFrameBuffer(const FrameBufferSpecifications& spec);
		virtual ~OpenGLFrameBuffer();

		void Invalidate();

		virtual void bind() override;
		virtual void unBind() override;

		virtual uint32_t getColorAttachmentRendererID() const override { return m_ColorAttachment; }

		virtual const FrameBufferSpecifications& getSpecifications() const override { return m_Specifications; }
	private:
		uint32_t m_RendererID;
		uint32_t m_ColorAttachment;
		uint32_t m_DepthAttachment;
		FrameBufferSpecifications m_Specifications;
	};
}