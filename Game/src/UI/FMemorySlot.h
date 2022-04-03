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

		void      Save    (const FGameData& Data, const std::wstring& FilePath);
		FGameData Load    (const std::wstring& FilePath);
		void      Draw    (class FScreenBuffer& ScreenBuffer);

	// Accessors:

		const COORD&        GetPosition    () const;
		const std::wstring& GetTime        () const;
		const std::wstring& GetDate        () const;

	// Modifiers:

		FMemorySlot& SetPosition    (COORD Position);
		FMemorySlot& SetTime        (const std::wstring& Time);
		FMemorySlot& SetData        (const std::wstring& Date);

	private:

	// Private Functions:

		void Init();

	// Variables:

		COORD Position;

	// Components:

		FTextField TimeField;
		FTextField DateField;
		FButton    SaveButton;
		FButton    LoadButton;

	public:

	// IEventListener Interface:

		void OnEvent(const FEvent* const Event) override;

	private:

	// Event Callbacks:

		void ButtonPressCallback    (const FEvent* const Event);
	};
}