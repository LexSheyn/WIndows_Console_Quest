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
			
		// Music:
			
			Instance.MusicChannels[i]->setChannelGroup(Instance.Groups[1]);
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

	void FSoundSystem::LoadFile(ESound Index, const std::string& FilePath)
	{
		System->createSound(FilePath.c_str(), FMOD_DEFAULT, nullptr, &Sounds[Index]);
	}

	void FSoundSystem::Play(ESound Index)
	{
		System->playSound(Sounds[Index], Groups[EChannelGroup::Sound], true, &SoundChannels[Index]);
		SoundChannels[Index]->setVolume(Volumes[EChannelGroup::Sound]);
		SoundChannels[Index]->setPaused(false);
	}

	void FSoundSystem::Play(EMusic Index)
	{
	}

	void FSoundSystem::Stop(ESound Index)
	{
	}

	void FSoundSystem::Stop(EMusic Index)
	{
	}

	void FSoundSystem::Stop(EChannelGroup Index)
	{
	}

	void FSoundSystem::Pause(ESound Index)
	{
	}

	void FSoundSystem::Pause(EMusic Index)
	{
	}

	void FSoundSystem::Pause(EChannelGroup Index)
	{
		Groups[Index]->setPaused(true);
	}

	void FSoundSystem::Unpause(ESound Index)
	{
	}

	void FSoundSystem::Unpause(EMusic Index)
	{
	}

	void FSoundSystem::Unpause(EChannelGroup Index)
	{
		Groups[Index]->setPaused(false);
	}


// Private Constructors and Destructor:

	FSoundSystem::FSoundSystem()
	{
		FEventSystem::Subscribe(EEventType::ApplicationStarted, &Instance);
		FEventSystem::Subscribe(EEventType::ApplicationClosed , &Instance);
		FEventSystem::Subscribe(EEventType::ScreenSwitched    , &Instance);
		FEventSystem::Subscribe(EEventType::ButtonPressed     , &Instance);
	//	FEventSystem::Subscribe(EEventType::KeyPressed        , &Instance);
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
		}
	}


// Event Callbacks:

	void FSoundSystem::ApplicationStartCallback(const FEvent* const Event)
	{
		FSoundSystem::Initialize(0.5f);

		Instance.LoadFile(ESound::ScreenSwitch, "Resources/Sound/ScreenSwitch.mp3");
		Instance.LoadFile(ESound::ButtonPress , "Resources/Sound/ButtonPress.mp3");
	//	Instance.LoadFile(ESound::KeyPress    , "Resources/Sound/ButtonPress.mp3");
	}

	void FSoundSystem::ApplicationCloseCallback(const FEvent* const Event)
	{
		FSoundSystem::Shutdown();
	}

	void FSoundSystem::ScreenSwitchCallback(const FEvent* const Event)
	{
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

}