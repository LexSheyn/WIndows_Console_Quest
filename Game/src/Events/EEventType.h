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

		ApplicationStarted,
		ApplicationUpdated,
		ApplicationClosed,
		ScreenSwitched,
		FontChanged,

	// UI:

		ButtonPressed,

	// Menu:

		MenuExit,

	// Game:

		GameCompleted,
		GameFinished,

	// Memory:

		GameSaved,
		GameLoaded,
		MemorySlotPressed,
		GameDataRequested,
		GameDataSent
	};
}