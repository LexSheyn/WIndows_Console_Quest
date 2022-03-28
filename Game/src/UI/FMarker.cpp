#include "../PrecompiledHeaders/wcepch.h"
#include "FMarker.h"

#include "../ScreenBuffer/FScreenBuffer.h"

namespace wce
{
// Constructors and Destructor:

	FMarker::FMarker()
		: Coord        (COORD{}),
		  Attribute    (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE),
		  Size         (10)
	{
	}

	FMarker::~FMarker()
	{
	}


// Functions:

	void FMarker::Draw(FScreenBuffer& ScreenBuffer)
	{
		ScreenBuffer.SetOutputAttribute(Attribute, Size, Coord);
	}


// Accessors:

	const COORD& FMarker::GetPosition() const
	{
		return Coord;
	}

	const WORD& FMarker::GetAttribute() const
	{
		return Attribute;
	}

	const DWORD& FMarker::GetSize() const
	{
		return Size;
	}


// Modifiers:

	void FMarker::SetPosition(COORD Position)
	{
		Coord = COORD{ static_cast<SHORT>(Position.X - 1), Position.Y };
	}

	void FMarker::SetAttribute(WORD Attribute)
	{
		this->Attribute = Attribute;
	}

	void FMarker::SetSize(DWORD Size)
	{
		this->Size = Size;
	}


}