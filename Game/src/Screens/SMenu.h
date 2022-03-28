#pragma once

#include "IScreen.h"

namespace wce
{
	class SMenu : IScreen
	{
	public:

	// Constructors and Destructor:

		 SMenu ();
		~SMenu ();

		WCE_NO_COPY(SMenu);
		WCE_NO_MOVE(SMenu);

	// IScreen Interface:

		void Render      () override;
		void Update      () override;

	private:

	// Private Functions:

		void Init ();

	public:

	// IEventListener Interface:

		void OnEvent(const FEvent* const Event) override;
	};
}