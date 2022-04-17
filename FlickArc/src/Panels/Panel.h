#pragma once

#include "Flick/Core/Core.h"
#include "Flick/Core/Log.h"
#include "Flick/Scene/Scene.h"
#include <string>

namespace Flick {
	class Panel{
	public:
		Panel() = default;
		Panel(Ref<Scene>& context);
		void SetContext(Ref<Scene>& context);
		void CreatePanel(std::string name = "Empty Panel");
	private:
		Ref<Scene> m_Context;
	};
}