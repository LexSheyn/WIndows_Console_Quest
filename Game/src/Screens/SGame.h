#pragma once

#include "IScreen.h"

namespace wce
{
	class SGame : public IScreen
	{
	public:

	// Constructors and Destructor:

		 SGame    ();
		~SGame    ();

	// IScreen Intarface:

		void Render    () override;
		void Update    () override;

	private:

	// Private Functions:

		void Init    ();

	// Components:

		std::map<size_t, FTextField> TextFields;
		std::map<EButton, FButton>   Buttons;

	// Variables:

		WORD Chapter;
		std::map<WORD, std::vector<std::wstring>> Dialogs;
		std::map<WORD, std::vector<FChoice>>      Choices;

	public:

	// IEventListener Interface:

		void OnEvent    (const FEvent* const Event) override;

	private:

	// Event Callbacks:

		void OnApplicationStart    (const FEvent* const Event);
		void OnApplicationClose    (const FEvent* const Event);
		void OnScreenSwitch        (const FEvent* const Event);
		void OnFontChange          (const FEvent* const Event);
		void OnButtonPress         (const FEvent* const Event);
		void OnKeyPress            (const FEvent* const Event);
		void OnGameSave            (const FEvent* const Event);
		void OnGameLoad            (const FEvent* const Event);
	};
}