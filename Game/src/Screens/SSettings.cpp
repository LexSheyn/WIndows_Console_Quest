#include "../PrecompiledHeaders/wcepch.h"
#include "SSettings.h"

namespace wce
{
// Constructors and Destructor:

	SSettings::SSettings()
		: IScreen(EScreenName::Settings)
	{
		this->Init();

		FEventSystem::Subscribe(EEventType::ApplicationStarted, this);
		FEventSystem::Subscribe(EEventType::ApplicationClosed , this);
		FEventSystem::Subscribe(EEventType::ScreenSwitched    , this);
		FEventSystem::Subscribe(EEventType::ButtonPressed     , this);
		FEventSystem::Subscribe(EEventType::KeyPressed        , this);
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

		TextFields[EScreenField::FontSize   ].SetPosition(COORD{ 10, 8  }).SetText(L"Font size"   );
		TextFields[EScreenField::MusicVolume].SetPosition(COORD{ 10, 10 }).SetText(L"Music volume");
		TextFields[EScreenField::SoundVolume].SetPosition(COORD{ 10, 12 }).SetText(L"Sound volume");

	// Buttons and Sliders:

		Buttons[EButtonName::Back].SetPosition(COORD{ 10, 14 }).SetWidth(12).SetName(EButtonName::Back).SetText(L"Back");

		Sliders[EScreenField::FontSize   ].SetPosition(COORD{ 30, 8  }).SetRange(ScreenBuffer.GetFontSizeMin(), ScreenBuffer.GetFontSizeMax());

		Buttons[EButtonName::FontSizePlus ].SetPosition(COORD{ 41, 8 }).SetWidth(3).SetName(EButtonName::FontSizePlus ).SetText(L"+");
		Buttons[EButtonName::FontSizeMinus].SetPosition(COORD{ 45, 8 }).SetWidth(3).SetName(EButtonName::FontSizeMinus).SetText(L"-");

		Sliders[EScreenField::MusicVolume].SetPosition(COORD{ 30, 10 }).SetRange(ScreenBuffer.GetFontSizeMin(), ScreenBuffer.GetFontSizeMax());

		Buttons[EButtonName::MusicVolumePlus ].SetPosition(COORD{ 41, 10 }).SetWidth(3).SetName(EButtonName::MusicVolumePlus ).SetText(L"+");
		Buttons[EButtonName::MusicVolumeMinus].SetPosition(COORD{ 45, 10 }).SetWidth(3).SetName(EButtonName::MusicVolumeMinus).SetText(L"-");

		Sliders[EScreenField::SoundVolume].SetPosition(COORD{ 30, 12 }).SetRange(ScreenBuffer.GetFontSizeMin(), ScreenBuffer.GetFontSizeMax());

		Buttons[EButtonName::SoundVolumePlus ].SetPosition(COORD{ 41, 12 }).SetWidth(3).SetName(EButtonName::SoundVolumePlus ).SetText(L"+");
		Buttons[EButtonName::SoundVolumeMinus].SetPosition(COORD{ 45, 12 }).SetWidth(3).SetName(EButtonName::SoundVolumeMinus).SetText(L"-");
	}


// IEventListener Interface:

	void SSettings::OnEvent(const FEvent* const Event)
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

				case EEventType::KeyPressed:
				{
					this->KeyPressCallback(Event);
				}
				break;

			}
		}
	}


// Event Callbacks:

	void SSettings::ApplicationStartCallback(const FEvent* const Event)
	{
		// Check does the file exist first, and if so - do the rest, but if not...
		
		FSettingsData Data = MDataManager::LoadSettings(L"Config/Settings.cfg");

		Sliders[EScreenField::FontSize].SetSizeFill(Data.FontSliderSize);
		ScreenBuffer.SetFontSize(Data.FontSize);
		
		Sliders[EScreenField::MusicVolume].SetSizeFill(Data.MusicSliderSize);
		// Music volume here.

		Sliders[EScreenField::SoundVolume].SetSizeFill(Data.SoundSliderSize);
		// Sound volume here.

		FEventSystem::PushEvent(FEvent(EEventType::FontChanged, FFontData{ ScreenBuffer.GetFontSizeMin(), ScreenBuffer.GetFontSize(), ScreenBuffer.GetFontName() }));
	}

	void SSettings::ApplicationCloseCallback(const FEvent* const Event)
	{
		FSettingsData Data;

		Data.FontSliderSize  = Sliders.at(EScreenField::FontSize).GetSizeFill();
		Data.FontSize        = ScreenBuffer.GetFontSize();
		Data.MusicSliderSize = Sliders.at(EScreenField::MusicVolume).GetSizeFill();
		Data.MusicVolume     = 1.0f; // Dummy value.
		Data.SoundSliderSize = Sliders.at(EScreenField::SoundVolume).GetSizeFill();
		Data.SoundVolume     = 1.0f; // Dummy value.

		MDataManager::SaveSettings(Data, L"Config/Settings.cfg");
	}

	void SSettings::ScreenSwitchCallback(const FEvent* const Event)
	{
		if (Event->GetType() == EEventType::ScreenSwitched && Event->ScreenData.ToScreen == this->GetName())
		{
			this->Activate();
		}
	}

	void SSettings::ButtonPressCallback(const FEvent* const Event)
	{
		if ( (Event->ButtonData.ButtonName == EButtonName::Back) && (Event->ButtonData.MouseButton == FMouseButton::Left) )
		{
			this->Deactivate();

			FEventSystem::PushEvent(FEvent(EEventType::ScreenSwitched, FScreenData{ this->GetName(), EScreenName::Menu }));
		}
		else if ( (Event->ButtonData.ButtonName == EButtonName::FontSizePlus) && (Event->ButtonData.MouseButton == FMouseButton::Left) )
		{
			ScreenBuffer.IncreaseFontSize();

			Sliders.at(EScreenField::FontSize).Increase();

			FEventSystem::PushEvent(FEvent(EEventType::FontChanged, FFontData{ 0, ScreenBuffer.GetFontSize(), ScreenBuffer.GetFontName() }));
		}
		else if ( (Event->ButtonData.ButtonName == EButtonName::FontSizeMinus) && (Event->ButtonData.MouseButton == FMouseButton::Left) )
		{
			ScreenBuffer.DecreaseFontSize();

			Sliders.at(EScreenField::FontSize).Decrease();

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