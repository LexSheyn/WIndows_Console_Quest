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
		std::map<EButton , FButton>    Buttons;
		std::map<EScreenField, FSlider>    Sliders;

	public:

	// IEventListener Interface:

		void OnEvent (const FEvent* const Event) override;

	private:

	// Event Callbacks:

		void ApplicationStartCallback    (const FEvent* const Event);
		void ApplicationCloseCallback    (const FEvent* const Event);
		void ScreenSwitchCallback        (const FEvent* const Event);
		void ButtonPressCallback         (const FEvent* const Event);
		void KeyPressCallback            (const FEvent* const Event);
	};
}