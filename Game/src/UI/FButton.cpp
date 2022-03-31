#include "../PrecompiledHeaders/wcepch.h"
#include "FButton.h"

#include "../ScreenBuffer/FScreenBuffer.h"

namespace wce
{
// Constructors and Destructor:

	FButton::FButton()
		: Position  (COORD{}),
		  Width     (10),
		  Attribute (ButtonEnabledAttribute),
		  Enabled   (true),
		  MousePositionLast(COORD{})
	{
		this->Enable();

		FEventSystem::Subscribe(EEventType::MouseMoved  , this);
		FEventSystem::Subscribe(EEventType::MousePressed, this);		
	}

	FButton::~FButton()
	{
		FEventSystem::UnsubscribeFromAll(this);
	}


// Functions:

	void FButton::Disable()
	{
		this->SetAttribute(ButtonDisabledAttribute);

		TextField.SetAttribute(TextDisabledAttribute);

		Enabled = false;
	}

	void FButton::Enable()
	{
		this->SetAttribute(ButtonEnabledAttribute);

		TextField.SetAttribute(TextEnabledAttribute);

		Enabled = true;
	}

	void FButton::Draw(FScreenBuffer& ScreenBuffer)
	{
		TextField.Draw(ScreenBuffer);

		ScreenBuffer.FillWithAttribute(Attribute, static_cast<DWORD>(Width), Position);
	}


// Accessors:

	const EButtonName& FButton::GetName() const
	{
		return Name;
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

	const bool8& FButton::IsEnabled() const
	{
		return Enabled;
	}


// Modifiers:

	FButton& FButton::SetName(EButtonName Name)
	{
		this->Name = Name;

		return *this;
	}

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


// IEventListener Interface:

	void FButton::OnEvent(const FEvent* const Event)
	{
		if (this->IsEnabled())
		{
			switch (Event->GetType())
			{
				case EEventType::MouseMoved:
				{
					MousePositionCallback(Event);
				}
				break;

				case EEventType::MousePressed:
				{
					MousePressCallback(Event);
				}
				break;
			}
		}
	}


// Event Callbacks:

	void FButton::MousePositionCallback(const FEvent* const Event)
	{
		MousePositionLast = Event->MouseData.dwMousePosition;

		if ( ((MousePositionLast.X >= Position.X) && (MousePositionLast.X <= Position.X + Width)) && (MousePositionLast.Y == Position.Y) )
		{
			this->SetAttribute(ButtonHoveredAttribute);
		}
		else
		{
			this->SetAttribute(ButtonEnabledAttribute);
		}
	}

	void FButton::MousePressCallback(const FEvent* const Event)
	{
		if ( ((MousePositionLast.X >= Position.X) && (MousePositionLast.X <= Position.X + Width)) && (MousePositionLast.Y == Position.Y) )
		{
			if (Event->MouseData.dwButtonState == FMouseButton::Left)
			{
				FEventSystem::PushEvent(FEvent(EEventType::ButtonPressed, FButtonData{ this->GetName(), FMouseButton::Left }));
			}
		}
	}


}