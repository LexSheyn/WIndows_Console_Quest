#pragma once

namespace wce
{
	class FScreenBuffer
	{
	public:

	// Constructors and Destructor:

		 FScreenBuffer    ();
		~FScreenBuffer    ();

	// Functions:

		void Activate             ();
		void Clear                ();
		void FillWithAttribute    (COORD Position, DWORD Length, WORD Attribute); // M
		void Write                (COORD Position, WCHAR Character);
		void Write                (COORD Position, const std::wstring& String);
		void Present              ();
		void IncreaseFontSize     (SHORT Offset = 1);
		void DecreaseFontSize     (SHORT Offset = 1);

	// Accessors:

		const WCHAR* GetFontName           () const;
		const SHORT& GetFontSize           () const;
		const SHORT& GetFontSizeMax        () const;
		const SHORT& GetFontSizeMin        () const;
		const WORD&  GetOutputAttribute    () const;

	// Modifiers:

		FScreenBuffer& SetFont               (const std::wstring& FontName);
		FScreenBuffer& SetFontSize           (SHORT Size); // M
		FScreenBuffer& SetOutputAttribute    (WORD Attribute);

	private:

	// Private Functions:

		void HideConsoleCursor    ();
		void UpdateFont           (); // M

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
		static constexpr SHORT     FontSizeMax = 26;
		static constexpr SHORT     FontSizeMin = 16;
		SHORT                      FontSize;     // M
		WCHAR                      FontName[32]; // M

		DWORD NumAttributesWritten;
	};
}