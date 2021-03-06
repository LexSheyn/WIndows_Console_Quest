#include "../PrecompiledHeaders/wcepch.h"
#include "FButton.h"

#include "../ScreenBuffer/FScreenBuffer.h"

namespace wce
{
// Constructors and Destructor:

	FButton::FButton()
		: Position          (COORD{}),
		  Width             (10),
		  Attribute         (ButtonAttributeEnabled),
		  Enabled           (true),
		  MousePositionLast (COORD{})
	{
		this->GenerateID();

		this->Enable();

		FEventSystem::Subscribe(EEventType::MouseMoved  , this);
		FEventSystem::Subscribe(EEventType::MousePressed, this);		
	}

	FButton::~FButton()
	{
		FEventSystem::UnsubscribeFromAll(this);
	}


// Functions:

	void FButton::Enable()
	{
		TextField.Enable();

		this->SetAttribute(ButtonAttributeEnabled);

		Enabled = true;
	}

	void FButton::Disable()
	{
		TextField.Disable();

		this->SetAttribute(ButtonAttributeDisabled);

		Enabled = false;
	}

	void FButton::Draw(FScreenBuffer& ScreenBuffer)
	{
		TextField.Draw(ScreenBuffer);

		ScreenBuffer.FillWithAttribute(Position, static_cast<DWORD>(Width), Attribute);
	}


// Accessors:

	const WORD& FButton::GetID() const
	{
		return ID;
	}

	const COORD& FButton::GetPosition() const
	{
		return Position;
	}

	const SHORT& FButton::GetWidth() const
	{
		return Width;
	}

	const WORD& FButton::GetAttribute() const
	{
		return Attribute;
	}

	const std::wstring& FButton::GetText() const
	{
		return TextField.GetText();
	}

	const bool& FButton::IsEnabled() const
	{
		return Enabled;
	}


// Modifiers:

	FButton& FButton::SetPosition(COORD Position)
	{
		this->Position = Position;

		TextField.SetPosition(COORD{ static_cast<SHORT>(Position.X + 1i16), Position.Y });

		return *this;
	}

	FButton& FButton::SetWidth(SHORT Width)
	{
		this->Width = Width;

		return *this;
	}

	FButton& FButton::SetAttribute(WORD Attribute)
	{
		this->Attribute = Attribute;

		return *this;
	}

	FButton& FButton::SetText(const std::wstring& Text)
	{
		TextField.SetText(Text);

		return *this;
	}


// Private Functions:

	void FButton::GenerateID()
	{
		static WORD NewID = 0;

		ID = NewID++;
	}


// IEventListener Interface:

	void FButton::OnEvent(const FEvent* const Event)
	{
		if (this->IsEnabled())
		{
			switch (Event->GetType())
			{
				case EEventType::MouseMoved:
				{
					this->OnMouseMove(Event);
				}
				break;

				case EEventType::MousePressed:
				{
					this->OnMousePress(Event);
				}
				break;
			}
		}
	}


// Event Callbacks:

	void FButton::OnMouseMove(const FEvent* const Event)
	{
		MousePositionLast = Event->MouseData.dwMousePosition;

		if ( ((MousePositionLast.X >= Position.X) && (MousePositionLast.X <= Position.X + Width)) && (MousePositionLast.Y == Position.Y) )
		{
			this->SetAttribute(ButtonAttributeHovered);
		}
		else
		{
			this->SetAttribute(ButtonAttributeEnabled);
		}
	}

	void FButton::OnMousePress(const FEvent* const Event)
	{
		if ( ((MousePositionLast.X >= Position.X) && (MousePositionLast.X <= Position.X + Width)) && (MousePositionLast.Y == Position.Y) )
		{
			if (Event->MouseData.dwButtonState == FMouseButton::Left)
			{
				FEventSystem::PushEvent(FEvent(EEventType::ButtonPressed, FButtonData{ this->GetID(), FMouseButton::Left }));
			}
		}
	}


}