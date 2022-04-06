#pragma once

namespace wce
{
	class FEventCatcher
	{
	public:

	// Constructors and Destructor:

		 FEventCatcher() = delete;
		~FEventCatcher() = delete;

	// Functions:

		static void Initialize     ();
		static void CatchEvents    ();
		static void ShutDown       ();

	private:

	// Private Functions:

		static void __stdcall KeyEventProc       (KEY_EVENT_RECORD KeyData);
		static void __stdcall MouseEventProc     (MOUSE_EVENT_RECORD MouseData);
		static void __stdcall ResizeEventProc    (WINDOW_BUFFER_SIZE_RECORD WindowBufferData);

	// Variables:

		static HANDLE StdInput;

		static DWORD ConsoleMode;
		static DWORD ConsoleModeOld;

		static INPUT_RECORD EventData[128];
		static DWORD NumRecordsRead;
	};
}