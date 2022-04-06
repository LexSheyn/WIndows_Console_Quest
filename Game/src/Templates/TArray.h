#pragma once

namespace wce
{
	template<typename T, size_t S>
	class TArray
	{
	public:

	// Accessors:

		constexpr size_t Size() const noexcept { return S; }
		const         T* Data() const          { return Array; }
		              T* Data()                { return Array; }

	// Operators:
		
		const T& operator [] (const size_t Index) const { return Array[Index]; }
		      T& operator [] (const size_t Index)       { return Array[Index]; }

		const T& operator [] (const enum class EChannelGroup Index) const { return Array[static_cast<size_t>(Index)]; }
		      T& operator [] (const enum class EChannelGroup Index)       { return Array[static_cast<size_t>(Index)]; }

		const T& operator [] (const enum class ESound Index) const { return Array[static_cast<size_t>(Index)]; }
		      T& operator [] (const enum class ESound Index)       { return Array[static_cast<size_t>(Index)]; }

		const T& operator [] (const enum class EMusic Index) const { return Array[static_cast<size_t>(Index)]; }
		      T& operator [] (const enum class EMusic Index)       { return Array[static_cast<size_t>(Index)]; }

	private:

	// Variables:

		T Array[S];
	};
}