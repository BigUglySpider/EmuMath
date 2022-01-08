#ifndef EMU_CORE_VARIADIC_HELPERS_H_INC_
#define EMU_CORE_VARIADIC_HELPERS_H_INC_ 1

#include "TypeComparators.h"
#include <utility>

namespace EmuCore::TMP
{
#pragma region TEMPLATE_HELPERS
	/// <summary>
	/// <para> Helper to safely instantiate a Template_ from variadic Args_, cancelling instantiation if it is a failure. </para>
	/// <para> If instantiation fails, type will be void. Otherwise, it will be an instance of Template_ instantiated with the provided Args_. </para>
	/// <para> Static member value may also be used to determine success (true if successful, otherwise false). </para>
	/// </summary>
	/// <typeparam name="Args_">All type arguments to attempt to instantiate Template_ with.</typeparam>
	template<template<class...> class Template_, class...Args_>
	struct safe_template_instantiate
	{
	private:
		template<template<class...> class ToInstantiate_, bool IsValid_ = EmuCore::TMP::valid_template_args_v<ToInstantiate_, Args_...>>
		struct _instantiator
		{
			static constexpr bool value = false;
			using type = void;
		};
		template<template<class...> class ToInstantiate_>
		struct _instantiator<ToInstantiate_, true>
		{
			static constexpr bool value = true;
			using type = ToInstantiate_<Args_...>;
		};

		using _make_instance = _instantiator<Template_>;

	public:
		static constexpr bool value = _make_instance::value;
		using type = typename _make_instance::type;
	};

	/// <summary>
	/// <para> Helper to safely use std::invoke_result on a Func_ that may or may not be invocable with the provided Args_. </para>
	/// <para> Type will be void upon failure, but does not directly indicate failure. For such checks, use value, which will be true on success and false on failure. </para>
	/// </summary>
	/// <typeparam name="Args_">All types to invoke Func_ with.</typeparam>
	template<class Func_, class...Args_>
	struct safe_invoke_result
	{
	private:
		template<class ToInvoke_, bool IsInvocable_ = std::is_invocable_v<ToInvoke_, Args_...>>
		struct _checker
		{
			static constexpr bool value = false;
			using type = void;
		};
		template<class ToInvoke_>
		struct _checker<ToInvoke_, true>
		{
			static constexpr bool value = true;
			using type = std::invoke_result_t<ToInvoke_, Args_...>;
		};

		using _check = _checker<Func_>;

	public:
		static constexpr bool value = _check::value;
		using type = typename _check::type;
	};
#pragma endregion

#pragma region TYPE_EXTRACTORS
	/// <summary>
	/// <para> Aliases a type T_, and ignores the provided Discarded_ type. </para>
	/// <para> Primarily exists for producing a variadic sequence of the same type, with a count based on variadic types that are unused. </para>
	/// <para> Useful for forming generic EmuCore functors with fixed outputs (such as do_clamp&lt;void, void, void, float&gt;) in allowing situations. </para>
	/// </summary>
	template<class T_, class Discarded_>
	struct type_and_discard
	{
		using type = T_;
	};
	template<class T_, class Discarded_>
	using type_and_discard_t = typename type_and_discard<T_, Discarded_>::type;
#pragma endregion

#pragma region VARIADIC_BOOLS
	/// <summary> Type to easily produce the result of a logical AND with variadic template argument results. </summary>
	template<bool...Bools_>
	struct variadic_and
	{
		static constexpr bool value = false;
	};
	template<bool First_, bool...Remaining_>
	struct variadic_and<First_, Remaining_...>
	{
		static constexpr bool value = First_ ? variadic_and<Remaining_...>::value : false;
	};
	template<bool First_>
	struct variadic_and<First_>
	{
		static constexpr bool value = First_;
	};
	template<>
	struct variadic_and<>
	{
		static constexpr bool value = false;
	};
	template<bool...Bools_>
	static constexpr bool variadic_and_v = variadic_and<Bools_...>::value;

	/// <summary> Type to easily produce the result of a logical OR with variadic template argument results. </summary>
	template<bool...Bools_>
	struct variadic_or
	{
		static constexpr bool value = false;
	};
	template<bool First_, bool...Remaining_>
	struct variadic_or<First_, Remaining_...>
	{
		static constexpr bool value = First_ ? true : variadic_or<Remaining_...>::value;
	};
	template<bool First_>
	struct variadic_or<First_>
	{
		static constexpr bool value = First_;
	};
	template<>
	struct variadic_or<>
	{
		static constexpr bool value = false;
	};
	template<bool...Bools_>
	static constexpr bool variadic_or_v = variadic_or<Bools_...>::value;

