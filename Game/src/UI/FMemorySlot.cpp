#include "../PrecompiledHeaders/wcepch.h"
#include "FMemorySlot.h"

#include "../ScreenBuffer/FScreenBuffer.h"

namespace wce
{
// Constructors and Destructor:

	FMemorySlot::FMemorySlot()
	{
		this->Init();

		FEventSystem::Subscribe(EEventType::ButtonPressed, this);
	}

	FMemorySlot::~FMemorySlot()
	{
		FEventSystem::UnsubscribeFromAll(this);
	}


// Functions:

	void FMemorySlot::Save(const FGameData& Data, const std::wstring& FilePath)
	{
	}

	FGameData FMemorySlot::Load(const std::wstring& FilePath)
	{
		return FGameData();
	}

	void FMemorySlot::Draw(FScreenBuffer& ScreenBuffer)
	{
		TimeField.Draw(ScreenBuffer);
		DateField.Draw(ScreenBuffer);
		SaveButton.Draw(ScreenBuffer);
		LoadButton.Draw(ScreenBuffer);
	}


// Accessors:

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


// Modifiers:

	FMemorySlot& FMemorySlot::SetPosition(COORD Position)
	{
		this->Position = Position;

		TimeField.SetPosition(Position);
		DateField.SetPosition(COORD{ Position.X, static_cast<SHORT>(Position.Y + 1i16) });
		SaveButton.SetPosition(COORD{ Position.X, static_cast<SHORT>(Position.Y + 2i16) });
		LoadButton.SetPosition(COORD{ static_cast<SHORT>(SaveButton.GetPosition().X + SaveButton.GetWidth() + 1i16), SaveButton.GetPosition().Y });

		return *this;
	}

	FMemorySlot& FMemorySlot::SetTime(const std::wstring& Time)
	{
		TimeField.SetText(Time);

		return *this;
	}

	FMemorySlot& FMemorySlot::SetData(const std::wstring& Date)
	{
		DateField.SetText(Date);

		return *this;
	}


// Private Functions:

	void FMemorySlot::Init()
	{
		TimeField.SetText(L"00:00:00");
		DateField.SetText(L"00/00/0000");
		SaveButton.SetText(L"Save");
		LoadButton.SetText(L"Load");

		this->SetPosition(COORD{ 0, 0 });
	}


// IEventListener Interface:

	void FMemorySlot::OnEvent(const FEvent* const Event)
	{
	}


// Event Callbacks:

	void FMemorySlot::ButtonPressCallback(const FEvent* const Event)
	{
	}


}