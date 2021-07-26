#include "fipch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "examples/imgui_impl_opengl3.h"
#include "examples/imgui_impl_glfw.h"

#include "Flick/Application.h"

//temporary
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Flick
{

	ImGuiLayer::ImGuiLayer()
		:Layer("ImGuiLayer")
	{
	}

	void ImGuiLayer::OnAttach()
	{
		//setup dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;         //enable keyboard controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;         //enable gamepad controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         //enable docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         //enable multi-viewport / platform windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskbarIcons;         
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;     

		//setup dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		//when viewports are enabled we tweak windowrounding/windowbg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		//setup platform/renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnImGuiRender()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

		//rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}
}