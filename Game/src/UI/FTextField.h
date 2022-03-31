#pragma once

namespace wce
{
	class FTextField
	{
	public:

	// Constructors and Destructor:

		 FTextField ();
		~FTextField ();

	// Functions:

		void Draw (class FScreenBuffer& ScreenBuffer);

	// Accessors:

		const COORD&        GetPosition     () const;
		const WORD&         GetAttribute    () const;
		const std::wstring& GetText         () const;
		uint64              GetLength       () const;

	// Modifiers:

		FTextField& SetPosition     (COORD Position);
		FTextField& SetAttribute    (WORD Attribute);
		FTextField& SetText         (const std::wstring Text);

	private:

	// Variables:

		COORD        Position;
		WORD         Attribute;
		std::wstring Text;
	};
}