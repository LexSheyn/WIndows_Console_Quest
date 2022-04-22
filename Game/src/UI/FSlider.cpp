#include "../PrecompiledHeaders/wcepch.h"
#include "FSlider.h"

#include "../ScreenBuffer/FScreenBuffer.h"

namespace wce
{
// Constructors and Destructors:

	FSlider::FSlider()
		: Position(COORD{}),
		  AttributeBack(128),
		  AttributeFill(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY),
	//	  AttributeFill(BACKGROUND_RED | BACKGROUND_GREEN |                   BACKGROUND_INTENSITY),
		  SizeBack(10),
		  SizeFill(0)
	{
	}

	FSlider::~FSlider()
	{
	}


// Functions:

	void FSlider::Draw(FScreenBuffer& ScreenBuffer)
	{
		ScreenBuffer.FillWithAttribute(Position, static_cast<DWORD>(SizeBack), AttributeBack);
		ScreenBuffer.FillWithAttribute(Position, static_cast<DWORD>(SizeFill), AttributeFill);
	}

	void FSlider::SetRange(SHORT ValueMin, SHORT ValueMax)
	{
		this->ValueMin = ValueMin;
		this->ValueMax = ValueMax;
	}

	void FSlider::SetRange(FLOAT ValueMin, FLOAT ValueMax)
	{
		this->ValueMin = static_cast<SHORT>(ValueMin);
		this->ValueMax = static_cast<SHORT>(ValueMax);
	}

	void FSlider::Increase(LONG Offset)
	{
		SizeFill += Offset;

		if (SizeFill >= SizeBack)
		{
			SizeFill = SizeBack;
		}
	}

	void FSlider::Decrease(LONG Offset)
	{
		SizeFill -= Offset;

		if (SizeFill < 0)
		{
			SizeFill = 0;
		}
	}


// Accessors:

	const COORD& FSlider::GetPosition() const
	{
		return Position;
	}

	const WORD& FSlider::GetAttributeBack() const
	{
		return AttributeBack;
	}

	const WORD& FSlider::GetAttributeFill() const
	{
		return AttributeFill;
	}

	const LONG& FSlider::GetSizeBack() const
	{
		return SizeBack;
	}

	const LONG& FSlider::GetSizeFill() const
	{
		return SizeFill;
	}


// Modifiers:

	FSlider& FSlider::SetPosition(COORD Position)
	{
		this->Position = Position;

		return *this;
	}

	FSlider& FSlider::SetAttributeBack(WORD Attribute)
	{
		AttributeBack = Attribute;

		return *this;
	}

	FSlider& FSlider::SetAttributeFill(WORD Attribute)
	{
		AttributeFill = Attribute;

		return *this;
	}

	FSlider& FSlider::SetSizeBack(DWORD Size)
	{
		SizeBack = Size;

		return *this;
	}

	FSlider& FSlider::SetSizeFill(DWORD Size)
	{
		SizeFill = Size;

		return *this;
	}


}