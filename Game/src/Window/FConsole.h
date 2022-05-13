#pragma once

namespace wce
{
	class FConsole
	{
	public:

	// Constructors and Destructor:

		 FConsole    ();
		~FConsole    ();

	// Functions:

		void ArrangeToCenter    ();

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

		HWND Desktop;
		RECT DesktopRect;

		LONG Style;
	};
}