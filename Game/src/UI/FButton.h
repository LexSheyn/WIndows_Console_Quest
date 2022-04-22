#pragma once

#include "EButton.h"
#include "FTextFIeld.h"
#include "../Input/FMouseButton.h"

namespace wce
{
	class FButton : public IEventListener
	{
	public:

	// Constructors and Destructor:

		 FButton    ();
		~FButton    ();

	// Functions:

		void Disable    ();
		void Enable     ();
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

		WORD  ID;
		COORD Position;
		SHORT Width;
		WORD  Attribute;
		bool  Enabled;

		COORD MousePositionLast;
		DWORD MouseButtonStateLast;

		FTextField TextField;

	//	static constexpr WORD ButtonEnabledAttribute  = 128;
	//	static constexpr WORD ButtonEnabledAttribute  = BACKGROUND_RED | BACKGROUND_GREEN ;
	//	static constexpr WORD ButtonEnabledAttribute  = BACKGROUND_RED                    | BACKGROUND_BLUE;
		static constexpr WORD ButtonEnabledAttribute  =                  BACKGROUND_GREEN | BACKGROUND_BLUE;
		static constexpr WORD ButtonDisabledAttribute = 8;
		static constexpr WORD ButtonHoveredAttribute  = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
		
		static constexpr WORD TextEnabledAttribute    = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
		static constexpr WORD TextDisabledAttribute   = 8;

	public:

	// IEventListener Interface:

		void OnEvent    (const FEvent* const Event) override;

	private:

	// Event Callbacks:

		void OnMouseMove     (const FEvent* const Event);
		void OnMousePress    (const FEvent* const Event);		
	};
}