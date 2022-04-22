#include "../PrecompiledHeaders/wcepch.h"
#include "SGame.h"

namespace wce
{
// Constructors and Destructor:

	SGame::SGame()
		: IScreen(EScreen::Game)
	{
		this->Init();

		FEventSystem::Subscribe(EEventType::ApplicationStarted, this);
		FEventSystem::Subscribe(EEventType::ApplicationClosed , this);
		FEventSystem::Subscribe(EEventType::ScreenSwitched    , this);
		FEventSystem::Subscribe(EEventType::FontChanged       , this);
		FEventSystem::Subscribe(EEventType::ButtonPressed     , this);
		FEventSystem::Subscribe(EEventType::KeyPressed        , this);
		FEventSystem::Subscribe(EEventType::GameSaveRequested , this);
		FEventSystem::Subscribe(EEventType::GameLoaded        , this);
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

		Buttons[EButton::Choice_0].SetText(Choices[Chapter][0].Text);
		Buttons[EButton::Choice_1].Disable();
		Buttons[EButton::Choice_2].Disable();
		Buttons[EButton::Choice_3].Disable();
		
		if (Choices[Chapter].size() > 1u)
		{
			Buttons[EButton::Choice_1].SetText(Choices[Chapter][1].Text).Enable();
		}
		
		if (Choices[Chapter].size() > 2u)
		{
			Buttons[EButton::Choice_2].SetText(Choices[Chapter][2].Text).Enable();
		}
		
		if (Choices[Chapter].size() > 3u)
		{
			Buttons[EButton::Choice_3].SetText(Choices[Chapter][3].Text).Enable();
		}
	}


// Private Functions:

	void SGame::Init()
	{
		TextFields[0].SetPosition(COORD{ 10, 5 });

		Buttons[EButton::Choice_0].SetPosition(COORD{ 10, 22 }).SetWidth(30);
		Buttons[EButton::Choice_1].SetPosition(COORD{ 10, 24 }).SetWidth(30);
		Buttons[EButton::Choice_2].SetPosition(COORD{ 50, 22 }).SetWidth(30);
		Buttons[EButton::Choice_3].SetPosition(COORD{ 50, 24 }).SetWidth(30);
	}


// IEventListener Interface:

	void SGame::OnEvent(const FEvent* const Event)
	{
		switch (Event->GetType())
		{
			case EEventType::ApplicationStarted:
			{
				this->OnApplicationStart(Event);
			}
			break;

			case EEventType::ApplicationClosed:
			{
				this->OnApplicationClose(Event);
			}
			break;

			case EEventType::ScreenSwitched:
			{
				this->OnScreenSwitch(Event);
			}
			break;

			case EEventType::FontChanged:
			{
				this->OnFontChange(Event);
			}
			break;

			case EEventType::GameSaveRequested:
			{
				this->OnGameSave(Event);
			}
			break;

			case EEventType::GameLoaded:
			{
				this->OnGameLoad(Event);
			}
			break;
		}

		if (this->IsActive())
		{
			switch (Event->GetType())
			{
				case EEventType::ButtonPressed:
				{
					this->OnButtonPress(Event);
				}
				break;

				case EEventType::KeyPressed:
				{
					this->OnKeyPress(Event);
				}
				break;
			}
		}
	}


// Event s:

	void SGame::OnApplicationStart(const FEvent* const Event)
	{
		MDataManager::LoadContent(Dialogs, Choices, L"Content/Content.tale");

		this->Update();
	}

	void SGame::OnApplicationClose(const FEvent* const Event)
	{
	}

	void SGame::OnScreenSwitch(const FEvent* const Event)
	{
		if (Event->ScreenData.ToScreen == this->GetName())
		{
			this->Activate();

			for (auto& [Key, Button] : Buttons)
			{
				Button.Enable();
			}

			this->Update();
		}
		else
		{
			this->Deactivate();

			for (auto& [Key, Button] : Buttons)
			{
				Button.Disable();
			}
		}
	}

	void SGame::OnFontChange(const FEvent* const Event)
	{
		ScreenBuffer.SetFontSize(Event->FontData.ToSize);
	}

	void SGame::OnButtonPress(const FEvent* const Event)
	{
		if      ( (Event->ButtonData.ID == Buttons.at(EButton::Choice_0).GetID()) && (Event->ButtonData.MouseButton == FMouseButton::Left) )
		{
			Chapter = Choices.at(Chapter)[0].ToChapter;
		}
		else if ( (Event->ButtonData.ID == Buttons.at(EButton::Choice_1).GetID()) && (Event->ButtonData.MouseButton == FMouseButton::Left) )
		{
			Chapter = Choices.at(Chapter)[1].ToChapter;
		}
		else if ( (Event->ButtonData.ID == Buttons.at(EButton::Choice_2).GetID()) && (Event->ButtonData.MouseButton == FMouseButton::Left) )
		{
			Chapter = Choices.at(Chapter)[2].ToChapter;
		}
		else if ( (Event->ButtonData.ID == Buttons.at(EButton::Choice_3).GetID()) && (Event->ButtonData.MouseButton == FMouseButton::Left) )
		{
			Chapter = Choices.at(Chapter)[3].ToChapter;
		}

		this->Update();
	}

	void SGame::OnKeyPress(const FEvent* const Event)
	{
		if (Event->KeyData.wVirtualKeyCode == FKey::Escape)
		{
			FEventSystem::PushEvent(FEvent(EEventType::ScreenSwitched, FScreenData{ this->GetName(), EScreen::Menu }));
		}
	}

	void SGame::OnGameSave(const FEvent* const Event)
	{
		FGameData Data;

		std::wstring TimeReceived = FTimeStamp::TimeAsString();
		std::wstring DateReceived = FTimeStamp::DateAsString();

		wmemcpy_s(Data.Time, 9 , TimeReceived.c_str(), 9);
		wmemcpy_s(Data.Date, 12, DateReceived.c_str(), 12);

		Data.Chapter      = Chapter;
		Data.MemorySlotID = Event->MemorySlotData.ID;

		FEventSystem::PushEvent(FEvent(EEventType::GameSaveApproved, Data));
	}

	void SGame::OnGameLoad(const FEvent* const Event)
	{
		Chapter = Event->GameData.Chapter;

		this->Update();
	}


}