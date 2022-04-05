#include "../PrecompiledHeaders/wcepch.h"
#include "FTimeStamp.h"

#pragma warning( push )
#pragma warning( disable : 6386 ) // Buffer overrun.

namespace wce
{
// Functions:

	std::wstring FTimeStamp::TimeAsString()
	{
		std::time_t CurrentCalendarTime = std::time(nullptr);

		std::tm LocalTime{};

		WCHAR TimeAsCharArray[9]{}; // HH:MM:SS, 9 chars: 8 for numbers + 1 for '\0' (null terminator).

		localtime_s(&LocalTime, &CurrentCalendarTime);

		std::wcsftime(TimeAsCharArray, sizeof(TimeAsCharArray), L"%H:%M:%S", &LocalTime); // C6386: Buffer overrun.

		return std::wstring(TimeAsCharArray);
	}

	std::wstring FTimeStamp::DateAsString()
	{
		std::time_t CurrentCalendarTime = std::time(nullptr);

		std::tm LocalTime{};

		WCHAR TimeAsCharArray[12]{}; // MM:DD:YYYY, 12 chars: 11 for numbers + 1 for '\0' (null terminator).

		localtime_s(&LocalTime, &CurrentCalendarTime);

		std::wcsftime(TimeAsCharArray, sizeof(TimeAsCharArray), L"%m/%d/%Y", &LocalTime); // C6386: Buffer overrun.

		return std::wstring(TimeAsCharArray);
	}


}

#pragma warning( push )