#pragma once

#include "FSettingsData.h"
#include "FGameData.h"

namespace wce
{
	class MDataManager
	{
	public:

	// Settings:

		static void          SaveSettings    (const FSettingsData& Data, const std::string& FilePath);
		static FSettingsData LoadSettings    (const std::string& FilePath);

	// Game:

		static void      SaveGame    (const FGameData&     Data, const std::string& FilePath);
		static FGameData LoadGame    (const std::string& FilePath);

	private:

	// Private Constructors and Destructor:

		 MDataManager () {}
		~MDataManager () {}
	};
}