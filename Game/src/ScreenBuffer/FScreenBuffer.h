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

		void Activate             ();
		void Clear                ();
		void FillWithAttribute    (WORD Attribute, DWORD Length, COORD Coordinate);
		void Write                (COORD Coordinate, WCHAR Character);
		void Write                (COORD Coordinate, const std::wstring& String);
		void Present              ();		

	// Accessors:

		const WCHAR* GetFontName           () const;
		const SHORT& GetFontHeight         () const;
		const WORD&  GetOutputAttribute    () const;

	// Modifiers:

		FScreenBuffer& SetFont               (const std::wstring& FontName);
		FScreenBuffer& SetFontHeight         (SHORT FontHeight);
		FScreenBuffer& SetOutputAttribute    (WORD Attribute);

	private:

	// Private Functions:

		void HideConsoleCursor();

	// Variables:

		WORD Width;
		WORD Height;

		WCHAR* CharBuffer;

		HANDLE ConsoleScreenBuffer;
		WORD   ConsoleOutputAttribute;
		DWORD  NumCharactersWritten;

		CONSOLE_SCREEN_BUFFER_INFO ConsoleScreenInfo;
		CONSOLE_CURSOR_INFO        ConsoleCursorInfo;
		CONSOLE_FONT_INFOEX        ConsoleFontInfo;

		DWORD NumAttributesWritten;
	};
}