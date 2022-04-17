#include "Panel.h"

#include "imgui/imgui.h"

namespace Flick {
	Flick::Panel::Panel(Ref<Scene>& context)
	{
		SetContext(context);
	}

	void Panel::SetContext(Ref<Scene>& context)
	{
		m_Context = context;
	}

	void Flick::Panel::CreatePanel(std::string panelname)
	{
		ImGui::Begin(panelname.c_str());
		ImGui::End();
	}
}
