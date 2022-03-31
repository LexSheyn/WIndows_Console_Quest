#include "../PrecompiledHeaders/wcepch.h"
#include "SSettings.h"

namespace wce
{
// Constructors and Destructor:

	SSettings::SSettings()
		: IScreen(EScreenName::Settings)
	{
		this->Init();

		FEventSystem::Subscribe(EEventType::ScreenSwitched, this);
		FEventSystem::Subscribe(EEventType::ButtonPressed , this);
		FEventSystem::Subscribe(EEventType::KeyPressed    , this);
	}

	SSettings::~SSettings()
	{
		FEventSystem::UnsubscribeFromAll(this);
	}


// IScreen Intarface:

	void SSettings::Render()
	{
		if (this->IsActive())
		{
			ScreenBuffer.Clear();

			for (auto&[Key, Field] : TextFields)
			{
				Field.Draw(ScreenBuffer);
			}

			for (auto&[Key, Button] : Buttons)
			{
				Button.Draw(ScreenBuffer);
			}

			for (auto&[Key, Slider] : Sliders)
			{
				Slider.Draw(ScreenBuffer);
			}

			ScreenBuffer.Present();
		}
	}

	void SSettings::Update()
	{
	}


// Private Functions:

	void SSettings::Init()
	{
	// Text:

		TextFields[EScreenField::CharacterSize].SetPosition(COORD{ 10, 8  }).SetText(L"Character size");
		TextFields[EScreenField::MusicVolume  ].SetPosition(COORD{ 10, 10 }).SetText(L"Music volume"  );

	// Buttons and Sliders:

		Buttons[EButtonName::Back].SetPosition(COORD{ 10, 14 }).SetWidth(12).SetName(EButtonName::Back).SetText(L"Back");

		Sliders[EScreenField::CharacterSize   ].SetPosition(COORD{ 30, 8  }).SetSizeFill(0).SetRange(ScreenBuffer.GetFontSizeMin(), ScreenBuffer.GetFontSizeMax());
		Buttons[EButtonName::CharacterSizePlus ].SetPosition(COORD{ 41, 8 }).SetWidth(3).SetName(EButtonName::CharacterSizePlus ).SetText(L"+");
		Buttons[EButtonName::CharacterSizeMinus].SetPosition(COORD{ 45, 8 }).SetWidth(3).SetName(EButtonName::CharacterSizeMinus).SetText(L"-");

		Sliders[EScreenField::MusicVolume].SetPosition(COORD{ 30, 10 }).SetSizeFill(0).SetRange(ScreenBuffer.GetFontSizeMin(), ScreenBuffer.GetFontSizeMax());
		Buttons[EButtonName::MusicVolumePlus ].SetPosition(COORD{ 41, 10 }).SetWidth(3).SetName(EButtonName::MusicVolumePlus ).SetText(L"+");
		Buttons[EButtonName::MusicVolumeMinus].SetPosition(COORD{ 45, 10 }).SetWidth(3).SetName(EButtonName::MusicVolumeMinus).SetText(L"-");
	}


// IEventListener Interface:

	void SSettings::OnEvent(const FEvent* const Event)
	{
		if (!this->IsActive())
		{
			if (Event->GetType() == EEventType::ScreenSwitched && Event->ScreenData.ToScreen == this->GetName())
			{
				this->Activate();
			}
		}
		else // When Active:
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

	void SSettings::ButtonPressCallback(const FEvent* const Event)
	{
		if ( (Event->ButtonData.ButtonName == EButtonName::Back) && (Event->ButtonData.MouseButton == FMouseButton::Left) )
		{
			this->Deactivate();

			FEventSystem::PushEvent(FEvent(EEventType::ScreenSwitched, FScreenData{ this->GetName(), EScreenName::Menu }));
		}
	}

	void SSettings::KeyPressCallback(const FEvent* const Event)
	{
		if (Event->KeyData.wVirtualKeyCode == FKey::Escape)
		{
			this->Deactivate();

			FEventSystem::PushEvent(FEvent(EEventType::ScreenSwitched, FScreenData{ this->GetName(), EScreenName::Menu }));
		}
	}

//	void SSettings::ProcessKey(const FEvent* const Event)
//	{
//		if (Event->KeyData.wVirtualKeyCode == FKey::Escape)
//		{
//			this->Deactivate();
//
//			FEventSystem::PushEvent(FEvent(EEventType::ScreenSwitched, FScreenData{ this->GetName(), EScreenName::Menu }));
//		}
//		else if ((Marker.GetPosition().Y == TextFields.at(EScreenField::CharSize).GetPosition().Y) && Event->KeyData.wVirtualKeyCode == FKey::A)
//		{
//			ScreenBuffer.DecreaseFontSize();
//
//			Sliders.at(EScreenField::CharSize).Decrease();
//
//			FEventSystem::PushEvent(FEvent(EEventType::FontChanged, FFontData{ 0, ScreenBuffer.GetFontSize(), ScreenBuffer.GetFontName() }));
//		}
//		else if ((Marker.GetPosition().Y == TextFields.at(EScreenField::CharSize).GetPosition().Y) && Event->KeyData.wVirtualKeyCode == FKey::D)
//		{
//			ScreenBuffer.IncreaseFontSize();
//
//			Sliders.at(EScreenField::CharSize).Increase();
//
//			FEventSystem::PushEvent(FEvent(EEventType::FontChanged, FFontData{ 0, ScreenBuffer.GetFontSize(), ScreenBuffer.GetFontName() }));
//		}
//	}


}