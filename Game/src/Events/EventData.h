#pragma once

#include "../Screens/EScreenName.h"

namespace wce
{
	struct FScreenData { EScreenName FromScreen; EScreenName ToScreen; };

	struct FFontData   { SHORT FromHeight; SHORT ToHeight; const WCHAR* Name; };
}