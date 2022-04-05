#pragma once

namespace wce
{
	struct FGameData
	{
		WCHAR Time[9] {};
		WCHAR Date[12]{};
		WORD  Chapter      = 0;
		WORD  MemorySlotID = 0;
	};
}