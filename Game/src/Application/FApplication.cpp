#include "../PrecompiledHeaders/wcepch.h"
#include "FApplication.h"

namespace wce
{
// Constructors and Destructor:

	FApplication::FApplication()
		: ShouldClose (false)
	{
		this->Init();

		Console.SetTitle(L"Game v.0.0.0.1");

		FEventCatcher::Initialize();

		FEventSystem::PushEvent(FEvent(EEventType::ApplicationStarted));
		FEventSystem::PushEvent(FEvent(EEventType::ScreenSwitched, FScreenData{ EScreenName::None, EScreenName::Menu }));

		FEventSystem::Subscribe(EEventType::MenuExit, this);
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

	// Game:

	//	Game.Update();
	}

	void FApplication::Render()
	{
		Menu.Render();
		Game.Render();
		Settings.Render();
	}


// Private Functions:

	void FApplication::Init()
	{
		MFileManager::CreateDirectory(L"Memory");
		MFileManager::CreateDirectory(L"Config");
	}


// IEventListener Interface:

	void FApplication::OnEvent(const FEvent* const Event)
	{
		if (Event->GetType() == EEventType::MenuExit)
		{
			ShouldClose = true;

			FEventSystem::PushEvent(FEvent(EEventType::ApplicationClosed));
		}
	}


}