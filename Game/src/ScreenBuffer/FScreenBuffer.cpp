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
	#pragma warning( push )
	#pragma warning( disable : 26451 ) // Arithmetic overflow.
		CharBuffer = new WCHAR[Width * Height];
	#pragma warning( pop )

		std::fill_n(CharBuffer, static_cast<INT>(Width * Height), ' ');

		ConsoleScreenBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, nullptr, CONSOLE_TEXTMODE_BUFFER, nullptr);

		GetConsoleScreenBufferInfo(ConsoleScreenBuffer, &ConsoleScreenInfo);

		this->HideConsoleCursor();

		SetConsoleCursorPosition(ConsoleScreenBuffer, COORD{ 0i16, 0i16 });

		this->SetFont(L"Consolas"); // M
		this->SetFontSize(FontSizeMin);
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
			this->FillWithAttribute(COORD{ 0, static_cast<SHORT>(i) }, Width, ConsoleOutputAttribute);
		}

		std::fill_n(CharBuffer, static_cast<INT>(Width * Height), ' ');
	}

	void FScreenBuffer::FillWithAttribute(COORD Position, DWORD Length, WORD Attribute)
	{
		FillConsoleOutputAttribute(ConsoleScreenBuffer, Attribute, Length, Position, &NumAttributesWritten);
	}

	void FScreenBuffer::Write(COORD Position, WCHAR Character)
	{
		CharBuffer[ (Position.Y * Width) + Position.X ] = Character;
	}

	void FScreenBuffer::Write(COORD Position, const std::wstring& String)
	{
		std::swprintf( &CharBuffer[ (Position.Y * Width) + Position.X ], String.size() + 1u, L"%s", String.c_str() );
	}

	void FScreenBuffer::Present()
	{
		WriteConsoleOutputCharacterW(ConsoleScreenBuffer, CharBuffer, static_cast<DWORD>(Width * Height), COORD{}, &NumCharactersWritten);		
	}

	void FScreenBuffer::IncreaseFontSize(SHORT Offset)
	{
		ConsoleFontInfo.dwFontSize.Y += Offset;

		if (ConsoleFontInfo.dwFontSize.Y > FontSizeMax)
		{
			ConsoleFontInfo.dwFontSize.Y = FontSizeMax;
		}

		this->SetFontSize(ConsoleFontInfo.dwFontSize.Y);
	}

	void FScreenBuffer::DecreaseFontSize(SHORT Offset)
	{
		ConsoleFontInfo.dwFontSize.Y -= Offset;

		if (ConsoleFontInfo.dwFontSize.Y < FontSizeMin)
		{
			ConsoleFontInfo.dwFontSize.Y = FontSizeMin;
		}

		this->SetFontSize(ConsoleFontInfo.dwFontSize.Y);
	}


// Accessors:

	const WCHAR* FScreenBuffer::GetFontName() const
	{
		return FontName; // M
	}

	const SHORT& FScreenBuffer::GetFontSize() const
	{
		return FontSize; // M
	}

	const SHORT& FScreenBuffer::GetFontSizeMax() const
	{
		return FontSizeMax;
	}

	const SHORT& FScreenBuffer::GetFontSizeMin() const
	{
		return FontSizeMin;
	}

	const WORD& FScreenBuffer::GetOutputAttribute() const
	{
		return ConsoleOutputAttribute;
	}


// Modifiers:

	FScreenBuffer& FScreenBuffer::SetFont(const std::wstring& FontName)
	{
		wcscpy_s(this->FontName, FontName.c_str()); // M
		
		this->UpdateFont(); // M

		return *this;
	}

	FScreenBuffer& FScreenBuffer::SetFontSize(SHORT Size)
	{
		FontSize = Size;

		this->UpdateFont(); // M

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

	void FScreenBuffer::UpdateFont()
	{
		ConsoleFontInfo.cbSize       = sizeof(ConsoleFontInfo);
		ConsoleFontInfo.nFont        = 0;
		ConsoleFontInfo.dwFontSize.X = 0;
		ConsoleFontInfo.dwFontSize.Y = FontSize;
		ConsoleFontInfo.FontFamily   = FF_DONTCARE;
		ConsoleFontInfo.FontWeight   = FW_NORMAL;

		wcscpy_s(ConsoleFontInfo.FaceName, FontName); // M

		SetCurrentConsoleFontEx(ConsoleScreenBuffer, FALSE, &ConsoleFontInfo);
	}


}