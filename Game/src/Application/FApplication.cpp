#include "../PrecompiledHeaders/wcepch.h"
#include "FApplication.h"

namespace wce
{
// Constructors and Destructor:

	FApplication::FApplication()
		: ShouldClose (false)
	{
		Console.SetTitle(L"Game v.0.0.0.1").ArrangeToCenter();

		FEventCatcher::Initialize();
		FEventSystem::PushEvent(FEvent(EEventType::ScreenSwitched, FScreenData{ EScreenName::None, EScreenName::Menu }));
		FEventSystem::Subscribe(EEventType::ScreenSwitched, this);
	}

	FApplication::~FApplication()
	{
		FEventSystem::UnsubscribeFromAll(this);
	}


// Functions:

	void FApplication::Run()
	{
		while (!ShouldClose)
		{
			this->Update();

			this->Render();

			std::this_thread::sleep_for(std::chrono::microseconds(33'333)); // ~30 FPS
		}
	}

	void FApplication::Update()
	{
	// Poll Events:

		FEventCatcher::CatchEvents();
		FEventSystem::PollEvents();
	}

	void FApplication::Render()
	{
		Menu.Render();
		Settings.Render();
	}

	void FApplication::OnEvent(const FEvent* const Event)
	{
		if ( (Event->GetType() == EEventType::ScreenSwitched) && (Event->ScreenData.ToScreen == EScreenName::Exit) )
		{
			ShouldClose = true;
		}
	}


}