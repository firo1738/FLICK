#pragma once

#include "Flick/Core/Core.h"
#include "Flick/Core/Log.h"
#include "Flick/Scene/Scene.h"
#include "Flick/Scene/Entity.h"

namespace Flick {
	class SceneHierarchyPanel {
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(Ref<Scene>& context);

		void SetContext(Ref<Scene>& context);

		void OnImGuiRender();

		Entity GetSelectedEntity() const { return m_SelectionContext; }
	private:
		void DrawEntityNode(Entity entity);

		void DrawComponents(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};
}