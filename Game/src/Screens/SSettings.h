#pragma once

#include "IScreen.h"

namespace wce
{
	class SSettings : public IScreen
	{
	public:

	// Constructors and Destructor:

		 SSettings ();
		~SSettings ();

		WCE_NO_COPY(SSettings);
		WCE_NO_MOVE(SSettings);

	// IScreen Intarface:

		void Render    () override;
		void Update    () override;

	private:

	// Private Functions:

		void Init ();

	public:

	// IEventListener Interface:

		void OnEvent(const FEvent* const Event) override;
	};
}