#include "../PrecompiledHeaders/wcepch.h"
#include "FSoundSystem.h"

namespace wce
{
// Constructors and Destructor:

	FSoundSystem::FSoundSystem()
	{
		FEventSystem::Subscribe(EEventType::ApplicationStarted, this);
		FEventSystem::Subscribe(EEventType::ApplicationClosed , this);
		FEventSystem::Subscribe(EEventType::ScreenSwitched    , this);
		FEventSystem::Subscribe(EEventType::ButtonPressed     , this);
		FEventSystem::Subscribe(EEventType::KeyPressed        , this);
		FEventSystem::Subscribe(EEventType::SoundVolumeChanged, this);
		FEventSystem::Subscribe(EEventType::MusicVolumeChanged, this);
	}

	FSoundSystem::~FSoundSystem()
	{
		FEventSystem::UnsubscribeFromAll(this);
	}


// Functions:

	void FSoundSystem::Update()
	{
		System->update();
	}


// Accessors:

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

	void FSoundSystem::Initialize(FLOAT Volume)
	{
	// Volume:

		Volumes[EChannelGroup::Sound ] = Volume;
		Volumes[EChannelGroup::Music ] = Volume;
		Volumes[EChannelGroup::Master] = Volume;

	// System:

		FMOD::System_Create(&System);

		System->init(static_cast<INT>(NumChannels * 2u), FMOD_DEFAULT, nullptr);

	// Channel groups:

		System->createChannelGroup("Sound", &Groups[EChannelGroup::Sound]);
		System->createChannelGroup("Music", &Groups[EChannelGroup::Music]);

		System->getMasterChannelGroup(&Groups[2]);

		Groups[2]->addGroup(Groups[0]);
		Groups[2]->addGroup(Groups[1]);

		for (size_t i = 0u; i < NumChannels; i++)
		{
		// Sound:

			SoundChannels[i]->setChannelGroup(Groups[0]);
			SoundChannels[i]->setVolume(VolumeMax);
			
		// Music:
			
			MusicChannels[i]->setChannelGroup(Groups[1]);
			MusicChannels[i]->setVolume(VolumeMax);
		}

		Groups[EChannelGroup::Sound ]->setVolume(Volume);
		Groups[EChannelGroup::Music ]->setVolume(Volume);
		Groups[EChannelGroup::Master]->setVolume(Volume);
	}

	void FSoundSystem::Shutdown()
	{
		Groups[EChannelGroup::Master]->stop();

		for (size_t i = 0u; i < NumChannels; i++)
		{
			Sounds[i]->release();
			Music [i]->release();
		}

		System->close();
		System->release();
	}

	void FSoundSystem::Switch(EMusic Index)
	{
		bool Paused;

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

	bool FSoundSystem::IsPlaying(ESound Index)
	{
		bool Playing;

		SoundChannels[Index]->isPlaying(&Playing);

		return Playing;
	}

	bool FSoundSystem::IsPlaying(EMusic Index)
	{
		bool Playing;

		MusicChannels[Index]->isPlaying(&Playing);

		return Playing;
	}

	bool FSoundSystem::IsPlaying(EChannelGroup Index)
	{
		bool Playing;

		Groups[Index]->isPlaying(&Playing);

		return Playing;
	}


// IEveneListener Interface:

	void FSoundSystem::OnEvent(const FEvent* const Event)
	{
		switch (Event->GetType())
		{
			case EEventType::ApplicationStarted:
			{
				OnApplicationStart(Event);
			}
			break;

			case EEventType::ApplicationClosed:
			{
				OnApplicationClose(Event);
			}
			break;

			case EEventType::ScreenSwitched:
			{
				OnScreenSwitch(Event);
			}
			break;

			case EEventType::ButtonPressed:
			{
				OnButtonPress(Event);
			}
			break;

			case EEventType::KeyPressed:
			{
				OnKeyPress(Event);
			}
			break;

			case EEventType::SoundVolumeChanged:
			{
				this->OnSoundVolumeChange(Event);
			}
			break;

			case EEventType::MusicVolumeChanged:
			{
				this->OnMusicVolumeChange(Event);
			}
			break;
		}
	}


// Event Callbacks:

	void FSoundSystem::OnApplicationStart(const FEvent* const Event)
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

	void FSoundSystem::OnApplicationClose(const FEvent* const Event)
	{
		FSoundSystem::Shutdown();
	}

	void FSoundSystem::OnScreenSwitch(const FEvent* const Event)
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

		Play(ESound::ScreenSwitch);
	}

	void FSoundSystem::OnButtonPress(const FEvent* const Event)
	{
		Play(ESound::ButtonPress);
	}

	void FSoundSystem::OnKeyPress(const FEvent* const Event)
	{
	//	Play(ESound::KeyPress);
	}

	void FSoundSystem::OnSoundVolumeChange(const FEvent* const Event)
	{
		Groups[EChannelGroup::Sound]->setVolume(Event->SoundVolumeData.ToVolume);
	}

	void FSoundSystem::OnMusicVolumeChange(const FEvent* const Event)
	{
		Groups[EChannelGroup::Music]->setVolume(Event->SoundVolumeData.ToVolume);
	}

}