#include "../PrecompiledHeaders/wcepch.h"
#include "../Application/FApplication.h"

INT wmain(INT argc, WCHAR** argv)
{
	wce::FApplication Application;

	try
	{
		Application.Run();
	}
	catch (const std::exception& Exception)
	{
		std::cout << Exception.what() << std::endl;

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}