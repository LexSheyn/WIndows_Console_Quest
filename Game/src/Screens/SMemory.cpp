#include "../PrecompiledHeaders/wcepch.h"
#include "SMemory.h"

namespace wce
{
// Constructors and Destructor:

	SMemory::SMemory()
		: IScreen(EScreenName::Memory)
	{
		this->Init();

		FEventSystem::Subscribe(EEventType::ApplicationStarted   , this);
		FEventSystem::Subscribe(EEventType::ScreenSwitched       , this);
		FEventSystem::Subscribe(EEventType::FontChanged          , this);
		FEventSystem::Subscribe(EEventType::ButtonPressed        , this);
		FEventSystem::Subscribe(EEventType::KeyPressed           , this);
		FEventSystem::Subscribe(EEventType::MemorySlotPressed    , this);
		FEventSystem::Subscribe(EEventType::GameSaveApproved     , this);
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

			for (auto&[Key, Slot] : MemorySlots)
			{
				Slot.Draw(ScreenBuffer);
			}

			for (auto& [Key, Button] : Buttons)
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
		MemorySlots[0].SetPosition(COORD{ 10, 10 });
		MemorySlots[1].SetPosition(COORD{ 10, 12 });
		MemorySlots[2].SetPosition(COORD{ 10, 14 });

		Buttons[EButton::Back].SetPosition(COORD{ 10, 16 }).SetText(L"Back");
	}


// IEventListener Interface:

	void SMemory::OnEvent(const FEvent* const Event)
	{
		switch (Event->GetType())
		{
			case EEventType::ApplicationStarted:
			{
				this->ApplicationStartCallback(Event);
			}
			break;

			case EEventType::ScreenSwitched:
			{
				this->ScreenSwitchCallback(Event);
			}
			break;

			case EEventType::FontChanged:
			{
				this->FontChangeCallback(Event);
			}
			break;
		}

		if (this->IsActive())
		{
			switch (Event->GetType())
			{
				case EEventType::ButtonPressed:
				{
					this->ButtonPressCallback(Event);
				}
				break;

				case EEventType::KeyPressed:
				{
					this->KeyPressCallback(Event);
				}
				break;

				case EEventType::MemorySlotPressed:
				{
					this->MemorySlotPressCallback(Event);
				}
				break;

				case EEventType::GameSaveApproved:
				{
					this->GameSaveApproveCallback(Event);
				}
				break;
			}
		}
	}


// Event Callbacks:

	void SMemory::ApplicationStartCallback(const FEvent* const Event)
	{
		if (MFileManager::Exists(L"Memory/Slot0.mem"))
		{
			FGameData Data = MDataManager::LoadGame(L"Memory/Slot0.mem");

			MemorySlots.at(0).SetTime(Data.Time).SetDate(Data.Date);
		}
		
		if (MFileManager::Exists(L"Memory/Slot1.mem"))
		{
			FGameData Data = MDataManager::LoadGame(L"Memory/Slot1.mem");
	
			MemorySlots.at(1).SetTime(Data.Time).SetDate(Data.Date);
		}
		
		if (MFileManager::Exists(L"Memory/Slot2.mem"))
		{
			FGameData Data = MDataManager::LoadGame(L"Memory/Slot2.mem");
	
			MemorySlots.at(2).SetTime(Data.Time).SetDate(Data.Date);
		}
	}

	void SMemory::ScreenSwitchCallback(const FEvent* const Event)
	{
		if (Event->GetType() == EEventType::ScreenSwitched && Event->ScreenData.ToScreen == this->GetName())
		{
			this->Activate();
		}
	}

	void SMemory::FontChangeCallback(const FEvent* const Event)
	{
		ScreenBuffer.SetFontSize(Event->FontData.ToSize);
	}

	void SMemory::ButtonPressCallback(const FEvent* const Event)
	{
		if ((Event->ButtonData.ID == Buttons.at(EButton::Back).GetID()) && (Event->ButtonData.MouseButton == FMouseButton::Left))
		{
			this->Deactivate();

			FEventSystem::PushEvent(FEvent(EEventType::ScreenSwitched, FScreenData{ this->GetName(), EScreenName::Menu }));
		}
	}

