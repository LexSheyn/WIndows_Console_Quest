#pragma once

namespace wce
{
	class FConsole
	{
	public:

	// Constructors and Destructor:

		 FConsole();
		~FConsole();

		WCE_NO_COPY(FConsole);
		WCE_NO_MOVE(FConsole);

	// Functions:

		void ArrangeToCenter ();

	// Accessors:

		//

	// Modifiers:

		FConsole& SetPosition    (INT X, INT Y);
		FConsole& SetSize        (INT Width, INT Height);
		FConsole& SetStyle       (LONG Style);
		FConsole& SetTitle       (const std::wstring& Title);

	private:

	// Variables:

		HWND Console;
		RECT ConsoleRect;
		INT  ConsoleWidth;
		INT  ConsoleHeight;
		INT  ConsoleX;
		INT  ConsoleY;

		HWND Desktop;
		RECT DesktopRect;
		INT  DesktopWidth;
		INT  DesktopHeight;
		INT  DesktopX;
		INT  DesktopY;

		LONG Style;
	};
}