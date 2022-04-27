#include "../PrecompiledHeaders/wcepch.h"
#include "SSettings.h"

namespace wce
{
// Constructors and Destructor:

	SSettings::SSettings() : IScreen(EScreen::Settings)
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

		TextFields[EScreenField::FontSize   ].SetPosition(COORD{ 10, 10 }).SetText(L"Font size"   );
		TextFields[EScreenField::SoundVolume].SetPosition(COORD{ 10, 12 }).SetText(L"Sound volume");
		TextFields[EScreenField::MusicVolume].SetPosition(COORD{ 10, 14 }).SetText(L"Music volume");
		

	// Buttons and Sliders:

		Buttons[EButton::Back].SetPosition(COORD{ 10, 16 }).SetWidth(12).SetText(L"Back");

		Sliders[EScreenField::FontSize   ].SetPosition(COORD{ 30, 10 }).SetRange(ScreenBuffer.GetFontSizeMin(), ScreenBuffer.GetFontSizeMax());

		Buttons[EButton::FontSizePlus ].SetPosition(COORD{ 41, 10 }).SetWidth(3).SetText(L"+");
		Buttons[EButton::FontSizeMinus].SetPosition(COORD{ 45, 10 }).SetWidth(3).SetText(L"-");

		Sliders[EScreenField::SoundVolume].SetPosition(COORD{ 30, 12 }).SetRange(ScreenBuffer.GetFontSizeMin(), ScreenBuffer.GetFontSizeMax());

		Buttons[EButton::SoundVolumePlus].SetPosition(COORD{ 41, 12 }).SetWidth(3).SetText(L"+");
		Buttons[EButton::SoundVolumeMinus].SetPosition(COORD{ 45, 12 }).SetWidth(3).SetText(L"-");

		Sliders[EScreenField::MusicVolume].SetPosition(COORD{ 30, 14 }).SetRange(ScreenBuffer.GetFontSizeMin(), ScreenBuffer.GetFontSizeMax());

		Buttons[EButton::MusicVolumePlus ].SetPosition(COORD{ 41, 14 }).SetWidth(3).SetText(L"+");
		Buttons[EButton::MusicVolumeMinus].SetPosition(COORD{ 45, 14 }).SetWidth(3).SetText(L"-");
	}


// IEventListener Interface:

	void SSettings::OnEvent(const FEvent* const Event)
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


