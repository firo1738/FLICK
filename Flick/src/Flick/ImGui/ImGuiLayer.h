#pragma once

#include "Flick/Layer.h"

#include "Flick/Events/MouseEvent.h"
#include "Flick/Events/KeyEvent.h"
#include "Flick/Events/ApplicationEvent.h"

namespace Flick
{
	class FLICK_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
		
	private:
		float m_Time = 0.0f;
	};
}
