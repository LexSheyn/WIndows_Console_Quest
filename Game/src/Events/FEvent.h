#pragma once

#include "EEventType.h"
#include "EventData.h"

#pragma warning( push )
#pragma warning( disable : 26495 ) // Uninitialized variables. Unions does not allow default initialization.

namespace wce
{
	class FEvent
	{
	public:

	// Constructors:

		FEvent (EEventType Type)                                             : Type(Type)                                      {} // No data.
		FEvent (EEventType Type, KEY_EVENT_RECORD          KeyData)          : Type(Type), KeyData          (KeyData)          {}
		FEvent (EEventType Type, MOUSE_EVENT_RECORD        MouseData)        : Type(Type), MouseData        (MouseData)        {}
		FEvent (EEventType Type, WINDOW_BUFFER_SIZE_RECORD WindowBufferData) : Type(Type), WindowBufferData (WindowBufferData) {}
		FEvent (EEventType Type, FScreenData               ScreenData)       : Type(Type), ScreenData       (ScreenData)       {}
		FEvent (EEventType Type, FFontData                 FontData)         : Type(Type), FontData         (FontData)         {}
		FEvent (EEventType Type, FButtonData               ButtonData)       : Type(Type), ButtonData       (ButtonData)       {}
		FEvent (EEventType Type, FGameData                 GameData)         : Type(Type), GameData         (GameData)         {}
		FEvent (EEventType Type, FMemorySlotData           MemorySlotData)   : Type(Type), MemorySlotData   (MemorySlotData)   {}
		FEvent (EEventType Type, FSoundVolumeData          SoundVolumeData)  : Type(Type), SoundVolumeData  (SoundVolumeData)  {}

		~FEvent () {}

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

			FScreenData      ScreenData;
			FFontData        FontData;
			FButtonData      ButtonData;
			FGameData        GameData;
			FMemorySlotData  MemorySlotData;
			FSoundVolumeData SoundVolumeData;
		};

	private:

	// Variables:

		EEventType Type;
	};
}

#pragma warning( push )