#pragma once

namespace wce
{
	struct FSettingsData
	{
		LONG  FontSliderSize  = 0;
		SHORT FontSize        = 16;

		LONG  MusicSliderSize = 0;
		FLOAT MusicVolume     = 0.0f;

		LONG  SoundSliderSize = 0;
		FLOAT SoundVolume     = 0.0f;
	};
}