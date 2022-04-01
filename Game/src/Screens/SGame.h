#pragma once

#include "IScreen.h"

namespace wce
{
	class SGame : public IScreen
	{
	public:

	// Constructors and Destructor:

		 SGame ();
		~SGame ();

	// IScreen Intarface:

		void Render    () override;
		void Update    () override;

	private:

	// Private Functions:

		void Init ();

	// Components:

		FTextField                     TextField;
		std::map<EButtonName, FButton> Buttons;

	// Variables:

		WORD Chapter;

	public:

	// IEventListener Interface:

		void OnEvent (const FEvent* const Event) override;

	private:

	// Event Callbacks:

		void ButtonPressCallback    (const FEvent* const Event);
		void KeyPressCallback       (const FEvent* const Event);
	};
}