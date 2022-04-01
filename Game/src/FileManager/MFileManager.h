#pragma once

namespace wce
{
	class MFileManager
	{
	public:

	// Functions:

		static void        Save    (const std::string& Content, const std::string& FilePath);
		static std::string Load    (const std::string& FilePath);

	private:

	// Private Constructors and Destructor:

		 MFileManager () {}
		~MFileManager () {}
	};
}