	void SMemory::KeyPressCallback(const FEvent* const Event)
	{
		if (Event->KeyData.wVirtualKeyCode == FKey::Escape)
		{
			this->Deactivate();

			FEventSystem::PushEvent(FEvent(EEventType::ScreenSwitched, FScreenData{ this->GetName(), EScreenName::Menu }));
		}
	}

	void SMemory::MemorySlotPressCallback(const FEvent* const Event)
	{
		if ( (Event->MemorySlotData.ID == MemorySlots.at(0).GetID()) && (Event->MemorySlotData.Button == EMemorySlotButton::Save) )
		{
			FEventSystem::PushEvent(FEvent(EEventType::GameSaveRequested, FMemorySlotData{ MemorySlots.at(0).GetID(), EMemorySlotButton::Save, Event->MemorySlotData.MouseButton }));
		}
		else if ( (Event->MemorySlotData.ID == MemorySlots.at(0).GetID()) && (Event->MemorySlotData.Button == EMemorySlotButton::Load) )
		{
			if (MFileManager::Exists(L"Memory/Slot0.mem"))
			{
				FEventSystem::PushEvent(FEvent(EEventType::GameLoaded, MDataManager::LoadGame(L"Memory/Slot0.mem")));
				FEventSystem::PushEvent(FEvent(EEventType::ScreenSwitched, FScreenData{ this->GetName(), EScreenName::Game }));
			}
		}
		if ( (Event->MemorySlotData.ID == MemorySlots.at(1).GetID()) && (Event->MemorySlotData.Button == EMemorySlotButton::Save) )
		{
			FEventSystem::PushEvent(FEvent(EEventType::GameSaveRequested, FMemorySlotData{ MemorySlots.at(1).GetID(), EMemorySlotButton::Save, Event->MemorySlotData.MouseButton }));
		}
		else if ( (Event->MemorySlotData.ID == MemorySlots.at(1).GetID()) && (Event->MemorySlotData.Button == EMemorySlotButton::Load) )
		{
			if (MFileManager::Exists(L"Memory/Slot1.mem"))
			{
				FEventSystem::PushEvent(FEvent(EEventType::GameLoaded, MDataManager::LoadGame(L"Memory/Slot1.mem")));
				FEventSystem::PushEvent(FEvent(EEventType::ScreenSwitched, FScreenData{ this->GetName(), EScreenName::Game }));
			}
		}
		if ( (Event->MemorySlotData.ID == MemorySlots.at(2).GetID()) && (Event->MemorySlotData.Button == EMemorySlotButton::Save) )
		{
			FEventSystem::PushEvent(FEvent(EEventType::GameSaveRequested, FMemorySlotData{ MemorySlots.at(2).GetID(), EMemorySlotButton::Save, Event->MemorySlotData.MouseButton }));
		}
		else if ( (Event->MemorySlotData.ID == MemorySlots.at(2).GetID()) && (Event->MemorySlotData.Button == EMemorySlotButton::Load) )
		{
			if (MFileManager::Exists(L"Memory/Slot2.mem"))
			{
				FEventSystem::PushEvent(FEvent(EEventType::GameLoaded, MDataManager::LoadGame(L"Memory/Slot2.mem")));
				FEventSystem::PushEvent(FEvent(EEventType::ScreenSwitched, FScreenData{ this->GetName(), EScreenName::Game }));
			}
		}
	}

	void SMemory::GameSaveApproveCallback(const FEvent* const Event)
	{
		if (Event->GameData.MemorySlotID == MemorySlots.at(0).GetID())
		{
			MemorySlots.at(0).SetTime(Event->GameData.Time);
			MemorySlots.at(0).SetDate(Event->GameData.Date);

			MDataManager::SaveGame(Event->GameData, L"Memory/Slot0.mem");
		}
		else if (Event->GameData.MemorySlotID == MemorySlots.at(1).GetID())
		{
			MemorySlots.at(1).SetTime(Event->GameData.Time);
			MemorySlots.at(1).SetDate(Event->GameData.Date);

			MDataManager::SaveGame(Event->GameData, L"Memory/Slot1.mem");
		}
		else if (Event->GameData.MemorySlotID == MemorySlots.at(2).GetID())
		{
			MemorySlots.at(2).SetTime(Event->GameData.Time);
			MemorySlots.at(2).SetDate(Event->GameData.Date);

			MDataManager::SaveGame(Event->GameData, L"Memory/Slot2.mem");
		}
	}


}