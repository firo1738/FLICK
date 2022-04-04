#pragma once

#include "Flick/Core/Core.h"
#include "Flick/Events/Event.h"
#include "Flick/Events/ApplicationEvent.h"
#include "Flick/Core/LayerStack.h"
#include "Flick/Core/Timestep.h"

#include "Flick/Core/Window.h"

#include "Flick/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace Flick
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void Close();

		Window& GetWindow() { return *m_Window; }

		static Application& Get() { return *s_Instance; }
	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	//to be defined in the client application
	Application* CreateApplication();
}
