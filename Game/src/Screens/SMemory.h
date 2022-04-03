#pragma once

#include "IScreen.h"
#include "../UI/FMemorySlot.h"

namespace wce
{
	class SMemory : public IScreen
	{
	public:

	// Constructors and Destructor:

		 SMemory ();
		~SMemory ();

	// IScreen Intarface:

		void Render    () override;
		void Update    () override;

	private:

	// Private Functions:

		void Init();

	// Components:

		std::map<EScreenField, FButton> Buttons;
		std::vector<FMemorySlot> MemorySlots;

	public:

	// IEventListener Interface:

		void OnEvent (const FEvent* const Event) override;

	private:

	// Event Callbacks:

		void ApplicationStartCallback    (const FEvent* const Event);
		void ScreenSwitchCallback        (const FEvent* const Event);
		void FontChangeCallback          (const FEvent* const Event);
		void KeyPressCallback            (const FEvent* const Event);
	};
}