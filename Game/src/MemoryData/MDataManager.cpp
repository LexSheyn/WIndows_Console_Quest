#include "../PrecompiledHeaders/wcepch.h"
#include "MDataManager.h"

namespace wce
{
// Functions:

	void MDataManager::SaveSettings(const FSettingsData& Data, const std::string& FilePath)
	{
		std::ostringstream Content;

		Content << Data.CharacterSize   << "\n";
		Content << Data.MusicSliderSize << "\n";
		Content << Data.MusicVolume     << "\n";
		Content << Data.SoundSliderSize << "\n";
		Content << Data.SoundVolume     << "\n";

		MFileManager::Save(Content.str(), "Config/Settings.cfg");
	}

	void MDataManager::SaveGame(const FGameData& Data, const std::string& FilePath)
	{
		std::ostringstream Content;

		Content << Data.Time    << "\n";
		Content << Data.Date    << "\n";
		Content << Data.Chapter << "\n";

		MFileManager::Save(Content.str(), "");
	}

	FSettingsData MDataManager::LoadSettings(const std::string& FilePath)
	{
		std::string Content = MFileManager::Load(FilePath);

		return FSettingsData();
	}

	FGameData MDataManager::LoadGame(const std::string& FilePath)
	{
		std::string Content = MFileManager::Load(FilePath);

		return FGameData();
	}


}