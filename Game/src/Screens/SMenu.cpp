#include "../PrecompiledHeaders/wcepch.h"
#include "SMenu.h"

namespace wce
{
// Constructors and Destructor:

	SMenu::SMenu()
		: IScreen(EScreenName::Menu)
	{
		this->Init();

		FEventSystem::Subscribe(EEventType::ApplicationStarted, this);
		FEventSystem::Subscribe(EEventType::ScreenSwitched    , this);
		FEventSystem::Subscribe(EEventType::FontChanged       , this);
		FEventSystem::Subscribe(EEventType::ButtonPressed     , this);
	}

	SMenu::~SMenu()
	{
		FEventSystem::UnsubscribeFromAll(this);
	}


// IScreen Intarface:

	void SMenu::Render()
	{
		if (this->IsActive())
		{
			ScreenBuffer.Clear();

			for (auto&[Key, Button] : Buttons)
			{
				Button.Draw(ScreenBuffer);
			}

			ScreenBuffer.Present();
		}
	}

	void SMenu::Update()
	{

	}


// Private Functions:

	void SMenu::Init()
	{
		Buttons[EButtonName::StartGame].SetPosition(COORD{ 10, 8  }).SetWidth(12).SetName(EButtonName::StartGame).SetText(L"Start game");
		Buttons[EButtonName::Memory   ].SetPosition(COORD{ 10, 10 }).SetWidth(12).SetName(EButtonName::Memory   ).SetText(L"Memory"    ).Disable();
		Buttons[EButtonName::Settings ].SetPosition(COORD{ 10, 12 }).SetWidth(12).SetName(EButtonName::Settings ).SetText(L"Settings"  );
		Buttons[EButtonName::Exit     ].SetPosition(COORD{ 10, 14 }).SetWidth(12).SetName(EButtonName::Exit     ).SetText(L"Exit"      );
	}


// IEventListener Interface:

	void SMenu::OnEvent(const FEvent* const Event)
	{
		switch (Event->GetType())
		{
			case EEventType::ApplicationStarted:
			{}
			break;

			case EEventType::ScreenSwitched:
			{
				this->ScreenSwitchCallback(Event);
			}
			break;

			case EEventType::FontChanged:
			{
				this->FontChangeCallback(Event);
			}
			break;
		}

		if (this->IsActive())
		{
			switch (Event->GetType())
			{
				case EEventType::ButtonPressed:
				{
					this->ButtonPressCallback(Event);
				}
				break;
			}
		}
	}


// Event Callbacks:

	void SMenu::ScreenSwitchCallback(const FEvent* const Event)
	{
		if (Event->ScreenData.ToScreen == this->GetName())
		{
			this->Activate();
		}
	}

	void SMenu::FontChangeCallback(const FEvent* const Event)
	{
		ScreenBuffer.SetFontSize(Event->FontData.ToSize);
	}

	void SMenu::ButtonPressCallback(const FEvent* const Event)
	{
		if      ( (Event->ButtonData.ButtonName == EButtonName::StartGame) && (Event->ButtonData.MouseButton == FMouseButton::Left) )
		{
			this->Deactivate();
		
			FEventSystem::PushEvent(FEvent(EEventType::ScreenSwitched, FScreenData{ this->GetName(), EScreenName::Game }));
		}
		else if ( (Event->ButtonData.ButtonName == EButtonName::Memory) && (Event->ButtonData.MouseButton == FMouseButton::Left) )
		{
			this->Deactivate();
		
			FEventSystem::PushEvent(FEvent(EEventType::ScreenSwitched, FScreenData{ this->GetName(), EScreenName::Memory }));
		}
		else if ( (Event->ButtonData.ButtonName == EButtonName::Settings) && (Event->ButtonData.MouseButton == FMouseButton::Left) )
		{
			this->Deactivate();

			FEventSystem::PushEvent(FEvent(EEventType::ScreenSwitched, FScreenData{ this->GetName(), EScreenName::Settings }));
		}
		else if ( (Event->ButtonData.ButtonName == EButtonName::Exit) && (Event->ButtonData.MouseButton == FMouseButton::Left) )
		{
			this->Deactivate();
		
			FEventSystem::PushEvent(FEvent(EEventType::MenuExit));
		}
	}


}