#pragma once

namespace wce
{
	class IEventListener
	{
	public:

	// Interface:

		virtual void OnEvent    (const class FEvent* const Event) = 0;
	};
}