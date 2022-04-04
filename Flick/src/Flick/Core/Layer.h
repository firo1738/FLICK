#pragma once

#include "Flick/Core/Core.h"
#include "Flick/Events/Event.h"
#include "Flick/Core/Timestep.h"

namespace Flick
{
	class FLICK_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		const std::string& GetName() { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}
