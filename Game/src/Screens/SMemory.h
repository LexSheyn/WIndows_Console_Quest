#pragma once

#include "IScreen.h"
#include "../UI/FMemorySlot.h"
#include "../FileManager/MFileManager.h"
#include "../Data/MDataManager.h"

namespace wce
{
	class SMemory : public IScreen
	{
	public:

	// Constructors and Destructor:

		 SMemory    ();
		~SMemory    ();

	// IScreen Intarface:

		void Render    () override;
		void Update    () override;

	private:

	// Private Functions:

		void Init();

	// Components:

		std::map<EButton, FButton>  Buttons;
		std::map<WORD, FMemorySlot> MemorySlots;

	public:

	// IEventListener Interface:

		void OnEvent    (const FEvent* const Event) override;

	private:

	// Event Callbacks:

		void OnApplicationStart    (const FEvent* const Event);
		void OnScreenSwitch        (const FEvent* const Event);
		void OnFontChange          (const FEvent* const Event);
		void OnButtonPress         (const FEvent* const Event);
		void OnKeyPress            (const FEvent* const Event);
		void OnMemorySlotPress     (const FEvent* const Event);
		void OnGameSaveApprove     (const FEvent* const Event);
	};
}