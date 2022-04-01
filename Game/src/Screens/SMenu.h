#pragma once

#include "IScreen.h"

namespace wce
{
	class SMenu : IScreen
	{
	public:

	// Constructors and Destructor:

		 SMenu ();
		~SMenu ();

	// IScreen Interface:

		void Render    () override;
		void Update    () override;

	private:

	// Private Functions:

		void Init ();

	// Components:

		std::map<EButtonName, FButton> Buttons;

	public:

	// IEventListener Interface:

		void OnEvent (const FEvent* const Event) override;

	private:

	// Event Callbacks:

		void ScreenSwitchCallback    (const FEvent* const Event);
		void FontChangeCallback      (const FEvent* const Event);
		void ButtonPressCallback     (const FEvent* const Event);
	};
}