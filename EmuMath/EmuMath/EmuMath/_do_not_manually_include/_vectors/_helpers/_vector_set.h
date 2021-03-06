#ifndef EMU_MATH_vector_SET_H_INC_
#define EMU_MATH_vector_SET_H_INC_

#include "_common_vector_helpers.h"

// CONTAINS:
// --- set
// --- set_all
// --- set_contained_only
// --- make

namespace EmuMath::Helpers
{
	/// <summary>
	/// <para> Sets the specified index of the passed EmuMath Vector via the passed arguments. </para>
	/// <para> If 1 args_ is provided: The stored_type of `to_set_` must be assignable, convertible-to, or constructible from the provided argument type. </para>
	/// <para> If more than 1 args_ is provided: The stored_type of `to_set_` must be constructible from the provided argument types in the provided order. </para>
	/// </summary>
	/// <typeparam name="Args_">Arguments to use for setting the specified index.</typeparam>
	/// <param name="to_set_">EmuMath Vector to set the specified index of.</param>
	/// <param name="args_">Argument(s) to set the specified index via as described.</param>
	template<std::size_t Index_, class...Args_, typename T_, std::size_t Size_, typename = std::enable_if_t<sizeof...(Args_) != 0>>
	constexpr inline void vector_set(EmuMath::Vector<Size_, T_>& to_set_, Args_&&...args_)
	{
		_vector_underlying::_vector_set_scalar<Index_, Args_...>(to_set_, std::forward<Args_>(args_)...);
	}

	/// <summary>
	/// <para>
	///		Sets all indices inside a valid range within the passed EmuMath Vector via the provided arg_, 
	///		starting from BeginIndex_ (inclusive) and stopping at EndIndex_ (exclusive).
	/// </para>
	/// <para> By default, this affects all indices. EndIndex_ will be clamped into a valid range 0:size (inclusive). </para>
	/// <para> If `BeginIndex_ == EndIndex_`, this will do nothing. </para>
	/// <para> The stored_type of to_set_ must be assignable, convertible-to, or constructible from the provided arg_ type. </para>
	/// <para> If to_set_ contains references of any type, arg_ must not be temporary. </para>
	/// <para> If to_set_ contains non-const references of any type, arg_ must additionally not be constant </para>
	/// <para> Note that EndIndex_ is exclusive; if the final index to be updated is 3, for example, then the provided EndIndex_ should be 4. </para>
	/// </summary>
	/// <typeparam name="Arg_">Type used for the argument to set all elements via.</typeparam>
	/// <param name="to_set_">EmuMath Vector to set all elements of in the specified inclusive:exclusive range of BeginIndex_:EndIndex_.</param>
	/// <param name="arg_">Argument to set all elements via.</param>
	template<std::size_t BeginIndex_ = 0, std::size_t EndIndex_ = std::numeric_limits<std::size_t>::max(), class Arg_, typename T_, std::size_t Size_>
	constexpr inline void vector_set_all(EmuMath::Vector<Size_, T_>& to_set_, Arg_&& arg_)
	{
		_vector_underlying::_vector_set_all<BeginIndex_, EndIndex_, Arg_>(to_set_, std::forward<Arg_>(arg_));
	}
	template<std::size_t BeginIndex_ = 0, std::size_t EndIndex_ = std::numeric_limits<std::size_t>::max(), class Arg_, typename T_, std::size_t Size_>
	constexpr inline void vector_set_all(EmuMath::Vector<Size_, T_>& to_set_, const Arg_& arg_)
	{
		_vector_underlying::_vector_set_all<BeginIndex_, EndIndex_, const Arg_&>(to_set_, arg_);
	}
	template<std::size_t BeginIndex_ = 0, std::size_t EndIndex_ = std::numeric_limits<std::size_t>::max(), class Arg_, typename T_, std::size_t Size_>
	constexpr inline void vector_set_all(EmuMath::Vector<Size_, T_>& to_set_, Arg_& arg_)
	{
		_vector_underlying::_vector_set_all<BeginIndex_, EndIndex_, Arg_&>(to_set_, arg_);
	}

