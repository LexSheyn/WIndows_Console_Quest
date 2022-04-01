#include "../PrecompiledHeaders/wcepch.h"
#include "MDataManager.h"

namespace wce
{
// Settings:

	void MDataManager::SaveSettings(const FSettingsData& Data, const std::string& FilePath)
	{
		std::ostringstream Content;

		Content << Data.FontSliderSize  << "\n";
		Content << Data.FontSize        << "\n";
		Content << Data.MusicSliderSize << "\n";
		Content << Data.MusicVolume     << "\n";
		Content << Data.SoundSliderSize << "\n";
		Content << Data.SoundVolume     << "\n";

		MFileManager::Save(Content.str(), FilePath);
	}

	FSettingsData MDataManager::LoadSettings(const std::string& FilePath)
	{
		std::vector<std::string> Content;

		FSettingsData Data;

		if (MFileManager::Exists(FilePath))
		{
			Content = MFileManager::Load(FilePath);

			Data.FontSliderSize  = std::stol(Content[0]);
			Data.FontSize        = static_cast<SHORT>( std::stoi(Content[1]) );
			Data.MusicSliderSize = std::stol(Content[2]);
			Data.MusicVolume     = std::stof(Content[3]);
			Data.SoundSliderSize = std::stol(Content[4]);
			Data.SoundVolume     = std::stof(Content[5]);
		}

		return Data;
	}


// Game:

	void MDataManager::SaveGame(const FGameData& Data, const std::string& FilePath)
	{
		std::ostringstream Content;

		Content << Data.Time    << "\n";
		Content << Data.Date    << "\n";
		Content << Data.Chapter << "\n";

		MFileManager::Save(Content.str(), FilePath);
	}



	FGameData MDataManager::LoadGame(const std::string& FilePath)
	{
		std::vector<std::string> Content = MFileManager::Load(FilePath);

		// To do...

		return FGameData();
	}


}