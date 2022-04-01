#include "../PrecompiledHeaders/wcepch.h"
#include "SGame.h"

namespace wce
{
// Constructors and Destructor:

	SGame::SGame()
		: IScreen(EScreenName::Game)
	{
		this->Init();

		FEventSystem::Subscribe(EEventType::ScreenSwitched, this);
		FEventSystem::Subscribe(EEventType::FontChanged   , this);
		FEventSystem::Subscribe(EEventType::ButtonPressed , this);
		FEventSystem::Subscribe(EEventType::KeyPressed    , this);
	}

	SGame::~SGame()
	{
		FEventSystem::UnsubscribeFromAll(this);
	}


// IScreen Interface:

	void SGame::Render()
	{
		if (this->IsActive())
		{
			ScreenBuffer.Clear();

			TextField.Draw(ScreenBuffer);

			for (auto& [Key, Button] : Buttons)
			{
				Button.Draw(ScreenBuffer);
			}

			ScreenBuffer.Present();
		}
	}

	void SGame::Update()
	{
	}


// Private Functions:

	void SGame::Init()
	{
		TextField.SetPosition(COORD{10, 5}).SetText(L"Here we are! Finally met you here! Come, come!");

		Buttons[EButtonName::Choice_1].SetPosition(COORD{ 10, 23 }).SetWidth(30).SetName(EButtonName::Choice_1).SetText(L"WTF?");
		Buttons[EButtonName::Choice_2].SetPosition(COORD{ 10, 25 }).SetWidth(30).SetName(EButtonName::Choice_2).SetText(L"It was not me!");
		Buttons[EButtonName::Choice_3].SetPosition(COORD{ 50, 23 }).SetWidth(30).SetName(EButtonName::Choice_3).SetText(L"Where the WC room?");
		Buttons[EButtonName::Choice_4].SetPosition(COORD{ 50, 25 }).SetWidth(30).SetName(EButtonName::Choice_4).SetText(L"DESTROY EVERYTHING!!!");
	}


// IEventListener Interface:

	void SGame::OnEvent(const FEvent* const Event)
	{
		if (!this->IsActive())
		{
			if (Event->GetType() == EEventType::ScreenSwitched && Event->ScreenData.ToScreen == this->GetName())
			{
				this->Activate();
			}
			else if (Event->GetType() == EEventType::FontChanged)
			{
				ScreenBuffer.SetFontSize(Event->FontData.ToSize);
			}
		}
		else
		{
			switch (Event->GetType())
			{
				case EEventType::ButtonPressed:
				{
					ButtonPressCallback(Event);
				}
				break;

				case EEventType::KeyPressed:
				{
					KeyPressCallback(Event);
				}
				break;
			}
		}
	}


// Event Callbacks:

	void SGame::ButtonPressCallback(const FEvent* const Event)
	{
	}

	void SGame::KeyPressCallback(const FEvent* const Event)
	{
		if (Event->KeyData.wVirtualKeyCode == FKey::Escape)
		{
			this->Deactivate();

			FEventSystem::PushEvent(FEvent(EEventType::ScreenSwitched, FScreenData{ this->GetName(), EScreenName::Menu }));
		}
	}


}