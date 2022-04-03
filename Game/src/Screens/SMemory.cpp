#include "../PrecompiledHeaders/wcepch.h"
#include "SMemory.h"

namespace wce
{
// Constructors and Destructor:

	SMemory::SMemory()
		: IScreen(EScreenName::Memory)
	{
		this->Init();

		FEventSystem::Subscribe(EEventType::ApplicationStarted, this);
		FEventSystem::Subscribe(EEventType::ScreenSwitched    , this);
		FEventSystem::Subscribe(EEventType::FontChanged       , this);
		FEventSystem::Subscribe(EEventType::KeyPressed        , this);
	}

	SMemory::~SMemory()
	{
		FEventSystem::UnsubscribeFromAll(this);
	}


// IScreen Interface:

	void SMemory::Render()
	{
		if (this->IsActive())
		{
			ScreenBuffer.Clear();

			for (auto& Slot : MemorySlots)
			{
				Slot.Draw(ScreenBuffer);
			}

			for (auto&[Key, Button] : Buttons)
			{
				Button.Draw(ScreenBuffer);
			}

			ScreenBuffer.Present();
		}
	}

	void SMemory::Update()
	{
	}


// Private Functions:

	void SMemory::Init()
	{
		MemorySlots.emplace_back(FMemorySlot());
		MemorySlots.emplace_back(FMemorySlot());
		MemorySlots.emplace_back(FMemorySlot());
		MemorySlots.emplace_back(FMemorySlot());
	}


// IEventListener Interface:

	void SMemory::OnEvent(const FEvent* const Event)
	{
	}


// Event Callbacks:

	void SMemory::ApplicationStartCallback(const FEvent* const Event)
	{
	}

	void SMemory::ScreenSwitchCallback(const FEvent* const Event)
	{
	}

	void SMemory::FontChangeCallback(const FEvent* const Event)
	{
	}

	void SMemory::KeyPressCallback(const FEvent* const Event)
	{
	}


}