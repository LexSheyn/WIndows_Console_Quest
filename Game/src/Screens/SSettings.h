#pragma once

#include "IScreen.h"

namespace wce
{
	class SSettings : public IScreen
	{
	public:

	// Constructors and Destructor:

		 SSettings ();
		~SSettings ();

	// IScreen Intarface:

		void Render    () override;
		void Update    () override;

	private:

	// Private Functions:

		void Init ();

	// Components:

		std::map<EScreenField, FTextField> TextFields;
		std::map<EButtonName , FButton>    Buttons;
		std::map<EScreenField, FSlider>    Sliders;

	public:

	// IEventListener Interface:

		void OnEvent (const FEvent* const Event) override;

	private:

	// Event Callbacks:

		void ButtonPressCallback (const FEvent* const Event);
		void KeyPressCallback    (const FEvent* const Event);
	};
}