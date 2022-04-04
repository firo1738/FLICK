#pragma once

namespace Flick
{
		typedef enum class MouseCode : uint16_t
		{
			// From glfw3.h
			Button0                = 0,
			Button1                = 1,
			Button2                = 2,
			Button3                = 3,
			Button4                = 4,
			Button5                = 5,
			Button6                = 6,
			Button7                = 7,
			//test
			KeyL                   = 76,

			ButtonLast             = Button7,
			ButtonLeft             = Button0,
			ButtonRight            = Button1,
			ButtonMiddle           = Button2
		}Mouse;

		inline std::ostream& operator<<(std::ostream& os, MouseCode button)
		{
			os << static_cast<int32_t>(button);
			return os;
		}
}

#define FI_MOUSE_BUTTON_0          ::Flick::Mouse::Button0
#define FI_MOUSE_BUTTON_1          ::Flick::Mouse::Button1
#define FI_MOUSE_BUTTON_2          ::Flick::Mouse::Button2
#define FI_MOUSE_BUTTON_3          ::Flick::Mouse::Button3
#define FI_MOUSE_BUTTON_4          ::Flick::Mouse::Button4
#define FI_MOUSE_BUTTON_5          ::Flick::Mouse::Button5
#define FI_MOUSE_BUTTON_6          ::Flick::Mouse::Button6
#define FI_MOUSE_BUTTON_7          ::Flick::Mouse::Button7
#define FI_MOUSE_BUTTON_LAST       ::Flick::Mouse::ButtonLast
#define FI_MOUSE_BUTTON_LEFT       ::Flick::Mouse::ButtonLeft
#define FI_MOUSE_BUTTON_RIGHT      ::Flick::Mouse::ButtonRight
#define FI_MOUSE_BUTTON_MIDDLE     ::Flick::Mouse::ButtonMiddle
//test
#define FI_BUTTON_L				   ::Flick::Mouse::KeyL