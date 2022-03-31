#pragma once

#include "IScreen.h"

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
		// Memory slots:

	public:

	// IEventListener Interface:

		void OnEvent (const FEvent* const Event) override;

	private:

	// Event Callbacks:

		// Process Memory Slot

		void ProcessKey(const FEvent* const Event);
	};
}