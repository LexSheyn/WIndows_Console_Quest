#pragma once

#include "EScreenName.h"
#include "EScreenField.h"
#include "../Input/FKey.h"
#include "../ScreenBuffer/FScreenBuffer.h"
#include "../UI/FTextField.h"
#include "../UI/FSlider.h"
#include "../UI/FMarker.h"

namespace wce
{
	class IScreen : public IEventListener
	{
	protected:

	// Constructors and Destructor:

		         IScreen(EScreenName Name);
		virtual ~IScreen();

	// Intarface:

		virtual void Render    () = 0;
		virtual void Update    () = 0;

	// Functions:

		void Activate      ();
		void Deactivate    ();

	// Accessors:

		const EScreenName& GetName     () const;
		const bool8&       IsActive    () const;

	// Components:

		FScreenBuffer                                ScreenBuffer;
		std::unordered_map<EScreenField, FTextField> TextFields;
		std::unordered_map<EScreenField, FSlider>    Sliders;
		FMarker                                      Marker;

	private:

	// Variables:

		EScreenName Name;
		bool8       IsActivated;

	public:

	// IEventListener Interface:

		virtual void OnEvent(const FEvent* const Event) override = 0;
	};
}