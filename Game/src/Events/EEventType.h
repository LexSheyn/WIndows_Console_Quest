#pragma once

namespace wce
{
	enum class EEventType
	{
	// Keyboard:

		KeyPressed = 0,
		KeyReleased,

	// Mouse:

		MouseLeftPressed,
		MouseRightPressed,
		MouseScrolled,
		MouseMoved,

	// Window:

		WindowResized,

	// Engine:

		ScreenSwitched
	};
}