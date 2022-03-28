#pragma once

namespace wce
{
	class FMarker
	{
	public:

	// Constructors and Destructor:

		 FMarker ();
		~FMarker ();

	// Functions:

		void Draw(class FScreenBuffer& ScreenBuffer);

	// Accessors:

		const COORD& GetPosition    () const;
		const WORD&  GetAttribute   () const;
		const DWORD& GetSize        () const;


	// Modifiers:

		void SetPosition     (COORD Position);
		void SetAttribute    (WORD Attribute);
		void SetSize         (DWORD Size);


	private:

	// Variables:

		COORD Coord;
		WORD  Attribute;
		DWORD Size;
	};
}