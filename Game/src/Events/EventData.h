#pragma once

#include "../Screens/EScreenName.h"
#include "../UI/EButtonName.h"

namespace wce
{
	struct FScreenData { EScreenName FromScreen; EScreenName ToScreen; };

	struct FFontData   { SHORT FromSize; SHORT ToSize; const WCHAR* Name; };

	struct FButtonData { EButtonName ButtonName; DWORD MouseButton; };
}