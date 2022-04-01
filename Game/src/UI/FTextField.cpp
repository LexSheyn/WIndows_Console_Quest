#include "../PrecompiledHeaders/wcepch.h"
#include "FTextField.h"

#include "../ScreenBuffer/FScreenBuffer.h"

namespace wce
{
// Constructors and Destructor:

	FTextField::FTextField()
		: Position  (COORD{}),
	//	  Attribute (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
		  Attribute (FOREGROUND_RED | FOREGROUND_GREEN )
	{
		Text.reserve(120);
	}

	FTextField::~FTextField()
	{
	}


// Functions:

	void FTextField::Draw(FScreenBuffer& ScreenBuffer)
	{
		ScreenBuffer.FillWithAttribute(Attribute, static_cast<DWORD>(Text.length()), Position);
		ScreenBuffer.Write(Position, Text);
	}


// Accessors:

	const COORD& FTextField::GetPosition() const
	{
		return Position;
	}

	const WORD& FTextField::GetAttribute() const
	{
		return Attribute;
	}

	const std::wstring& FTextField::GetText() const
	{
		return Text;
	}

	uint64 FTextField::GetLength() const
	{
		return static_cast<uint64>(Text.length());
	}


// Modifiers:

	FTextField& FTextField::SetPosition(COORD Position)
	{
		this->Position = Position;

		return *this;
	}

	FTextField& FTextField::SetAttribute(WORD Attribute)
	{
		this->Attribute = Attribute;

		return *this;
	}

	FTextField& FTextField::SetText(const std::wstring Text)
	{
		this->Text = Text;

		return *this;
	}


}