#include "../PrecompiledHeaders/wcepch.h"
#include "FSoundSystem.h"

namespace wce
{
// Functions:

	void FSoundSystem::Initialize(FLOAT Volume)
	{
	// Volume:

		Instance.Volumes[EChannelGroup::Sound ] = Volume;
		Instance.Volumes[EChannelGroup::Music ] = Volume;
		Instance.Volumes[EChannelGroup::Master] = Volume;

	// System:

		FMOD::System_Create(&Instance.System);

		Instance.System->init(static_cast<INT>(NumChannels * 2u), FMOD_DEFAULT, nullptr);

	// Channel groups:

		Instance.System->createChannelGroup("Sound", &Instance.Groups[EChannelGroup::Sound]);
		Instance.System->createChannelGroup("Music", &Instance.Groups[EChannelGroup::Music]);

		Instance.System->getMasterChannelGroup(&Instance.Groups[2]);

		Instance.Groups[2]->addGroup(Instance.Groups[0]);
		Instance.Groups[2]->addGroup(Instance.Groups[1]);

		for (size_t i = 0u; i < NumChannels; i++)
		{
		// Sound:

			Instance.SoundChannels[i]->setChannelGroup(Instance.Groups[0]);
			Instance.SoundChannels[i]->setVolume(VolumeMax);
			
		// Music:
			
			Instance.MusicChannels[i]->setChannelGroup(Instance.Groups[1]);
			Instance.MusicChannels[i]->setVolume(VolumeMax);
		}

		Instance.Groups[EChannelGroup::Sound ]->setVolume(Volume);
		Instance.Groups[EChannelGroup::Music ]->setVolume(Volume);
		Instance.Groups[EChannelGroup::Master]->setVolume(Volume);
	}

	void FSoundSystem::Shutdown()
	{
		Instance.Groups[EChannelGroup::Master]->stop();

		for (size_t i = 0u; i < NumChannels; i++)
		{
			Instance.Sounds[i]->release();
			Instance.Music [i]->release();
		}

		Instance.System->close();
		Instance.System->release();
	}

	void FSoundSystem::Update()
	{
		Instance.System->update();
	}


// Accessors:

	FSoundSystem* FSoundSystem::GetInstance()
	{
		return &Instance;
	}

	const FLOAT& FSoundSystem::GetVolume(EChannelGroup Index)
	{
		return Volumes[Index];
	}


// Modifiers:

	void FSoundSystem::SetVolume(EChannelGroup Index, FLOAT Value)
	{
		if (Value < VolumeMin)
		{
			Volumes[Index] = VolumeMin;
		}
		else if (Value > VolumeMax)
		{
			Volumes[Index] = VolumeMax;
		}
		else
		{
			Volumes[Index] = Value;
		}
	}


// Private Functions:

	void FSoundSystem::Switch(EMusic Index)
	{
		bool8 Paused;

		MusicChannels[Index]->getPaused(&Paused);
		MusicChannels[Index]->setPaused(!Paused);
	}

	void FSoundSystem::CreateSound(ESound Index, const std::string& FilePath)
	{
		System->createSound(FilePath.c_str(), FMOD_DEFAULT | FMOD_2D, nullptr, &Sounds[Index]);
	}

	void FSoundSystem::CreateStream(EMusic Index, const std::string& FilePath)
	{
		System->createStream(FilePath.c_str(), FMOD_LOOP_NORMAL | FMOD_2D, nullptr, &Music[Index]);
	}

	void FSoundSystem::Play(ESound Index)
	{
		System->playSound(Sounds[Index], Groups[EChannelGroup::Sound], false, &SoundChannels[Index]);
	}

	void FSoundSystem::Play(EMusic Index)
	{
		System->playSound(Music[Index], Groups[EChannelGroup::Music], false, &MusicChannels[Index]);
	}

	void FSoundSystem::Stop(ESound Index)
	{
		SoundChannels[Index]->stop();
	}

	void FSoundSystem::Stop(EMusic Index)
	{
		MusicChannels[Index]->stop();
	}

	void FSoundSystem::Stop(EChannelGroup Index)
	{
		Groups[Index]->stop();
	}

	void FSoundSystem::Pause(ESound Index)
	{
		SoundChannels[Index]->setPaused(true);
	}

	void FSoundSystem::Pause(EMusic Index)
	{
		MusicChannels[Index]->setPaused(true);
	}

	void FSoundSystem::Pause(EChannelGroup Index)
	{
		Groups[Index]->setPaused(true);
	}

	void FSoundSystem::Unpause(ESound Index)
	{
		SoundChannels[Index]->setPaused(false);
	}

	void FSoundSystem::Unpause(EMusic Index)
	{
		MusicChannels[Index]->setPaused(false);
	}

