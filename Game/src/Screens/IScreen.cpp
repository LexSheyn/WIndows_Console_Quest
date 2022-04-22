#include "../PrecompiledHeaders/wcepch.h"
#include "IScreen.h"

namespace wce
{
// Constructors and Destructor:

	IScreen::IScreen(EScreen Name)
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

	const EScreen& IScreen::GetName() const
	{
		return Name;
	}

	const bool& IScreen::IsActive() const
	{
		return Activated;
	}


}