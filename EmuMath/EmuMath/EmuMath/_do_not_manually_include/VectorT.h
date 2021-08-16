#ifndef EMU_MATH_VECTOR_T_H_INC_
#define EMU_MATH_VECTOR_T_H_INC_ 1

#include "VectorHelpers.h"
#include "../../EmuCore/TMPHelpers/TypeConvertors.h"
#include <array>
#include <ostream>

namespace EmuMath
{
	template<std::size_t Size_, typename T_>
	struct Vector
	{
	public:
		static_assert(Size_ > 0, "Unable to create an EmuMath Vector which contains 0 elements.");
		static_assert(!std::is_same_v<T_, void>, "Unable to create an EmuMath Vector which contains void elements.");

		/// <summary> The type contained within this vector. </summary>
		using contained_type = T_;
		/// <summary> Boolean indicating if this vector contains std::reference_wrapper types. </summary>
		static constexpr bool contains_reference_wrappers = EmuCore::TMPHelpers::is_reference_wrapper<contained_type>::value;
		/// <summary> Value type of the items stored within this vector. </summary>
		using value_type = std::conditional_t<contains_reference_wrappers, typename EmuCore::TMPHelpers::get_value_type<contained_type>::type&, contained_type>;
		/// <summary> The preferred floating point type for this vector. Float if this vector contains non-floating-point types, otherwise matches value_type. </summary>
		using preferred_floating_point = EmuCore::TMPHelpers::first_floating_point_t<value_type, float>;

		/// <summary> The number of elements contained in this vector. </summary>
		static constexpr std::size_t size = Size_;
		/// <summary> This vector's instantiated type. </summary>
		using this_type = Vector<size, contained_type>;

		static constexpr bool has_integral_elements = std::is_integral_v<std::remove_cv_t<value_type>>;
		static constexpr bool has_floating_point_elements = std::is_floating_point_v<std::remove_cv_t<value_type>>;

		constexpr Vector() : data()
		{
		}
		constexpr Vector(const this_type& toCopy_) : data(toCopy_.data)
		{
		}
		template<std::size_t ToCopySize_, typename ToCopyValueType_>
		constexpr Vector(const Vector<ToCopySize_, ToCopyValueType_>& toCopy_) : Vector()
		{
			Copy<ToCopySize_, ToCopyValueType_>(toCopy_);
		}
		/// <summary>
		/// <para> Constructs this vector with its elements matching the passed data, in contiguous order of the 0th to the (size - 1)th element. </para>
		/// <para> This constructor requires a number of arguments equal to the number of elements in the vector. </para>
		/// </summary>
		/// <typeparam name="Args">All arguments passed to construct this vector via.</typeparam>
		/// <typeparam name="RequiresArgumentCountEqualToSize">Dummy parameter used to make use of std::enable_if.</typeparam>
		/// <param name="contiguousData_">Arguments to create this vector's elements, in contiguous order from the 0th-(size - 1)th element in this vector.</param>
		template<typename...Args, typename RequiresArgumentCountEqualToSize = std::enable_if_t<sizeof...(Args) == size>>
		constexpr Vector(Args&&...contiguousData_) : data({ static_cast<value_type>(std::forward<Args>(contiguousData_))... })
		{
			static_assert(sizeof...(Args) == size, "Provided an amount of arguments to an EmuMath Vector constructor that is not equal to the number of elements in the Vector.");
			static_assert
			(
				EmuCore::TMPHelpers::are_all_comparisons_true<std::is_constructible, contained_type, Args...>::value,
				"Attempted to construct an EmuMath Vector via it's template constructor, but at least one provided argument cannot be used to construct the Vector's value_type."
			);
		}

		template<std::size_t Index_>
		[[nodiscard]] constexpr inline value_type& at()
		{
			if constexpr (Index_ < size)
			{
				return std::get<Index_>(data);
			}
			else
			{
				static_assert(false, "Attempted to retrieve data from an EmuMath vector using an out-of-range index.");
			}
		}
		template<std::size_t Index_>
		[[nodiscard]] constexpr inline const value_type& at() const
		{
			if constexpr (Index_ < size)
			{
				return std::get<Index_>(data);
			}
			else
			{
				static_assert(false, "Attempted to retrieve data from an EmuMath vector using an out-of-range index.");
			}
		}
		[[nodiscard]] constexpr inline value_type& at(const std::size_t index_)
		{
			return data[index_];
		}
		[[nodiscard]] constexpr inline const value_type& at(const std::size_t index_) const
		{
			return data[index_];
		}
		[[nodiscard]] constexpr inline value_type& operator[](const std::size_t index_)
		{
			return this->at(index_);
		}
		[[nodiscard]] constexpr inline const value_type& operator[](const std::size_t index_) const
		{
			return this->at(index_);
		}

		template<std::size_t ToCopySize_, typename ToCopyValueType_>
		constexpr inline this_type& Copy(const Vector<ToCopySize_, ToCopyValueType_>& toCopy_)
		{
			return EmuMath::Helpers::VectorSet<this_type, Vector<ToCopySize_, ToCopyValueType_>>(*this, toCopy_);
		}

	private:
		/// <summary> The type used to store this vector's data. </summary>
		using data_storage_type = std::array<contained_type, size>;

		/// <summary> Contiguous data stored within this matrix. </summary>
		data_storage_type data;
	};
}

template<std::size_t Size_, typename T_>
inline std::ostream& operator<<(std::ostream& stream_, const EmuMath::Vector<Size_, T_>& vector_)
{
	return EmuMath::Helpers::_underlying_vector_funcs::_append_vector_to_stream(stream_, vector_);
}
template<std::size_t Size_, typename T_>
inline std::wostream& operator<<(std::wostream& stream_, const EmuMath::Vector<Size_, T_>& vector_)
{
	return EmuMath::Helpers::_underlying_vector_funcs::_append_vector_to_wide_stream(stream_, vector_);
}

#endif
