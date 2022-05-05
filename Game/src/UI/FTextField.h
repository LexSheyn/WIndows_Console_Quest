#pragma once

namespace wce
{
	class FTextField
	{
	public:

	// Constructors and Destructor:

		 FTextField    ();
		~FTextField    ();

	// Functions:

		void Enable     ();
		void Disable    ();
		void Draw       (class FScreenBuffer& ScreenBuffer);

	// Accessors:

		const COORD&        GetPosition     () const;
		const WORD&         GetAttribute    () const;
		const std::wstring& GetText         () const;
		size_t              GetLength       () const;

	// Modifiers:

		FTextField& SetPosition     (COORD Position);
		FTextField& SetAttribute    (WORD Attribute);
		FTextField& SetText         (const std::wstring& Text);

	private:

	// Variables:

		COORD        Position;
		WORD         Attribute;
		std::wstring Text;
		bool         Enabled;

		static constexpr WORD TextAttributeEnabled  = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
		static constexpr WORD TextAttributeDisabled = 8;
	};
}