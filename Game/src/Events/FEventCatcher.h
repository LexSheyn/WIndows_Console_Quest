#pragma once

namespace wce
{
	class FEventCatcher
	{
	public:

	// Constructors and Destructor:

		 FEventCatcher    ();
		~FEventCatcher    ();

	// Functions:

		void CatchEvents    ();

	private:

	// Private Functions:

		void Initialize    ();
		void Shutdown      ();

	// Event Process Functions:

		static void __stdcall KeyEventProc       (KEY_EVENT_RECORD KeyData);
		static void __stdcall MouseEventProc     (MOUSE_EVENT_RECORD MouseData);
		static void __stdcall ResizeEventProc    (WINDOW_BUFFER_SIZE_RECORD WindowBufferData);

	// Variables:

		HANDLE StdInput;

		DWORD ConsoleMode;
		DWORD ConsoleModeOld;

		INPUT_RECORD EventData[128];
		DWORD NumRecordsRead;
	};
}