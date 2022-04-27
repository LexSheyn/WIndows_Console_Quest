#include "../PrecompiledHeaders/wcepch.h"
#include "SMenu.h"

namespace wce
{
// Constructors and Destructor:

	SMenu::SMenu() : IScreen(EScreen::Menu)
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
		Buttons[EButton::StartGame].SetPosition(COORD{ 10, 10 }).SetWidth(12).SetText(L"Start game");
		Buttons[EButton::Memory   ].SetPosition(COORD{ 10, 12 }).SetWidth(12).SetText(L"Memory"    );
		Buttons[EButton::Settings ].SetPosition(COORD{ 10, 14 }).SetWidth(12).SetText(L"Settings"  );
		Buttons[EButton::Exit     ].SetPosition(COORD{ 10, 16 }).SetWidth(12).SetText(L"Exit"      );
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
				this->OnScreenSwitch(Event);
			}
			break;

			case EEventType::FontChanged:
			{
				this->OnFontChange(Event);
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
			}
		}
	}


// Event Callbacks:

	void SMenu::OnScreenSwitch(const FEvent* const Event)
	{
		if (Event->ScreenData.ToScreen == this->GetName())
		{
			this->Activate();

			for (auto& [Key, Button] : Buttons)
			{
				Button.Enable();
			}
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

	void SMenu::OnFontChange(const FEvent* const Event)
	{
		ScreenBuffer.SetFontSize(Event->FontData.ToSize);
	}

	void SMenu::OnButtonPress(const FEvent* const Event)
	{
		if      ( (Event->ButtonData.ID == Buttons[EButton::StartGame].GetID()) && (Event->ButtonData.MouseButton == FMouseButton::Left) )
		{
			FEventSystem::PushEvent(FEvent(EEventType::ScreenSwitched, FScreenData{ this->GetName(), EScreen::Game }));
		}
		else if ( (Event->ButtonData.ID == Buttons[EButton::Memory].GetID()) && (Event->ButtonData.MouseButton == FMouseButton::Left) )
		{
			FEventSystem::PushEvent(FEvent(EEventType::ScreenSwitched, FScreenData{ this->GetName(), EScreen::Memory }));
		}
		else if ( (Event->ButtonData.ID == Buttons[EButton::Settings].GetID()) && (Event->ButtonData.MouseButton == FMouseButton::Left) )
		{
			FEventSystem::PushEvent(FEvent(EEventType::ScreenSwitched, FScreenData{ this->GetName(), EScreen::Settings }));
		}
		else if ( (Event->ButtonData.ID == Buttons[EButton::Exit].GetID()) && (Event->ButtonData.MouseButton == FMouseButton::Left) )
		{
			FEventSystem::PushEvent(FEvent(EEventType::MenuExit));
		}
	}


}