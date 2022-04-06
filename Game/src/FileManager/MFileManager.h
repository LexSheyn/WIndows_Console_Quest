#pragma once

namespace wce
{
	class MFileManager
	{
	public:

	// Constructors and Destructor:

		 MFileManager () = delete;
		~MFileManager () = delete;

	// Functions:

		static void                      CreateDirectory      (const std::wstring& Path);
		static void                      CreateDirectories    (const std::wstring& Path);
		static bool8                     Exists               (const std::wstring& FilePath);
		static void                      Save                 (const std::wstring& Content, const std::wstring& FilePath);
		static std::vector<std::wstring> Load                 (const std::wstring& FilePath);
	};
}