#include "../PrecompiledHeaders/wcepch.h"
#include "FTextField.h"

#include "../ScreenBuffer/FScreenBuffer.h"

namespace wce
{
// Constructors and Destructor:

	FTextField::FTextField()
		: Position  (COORD{}),
		  Attribute (FOREGROUND_GREEN | FOREGROUND_BLUE),
		  Enabled   (true)
	{
		Text.reserve(120);
	}

	FTextField::~FTextField()
	{
	}


// Functions:

	void FTextField::Enable()
	{
		this->SetAttribute(TextAttributeEnabled);

		Enabled = true;
	}

	void FTextField::Disable()
	{
		this->SetAttribute(TextAttributeDisabled);

		Enabled = false;
	}

	void FTextField::Draw(FScreenBuffer& ScreenBuffer)
	{
		ScreenBuffer.FillWithAttribute(Position, static_cast<DWORD>(Text.length()), Attribute);
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

	size_t FTextField::GetLength() const
	{
		return Text.length();
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

	FTextField& FTextField::SetText(const std::wstring& Text)
	{
		this->Text = Text;

		return *this;
	}


}