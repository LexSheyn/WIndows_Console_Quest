#include "../PrecompiledHeaders/wcepch.h"
#include "FConsole.h"

namespace wce
{
// Constructors and Destructor:

	FConsole::FConsole()
		: Console(GetConsoleWindow()),
		  Desktop(GetDesktopWindow())
	{
	// Get console window size:

		GetWindowRect(Console, &ConsoleRect);

		ConsoleWidth  = ConsoleRect.right;
		ConsoleHeight = ConsoleRect.bottom;
		ConsoleX      = ConsoleRect.left;
		ConsoleY      = ConsoleRect.top;

	// Get desktop window size:

		GetWindowRect(Desktop, &DesktopRect);

		DesktopWidth  = DesktopRect.right;
		DesktopHeight = DesktopRect.bottom;
		DesktopX      = DesktopRect.left;
		DesktopY      = DesktopRect.top;

	// Remove resize and maximize functionality:

		Style  = GetWindowLong(Console, GWL_STYLE);
		Style &= ~WS_MAXIMIZEBOX;
		Style &= ~WS_SIZEBOX;

		SetWindowLong(Console, GWL_STYLE, Style);
	}

	FConsole::~FConsole()
	{
	}

	void FConsole::ArrangeToCenter()
	{
		SetWindowPos(Console,
			         nullptr,
			         static_cast<INT>((static_cast<FLOAT>(DesktopWidth ) / 2.0f) - (static_cast<FLOAT>(ConsoleWidth ) / 2.0f)),
			         static_cast<INT>((static_cast<FLOAT>(DesktopHeight) / 2.0f) - (static_cast<FLOAT>(ConsoleHeight) / 2.0f)),
			         0,
			         0,
			         SWP_NOSIZE);
	}

	FConsole& FConsole::SetPosition(INT X, INT Y)
	{
		SetWindowPos(Console, nullptr, X, Y, 0, 0, SWP_NOSIZE);

		return *this;
	}

	FConsole& FConsole::SetSize(INT Width, INT Height)
	{
		SetWindowPos(Console, nullptr, 0, 0, Width, Height, SWP_NOMOVE);

		return *this;
	}

	FConsole& FConsole::SetStyle(LONG Style)
	{
		SetWindowLong(Console, GWL_STYLE, Style);

		return *this;
	}

	FConsole& FConsole::SetTitle(const std::wstring& Title)
	{
		SetConsoleTitle(Title.c_str());

		return *this;
	}


}