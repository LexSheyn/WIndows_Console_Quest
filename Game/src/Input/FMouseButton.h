#pragma once

namespace wce
{
	struct FMouseButton
	{
		static constexpr DWORD Left  = FROM_LEFT_1ST_BUTTON_PRESSED;
		static constexpr DWORD Right = RIGHTMOST_BUTTON_PRESSED;
	};
}