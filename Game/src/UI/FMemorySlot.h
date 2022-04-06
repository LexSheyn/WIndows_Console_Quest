#pragma once

#include "FButton.h"

namespace wce
{
	class FMemorySlot : public IEventListener
	{
	public:

	// Constructors and Destructor:

		 FMemorySlot ();
		~FMemorySlot ();

	// Functions:

		void Disable    ();
		void Enable     ();
		void Draw       (class FScreenBuffer& ScreenBuffer);

	// Accessors:

		const WORD&         GetID          () const;
		const COORD&        GetPosition    () const;
		const std::wstring& GetTime        () const;
		const std::wstring& GetDate        () const;
		const bool8&        IsEnabled      () const;


	// Modifiers:

		FMemorySlot& SetPosition    (COORD Position);
		FMemorySlot& SetTime        (const std::wstring& Time);
		FMemorySlot& SetDate        (const std::wstring& Date);

	private:

	// Private Functions:

		void GenerateID    ();
		void Init          ();

	// Variables:

		WORD  ID;
		COORD Position;
		bool8 Enabled;

	// Components:

		FTextField TimeField;
		FTextField DateField;
		std::map<EButton, FButton> Buttons;

	public:

	// IEventListener Interface:

		void OnEvent(const FEvent* const Event) override;

	private:

	// Event Callbacks:

		void ButtonPressCallback    (const FEvent* const Event);
	};
}