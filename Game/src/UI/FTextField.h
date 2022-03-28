#pragma once

namespace wce
{
	class FTextField
	{
	public:

	// Constructors and Destructor:

		 FTextField();
		~FTextField();

	// Functions:

		void Disable    ();
		void Enable     ();
		void Draw       (class FScreenBuffer& ScreenBuffer);

	// Accessors:

		const COORD&        GetPosition    () const;
		const std::wstring& GetText        () const;
		const bool8&        IsEnabled      () const;
		uint64              GetLength      () const;

	// Modifiers:

		FTextField& SetPosition    (COORD Position);
		FTextField& SetText        (const std::wstring Text);

	private:

	// Variables:

		std::wstring Text;
		COORD Coord;
		WORD  Attribute;
		bool8 Enabled;
	};
}