#pragma once

#include "EChannelGroup.h"
#include "ESound.h"
#include "EMusic.h"
#include "../Templates/TArray.h"

namespace wce
{
	class FSoundSystem : IEventListener
	{
	public:

	// Functions:

		static void Initialize    (FLOAT Volume);
		static void Shutdown      ();
		static void Update        ();

	// Accessors:

		static FSoundSystem* GetInstance ();
		
		const FLOAT& GetVolume (EChannelGroup Index);

	// Modifiers:

		void SetVolume (EChannelGroup Index, FLOAT Value);

	private:

	// Private Functions:

		void LoadFile    (ESound Index, const std::wstring& FilePath);
		void Play        (ESound Index);
		void Play        (EMusic Index);
		void Stop        (ESound Index);
		void Stop        (EMusic Index);
		void Stop        (EChannelGroup Index = EChannelGroup::Master);
		void Pause       (ESound Index);
		void Pause       (EMusic Index);
		void Pause       (EChannelGroup Index = EChannelGroup::Master);
		void Unpause     (ESound Index);
		void Unpause     (EMusic Index);
		void Unpause     (EChannelGroup Index = EChannelGroup::Master);

	// Private Constructors and Destructor:

		 FSoundSystem () {}
		~FSoundSystem () {}

	// Instance:

		static FSoundSystem Instance;

	// System:

		static constexpr size_t NumChannels = 16;

		FMOD::System* System;

		TArray<FMOD::Sound*, NumChannels> Sounds;
		TArray<FMOD::Sound*, NumChannels> Music;

		TArray<FMOD::Channel*, NumChannels> SoundChannels;
		TArray<FMOD::Channel*, NumChannels> MusicChannels;

		TArray<FMOD::ChannelGroup*, static_cast<size_t>(EChannelGroup::MAX)> Groups;

	// Variables:

		static constexpr FLOAT VolumeMin = 0.0f;
		static constexpr FLOAT VolumeMax = 1.0f;
		TArray<FLOAT, static_cast<size_t>(EChannelGroup::MAX)> Volumes;

	public:

	// IEveneListener Interface:

		void OnEvent(const FEvent* const Event) override;

	private:

	// Event Callbacks:

		void ApplicationStartCallback    (const FEvent* const Event);
		void ApplicationCloseCallback    (const FEvent* const Event);
	};
}