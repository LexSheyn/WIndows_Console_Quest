#include "../PrecompiledHeaders/wcepch.h"
#include "FEventCatcher.h"
#include "FEventSystem.h"

namespace wce
{
// Functions:

	void FEventCatcher::Initialize()
	{
	// Get standsrd input handle:

		StdInput = GetStdHandle(STD_INPUT_HANDLE);

	// Save current input mode to be restored on exit:

		GetConsoleMode(StdInput, &ConsoleModeOld);

	// Disable Quick Edit Mode and enable the window and mouse input events:

		SetConsoleMode(StdInput, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
	}

	void FEventCatcher::CatchEvents()
	{
	// Read and handle console input events:

		ReadConsoleInputW(StdInput, EventData, 128, &NumRecordsRead);

	// Dispatch events to the appropriate handler:

		for (DWORD i = 0; i < NumRecordsRead; i++)
		{
			switch (EventData[i].EventType)
			{
				case KEY_EVENT:
				{
					KeyEventProc(EventData[i].Event.KeyEvent);
				}
				break;

				case MOUSE_EVENT:
				{
					MouseEventProc(EventData[i].Event.MouseEvent);
				}
				break;

				case WINDOW_BUFFER_SIZE_EVENT:
				{
					ResizeEventProc(EventData[i].Event.WindowBufferSizeEvent);
				}
				break;

				case MENU_EVENT:
				{
					// To do...
				}
				break;

				case FOCUS_EVENT:
				{
					// To do...
				}
				break;

				default:
				{
				}
				break;
			}
		}
	}

	void FEventCatcher::ShutDown()
	{
	// Restored default console mode on exit:

		SetConsoleMode(StdInput, ConsoleModeOld);
	}


// Event Process Functions:

	void __stdcall FEventCatcher::KeyEventProc(KEY_EVENT_RECORD KeyData)
	{
		if      (KeyData.bKeyDown)
		{
			FEventSystem::PushEvent(FEvent(EEventType::KeyPressed, KeyData));
		}
		else if (!KeyData.bKeyDown)
		{
			FEventSystem::PushEvent(FEvent(EEventType::KeyReleased, KeyData));
		}
	}

	void __stdcall FEventCatcher::MouseEventProc(MOUSE_EVENT_RECORD MouseData)
	{
		switch (MouseData.dwEventFlags)
		{
			case 0:
			{
				FEventSystem::PushEvent(FEvent(EEventType::MousePressed, MouseData));
			}
			break;

			case MOUSE_WHEELED:
			{
				FEventSystem::PushEvent(FEvent(EEventType::MouseScrolled, MouseData));
			}
			break;

			case MOUSE_MOVED:
			{
				FEventSystem::PushEvent(FEvent(EEventType::MouseMoved, MouseData));
			}
			break;

			default:
			{
			}
			break;
		}
	}

	void __stdcall FEventCatcher::ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD WindowBufferData)
	{
		FEventSystem::PushEvent(FEvent(EEventType::WindowResized, WindowBufferData));
	}


// Static Variables:

	HANDLE FEventCatcher::StdInput = nullptr;

	DWORD FEventCatcher::ConsoleMode    = 0;
	DWORD FEventCatcher::ConsoleModeOld = 0;

	INPUT_RECORD FEventCatcher::EventData[128];
	DWORD        FEventCatcher::NumRecordsRead = 0;


}