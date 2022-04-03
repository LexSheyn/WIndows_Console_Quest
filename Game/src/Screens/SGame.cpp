#include "../PrecompiledHeaders/wcepch.h"
#include "SGame.h"

namespace wce
{
// Constructors and Destructor:

	SGame::SGame()
		: IScreen(EScreenName::Game)
	{
		this->Init();

		FEventSystem::Subscribe(EEventType::ApplicationStarted, this);
		FEventSystem::Subscribe(EEventType::ApplicationClosed , this);
		FEventSystem::Subscribe(EEventType::ScreenSwitched    , this);
		FEventSystem::Subscribe(EEventType::FontChanged       , this);
		FEventSystem::Subscribe(EEventType::ButtonPressed     , this);
		FEventSystem::Subscribe(EEventType::KeyPressed        , this);
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

			for (size_t i = 0u; i < Dialogs[Chapter].size(); i++)
			{
				TextFields[i].Draw(ScreenBuffer);
			}

			for (auto& [Key, Button] : Buttons)
			{
				if (Button.IsEnabled())
				{
					Button.Draw(ScreenBuffer);
				}				
			}

			ScreenBuffer.Present();
		}
	}

	void SGame::Update()
	{
		for (size_t i = 0u; i < Dialogs[Chapter].size(); i++)
		{
			TextFields[i].SetPosition(COORD{ 10, static_cast<SHORT>(5 + i) }).SetText(Dialogs[Chapter][i]);
		}

		Buttons[EButtonName::Choice_0].SetText(Choices[Chapter][0].Text);
		Buttons[EButtonName::Choice_1].Disable();
		Buttons[EButtonName::Choice_2].Disable();
		Buttons[EButtonName::Choice_3].Disable();
		
		if (Choices[Chapter].size() > 1u)
		{
			Buttons[EButtonName::Choice_1].SetText(Choices[Chapter][1].Text).Enable();
		}
		
		if (Choices[Chapter].size() > 2u)
		{
			Buttons[EButtonName::Choice_2].SetText(Choices[Chapter][2].Text).Enable();
		}
		
		if (Choices[Chapter].size() > 3u)
		{
			Buttons[EButtonName::Choice_3].SetText(Choices[Chapter][3].Text).Enable();
		}
	}


// Private Functions:

	void SGame::Init()
	{
		TextFields[0].SetPosition(COORD{ 10, 5 });

		Buttons[EButtonName::Choice_0].SetPosition(COORD{ 10, 23 }).SetWidth(30).SetName(EButtonName::Choice_0);
		Buttons[EButtonName::Choice_1].SetPosition(COORD{ 10, 25 }).SetWidth(30).SetName(EButtonName::Choice_1);
		Buttons[EButtonName::Choice_2].SetPosition(COORD{ 50, 23 }).SetWidth(30).SetName(EButtonName::Choice_2);
		Buttons[EButtonName::Choice_3].SetPosition(COORD{ 50, 25 }).SetWidth(30).SetName(EButtonName::Choice_3);
	}


// IEventListener Interface:

	void SGame::OnEvent(const FEvent* const Event)
	{
		switch (Event->GetType())
		{
			case EEventType::ApplicationStarted:
			{
				this->ApplicationStartCallback(Event);
			}
			break;

			case EEventType::ApplicationClosed:
			{
				this->ApplicationCloseCallback(Event);
			}
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

	void SGame::ApplicationStartCallback(const FEvent* const Event)
	{
		MDataManager::LoadContent(Dialogs, Choices, L"Content/Content.tale");

		this->Update();
	}

	void SGame::ApplicationCloseCallback(const FEvent* const Event)
	{
		FGameData Data;

		Data.Time    = L"Dummy Time: 11:11:11";
		Data.Date    = L"Dummy Date: 22/22/22";
		Data.Chapter = Chapter;

		MDataManager::SaveGame(Data, L"Memory/0001.mem");
	}

	void SGame::ScreenSwitchCallback(const FEvent* const Event)
	{
		if (Event->ScreenData.ToScreen == this->GetName())
		{
			this->Activate();
		}
	}

	void SGame::FontChangeCallback(const FEvent* const Event)
	{
		ScreenBuffer.SetFontSize(Event->FontData.ToSize);
	}

	void SGame::ButtonPressCallback(const FEvent* const Event)
	{
		if      ( (Event->ButtonData.ButtonName == EButtonName::Choice_0) && (Event->ButtonData.MouseButton == FMouseButton::Left) )
		{
			Chapter = Choices.at(Chapter)[0].ToChapter;
		}
		else if ( (Event->ButtonData.ButtonName == EButtonName::Choice_1) && (Event->ButtonData.MouseButton == FMouseButton::Left) )
		{
			Chapter = Choices.at(Chapter)[1].ToChapter;
		}
		else if ( (Event->ButtonData.ButtonName == EButtonName::Choice_2) && (Event->ButtonData.MouseButton == FMouseButton::Left) )
		{
			Chapter = Choices.at(Chapter)[2].ToChapter;
		}
		else if ( (Event->ButtonData.ButtonName == EButtonName::Choice_3) && (Event->ButtonData.MouseButton == FMouseButton::Left) )
		{
			Chapter = Choices.at(Chapter)[3].ToChapter;
		}

		this->Update();
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