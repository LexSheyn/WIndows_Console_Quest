#include "../PrecompiledHeaders/wcepch.h"
#include "SMenu.h"

namespace wce
{
// Constructors and Destructor:

	SMenu::SMenu()
		: IScreen(EScreenName::MainMenu)
	{
		this->Init();

		FEventSystem::Subscribe(EEventType::ScreenSwitched  , this);
		FEventSystem::Subscribe(EEventType::MouseMoved      , this);
		FEventSystem::Subscribe(EEventType::MouseLeftPressed, this);
		FEventSystem::Subscribe(EEventType::FontChanged     , this);
	}

	SMenu::~SMenu()
	{
		FEventSystem::UnsubscribeFromAll(this);
	}


// IScreen Intarface:

	void SMenu::Render()
	{
		ScreenBuffer.Clear();

		for (auto& Field : TextFields)
		{
			Field.second.Draw(ScreenBuffer);
		}
		
		Marker.Draw(ScreenBuffer);

		ScreenBuffer.Present();
	}

	void SMenu::Update()
	{
		// To do...
	}


// Private Functions:

	void SMenu::Init()
	{
		TextFields[EScreenField::Play    ].SetPosition(COORD{ 10, 8  }).SetText(L"Play");
		TextFields[EScreenField::Save    ].SetPosition(COORD{ 10, 10 }).SetText(L"Save").Disable();
		TextFields[EScreenField::Load    ].SetPosition(COORD{ 10, 12 }).SetText(L"Load").Disable();
		TextFields[EScreenField::Settings].SetPosition(COORD{ 10, 14 }).SetText(L"Settings");
		TextFields[EScreenField::Exit    ].SetPosition(COORD{ 10, 16 }).SetText(L"Exit");

		Marker.SetPosition(TextFields[EScreenField::Play].GetPosition());
		Marker.SetSize(12);
	}


// IEventListener Interface:

	void SMenu::OnEvent(const FEvent* const Event)
	{
		if (Event->GetType() == EEventType::ScreenSwitched && Event->ScreenData.ToScreen == this->GetName())
		{
			this->Activate();
		}
		else if (Event->GetType() == EEventType::FontChanged)
		{
			ScreenBuffer.SetFontHeight(Event->FontData.ToHeight);
		}

		if (this->IsActive())
		{
			if (Event->GetType() == EEventType::MouseMoved)
			{
				for (auto& Field : TextFields)
				{
					if ( (Event->MouseData.dwMousePosition.Y == Field.second.GetPosition().Y) && Field.second.IsEnabled())
					{
						Marker.SetPosition(Field.second.GetPosition());
					}
				}
			}
			else if (Event->GetType() == EEventType::MouseLeftPressed)
			{
				if      (Marker.GetPosition().Y == TextFields.at(EScreenField::Play).GetPosition().Y)
				{
					//
				}
				else if (Marker.GetPosition().Y == TextFields.at(EScreenField::Settings).GetPosition().Y)
				{
					this->Deactivate();

					FEventSystem::PushEvent(FEvent(EEventType::ScreenSwitched, FScreenData{ this->GetName(), EScreenName::Settings }));
				}
				else if (Marker.GetPosition().Y == TextFields.at(EScreenField::Exit).GetPosition().Y)
				{
					this->Deactivate();

					FEventSystem::PushEvent(FEvent(EEventType::ScreenSwitched, FScreenData{ this->GetName(), EScreenName::Exit }));
				}
			}

			this->Render();
		}
	}


}