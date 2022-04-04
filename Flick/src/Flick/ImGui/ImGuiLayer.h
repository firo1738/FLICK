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

		void Begin();
		void End();
		
	private:
		float m_Time = 0.0f;
	};
}
