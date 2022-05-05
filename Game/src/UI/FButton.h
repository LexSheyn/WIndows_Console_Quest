#pragma once

#include "EButton.h"
#include "FTextFIeld.h"
#include "../Input/FMouseButton.h"
#include "../Events/FEventSystem.h"

namespace wce
{
	class FButton : public IEventListener
	{
	public:

	// Constructors and Destructor:

		 FButton    ();
		~FButton    ();

	// Functions:

		void Enable     ();
		void Disable    ();		
		void Draw       (class FScreenBuffer& ScreenBuffer);

	// Accessors:

		const WORD&         GetID           () const;
		const COORD&        GetPosition     () const;
		const SHORT&        GetWidth        () const;
		const WORD&         GetAttribute    () const;
		const std::wstring& GetText         () const;
		const bool&         IsEnabled       () const;

	// Modifiers:

		FButton& SetPosition     (COORD Position);
		FButton& SetWidth        (SHORT Width);
		FButton& SetAttribute    (WORD Attribute);
		FButton& SetText         (const std::wstring& Text);

	private:

	// Private Functions:

		void GenerateID    ();

	// Components:

		FTextField TextField;

	// Variables:

		WORD  ID;
		COORD Position;
		SHORT Width;
		WORD  Attribute;
		bool  Enabled;

		COORD MousePositionLast;
		DWORD MouseButtonStateLast;		

		static constexpr WORD ButtonAttributeEnabled  = BACKGROUND_GREEN | BACKGROUND_BLUE;
		static constexpr WORD ButtonAttributeDisabled = 8;
		static constexpr WORD ButtonAttributeHovered  = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;

	public:

	// IEventListener Interface:

		void OnEvent    (const FEvent* const Event) override;

	private:

	// Event Callbacks:

		void OnMouseMove     (const FEvent* const Event);
		void OnMousePress    (const FEvent* const Event);		
	};
}