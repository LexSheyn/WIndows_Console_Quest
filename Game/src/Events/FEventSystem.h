#pragma once

#include "FEvent.h"
#include "IEventListener.h"

namespace wce
{
	class FEventSystem
	{
	public:

	// Constructors and Destructor:

		 FEventSystem    () = delete;
		~FEventSystem    () = delete;

	// Functions:

		static void PushEvent                (const FEvent& Event);
		static void PollEvents               ();
		static void Subscribe                (EEventType Type, IEventListener* Listener);
		static void Unsubscribe              (EEventType Type, IEventListener* Listener);
		static void UnsubscribeFromAll       (IEventListener* Listener);
		static bool IsSubscribed             (EEventType Type, IEventListener* Listener);
		static void ClearEventQueue          ();
		static void ClearListenerRegistry    ();

	private:

	// Private Functions:

		static void  Dispatch    (FEvent* Event);

	// Variables:

		static std::list<FEvent>                                    EventQueue;
		static std::unordered_multimap<EEventType, IEventListener*> ListenerRegistry;
	};
}