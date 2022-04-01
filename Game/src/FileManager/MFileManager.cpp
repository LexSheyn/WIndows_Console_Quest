#include "../PrecompiledHeaders/wcepch.h"
#include "MFileManager.h"

namespace wce
{
// Functions:

	bool8 MFileManager::Exists(const std::string& FilePath)
	{
		return std::filesystem::exists(FilePath);
	}

	void MFileManager::Save(const std::string& Content, const std::string& FilePath)
	{
		std::ofstream OutFile;

		OutFile.open(FilePath);

		OutFile << Content;

		OutFile.close();
	}

	std::vector<std::string> MFileManager::Load(const std::string& FilePath)
	{
		std::vector<std::string> Content;
		Content.reserve(10);

		std::string Line;
		Line.reserve(100);

		std::ifstream InFile;

		InFile.open(FilePath);

		if (!InFile.is_open())
		{
			Content.push_back(std::string("Failed to load " + FilePath));

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