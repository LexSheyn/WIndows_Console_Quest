#include "../PrecompiledHeaders/wcepch.h"
#include "FScreenBuffer.h"

namespace wce
{
// Constructors and Destructor:

	FScreenBuffer::FScreenBuffer()
		: Width  (120),
		  Height (30),
		  ConsoleOutputAttribute(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
	{
	// Create char buffer:

		CharBuffer = new WCHAR[Width * Height];

	// Fill char buffer with spaces:

		std::fill_n(CharBuffer, static_cast<int32>(Width * Height), ' ');

	// Create console screen buffer:

		ConsoleScreenBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, nullptr, CONSOLE_TEXTMODE_BUFFER, nullptr);

	// Get screen buffer information including size and position of the window:

		GetConsoleScreenBufferInfo(ConsoleScreenBuffer, &ConsoleScreenInfo);

	// Hire console cursor:

		this->HideConsoleCursor();

	// Set console screen buffer cursor position:

		SetConsoleCursorPosition(ConsoleScreenBuffer, COORD{ 0i16, 0i16 });

	// Set console font height:

		this->SetFontHeight(16);
	}

	FScreenBuffer::~FScreenBuffer()
	{
		delete CharBuffer;
	}


// Functions:

	void FScreenBuffer::Activate()
	{
		SetConsoleActiveScreenBuffer(ConsoleScreenBuffer);
	}

	void FScreenBuffer::Clear()
	{
		this->HideConsoleCursor();

		for (WORD i = 0ui16; i < Height; i++)
		{
			this->FillWithAttribute(ConsoleOutputAttribute, Width, COORD{ 0, static_cast<SHORT>(i) });
		}

		std::fill_n(CharBuffer, static_cast<int32>(Width * Height), ' ');
	}

	void FScreenBuffer::FillWithAttribute(WORD Attribute, DWORD Length, COORD Coordinate)
	{
		FillConsoleOutputAttribute(ConsoleScreenBuffer, Attribute, Length, Coordinate, &NumAttributesWritten);
	}

	void FScreenBuffer::Write(COORD Coordinate, WCHAR Character)
	{
		CharBuffer[ (Coordinate.Y * Width) + Coordinate.X ] = Character;
	}

	void FScreenBuffer::Write(COORD Coordinate, const std::wstring& String)
	{
		std::swprintf( &CharBuffer[ (Coordinate.Y * Width) + Coordinate.X ], String.size() + 1u, L"%s", String.c_str() );
	}

	void FScreenBuffer::Present()
	{
		WriteConsoleOutputCharacterW(ConsoleScreenBuffer, CharBuffer, static_cast<DWORD>(Width * Height), COORD{}, &NumCharactersWritten);		
	}


// Accessors:

	const WCHAR* FScreenBuffer::GetFontName() const
	{
		return ConsoleFontInfo.FaceName;
	}

	const SHORT& FScreenBuffer::GetFontHeight() const
	{
		return ConsoleFontInfo.dwFontSize.Y;
	}

	const WORD& FScreenBuffer::GetOutputAttribute() const
	{
		return ConsoleOutputAttribute;
	}


// Modifiers:

	FScreenBuffer& FScreenBuffer::SetFont(const std::wstring& FontName)
	{
		for (uint64 i = 0u; i < FontName.size(); i++)
		{
			ConsoleFontInfo.FaceName[i] = FontName[i];
		}

		return *this;
	}

	FScreenBuffer& FScreenBuffer::SetFontHeight(SHORT FontHeight)
	{
		ConsoleFontInfo.cbSize       = sizeof(ConsoleFontInfo);
		ConsoleFontInfo.nFont        = 0;
		ConsoleFontInfo.dwFontSize.X = 0;
		ConsoleFontInfo.dwFontSize.Y = FontHeight;
		ConsoleFontInfo.FontFamily   = FF_DONTCARE;
		ConsoleFontInfo.FontWeight   = FW_NORMAL;
	//	ConsoleFontInfo.FaceName;

		wcscpy_s(ConsoleFontInfo.FaceName, L"Consolas");

		SetCurrentConsoleFontEx(ConsoleScreenBuffer, FALSE, &ConsoleFontInfo);

		return *this;
	}

	FScreenBuffer& FScreenBuffer::SetOutputAttribute(WORD Attribute)
	{
		ConsoleOutputAttribute = Attribute;

		return *this;
	}


// Private Functions:

	void FScreenBuffer::HideConsoleCursor()
	{
		GetConsoleCursorInfo(ConsoleScreenBuffer, &ConsoleCursorInfo);
		ConsoleCursorInfo.bVisible = FALSE;
		SetConsoleCursorInfo(ConsoleScreenBuffer, &ConsoleCursorInfo);
	}


}