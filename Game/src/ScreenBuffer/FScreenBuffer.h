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
		void IncreaseFontSize     (SHORT Offset = 1i16);
		void DecreaseFontSize     (SHORT Offset = 1i16);

	// Accessors:

		const WCHAR* GetFontName           () const;
		const SHORT& GetFontSize           () const;
		const SHORT& GetFontSizeMax        () const;
		const SHORT& GetFontSizeMin        () const;
		const WORD&  GetOutputAttribute    () const;

	// Modifiers:

		FScreenBuffer& SetFont               (const std::wstring& FontName);
		FScreenBuffer& SetFontSize           (SHORT FontHeight);
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
		static constexpr SHORT     FontSizeMax = 26i16;
		static constexpr SHORT     FontSizeMin = 16i16;

		DWORD NumAttributesWritten;
	};
}