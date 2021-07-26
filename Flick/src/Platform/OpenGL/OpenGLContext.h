#pragma once

#include "Flick/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Flick
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowhandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}