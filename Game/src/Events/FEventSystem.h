#pragma once

#include "IEventListener.h"
#include "FEvent.h"

namespace wce
{
	class FEventSystem
	{
	public:

	// Functions:

		static void  WCE_CALL PushEvent                (FEvent&& Event);
		static void  WCE_CALL PollEvents               ();
		static void  WCE_CALL Subscribe                (EEventType Type, IEventListener* Listener);
		static void  WCE_CALL Unsubscribe              (EEventType Type, IEventListener* Listener);
		static void  WCE_CALL UnsubscribeFromAll       (IEventListener* Listener);
		static bool8 WCE_CALL IsSubscribed             (EEventType Type, IEventListener* Listener);
		static void  WCE_CALL ClearEventQueue          ();
		static void  WCE_CALL ClearListenerRegistry    ();

	private:

	// Private Functions:

		static void WCE_CALL Dispatch(FEvent* Event);

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