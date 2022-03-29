#pragma once

#include "../Screens/EScreenName.h"

namespace wce
{
	struct FScreenData { EScreenName FromScreen; EScreenName ToScreen; };

	struct FFontData   { SHORT FromSize; SHORT ToSize; const WCHAR* Name; };
}