	void FSoundSystem::Unpause(EChannelGroup Index)
	{
		Groups[Index]->setPaused(false);
	}

	bool8 FSoundSystem::IsPlaying(ESound Index)
	{
		bool8 Playing;

		SoundChannels[Index]->isPlaying(&Playing);

		return Playing;
	}

	bool8 FSoundSystem::IsPlaying(EMusic Index)
	{
		bool8 Playing;

		MusicChannels[Index]->isPlaying(&Playing);

		return Playing;
	}

	bool8 FSoundSystem::IsPlaying(EChannelGroup Index)
	{
		bool8 Playing;

		Groups[Index]->isPlaying(&Playing);

		return Playing;
	}


// Private Constructors and Destructor:

	FSoundSystem::FSoundSystem()
	{
		FEventSystem::Subscribe(EEventType::ApplicationStarted, &Instance);
		FEventSystem::Subscribe(EEventType::ApplicationClosed , &Instance);
		FEventSystem::Subscribe(EEventType::ScreenSwitched    , &Instance);
		FEventSystem::Subscribe(EEventType::ButtonPressed     , &Instance);
		FEventSystem::Subscribe(EEventType::KeyPressed        , &Instance);
		FEventSystem::Subscribe(EEventType::SoundVolumeChanged, &Instance);
		FEventSystem::Subscribe(EEventType::MusicVolumeChanged, &Instance);
	}

	FSoundSystem::~FSoundSystem()
	{
		FEventSystem::UnsubscribeFromAll(&Instance);
	}


// Instance:

	FSoundSystem FSoundSystem::Instance;


// IEveneListener Interface:

	void FSoundSystem::OnEvent(const FEvent* const Event)
	{
		switch (Event->GetType())
		{
			case EEventType::ApplicationStarted:
			{
				Instance.ApplicationStartCallback(Event);
			}
			break;

			case EEventType::ApplicationClosed:
			{
				Instance.ApplicationCloseCallback(Event);
			}
			break;

			case EEventType::ScreenSwitched:
			{
				Instance.ScreenSwitchCallback(Event);
			}
			break;

			case EEventType::ButtonPressed:
			{
				Instance.ButtonPressCallback(Event);
			}
			break;

			case EEventType::KeyPressed:
			{
				Instance.KeyPressCallback(Event);
			}
			break;

			case EEventType::SoundVolumeChanged:
			{
				this->SoundVolumeChangeCallback(Event);
			}
			break;

			case EEventType::MusicVolumeChanged:
			{
				this->MusicVolumeChangeCallback(Event);
			}
			break;
		}
	}


// Event Callbacks:

	void FSoundSystem::ApplicationStartCallback(const FEvent* const Event)
	{
	// System:

		FSoundSystem::Initialize(0.4f);

	// Sound:

		this->CreateSound(ESound::ScreenSwitch, "Resources/Sound/ScreenSwitch.mp3");
		this->CreateSound(ESound::ButtonPress , "Resources/Sound/ButtonPress.mp3");
	//	this->CreateSound(ESound::KeyPress    , "Resources/Sound/ButtonPress.mp3");
		
	// Music:

		this->CreateStream(EMusic::Menu, "Resources/Music/Menu.mp3");
		this->CreateStream(EMusic::Game, "Resources/Music/Game.mp3");

		this->Play(EMusic::Menu);
		this->Pause(EMusic::Menu);

		this->Play(EMusic::Game);
		this->Pause(EMusic::Game);
	}

	void FSoundSystem::ApplicationCloseCallback(const FEvent* const Event)
	{
		FSoundSystem::Shutdown();
	}

	void FSoundSystem::ScreenSwitchCallback(const FEvent* const Event)
	{
		if (Event->ScreenData.ToScreen == EScreen::Menu)
		{
			this->Pause(EMusic::Game);
			this->Unpause(EMusic::Menu);
		}
		else if (Event->ScreenData.ToScreen == EScreen::Game)
		{
			this->Pause(EMusic::Menu);
			this->Unpause(EMusic::Game);
		}

		Instance.Play(ESound::ScreenSwitch);
	}

	void FSoundSystem::ButtonPressCallback(const FEvent* const Event)
	{
		Instance.Play(ESound::ButtonPress);
	}

	void FSoundSystem::KeyPressCallback(const FEvent* const Event)
	{
	//	Instance.Play(ESound::KeyPress);
	}

	void FSoundSystem::SoundVolumeChangeCallback(const FEvent* const Event)
	{
		Groups[EChannelGroup::Sound]->setVolume(Event->SoundVolumeData.ToVolume);
	}

	void FSoundSystem::MusicVolumeChangeCallback(const FEvent* const Event)
	{
		Groups[EChannelGroup::Music]->setVolume(Event->SoundVolumeData.ToVolume);
	}

}