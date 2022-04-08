#pragma once

#include "../Screens/EScreen.h"
#include "../UI/EButton.h"
#include "../UI/EMemorySlotButton.h"
#include "../Data/FGameData.h"

#pragma warning( push )
#pragma warning( disable : 26495 ) // Uninitialized variables.

namespace wce
{
	struct FScreenData      { EScreen FromScreen; EScreen ToScreen; };					       
	struct FFontData        { SHORT FromSize; SHORT ToSize; const WCHAR* Name; };					       
	struct FButtonData      { WORD ID; DWORD MouseButton; };
	struct FMemorySlotData  { WORD ID; EMemorySlotButton Button; DWORD MouseButton; };
	struct FSoundVolumeData { FLOAT FromVolume; FLOAT ToVolume; };
}

#pragma warning( push )