// Event Callbacks:

	void SSettings::OnApplicationStart(const FEvent* const Event)
	{
		// Check does the file exist first, and if so - do the rest, but if not...
		
		FSettingsData Data;

		if (MFileManager::Exists(L"Config/Settings.cfg"))
		{
			Data = MDataManager::LoadSettings(L"Config/Settings.cfg");
		}
		else
		{
		// Default initialization:

			Data.FontSliderSize  = 0;
			Data.FontSize        = ScreenBuffer.GetFontSizeMin(); // 16
			Data.MusicSliderSize = 3;
			Data.MusicVolume     = 0.3f;
			Data.SoundSliderSize = 5;
			Data.SoundVolume     = 0.5f;
		}
			
		Sliders[EScreenField::FontSize].SetSizeFill(Data.FontSliderSize);
		ScreenBuffer.SetFontSize(Data.FontSize);
		FEventSystem::PushEvent(FEvent(EEventType::FontChanged, FFontData{ ScreenBuffer.GetFontSizeMin(), ScreenBuffer.GetFontSize(), ScreenBuffer.GetFontName() }));

		Sliders[EScreenField::MusicVolume].SetSizeFill(Data.MusicSliderSize);
		FEventSystem::PushEvent(FEvent(EEventType::SoundVolumeChanged, FSoundVolumeData{ 0.0f, Data.SoundVolume }));

		Sliders[EScreenField::SoundVolume].SetSizeFill(Data.SoundSliderSize);
		FEventSystem::PushEvent(FEvent(EEventType::MusicVolumeChanged, FSoundVolumeData{ 0.0f, Data.MusicVolume }));
	}

	void SSettings::OnApplicationClose(const FEvent* const Event)
	{
		FSettingsData Data;

		Data.FontSliderSize  = Sliders.at(EScreenField::FontSize).GetSizeFill();
		Data.FontSize        = ScreenBuffer.GetFontSize();
		Data.MusicSliderSize = Sliders.at(EScreenField::MusicVolume).GetSizeFill();
		Data.MusicVolume     = static_cast<FLOAT>( Sliders.at(EScreenField::MusicVolume).GetSizeFill() ) / 10.0f; // TEST
		Data.SoundSliderSize = Sliders.at(EScreenField::SoundVolume).GetSizeFill();
		Data.SoundVolume     = static_cast<FLOAT>( Sliders.at(EScreenField::SoundVolume).GetSizeFill() ) / 10.0f; // TEST

		MDataManager::SaveSettings(Data, L"Config/Settings.cfg");
	}

	void SSettings::OnScreenSwitch(const FEvent* const Event)
	{
		if (Event->ScreenData.ToScreen == this->GetName())
		{
			this->Activate();

			for (auto&[Key, Button] : Buttons)
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

	void SSettings::OnButtonPress(const FEvent* const Event)
	{
		if ( (Event->ButtonData.ID == Buttons.at(EButton::Back).GetID()) && (Event->ButtonData.MouseButton == FMouseButton::Left) )
		{
			this->Deactivate();

			FEventSystem::PushEvent(FEvent(EEventType::ScreenSwitched, FScreenData{ this->GetName(), EScreen::Menu }));
		}
		else if ( (Event->ButtonData.ID == Buttons.at(EButton::FontSizePlus).GetID()) && (Event->ButtonData.MouseButton == FMouseButton::Left) )
		{
			ScreenBuffer.IncreaseFontSize();

			Sliders.at(EScreenField::FontSize).Increase();

			FEventSystem::PushEvent(FEvent(EEventType::FontChanged, FFontData{ 0, ScreenBuffer.GetFontSize(), ScreenBuffer.GetFontName() }));
		}
		else if ( (Event->ButtonData.ID == Buttons.at(EButton::FontSizeMinus).GetID()) && (Event->ButtonData.MouseButton == FMouseButton::Left) )
		{
			ScreenBuffer.DecreaseFontSize();

			Sliders.at(EScreenField::FontSize).Decrease();

			FEventSystem::PushEvent(FEvent(EEventType::FontChanged, FFontData{ 0, ScreenBuffer.GetFontSize(), ScreenBuffer.GetFontName() }));
		}
		else if ((Event->ButtonData.ID == Buttons.at(EButton::SoundVolumePlus).GetID()) && (Event->ButtonData.MouseButton == FMouseButton::Left))
		{
			FLOAT FromVolume = static_cast<FLOAT>( Sliders.at(EScreenField::SoundVolume).GetSizeFill() ) / 10.0f;

			Sliders.at(EScreenField::SoundVolume).Increase();

			FLOAT ToVolume = static_cast<FLOAT>( Sliders.at(EScreenField::SoundVolume).GetSizeFill() ) / 10.0f;

			FEventSystem::PushEvent(FEvent(EEventType::SoundVolumeChanged, FSoundVolumeData{ FromVolume, ToVolume }));
		}
		else if ((Event->ButtonData.ID == Buttons.at(EButton::SoundVolumeMinus).GetID()) && (Event->ButtonData.MouseButton == FMouseButton::Left))
		{
			FLOAT FromVolume = static_cast<FLOAT>( Sliders.at(EScreenField::SoundVolume).GetSizeFill() ) / 10.0f;

			Sliders.at(EScreenField::SoundVolume).Decrease();

			FLOAT ToVolume = static_cast<FLOAT>( Sliders.at(EScreenField::SoundVolume).GetSizeFill() ) / 10.0f;

			FEventSystem::PushEvent(FEvent(EEventType::SoundVolumeChanged, FSoundVolumeData{ FromVolume, ToVolume }));
		}
		else if ( (Event->ButtonData.ID == Buttons.at(EButton::MusicVolumePlus).GetID()) && (Event->ButtonData.MouseButton == FMouseButton::Left) )
		{
			FLOAT FromVolume = static_cast<FLOAT>( Sliders.at(EScreenField::MusicVolume).GetSizeFill() ) / 10.0f;

			Sliders.at(EScreenField::MusicVolume).Increase();

			FLOAT ToVolume = static_cast<FLOAT>( Sliders.at(EScreenField::MusicVolume).GetSizeFill() ) / 10.0f;

			FEventSystem::PushEvent(FEvent(EEventType::MusicVolumeChanged, FSoundVolumeData{ FromVolume, ToVolume }));
		}
		else if ( (Event->ButtonData.ID == Buttons.at(EButton::MusicVolumeMinus).GetID()) && (Event->ButtonData.MouseButton == FMouseButton::Left) )
		{
			FLOAT FromVolume = static_cast<FLOAT>( Sliders.at(EScreenField::MusicVolume).GetSizeFill() ) / 10.0f;

			Sliders.at(EScreenField::MusicVolume).Decrease();

			FLOAT ToVolume = static_cast<FLOAT>( Sliders.at(EScreenField::MusicVolume).GetSizeFill() ) / 10.0f;

			FEventSystem::PushEvent(FEvent(EEventType::MusicVolumeChanged, FSoundVolumeData{ FromVolume, ToVolume }));
		}
	}

	void SSettings::OnKeyPress(const FEvent* const Event)
	{
		if (Event->KeyData.wVirtualKeyCode == FKey::Escape)
		{
			FEventSystem::PushEvent(FEvent(EEventType::ScreenSwitched, FScreenData{ this->GetName(), EScreen::Menu }));
		}
	}


}