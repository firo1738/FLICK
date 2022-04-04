#include "fipch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Flick
{

	OpenGLContext::OpenGLContext(GLFWwindow* windowhandle)
		:m_WindowHandle(windowhandle)
	{
		FI_CORE_ASSERT(windowhandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		FI_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		FI_CORE_ASSERT(status, "Failed to initialize glad!");

		FI_CORE_INFO("OpenGL Info");
		FI_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
		FI_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
		FI_CORE_INFO("Version: {0}", glGetString(GL_VERSION));

#ifdef FI_ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		FI_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Flick requires at least OpenGL version 4.5!");
#endif // OpenGl version required to run Flick

	}

	void OpenGLContext::SwapBuffers()
	{
		FI_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}