	/// <summary>
	/// <para> Sets the entire passed EmuMath Vector to_Set_ via the passed move_arg_ EmuMath Vector. </para>
	/// <para> If move_arg_ contains less elements than to_set_, to_set_ elements will be set via the inferred-zero for non-contained elements. </para>
	/// <para> If to_set_ contains references of any type, move_arg_ must have at least as many elements as to_set_, and must not be temporary. </para>
	/// <para> If to_set_ contains non-const references of any type, move_arg_ must additionally not be constant or contain constant values. </para>
	/// </summary>
	/// <param name="to_set_">EmuMath Vector to set all elements of.</param>
	/// <param name="move_arg_">EmuMath Vector to set to_set_ via.</param>
	template<typename T_, std::size_t Size_, std::size_t ArgSize_, typename ArgT_>
	constexpr inline void vector_set
	(
		EmuMath::Vector<Size_, T_>& to_set_,
		EmuMath::Vector<ArgSize_, ArgT_>&& move_arg_
	)
	{
		using arg_type = EmuMath::Vector<ArgSize_, ArgT_>;
		_vector_underlying::_vector_set_vector<true, arg_type, Size_, T_>(to_set_, std::forward<arg_type>(move_arg_));
	}

	/// <summary>
	/// <para> Sets the entire passed EmuMath Vector to_Set_ via the passed copy_arg_ EmuMath Vector. </para>
	/// <para> If copy_arg_ contains less elements than to_set_, to_set_ elements will be set via the inferred-zero for non-contained elements. </para>
	/// <para> If to_set_ contains references of any type, copy_arg_ must have at least as many elements as to_set_, and must not be temporary. </para>
	/// <para> If to_set_ contains non-const references of any type, copy_arg_ must additionally not be constant or contain constant values. </para>
	/// </summary>
	/// <param name="to_set_">EmuMath Vector to set all elements of.</param>
	/// <param name="copy_arg_">EmuMath Vector to set to_set_ via.</param>
	template<typename T_, std::size_t Size_, std::size_t ArgSize_, typename ArgT_>
	constexpr inline void vector_set
	(
		EmuMath::Vector<Size_, T_>& to_set_,
		EmuMath::Vector<ArgSize_, ArgT_>& copy_arg_
	)
	{
		using arg_type = EmuMath::Vector<ArgSize_, ArgT_>;
		_vector_underlying::_vector_set_vector<true, arg_type, Size_, T_>(to_set_, copy_arg_);
	}

	/// <summary>
	/// <para> Sets the entire passed EmuMath Vector to_Set_ via the passed copy_arg_ EmuMath Vector. </para>
	/// <para> If copy_arg_ contains less elements than to_set_, to_set_ elements will be set via the inferred-zero for non-contained elements. </para>
	/// <para> If to_set_ contains references of any type, copy_arg_ must have at least as many elements as to_set_, and must not be temporary. </para>
	/// <para> If to_set_ contains non-const references of any type, copy_arg_ must additionally not be constant or contain constant values. </para>
	/// </summary>
	/// <param name="to_set_">EmuMath Vector to set all elements of.</param>
	/// <param name="copy_arg_">EmuMath Vector to set to_set_ via.</param>
	template<typename T_, std::size_t Size_, std::size_t ArgSize_, typename ArgT_>
	constexpr inline void vector_set
	(
		EmuMath::Vector<Size_, T_>& to_set_,
		const EmuMath::Vector<ArgSize_, ArgT_>& copy_arg_
	)
	{
		using arg_type = const EmuMath::Vector<ArgSize_, ArgT_>;
		_vector_underlying::_vector_set_vector<true, arg_type, Size_, T_>(to_set_, copy_arg_);
	}

	/// <summary>
	/// <para> Sets EmuMath Vector to_Set_ via all respective shared indices in the passed move_arg_ EmuMath Vector. </para>
	/// <para> If move_arg_ contains less elements than to_set_, non-shared indices within to_set_ will not be modified. </para>
	/// <para> If to_set_ contains references of any type, move_arg_ must have at least as many elements as to_set_, and must not be temporary. </para>
	/// <para> If to_set_ contains non-const references of any type, move_arg_ must additionally not be constant or contain constant values. </para>
	/// </summary>
	/// <param name="to_set_">EmuMath Vector to set elements of.</param>
	/// <param name="move_arg_">EmuMath Vector to set to_set_ via.</param>
	template<typename T_, std::size_t Size_, std::size_t ArgSize_, typename ArgT_>
	constexpr inline void vector_set_contained_only
	(
		EmuMath::Vector<Size_, T_>& to_set_,
		EmuMath::Vector<ArgSize_, ArgT_>&& move_arg_
	)
	{
		using arg_type = EmuMath::Vector<ArgSize_, ArgT_>;
		_vector_underlying::_vector_set_vector<false, arg_type, Size_, T_>(to_set_, std::forward<arg_type>(move_arg_));
	}

