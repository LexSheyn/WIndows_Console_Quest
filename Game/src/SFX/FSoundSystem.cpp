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

        for (ULONG i = 0u; i < NumChannels; i++)
        {
        // Sound:

            Instance.SoundChannels[i]->setChannelGroup(Instance.Groups[0]);
            
        // Music:
            
            Instance.MusicChannels[i]->setChannelGroup(Instance.Groups[1]);
        }

        Instance.Groups[EChannelGroup::Sound ]->setVolume(Volume);
        Instance.Groups[EChannelGroup::Music ]->setVolume(Volume);
        Instance.Groups[EChannelGroup::Master]->setVolume(Volume);

    // Events:

        FEventSystem::Subscribe(EEventType::ApplicationStarted, &Instance);
        FEventSystem::Subscribe(EEventType::ApplicationClosed , &Instance);
    }

    void FSoundSystem::Shutdown()
    {
    // System:

        Instance.Groups[EChannelGroup::Master]->stop();

        for (size_t i = 0u; i < NumChannels; i++)
        {
            Instance.Sounds[i]->release();
            Instance.Music [i]->release();
        }

        Instance.System->close();
        Instance.System->release();

    // Events:

        FEventSystem::UnsubscribeFromAll(&Instance);
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

    void FSoundSystem::LoadFile(ESound Index, const std::wstring& FilePath)
    {
    }

    void FSoundSystem::Play(ESound Index)
    {
        System->playSound(Sounds[Index], Groups[Index], false, &SoundChannels[Index]);
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
        }
    }


// Event Callbacks:

    void FSoundSystem::ApplicationStartCallback(const FEvent* const Event)
    {
    }

    void FSoundSystem::ApplicationCloseCallback(const FEvent* const Event)
    {
    }

}