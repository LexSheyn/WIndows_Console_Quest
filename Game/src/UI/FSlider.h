#pragma once

namespace wce
{
	class FSlider
	{
	public:

	// Constructors and Destructor:

		 FSlider ();
		~FSlider ();

	// Functions:

		void Draw(class FScreenBuffer& ScreenBuffer);

		void SetRange    (SHORT ValueMin, SHORT ValueMax);
		void SetRange    (FLOAT ValueMin, FLOAT ValueMax);
		void Increase    (LONG Offset = 1i16);
		void Decrease    (LONG Offset = 1i16);

	// Accessors:

		const COORD& GetPosition         () const;
		const WORD&  GetAttributeBack    () const;
		const WORD&  GetAttributeFill    () const;
		const LONG&  GetSizeBack         () const;
		const LONG&  GetSizeFill         () const;

	// Modifiers:

		FSlider& SetPosition         (COORD Position);
		FSlider& SetAttributeBack    (WORD  Attribute);
		FSlider& SetAttributeFill    (WORD  Attribute);
		FSlider& SetSizeBack         (DWORD Size);
		FSlider& SetSizeFill         (DWORD Size);

	private:

	// Variables:

		COORD Coord;
		WORD  AttributeBack;
		WORD  AttributeFill;
		LONG SizeBack;
		LONG SizeFill;

		SHORT ValueMin;
		SHORT ValueMax;
	};
}