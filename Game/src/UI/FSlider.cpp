#include "../PrecompiledHeaders/wcepch.h"
#include "FSlider.h"

#include "../ScreenBuffer/FScreenBuffer.h"

namespace wce
{
// Constructors and Destructors:

	FSlider::FSlider()
		: Coord(COORD{}),
		  AttributeBack(128),
		  AttributeFill(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY),
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
		ScreenBuffer.FillWithAttribute(AttributeBack, SizeBack, Coord);
		ScreenBuffer.FillWithAttribute(AttributeFill, SizeFill, Coord);
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

	void FSlider::Update(SHORT Value)
	{
		SizeFill = 10u * (Value / ValueMax);
	}

	void FSlider::Update(FLOAT Value)
	{
		SizeFill = 10u * (static_cast<SHORT>(Value) / ValueMax);
	}


// Accessors:

	const COORD& FSlider::GetPosition() const
	{
		return Coord;
	}

	const WORD& FSlider::GetAttributeBack() const
	{
		return AttributeBack;
	}

	const WORD& FSlider::GetAttributeFill() const
	{
		return AttributeFill;
	}

	const DWORD& FSlider::GetSizeBack() const
	{
		return SizeBack;
	}

	const DWORD& FSlider::GetSizeFill() const
	{
		return SizeFill;
	}


// Modifiers:

	FSlider& FSlider::SetPosition(COORD Position)
	{
		Coord = Position;

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