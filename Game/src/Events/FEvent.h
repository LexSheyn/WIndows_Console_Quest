#pragma once

#include "EEventType.h"
#include "EventData.h"

namespace wce
{
	class FEvent
	{
	public:

	// Constructors:

		FEvent (EEventType Type, KEY_EVENT_RECORD          KeyData)          : Type(Type), KeyData          (KeyData)          {}
		FEvent (EEventType Type, MOUSE_EVENT_RECORD        MouseData)        : Type(Type), MouseData        (MouseData)        {}
		FEvent (EEventType Type, WINDOW_BUFFER_SIZE_RECORD WindowBufferData) : Type(Type), WindowBufferData (WindowBufferData) {}
		FEvent (EEventType Type, FScreenData               ScreenData)       : Type(Type), ScreenData       (ScreenData)       {}

		WCE_NO_COPY(FEvent);
		WCE_DEFAULT_MOVE(FEvent);

	// Accessors:

		inline const EEventType& GetType () const { return Type; }

	// Public Variables:

		union
		{
		// Win32:

			KEY_EVENT_RECORD          KeyData;
			MOUSE_EVENT_RECORD        MouseData;
			WINDOW_BUFFER_SIZE_RECORD WindowBufferData;

		// Engine:

			FScreenData ScreenData;
		};

	private:

	// Variables:

		EEventType Type;
	};
}