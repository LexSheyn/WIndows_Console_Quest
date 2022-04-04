#pragma once

namespace wce
{
	struct FGameData
	{
		const WCHAR* Time         = nullptr;
		const WCHAR* Date         = nullptr;
		WORD         Chapter      = 0;
		WORD         MemorySlotID = 0;
	};
}