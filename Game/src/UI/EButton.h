#pragma once

namespace wce
{
	enum class EButton
	{
	// Menu:

		StartGame = 0,
		Memory,
		Settings,
		Exit,

	// Game:

		Choice_0,
		Choice_1,
		Choice_2,
		Choice_3,

	// Memory:

		Save,
		Load,

	// Settings:

		FontSize,
		FontSizePlus,
		FontSizeMinus,

		MusicVolume,
		MusicVolumePlus,
		MusicVolumeMinus,
		
		SoundVolume,
		SoundVolumePlus,
		SoundVolumeMinus,
		
		Back
	};
}