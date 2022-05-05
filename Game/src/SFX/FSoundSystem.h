#pragma once

#include "EChannelGroup.h"
#include "ESound.h"
#include "EMusic.h"
#include "../Templates/TArray.h"
#include "../Events/FEventSystem.h"

namespace wce
{
	class FSoundSystem : IEventListener
	{
	public:

	// Constructors and Destructor:

		 FSoundSystem    ();
		~FSoundSystem    ();

	// Functions:

		void Update    ();

	// Accessors:

		const FLOAT& GetVolume    (EChannelGroup Index);

	// Modifiers:

		void SetVolume    (EChannelGroup Index, FLOAT Value);

	private:

	// Private Functions:

		void Initialize      (FLOAT Volume);
		void Shutdown        ();
		void Switch          (EMusic Index);
		void CreateSound     (ESound Index, const std::string& FilePath);
		void CreateStream    (EMusic Index, const std::string& FilePath);
		void Play            (ESound Index);
		void Play            (EMusic Index);
		void Stop            (ESound Index);
		void Stop            (EMusic Index);
		void Stop            (EChannelGroup Index = EChannelGroup::Master);
		void Pause           (ESound Index);
		void Pause           (EMusic Index);
		void Pause           (EChannelGroup Index = EChannelGroup::Master);
		void Unpause         (ESound Index);
		void Unpause         (EMusic Index);
		void Unpause         (EChannelGroup Index = EChannelGroup::Master);
		bool IsPlaying       (ESound Index);
		bool IsPlaying       (EMusic Index);
		bool IsPlaying       (EChannelGroup Index = EChannelGroup::Master);

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

		void OnEvent    (const FEvent* const Event) override;

	private:

	// Event Callbacks:

		void OnApplicationStart     (const FEvent* const Event);
		void OnApplicationClose     (const FEvent* const Event);
		void OnScreenSwitch         (const FEvent* const Event);
		void OnButtonPress          (const FEvent* const Event);
		void OnKeyPress             (const FEvent* const Event);
		void OnSoundVolumeChange    (const FEvent* const Event);
		void OnMusicVolumeChange    (const FEvent* const Event);
	};
}