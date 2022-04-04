#include "../PrecompiledHeaders/wcepch.h"
#include "MDataManager.h"

namespace wce
{
// Settings:

	void MDataManager::SaveSettings(const FSettingsData& Data, const std::wstring& FilePath)
	{
		std::wostringstream Content;

		Content << Data.FontSliderSize  << "\n";
		Content << Data.FontSize        << "\n";
		Content << Data.MusicSliderSize << "\n";
		Content << Data.MusicVolume     << "\n";
		Content << Data.SoundSliderSize << "\n";
		Content << Data.SoundVolume     << "\n";

		MFileManager::Save(Content.str(), FilePath);
	}

	FSettingsData MDataManager::LoadSettings(const std::wstring& FilePath)
	{
		std::vector<std::wstring> Content;

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


// Memory:

	void MDataManager::SaveGame(const FGameData& Data, const std::wstring& FilePath)
	{
		std::wostringstream Content;

		Content << Data.Time    << "\n";
		Content << Data.Date    << "\n";
		Content << Data.Chapter << "\n";

		MFileManager::Save(Content.str(), FilePath);
	}

	FGameData MDataManager::LoadGame(const std::wstring& FilePath)
	{
		std::vector<std::wstring> Content = MFileManager::Load(FilePath);

		FGameData Data;

		Data.Time    = Content[0].c_str();
		Data.Date    = Content[1].c_str();
		Data.Chapter = static_cast<WORD>( std::stoul(Content[2]) );

		return Data;
	}


// Game:

	void MDataManager::LoadContent(std::map<WORD, std::vector<std::wstring>>& Dialogs, std::map<WORD, std::vector<FChoice>>& Choices, const std::wstring& FilePath)
	{
		std::vector<std::wstring> Content = MFileManager::Load(FilePath);

		std::wstring ChapterToken = L"<chapter>";
		std::wstring DialogToken  = L"<dialog>";
		std::wstring ChoiceToken  = L"<choice>";
		std::wstring MoveToken    = L"<move>";

		WORD         Chapter = 0;
		std::wstring Line;
		std::wstring ToChapter;

		for (size_t i = 0u; i < Content.size(); i++)
		{
			if (Content[i].starts_with(ChapterToken))
			{
				Line = Content[i];
				Line.erase(0, Line.find(ChapterToken) + ChapterToken.length());
				Chapter = static_cast<WORD>(std::stoul(Line));

				continue;
			}
			else if (Content[i].starts_with(DialogToken))
			{
				Line = Content[i];
				Line.erase(0, Line.find(DialogToken) + DialogToken.length());

				Dialogs[Chapter].push_back(Line);
			}
			else if (Content[i].starts_with(ChoiceToken))
			{
				Line = Content[i];
				Line.erase(0, Line.find(ChoiceToken) + ChoiceToken.length());

				ToChapter = Line;

				Line.erase(Line.find(MoveToken), Line.find(MoveToken) + MoveToken.length());

				ToChapter.erase(0, ToChapter.find(MoveToken));
				ToChapter.erase(0, ToChapter.find(MoveToken) + MoveToken.length());

				Choices[Chapter].push_back(FChoice{ static_cast<WORD>(std::stoul(ToChapter)), Line });
			}
		}
	}


}