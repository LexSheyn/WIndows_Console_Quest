#include "../PrecompiledHeaders/wcepch.h"
#include "FTextField.h"

#include "../ScreenBuffer/FScreenBuffer.h"

namespace wce
{
// Constructors and Destructor:

	FTextField::FTextField()
		: Coord        (COORD{}),
		  Attribute    (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE),
		  Enabled      (true)
	{
		Text.reserve(120);
	}

	FTextField::~FTextField()
	{
	}


// Functions:

	void FTextField::Disable()
	{
		Enabled = false;
		Attribute = 8;
	}

	void FTextField::Enable()
	{
		Enabled = true;
		Attribute = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	}

	void FTextField::Draw(FScreenBuffer& ScreenBuffer)
	{
		ScreenBuffer.FillWithAttribute(Attribute, static_cast<DWORD>(Text.length()), Coord);
		ScreenBuffer.Write(Coord, Text);
	}


// Accessors:

	const COORD& FTextField::GetPosition() const
	{
		return Coord;
	}

	const std::wstring& FTextField::GetText() const
	{
		return Text;
	}

	const bool8& FTextField::IsEnabled() const
	{
		return Enabled;
	}

	uint64 FTextField::GetLength() const
	{
		return static_cast<uint64>(Text.length());
	}


// Modifiers:

	FTextField& FTextField::SetPosition(COORD Position)
	{
		Coord = Position;

		return *this;
	}

	FTextField& FTextField::SetText(const std::wstring Text)
	{
		this->Text = Text;

		return *this;
	}


}