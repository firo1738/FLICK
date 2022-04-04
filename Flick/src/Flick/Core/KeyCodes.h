#pragma once

namespace Flick
{
	typedef enum class KeyCode : uint16_t
	{
		//taken from glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

/* Printable keys */
#define FI_KEY_SPACE              ::Flick::Key::Space
#define FI_KEY_APOSTROPHE         ::Flick::Key::Apostrphe  /* ' */
#define FI_KEY_COMMA              ::Flick::Key::Comma  /* , */
#define FI_KEY_MINUS              ::Flick::Key::Minus  /* - */
#define FI_KEY_PERIOD			  ::Flick::Key::Period  /* . */
#define FI_KEY_SLASH              ::Flick::Key::Slash  /* / */
#define FI_KEY_0                  ::Flick::Key::D0
#define FI_KEY_1                  ::Flick::Key::D1
#define FI_KEY_2                  ::Flick::Key::D2
#define FI_KEY_3                  ::Flick::Key::D3
#define FI_KEY_4                  ::Flick::Key::D4
#define FI_KEY_5                  ::Flick::Key::D5
#define FI_KEY_6                  ::Flick::Key::D6
#define FI_KEY_7                  ::Flick::Key::D7
#define FI_KEY_8                  ::Flick::Key::D8
#define FI_KEY_9                  ::Flick::Key::D9
#define FI_KEY_SEMICOLON          ::Flick::Key::Semicolon  /* ; */
#define FI_KEY_EQUAL              ::Flick::Key::Equal  /* = */
#define FI_KEY_A                  ::Flick::Key::A
#define FI_KEY_B                  ::Flick::Key::B
#define FI_KEY_C                  ::Flick::Key::C
#define FI_KEY_D                  ::Flick::Key::D
#define FI_KEY_E                  ::Flick::Key::E
#define FI_KEY_F                  ::Flick::Key::F
#define FI_KEY_G                  ::Flick::Key::G
#define FI_KEY_H                  ::Flick::Key::H
#define FI_KEY_I                  ::Flick::Key::I
#define FI_KEY_J                  ::Flick::Key::J
#define FI_KEY_K                  ::Flick::Key::K
#define FI_KEY_L                  ::Flick::Key::L
#define FI_KEY_M                  ::Flick::Key::M
#define FI_KEY_N                  ::Flick::Key::N
#define FI_KEY_O                  ::Flick::Key::O
#define FI_KEY_P                  ::Flick::Key::P
#define FI_KEY_Q                  ::Flick::Key::Q
#define FI_KEY_R                  ::Flick::Key::R
#define FI_KEY_S                  ::Flick::Key::S
#define FI_KEY_T                  ::Flick::Key::T
#define FI_KEY_U                  ::Flick::Key::U
#define FI_KEY_V                  ::Flick::Key::V
#define FI_KEY_W                  ::Flick::Key::W
#define FI_KEY_X                  ::Flick::Key::X
#define FI_KEY_Y                  ::Flick::Key::Y
#define FI_KEY_Z                  ::Flick::Key::Z
#define FI_KEY_LEFT_BRACKET       ::Flick::Key::LeftBracket  /* [ */
#define FI_KEY_BACKSLASH          ::Flick::Key::Backslash  /* \ */
#define FI_KEY_RIGHT_BRACKET      ::Flick::Key::RightBracket  /* ] */
#define FI_KEY_GRAVE_ACCENT       ::Flick::Key::GraveAccent  /* ` */
#define FI_KEY_WORLD_1            ::Flick::Key::World1 /* non-US #1 */
#define FI_KEY_WORLD_2            ::Flick::Key::World2 /* non-US #2 */

/* Function keys */
#define FI_KEY_ESCAPE             ::Flick::Key::Escape
#define FI_KEY_ENTER              ::Flick::Key::Enter
#define FI_KEY_TAB                ::Flick::Key::Tab
#define FI_KEY_BACKSPACE          ::Flick::Key::Backspace
#define FI_KEY_INSERT             ::Flick::Key::Insert
#define FI_KEY_DELETE             ::Flick::Key::Delete
#define FI_KEY_RIGHT              ::Flick::Key::Right
#define FI_KEY_LEFT               ::Flick::Key::Left
#define FI_KEY_DOWN               ::Flick::Key::Down
#define FI_KEY_UP                 ::Flick::Key::Up
#define FI_KEY_PAGE_UP            ::Flick::Key::PageUp
#define FI_KEY_PAGE_DOWN          ::Flick::Key::PageDown
#define FI_KEY_HOME               ::Flick::Key::Home
#define FI_KEY_END                ::Flick::Key::End
#define FI_KEY_CAPS_LOCK          ::Flick::Key::CapsLock
#define FI_KEY_SCROLL_LOCK        ::Flick::Key::ScrollLock
#define FI_KEY_NUM_LOCK           ::Flick::Key::NumLock
#define FI_KEY_PRINT_SCREEN       ::Flick::Key::PrintScreen
#define FI_KEY_PAUSE              ::Flick::Key::Pause
#define FI_KEY_F1                 ::Flick::Key::F1
#define FI_KEY_F2                 ::Flick::Key::F2
#define FI_KEY_F3                 ::Flick::Key::F3
#define FI_KEY_F4                 ::Flick::Key::F4
#define FI_KEY_F5                 ::Flick::Key::F5
#define FI_KEY_F6                 ::Flick::Key::F6
#define FI_KEY_F7                 ::Flick::Key::F7
#define FI_KEY_F8                 ::Flick::Key::F8
#define FI_KEY_F9                 ::Flick::Key::F9
#define FI_KEY_F10                ::Flick::Key::F10
#define FI_KEY_F11                ::Flick::Key::F11
#define FI_KEY_F12                ::Flick::Key::F12
#define FI_KEY_F13                ::Flick::Key::F13
#define FI_KEY_F14                ::Flick::Key::F14
#define FI_KEY_F15                ::Flick::Key::F15
#define FI_KEY_F16                ::Flick::Key::F16
#define FI_KEY_F17                ::Flick::Key::F17
#define FI_KEY_F18                ::Flick::Key::F18
#define FI_KEY_F19                ::Flick::Key::F19
#define FI_KEY_F20                ::Flick::Key::F20
#define FI_KEY_F21                ::Flick::Key::F21
#define FI_KEY_F22                ::Flick::Key::F22
#define FI_KEY_F23                ::Flick::Key::F23
#define FI_KEY_F24                ::Flick::Key::F24
#define FI_KEY_F25                ::Flick::Key::F25
								  
//Function keys					  
#define FI_KEY_KP_0               ::Flick::Key::KP0
#define FI_KEY_KP_1               ::Flick::Key::KP1
#define FI_KEY_KP_2               ::Flick::Key::KP2
#define FI_KEY_KP_3               ::Flick::Key::KP3
#define FI_KEY_KP_4               ::Flick::Key::KP4
#define FI_KEY_KP_5               ::Flick::Key::KP5
#define FI_KEY_KP_6               ::Flick::Key::KP6
#define FI_KEY_KP_7               ::Flick::Key::KP7
#define FI_KEY_KP_8               ::Flick::Key::KP8
#define FI_KEY_KP_9               ::Flick::Key::KP9
#define FI_KEY_KP_DECIMAL         ::Flick::Key::KPDecimal
#define FI_KEY_KP_DIVIDE          ::Flick::Key::KPDivide
#define FI_KEY_KP_MULTIPLY        ::Flick::Key::KPMultiply
#define FI_KEY_KP_SUBTRACT        ::Flick::Key::KPSubtract
#define FI_KEY_KP_ADD             ::Flick::Key::KPAdd
#define FI_KEY_KP_ENTER           ::Flick::Key::KPEnter
#define FI_KEY_KP_EQUAL           ::Flick::Key::KPEqual
								  
#define FI_KEY_LEFT_SHIFT         ::Flick::Key::LeftShift
#define FI_KEY_LEFT_CONTROL       ::Flick::Key::LeftControl
#define FI_KEY_LEFT_ALT           ::Flick::Key::LeftAlt
#define FI_KEY_LEFT_SUPER         ::Flick::Key::LeftSuper
#define FI_KEY_RIGHT_SHIFT        ::Flick::Key::RightShift
#define FI_KEY_RIGHT_CONTROL      ::Flick::Key::RightControl
#define FI_KEY_RIGHT_ALT          ::Flick::Key::RightAlt
#define FI_KEY_RIGHT_SUPER        ::Flick::Key::RightSuper
#define FI_KEY_MENU               ::Flick::Key::Menu
