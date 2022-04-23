#pragma once

#include "Flick/Core/Layer.h"

#include "Flick/Events/MouseEvent.h"
#include "Flick/Events/KeyEvent.h"
#include "Flick/Events/ApplicationEvent.h"

namespace Flick
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnEvent(Event& e) override;

		bool BlockEvents(bool block) { return m_Block = block; }

		void Begin();
		void End();
		
		void SetDarkThemeColors();
	private:
		bool m_Block = true;
		float m_Time = 0.0f;
	};
}
