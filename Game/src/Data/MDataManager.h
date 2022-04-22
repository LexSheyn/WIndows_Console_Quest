#pragma once

#include "FSettingsData.h"
#include "FGameData.h"
#include "FChoice.h"

namespace wce
{
	class MDataManager
	{
	public:

	// Constructors and Destructor:

		 MDataManager    () = delete;
		~MDataManager    () = delete;

	// Settings:

		static void          SaveSettings    (const FSettingsData& Data, const std::wstring& FilePath);
		static FSettingsData LoadSettings    (const std::wstring& FilePath);

	// Memory:

		static void      SaveGame    (const FGameData&     Data, const std::wstring& FilePath);
		static FGameData LoadGame    (const std::wstring& FilePath);

	// Game:

		static void LoadContent    (std::map<WORD, std::vector<std::wstring>>& Dialogs, std::map<WORD, std::vector<FChoice>>& Choices, const std::wstring& FilePath);
	};
}