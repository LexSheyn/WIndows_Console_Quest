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
		TextFields[EScreenField::SoundVolume  ].SetPosition(COORD{ 10, 12 }).SetText(L"Sound volume"  );

	// Buttons and Sliders:

		Buttons[EButtonName::Back].SetPosition(COORD{ 10, 14 }).SetWidth(12).SetName(EButtonName::Back).SetText(L"Back");

		Sliders[EScreenField::CharacterSize   ].SetPosition(COORD{ 30, 8  }).SetSizeFill(0).SetRange(ScreenBuffer.GetFontSizeMin(), ScreenBuffer.GetFontSizeMax());
		Buttons[EButtonName::CharacterSizePlus ].SetPosition(COORD{ 41, 8 }).SetWidth(3).SetName(EButtonName::CharacterSizePlus ).SetText(L"+");
		Buttons[EButtonName::CharacterSizeMinus].SetPosition(COORD{ 45, 8 }).SetWidth(3).SetName(EButtonName::CharacterSizeMinus).SetText(L"-");

		Sliders[EScreenField::MusicVolume].SetPosition(COORD{ 30, 10 }).SetSizeFill(0).SetRange(ScreenBuffer.GetFontSizeMin(), ScreenBuffer.GetFontSizeMax());
		Buttons[EButtonName::MusicVolumePlus ].SetPosition(COORD{ 41, 10 }).SetWidth(3).SetName(EButtonName::MusicVolumePlus ).SetText(L"+");
		Buttons[EButtonName::MusicVolumeMinus].SetPosition(COORD{ 45, 10 }).SetWidth(3).SetName(EButtonName::MusicVolumeMinus).SetText(L"-");

		Sliders[EScreenField::SoundVolume].SetPosition(COORD{ 30, 12 }).SetSizeFill(0).SetRange(ScreenBuffer.GetFontSizeMin(), ScreenBuffer.GetFontSizeMax());
		Buttons[EButtonName::SoundVolumePlus ].SetPosition(COORD{ 41, 12 }).SetWidth(3).SetName(EButtonName::SoundVolumePlus ).SetText(L"+");
		Buttons[EButtonName::SoundVolumeMinus].SetPosition(COORD{ 45, 12 }).SetWidth(3).SetName(EButtonName::SoundVolumeMinus).SetText(L"-");
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
		else if ( (Event->ButtonData.ButtonName == EButtonName::CharacterSizePlus) && (Event->ButtonData.MouseButton == FMouseButton::Left) )
		{
			ScreenBuffer.IncreaseFontSize();

			Sliders.at(EScreenField::CharacterSize).Increase();

			FEventSystem::PushEvent(FEvent(EEventType::FontChanged, FFontData{ 0, ScreenBuffer.GetFontSize(), ScreenBuffer.GetFontName() }));
		}
		else if ( (Event->ButtonData.ButtonName == EButtonName::CharacterSizeMinus) && (Event->ButtonData.MouseButton == FMouseButton::Left) )
		{
			ScreenBuffer.DecreaseFontSize();

			Sliders.at(EScreenField::CharacterSize).Decrease();

			FEventSystem::PushEvent(FEvent(EEventType::FontChanged, FFontData{ 0, ScreenBuffer.GetFontSize(), ScreenBuffer.GetFontName() }));
		}
		else if ( (Event->ButtonData.ButtonName == EButtonName::MusicVolumePlus) && (Event->ButtonData.MouseButton == FMouseButton::Left) )
		{
			// Music stuff

			Sliders.at(EScreenField::MusicVolume).Increase();
		}
		else if ( (Event->ButtonData.ButtonName == EButtonName::MusicVolumeMinus) && (Event->ButtonData.MouseButton == FMouseButton::Left) )
		{
			// Music stuff

			Sliders.at(EScreenField::MusicVolume).Decrease();
		}
		else if ( (Event->ButtonData.ButtonName == EButtonName::SoundVolumePlus) && (Event->ButtonData.MouseButton == FMouseButton::Left) )
		{
			// Sound stuff

			Sliders.at(EScreenField::SoundVolume).Increase();
		}
		else if ( (Event->ButtonData.ButtonName == EButtonName::SoundVolumeMinus) && (Event->ButtonData.MouseButton == FMouseButton::Left) )
		{
			// Sound stuff

			Sliders.at(EScreenField::SoundVolume).Decrease();
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


}