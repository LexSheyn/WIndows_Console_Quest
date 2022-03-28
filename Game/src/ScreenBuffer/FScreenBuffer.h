#pragma once

namespace wce
{
	class FScreenBuffer
	{
	public:

	// Constructors and Destructor:

		 FScreenBuffer ();
		~FScreenBuffer ();

	// Functions:

		void Activate      ();
		void Clear         (WORD Attribute = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		void Write         (COORD Coordinate, WCHAR Character);
		void Write         (COORD Coordinate, const std::wstring& String);
		void Present       ();		

	// Modifiers:

		void SetFontHeight         (SHORT FontHeight);
		void SetOutputAttribute    (WORD Attribute, DWORD Length, COORD Coordinte);

	private:

	// Private Functions:

		void HideConsoleCursor();

	// Variables:

		WORD Width;
		WORD Height;

		WCHAR* CharBuffer;

		HANDLE ConsoleScreenBuffer;
		DWORD  NumCharactersWritten;

		CONSOLE_SCREEN_BUFFER_INFO ConsoleScreenInfo;
		CONSOLE_CURSOR_INFO        ConsoleCursorInfo;
		CONSOLE_FONT_INFOEX        ConsoleFontInfo;

		DWORD NumAttributesWritten;
	};
}