#pragma once

#include "IEventListener.h"
#include "FEvent.h"

namespace wce
{
	class FEventSystem
	{
	public:

	// Functions:

		static void   PushEvent                (const FEvent& Event);
		static void   PollEvents               ();
		static void   Subscribe                (EEventType Type, IEventListener* Listener);
		static void   Unsubscribe              (EEventType Type, IEventListener* Listener);
		static void   UnsubscribeFromAll       (IEventListener* Listener);
		static bool8  IsSubscribed             (EEventType Type, IEventListener* Listener);
		static void   ClearEventQueue          ();
		static void   ClearListenerRegistry    ();

	private:

	// Private Functions:

		static void  Dispatch(FEvent* Event);

	// Private Constructors and Destructor:

		 FEventSystem () {}
		~FEventSystem () {}

		WCE_NO_COPY(FEventSystem);
		WCE_NO_MOVE(FEventSystem);

	// Variables:

		static std::list<FEvent>                                    EventQueue;
		static std::unordered_multimap<EEventType, IEventListener*> ListenerRegistry;
	};
}