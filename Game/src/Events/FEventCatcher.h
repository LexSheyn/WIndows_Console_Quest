#pragma once

namespace wce
{
	class FEventCatcher
	{
	public:

	// Functions:

		static void Initialize     ();
		static void CatchEvents    ();
		static void ShutDown       ();

	private:

	// Private Functions:

		static void __stdcall KeyEventProc       (KEY_EVENT_RECORD KeyData);
		static void __stdcall MouseEventProc     (MOUSE_EVENT_RECORD MouseData);
		static void __stdcall ResizeEventProc    (WINDOW_BUFFER_SIZE_RECORD WindowBufferData);

	// Private Constructors and Destructor:

		 FEventCatcher() {}
		~FEventCatcher() {}

		WCE_NO_COPY(FEventCatcher);
		WCE_NO_MOVE(FEventCatcher);

	// Variables:

		static HANDLE StdInput;

		static DWORD ConsoleMode;
		static DWORD ConsoleModeOld;

		static INPUT_RECORD EventData[128];
		static DWORD NumRecordsRead;
	};
}