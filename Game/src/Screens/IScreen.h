#pragma once

#include "EScreen.h"
#include "EScreenField.h"
#include "../Input/FKey.h"
#include "../Input/FMouseButton.h"
#include "../ScreenBuffer/FScreenBuffer.h"
#include "../UI/FButton.h"
#include "../UI/FSlider.h"

namespace wce
{
	class IScreen : public IEventListener
	{
	protected:

	// Constructors and Destructor:

		         IScreen (EScreen Name);
		virtual ~IScreen ();

	// Intarface:

		virtual void Render    () = 0;
		virtual void Update    () = 0;

	// Functions:

		void Activate      ();
		void Deactivate    ();

	// Accessors:

		const EScreen& GetName     () const;
		const bool8&       IsActive    () const;

	// Components:

		FScreenBuffer ScreenBuffer;

	private:

	// Variables:

		EScreen Name;
		bool8       Activated;

	public:

	// IEventListener Interface:

		virtual void OnEvent (const FEvent* const Event) override = 0;
	};
}