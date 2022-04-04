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

		std::map<size_t, FTextField> TextFields;
		std::map<EButton, FButton>   Buttons;

	// Variables:

		WORD Chapter;
		std::map<WORD, std::vector<std::wstring>> Dialogs;
		std::map<WORD, std::vector<FChoice>>      Choices;

	public:

	// IEventListener Interface:

		void OnEvent (const FEvent* const Event) override;

	private:

	// Event Callbacks:

		void ApplicationStartCallback    (const FEvent* const Event);
		void ApplicationCloseCallback    (const FEvent* const Event);
		void ScreenSwitchCallback        (const FEvent* const Event);
		void FontChangeCallback          (const FEvent* const Event);
		void ButtonPressCallback         (const FEvent* const Event);
		void KeyPressCallback            (const FEvent* const Event);
		void GameDataRequestCallback     (const FEvent* const Event);
		void GameLoadCallback            (const FEvent* const Event);
	};
}