#pragma once

namespace wce
{
	enum class EEventType
	{
	// Keyboard:

		KeyPressed = 0,
		KeyReleased,

	// Mouse:

		MousePressed,
		MouseScrolled,
		MouseMoved,

	// Window:

		WindowResized,

	// Engine:

		ApplicationUpdated,
		ApplicationClosed,
		ScreenSwitched,
		FontChanged,

	// UI:

		ButtonPressed
	};
}