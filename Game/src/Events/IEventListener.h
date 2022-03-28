#pragma once

//#include "FEvent.h"

namespace wce
{
	class IEventListener
	{
	public:

	// Constructors and Destructor:

		         IEventListener () {}
		virtual ~IEventListener () {}

	// Interface:

		virtual void OnEvent(const class FEvent* const Event) = 0;
	};
}