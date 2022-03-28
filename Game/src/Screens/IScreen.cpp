#include "../PrecompiledHeaders/wcepch.h"
#include "IScreen.h"

namespace wce
{
// Constructors and Destructor:

	IScreen::IScreen(EScreenName Name)
		: Name(Name),
		  IsActivated(false)
	{
	}

	IScreen::~IScreen()
	{
	}


// Functions:

	void IScreen::Activate()
	{
		ScreenBuffer.Activate();
		IsActivated = true;
	}

	void IScreen::Deactivate()
	{
		IsActivated = false;
	}


// Accessors:

	const EScreenName& IScreen::GetName() const
	{
		return Name;
	}

	const bool8& IScreen::IsActive() const
	{
		return IsActivated;
	}


}