#pragma once

#include "Flick/Core/Core.h"
#include "Flick/Core/KeyCodes.h"
#include "Flick/Core/MouseCodes.h"

namespace Flick
{
	class FLICK_API Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}
