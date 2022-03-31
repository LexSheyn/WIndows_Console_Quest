#include "../PrecompiledHeaders/wcepch.h"
#include "IScreen.h"

namespace wce
{
// Constructors and Destructor:

	IScreen::IScreen(EScreenName Name)
		: Name(Name),
		  Activated(false)
	{
	}

	IScreen::~IScreen()
	{
	}


// Functions:

	void IScreen::Activate()
	{
		ScreenBuffer.Activate();
		Activated = true;
	}

	void IScreen::Deactivate()
	{
		Activated = false;
	}


// Accessors:

	const EScreenName& IScreen::GetName() const
	{
		return Name;
	}

	const bool8& IScreen::IsActive() const
	{
		return Activated;
	}


}