#include "../PrecompiledHeaders/wcepch.h"
#include "FMemorySlot.h"

#include "../ScreenBuffer/FScreenBuffer.h"

namespace wce
{
// Constructors and Destructor:

	FMemorySlot::FMemorySlot()
		: Enabled(true)
	{
		this->GenerateID();
		this->Init();

		FEventSystem::Subscribe(EEventType::ButtonPressed, this);
	}

	FMemorySlot::~FMemorySlot()
	{
		FEventSystem::UnsubscribeFromAll(this);
	}


// Functions:

	void FMemorySlot::Disable()
	{
		for (auto&[Key, Button] : Buttons)
		{
			Button.Disable();
		}

		Enabled = false;
	}

	void FMemorySlot::Enable()
	{
		for (auto& [Key, Button] : Buttons)
		{
			Button.Enable();
		}

		Enabled = true;
	}

	void FMemorySlot::Draw(FScreenBuffer& ScreenBuffer)
	{
		TimeField.Draw(ScreenBuffer);
		DateField.Draw(ScreenBuffer);

		for (auto&[Key, Button] : Buttons)
		{
			Button.Draw(ScreenBuffer);
		}
	}


// Accessors:

	const WORD& FMemorySlot::GetID() const
	{
		return ID;
	}

	const COORD& FMemorySlot::GetPosition() const
	{
		return Position;
	}

	const std::wstring& FMemorySlot::GetTime() const
	{
		return TimeField.GetText();
	}

	const std::wstring& FMemorySlot::GetDate() const
	{
		return DateField.GetText();
	}

	const bool& FMemorySlot::IsEnabled() const
	{
		return Enabled;
	}


// Modifiers:

	FMemorySlot& FMemorySlot::SetPosition(COORD Position)
	{
		this->Position = Position;

		TimeField.SetPosition(Position);
		DateField.SetPosition(COORD{ static_cast<SHORT>(TimeField.GetPosition().X + TimeField.GetLength() + 2i16), Position.Y });
		Buttons.at(EButton::Save).SetPosition(COORD{ static_cast<SHORT>(DateField.GetPosition().X + DateField.GetLength() + 2i16), Position.Y });
		Buttons.at(EButton::Load).SetPosition(COORD{ static_cast<SHORT>(Buttons.at(EButton::Save).GetPosition().X + Buttons.at(EButton::Save).GetWidth() + 2i16), Position.Y });

		return *this;
	}

	FMemorySlot& FMemorySlot::SetTime(const std::wstring& Time)
	{
		TimeField.SetText(Time);

		return *this;
	}

	FMemorySlot& FMemorySlot::SetDate(const std::wstring& Date)
	{
		DateField.SetText(Date);

		return *this;
	}


// Private Functions:

	void FMemorySlot::GenerateID()
	{
		static WORD NewID = 0;

		ID = NewID++;
	}

	void FMemorySlot::Init()
	{
		TimeField.SetText(L"--:--:--");
		DateField.SetText(L"--/--/----");
		Buttons[EButton::Save].SetWidth(6).SetText(L"Save");
		Buttons[EButton::Load].SetWidth(6).SetText(L"Load");

		this->SetPosition(COORD{ 0, 0 });
	}


// IEventListener Interface:

	void FMemorySlot::OnEvent(const FEvent* const Event)
	{
		if (this->IsEnabled())
		{
			switch (Event->GetType())
			{
				case EEventType::ButtonPressed:
				{
					this->OnButtonPress(Event);
				}
				break;
			}
		}
	}


// Event Callbacks:

	void FMemorySlot::OnButtonPress(const FEvent* const Event)
	{
		if      ( (Event->ButtonData.ID == Buttons.at(EButton::Save).GetID()) && (Event->ButtonData.MouseButton == FMouseButton::Left) )
		{
			FEventSystem::PushEvent(FEvent(EEventType::MemorySlotPressed, FMemorySlotData{ this->GetID(), EMemorySlotButton::Save, Event->ButtonData.MouseButton }));
		}
		else if ( (Event->ButtonData.ID == Buttons.at(EButton::Load).GetID()) && (Event->ButtonData.MouseButton == FMouseButton::Left) )
		{
			FEventSystem::PushEvent(FEvent(EEventType::MemorySlotPressed, FMemorySlotData{ this->GetID(), EMemorySlotButton::Load, Event->ButtonData.MouseButton }));
		}
	}


}