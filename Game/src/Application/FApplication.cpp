#include "../PrecompiledHeaders/wcepch.h"
#include "FApplication.h"

namespace wce
{
// Constructors and Destructor:

	FApplication::FApplication()
		: ShouldClose (false)
	{
		this->Init();

		FEventCatcher::Initialize();

		FEventSystem::Subscribe(EEventType::ApplicationClosed, this);
		FEventSystem::Subscribe(EEventType::MenuExit         , this);

		FEventSystem::PushEvent(FEvent(EEventType::ApplicationStarted));
		FEventSystem::PushEvent(FEvent(EEventType::ScreenSwitched, FScreenData{ EScreen::None, EScreen::Menu }));
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

	// Sound system:

		SoundSystem.Update();
	}

	void FApplication::Render()
	{
		Menu.Render();
		Game.Render();
		Memory.Render();
		Settings.Render();
	}


// Private Functions:

	void FApplication::Init()
	{
		Console.SetTitle(L"Ultimate Super Quest 3000");

		MFileManager::CreateDirectory(L"Config");
		MFileManager::CreateDirectory(L"Content");
		MFileManager::CreateDirectory(L"Memory");
		MFileManager::CreateDirectory(L"Resources");
		MFileManager::CreateDirectory(L"Resources/Sound");
		MFileManager::CreateDirectory(L"Resources/Music");
		MFileManager::CreateDirectory(L"Resources/Icons");
	}


// IEventListener Interface:

	void FApplication::OnEvent(const FEvent* const Event)
	{
		switch (Event->GetType())
		{
			case EEventType::ApplicationClosed:
			{
				this->OnApplication(Event);
			}
			break;

			case EEventType::MenuExit:
			{
				this->OnMenuExit(Event);
			}
			break;
		}
	}


// Event Callbacks:

	void FApplication::OnApplication(const FEvent* const Event)
	{
		ShouldClose = true;
	}

	void FApplication::OnMenuExit(const FEvent* const Event)
	{
		FEventSystem::PushEvent(FEvent(EEventType::ApplicationClosed));
	}


}