#include "../PrecompiledHeaders/wcepch.h"
#include "MFileManager.h"

namespace wce
{
// Functions:

	void MFileManager::Save(const std::string& Content, const std::string& FilePath)
	{
		std::ofstream OutFile;

		OutFile.open(FilePath);

		OutFile << Content;

		OutFile.close();
	}

	std::string MFileManager::Load(const std::string& FilePath)
	{
		std::string Content;
		Content.reserve(10'000);

		std::string Line;
		Line.reserve(100);

		std::ifstream InFile;

		InFile.open(FilePath);

		if (!InFile.is_open())
		{
			return std::string("Failed to load " + FilePath);
		}

		while (std::getline(InFile, Line))
		{
			Content += Line + "\n";
		}

		InFile.close();

		return Content;
	}


}