	/// <summary>
	/// <para> Sets EmuMath Vector to_Set_ via all respective shared indices in the passed copy_arg_ EmuMath Vector. </para>
	/// <para> If copy_arg_ contains less elements than to_set_, non-shared indices within to_set_ will not be modified. </para>
	/// <para> If to_set_ contains references of any type, copy_arg_ must have at least as many elements as to_set_, and must not be temporary. </para>
	/// <para> If to_set_ contains non-const references of any type, copy_arg_ must additionally not be constant or contain constant values. </para>
	/// </summary>
	/// <param name="to_set_">EmuMath Vector to set elements of.</param>
	/// <param name="copy_arg_">EmuMath Vector to set to_set_ via.</param>
	template<typename T_, std::size_t Size_, std::size_t ArgSize_, typename ArgT_>
	constexpr inline void vector_set_contained_only
	(
		EmuMath::Vector<Size_, T_>& to_set_,
		EmuMath::Vector<ArgSize_, ArgT_>& copy_arg_
	)
	{
		using arg_type = EmuMath::Vector<ArgSize_, ArgT_>;
		_vector_underlying::_vector_set_vector<false, arg_type, Size_, T_>(to_set_, copy_arg_);
	}

	/// <summary>
	/// <para> Sets EmuMath Vector to_Set_ via all respective shared indices in the passed copy_arg_ EmuMath Vector. </para>
	/// <para> If copy_arg_ contains less elements than to_set_, non-shared indices within to_set_ will not be modified. </para>
	/// <para> If to_set_ contains references of any type, copy_arg_ must have at least as many elements as to_set_, and must not be temporary. </para>
	/// <para> If to_set_ contains non-const references of any type, copy_arg_ must additionally not be constant or contain constant values. </para>
	/// </summary>
	/// <param name="to_set_">EmuMath Vector to set elements of.</param>
	/// <param name="copy_arg_">EmuMath Vector to set to_set_ via.</param>
	template<typename T_, std::size_t Size_, std::size_t ArgSize_, typename ArgT_>
	constexpr inline void vector_set_contained_only
	(
		EmuMath::Vector<Size_, T_>& to_set_,
		const EmuMath::Vector<ArgSize_, ArgT_>& copy_arg_
	)
	{
		using arg_type = const EmuMath::Vector<ArgSize_, ArgT_>;
		_vector_underlying::_vector_set_vector<false, arg_type, Size_, T_>(to_set_, copy_arg_);
	}
}

namespace EmuMath
{
	/// <summary>
	/// <para> Creates an EmuMath Vector with the provided T_ argument, containing a number of elements equal to the provided number of construction_args_. </para>
	/// <para> All passed construction_args_ must be be valid construction arguments for the output Vector type, otherwise this function is disabled. </para>
	/// </summary>
	/// <typeparam name="T_">Type provided as T_ to the output Vector.</typeparam>
	/// <typeparam name="ConstructionArgs_">Types of all passed arguments. Must all be valid for construction of the output Vector type.</typeparam>
	/// <param name="construction_args_">Arguments to construct the output Vector via. The output Vector's size will be equal to the number of arguments provided.</param>
	/// <returns>
	///		EmuMath Vector with a Size_ argument equal to the number of provided construction_args_, and a T_ argument of T_,
	///		constructed with the passed construction_args_.
	/// </returns>
	template
	<
		typename T_,
		typename...ConstructionArgs_,
		typename = std::enable_if_t<std::is_constructible_v<EmuMath::Vector<sizeof...(ConstructionArgs_), T_>, ConstructionArgs_...>>
	>
	[[nodiscard]] constexpr inline EmuMath::Vector<sizeof...(ConstructionArgs_), T_> make_vector(ConstructionArgs_&&...construction_args_)
	{
		return EmuMath::Vector<sizeof...(ConstructionArgs_), T_>(std::forward<ConstructionArgs_>(construction_args_)...);
	}
}

#endif
