#include "../PrecompiledHeaders/wcepch.h"
#include "SSettings.h"

namespace wce
{
// Constructors and Destructor:

	SSettings::SSettings()
		: IScreen(EScreenName::Settings)
	{
		this->Init();

		FEventSystem::Subscribe(EEventType::ScreenSwitched  , this);
		FEventSystem::Subscribe(EEventType::MouseMoved      , this);
		FEventSystem::Subscribe(EEventType::MouseLeftPressed, this);
		FEventSystem::Subscribe(EEventType::MouseScrolled   , this);
		FEventSystem::Subscribe(EEventType::KeyPressed      , this);
	}

	SSettings::~SSettings()
	{
		FEventSystem::UnsubscribeFromAll(this);
	}


// IScreen Intarface:

	void SSettings::Render()
	{
		ScreenBuffer.Clear();

		for (auto& Field : TextFields)
		{
			Field.second.Draw(ScreenBuffer);
		}

		for (auto& Slider : Sliders)
		{
			Slider.second.Draw(ScreenBuffer);
		}

		Marker.Draw(ScreenBuffer);

		ScreenBuffer.Present();
	}

	void SSettings::Update()
	{
	}


// Private Functions:

	void SSettings::Init()
	{
		TextFields[EScreenField::CharSize].SetPosition(COORD{ 10, 8  }).SetText(L"Character size");
		TextFields[EScreenField::Back    ].SetPosition(COORD{ 10, 16 }).SetText(L"Back");

		Sliders[EScreenField::CharSize].SetPosition(COORD{ 30, 8 }).SetSizeFill(1).SetRange(14i16, 20i16);

		Marker.SetPosition(TextFields[EScreenField::CharSize].GetPosition());
		Marker.SetSize(18);
	}


// IEventListener Interface:

	void SSettings::OnEvent(const FEvent* const Event)
	{
		if (Event->GetType() == EEventType::ScreenSwitched && Event->ScreenData.ToScreen == this->GetName())
		{
			this->Activate();
		}

		if (this->IsActive())
		{
			if (Event->GetType() == EEventType::MouseMoved)
			{
				for (auto& Field : TextFields)
				{
					if (Event->MouseData.dwMousePosition.Y == Field.second.GetPosition().Y)
					{
						Marker.SetPosition(Field.second.GetPosition());
					}
				}
			}
			else if (Event->GetType() == EEventType::MouseLeftPressed)
			{
				if (Event->MouseData.dwMousePosition.Y == TextFields.at(EScreenField::CharSize).GetPosition().Y)
				{
					//
				}
				else if (Event->MouseData.dwMousePosition.Y == TextFields.at(EScreenField::Back).GetPosition().Y)
				{
					this->Deactivate();

					FEventSystem::PushEvent(FEvent(EEventType::ScreenSwitched, FScreenData{ this->GetName(), EScreenName::MainMenu }));
				}
			}
			else if ( (Event->GetType() == EEventType::KeyPressed) && (Event->KeyData.wVirtualKeyCode == FKey::Escape) )
			{
				this->Deactivate();

				FEventSystem::PushEvent(FEvent(EEventType::ScreenSwitched, FScreenData{ this->GetName(), EScreenName::MainMenu }));
			}

			this->Render();
		}
	}


}