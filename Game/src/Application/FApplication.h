#pragma once

#include "../Window/FConsole.h"
#include "../SFX/FSoundSystem.h"
#include "../Screens/SMenu.h"
#include "../Screens/SGame.h"
#include "../Screens/SMemory.h"
#include "../Screens/SSettings.h"

namespace wce
{
	class FApplication : public IEventListener
	{
	public:

	// Constructors and Destructor:

		 FApplication();
		~FApplication();

	// Functions:

		void Run       ();
		void Update    ();
		void Render    ();

	private:

	// Private Functons:

		void Init ();

	// Variables:

		bool8 ShouldClose;

	// Screens:

		SMenu     Menu;
		SGame     Game;
		SMemory   Memory;
		SSettings Settings;

	// Window:

		FConsole Console;

	// IEventListener Interface:

		void OnEvent(const FEvent* const Event) override;

	// Event Callbacks:

		void MenuExitCallback (const FEvent* const Event);
	};
}