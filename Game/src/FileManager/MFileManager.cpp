#include "../PrecompiledHeaders/wcepch.h"
#include "MFileManager.h"

namespace wce
{
// Functions:

	void MFileManager::CreateDirectory(const std::wstring& Path)
	{
		std::filesystem::create_directory(Path);
	}

	void MFileManager::CreateDirectories(const std::wstring& Path)
	{
		std::filesystem::create_directories(Path);
	}

	bool8 MFileManager::Exists(const std::wstring& FilePath)
	{
		return std::filesystem::exists(FilePath);
	}

	void MFileManager::Save(const std::wstring& Content, const std::wstring& FilePath)
	{
		std::wofstream OutFile;

		OutFile.open(FilePath);

		OutFile << Content;

		OutFile.close();
	}

	std::vector<std::wstring> MFileManager::Load(const std::wstring& FilePath)
	{
		std::vector<std::wstring> Content;
		Content.reserve(10);

		std::wstring Line;
		Line.reserve(100);

		std::wifstream InFile;

		InFile.open(FilePath);

		if (!InFile.is_open())
		{
			Content.push_back(std::wstring(L"Failed to load " + FilePath));

			return Content;
		}

		while (std::getline(InFile, Line))
		{
			Content.push_back(Line);
		}

		InFile.close();

		return Content;
	}


}