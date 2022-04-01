#pragma once

namespace wce
{
	class MFileManager
	{
	public:

	// Functions:

		static bool8                    Exists    (const std::string& FilePath);
		static void                     Save      (const std::string& Content, const std::string& FilePath);
		static std::vector<std::string> Load      (const std::string& FilePath);

	private:

	// Private Constructors and Destructor:

		 MFileManager () {}
		~MFileManager () {}
	};
}