	/// <summary> Type to easily produce the result of a logical XOR with variadic template argument results. </summary>
	template<bool...Bools_>
	struct variadic_xor
	{
	private:
		template<bool Current, bool...Bools_>
		struct _variadic_xor_executor
		{
			static constexpr bool value = Current;
		};
		template<bool Current_, bool First_, bool...Remaining_>
		struct _variadic_xor_executor<Current_, First_, Remaining_...>
		{
			[[nodiscard]] static constexpr inline bool _get()
			{
				if constexpr (Current_)
				{
					return First_ ? false : _variadic_xor_executor<Current_, Remaining_...>::value;
				}
				else
				{
					return _variadic_xor_executor<First_, Remaining_...>::value;
				}
			}

			static constexpr bool value = _get();
		};
		template<bool Current_, bool First_>
		struct _variadic_xor_executor<Current_, First_>
		{
			static constexpr bool value = Current_ ^ First_;
		};
		template<bool Current_>
		struct _variadic_xor_executor<Current_>
		{
			static constexpr bool value = Current_;
		};

	public:
		static constexpr bool value = _variadic_xor_executor<false, Bools_...>::value;
	};
	template<bool...Bools_>
	static constexpr bool variadic_xor_v = variadic_xor<Bools_...>::value;
#pragma endregion

#pragma region EXTRA_INDEX_SEQUENCES
	/// <summary> Type to create an Index_ sequence of the specified size similar to std::make_index_sequence, but starting at the provided Offset_ instead of 0. </summary>
	template<std::size_t Offset_, std::size_t Size_>
	struct offset_index_sequence_maker
	{
	private:
		template<std::size_t Remaining_, std::size_t Current_, typename Previous_>
		struct _maker
		{
			using type = void;
		};
		template<std::size_t Remaining_, std::size_t Current_, std::size_t...PreviousIndices_>
		struct _maker<Remaining_, Current_, std::index_sequence<PreviousIndices_...>>
		{
			using type = typename _maker<Remaining_ - 1, Current_ + 1, std::index_sequence<PreviousIndices_..., Current_>>::type;
		};
		template<std::size_t Current_, std::size_t...PreviousIndices_>
		struct _maker<0, Current_, std::index_sequence<PreviousIndices_...>>
		{
			using type = std::index_sequence<PreviousIndices_...>;
		};

	public:
		using type = typename _maker<Size_, Offset_, std::index_sequence<>>::type;
	};

	template<std::size_t Offset_, std::size_t Size_>
	using make_offset_index_sequence = typename offset_index_sequence_maker<Offset_, Size_>::type;

	/// <summary>
	///	<para> Type used to splice to index sequences into a single one. Indices in the left-hand sequence will all appear first, then those in the right-hand sequence. </para>
	/// <para> If an argument is not a std::index_sequence, it will be interpreted as an empty std::index_sequence. </para>
	/// </summary>
	template<class LhsIndexSequence_, class RhsIndexSequence_>
	struct splice_index_sequences
	{
		using type = std::index_sequence<>;
	};
	template<std::size_t...LhsIndices_, class Rhs_>
	struct splice_index_sequences<std::index_sequence<LhsIndices_...>, Rhs_>
	{
		using type = std::index_sequence<LhsIndices_...>;
	};
	template<class Lhs_, std::size_t...RhsIndices_>
	struct splice_index_sequences<Lhs_, std::index_sequence<RhsIndices_...>>
	{
		using type = std::index_sequence<RhsIndices_...>;
	};
	template<std::size_t...LhsIndices_, std::size_t...RhsIndices_>
	struct splice_index_sequences<std::index_sequence<LhsIndices_...>, std::index_sequence<RhsIndices_...>>
	{
		using type = std::index_sequence<LhsIndices_..., RhsIndices_...>;
	};
	template<class Lhs_, class Rhs_>
	using splice_index_sequences_t = typename splice_index_sequences<Lhs_, Rhs_>::type;

	/// <summary> Type used to form an index sequence containing only the specified Index_ the specified Count_ of times. </summary>
	template<std::size_t Index_, std::size_t Count_>
	struct duplicated_index_sequence
	{
		using type = typename splice_index_sequences
		<
			std::index_sequence<Index_>,
			typename duplicated_index_sequence<Index_, Count_ - 1>::type
		>::type;
	};
	template<std::size_t Index_>
	struct duplicated_index_sequence<Index_, 0>
	{
		using type = std::index_sequence<>;
	};
	template<std::size_t Index_>
	struct duplicated_index_sequence<Index_, 1>
	{
		using type = std::index_sequence<Index_>;
	};
	template<std::size_t Index_, std::size_t Count_>
	using make_duplicated_index_sequence = typename duplicated_index_sequence<Index_, Count_>::type;
#pragma endregion
}

#endif