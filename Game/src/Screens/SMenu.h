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

	// IScreen Interface:

		void Render      () override;
		void Update      () override;

	private:

	// Private Functions:

		void Init ();

	public:

	// IEventListener Interface:

		void OnEvent(const FEvent* const Event) override;

	// Event Callbacks:

		void MarkField       (const FEvent* const Event);
		void ProcessField    (const FEvent* const Event);
	};
}