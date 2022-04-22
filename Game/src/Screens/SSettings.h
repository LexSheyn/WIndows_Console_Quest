#pragma once

#include "IScreen.h"

namespace wce
{
	class SSettings : public IScreen
	{
	public:

	// Constructors and Destructor:

		 SSettings    ();
		~SSettings    ();

	// IScreen Intarface:

		void Render    () override;
		void Update    () override;

	private:

	// Private Functions:

		void Init    ();

	// Components:

		std::map<EScreenField, FTextField> TextFields;
		std::map<EButton     , FButton>    Buttons;
		std::map<EScreenField, FSlider>    Sliders;

	public:

	// IEventListener Interface:

		void OnEvent    (const FEvent* const Event) override;

	private:

	// Event Callbacks:

		void OnApplicationStart    (const FEvent* const Event);
		void OnApplicationClose    (const FEvent* const Event);
		void OnScreenSwitch        (const FEvent* const Event);
		void OnButtonPress         (const FEvent* const Event);
		void OnKeyPress            (const FEvent* const Event);
	};
}