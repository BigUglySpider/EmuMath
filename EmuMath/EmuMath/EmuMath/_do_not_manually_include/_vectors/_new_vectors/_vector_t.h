#ifndef EMU_MATH_NEW_VECTOR_T_H_INC_
#define EMU_MATH_NEW_VECTOR_T_H_INC_ 1

#include "_helpers/_vector_helpers.h"
#include <array>
#include <ostream>

namespace EmuMath
{
	/// <summary>
	/// <para> Mathematical Vector of any number of dimensions. </para>
	/// <para> 
	///		Provides support for Vectors of lvalue references.
	///		References to a type T are intended to be stored as vector_internal_ref&lt;T&gt;.
	///		As such, instantiations of `Vector&lt;size, T&amp;&gt;` are identical to instantiations of `Vector&lt;size, vector_internal_ref&lt;T&gt;&gt;`.
	/// </para>
	/// </summary>
	/// <typeparam name="T_">
	///		Type for this Vector to store.
	///		If T_ is an l-value reference type, it will be reinterpreted as `vector_internal_ref&lt;std::remove_ref_t&lt;T_&gt;&gt;`.
	/// </typeparam>
	template<std::size_t Size_, typename T_>
	struct NewVector
	{
#pragma region COMMON_STATIC_INFO
	public:
		using this_type = NewVector<Size_, T_>;
		using vector_info = EmuMath::TMP::common_vector_info<Size_, T_, true>;

		using stored_type = typename vector_info::stored_type;
		using value_type = typename vector_info::value_type;
		using value_type_uq = typename vector_info::value_type_uq;
		using alternative_rep = typename vector_info::alternative_vector_rep;
		friend typename alternative_rep;

		static constexpr std::size_t size = vector_info::size;
		static constexpr bool contains_ref = vector_info::contains_ref;
		static constexpr bool contains_const_ref = vector_info::contains_const_ref;
		static constexpr bool contains_non_const_ref = vector_info::contains_non_const_ref;
		static constexpr bool is_integral = vector_info::is_integral;
		static constexpr bool is_floating_point = vector_info::is_floating_point;
		static constexpr bool is_class = vector_info::is_class;
		static constexpr std::size_t element_byte_size = vector_info::element_byte_size;
		static constexpr bool is_default_constructible = vector_info::is_default_constructible;
		static constexpr bool has_alternative_representation = vector_info::has_alternative_representation;

		using data_storage_type = std::array<stored_type, size>;

		template<class...Args_>
		[[nodiscard]] static constexpr inline bool valid_template_construction_args()
		{
			return vector_info::template valid_template_construct_args<Args_...>();
		}

		template<std::size_t OtherSize_, typename OtherT_>
		[[nodiscard]] static constexpr inline bool valid_template_vector_copy_construct_arg()
		{
			return 
			(
				vector_info::template valid_template_vector_copy_construct_arg<OtherSize_, OtherT_>() &&
				!vector_info::template is_valid_lone_type_for_set_all_construction<EmuMath::NewVector<OtherSize_, OtherT_>&>()
			);
		}

		template<std::size_t OtherSize_, typename OtherT_>
		[[nodiscard]] static constexpr inline bool valid_template_vector_const_copy_construct_arg()
		{
			return 
			(
				vector_info::template valid_template_vector_const_copy_construct_arg<OtherSize_, OtherT_>() &&
				!vector_info::template is_valid_lone_type_for_set_all_construction<const EmuMath::NewVector<OtherSize_, OtherT_>&>()
			);
		}

		template<std::size_t OtherSize_, typename OtherT_>
		[[nodiscard]] static constexpr inline bool valid_template_vector_move_construct_arg()
		{
			return
			(
				vector_info::template valid_template_vector_move_construct_arg<OtherSize_, OtherT_>() &&
				!vector_info::template is_valid_lone_type_for_set_all_construction<EmuMath::NewVector<OtherSize_, OtherT_>&&>()
			);
		}

		template<std::size_t InSize_, typename InT_, bool in_is_const, bool in_is_temp>
		[[nodiscard]] static constexpr inline bool is_valid_vector_for_set()
		{
			return vector_info::template is_valid_vector_for_set<InSize_, InT_, in_is_const, in_is_temp>();
		}

		template<typename T_>
		[[nodiscard]] static constexpr inline bool is_valid_type_for_single_set()
		{
			return vector_info::template is_valid_type_for_single_set<T_>();
		}

		template<typename T_>
		[[nodiscard]] static constexpr inline bool is_valid_type_for_set_all()
		{
			return vector_info::template is_valid_type_for_set_all<T_>();
		}

		template<typename T_, bool WhileConst_>
		[[nodiscard]] static constexpr inline bool is_valid_try_get_output_ref()
		{
			return vector_info::template is_valid_try_get_output_ref<T_, WhileConst_>();
		}

		template<typename T_>
		[[nodiscard]] static constexpr inline bool is_valid_lone_type_for_set_all_construction()
		{
			return vector_info::template is_valid_lone_type_for_set_all_construction<T_>();
		}

		[[nodiscard]] static constexpr inline value_type_uq get_implied_zero()
		{
			return EmuMath::Helpers::new_vector_get_non_contained<this_type>();
		}

		template<typename Arg_>
		[[nodiscard]] static constexpr inline bool is_valid_template_copy_arg()
		{
			return vector_info::template is_valid_template_copy_arg<Arg_, false>();
		}

		template<typename Arg_>
		[[nodiscard]] static constexpr inline bool is_valid_template_assign_arg()
		{
			return vector_info::template is_valid_template_copy_arg<Arg_, true>();
		}

	private:
		struct _dummy_arg_for_private_lazy_default
		{
			constexpr inline _dummy_arg_for_private_lazy_default() {}
		};
#pragma endregion

#pragma region CONSTRUCTORS
	public:
		/// <summary>
		/// <para> Default constructs all elements within this Vector. </para>
		/// <para> This is only available for Vectors which contain default-constructible, non-reference types. </para>
		/// </summary>
		template<typename OnlyIfNonRefAndContainsDefaultConstructibles_ = std::enable_if_t<is_default_constructible>>
		constexpr inline NewVector() : _data()
		{
		}

		/// <summary>
		/// <para> Constructs a copy of the passed non-const Vector reference. </para>
		/// </summary>
		/// <param name="to_copy_">
		///		: Non-const reference to an EmuMath Vector to copy. If this vector contains references, it will reference the same data as the passed Vector.
		/// </param>
		constexpr inline NewVector(this_type& to_copy_) : _data(to_copy_._data)
		{
		}

		/// <summary>
		/// <para> Constructs a copy of the passed const Vector reference. </para>
		/// <para> This is only avaialble for Vectors which do not contain non-const references. </para>
		/// </summary>
		/// <param name="to_copy_">
		///		: Const reference to an EmuMath Vector to copy. If this vector contains references, it will reference the same data as the passed Vector.
		/// </param>
		template<typename = std::enable_if_t<!contains_non_const_ref>>
		constexpr inline NewVector(const this_type& to_copy_) : _data(to_copy_._data)
		{
		}

		/// <summary>
		/// <para> Moves the data of the passed Vector reference into a newly constructed Vector. </para>
		/// </summary>
		/// <param name="to_move_">: Vector to move into the newly constructed vector.</param>
		constexpr inline NewVector(this_type&& to_move_) noexcept : _data(std::move(to_move_._data))
		{
		}

		/// <summary>
		/// <para> 
		///		Constructs a copy of the passed non-const Vector reference,
		///		whose underlying structure is the same as this Vector but with different template arguments.
		/// </para>
		/// <para> This is only available for reference-containing Vectors, where has_alternative_representation is true. </para>
		/// <para> If this construction method is invalid, the input type for this constructor will be std::false_type. </para>
		/// </summary>
		/// <param name="to_copy_">
		///		: Non-const reference to an EmuMath Vector to copy. If this vector contains references, it will reference the same data as the passed Vector.
		/// </param>
		template<typename OnlyIfAlternativeRepExists_ = std::enable_if_t<has_alternative_representation>>
		constexpr inline NewVector(alternative_rep& to_copy_) : _data(to_copy_._data)
		{
		}

		/// <summary>
		/// <para> 
		///		Constructs a copy of the passed const Vector reference,
		///		whose underlying structure is the same as this Vector but with different template arguments.
		/// </para>
		/// <para> This is only available for const-reference-containing Vectors, where has_alternative_representation is true. </para>
		/// <para> If there is no alternative representation, the input type for this constructor will be std::false_type. </para>
		/// </summary>
		/// <param name="to_copy_">
		///		: Const reference to an EmuMath Vector to copy. If this vector contains references, it will reference the same data as the passed Vector.
		/// </param>
		template<typename OnlyIfAlternativeRepExists_ = std::enable_if_t<has_alternative_representation && !contains_non_const_ref>>
		constexpr inline NewVector(const alternative_rep& to_copy_) : _data(to_copy_._data)
		{
		}

		/// <summary>
		/// <para> 
		///		Moves the data of the passed Vector reference, whose underlying structure is the same as this Vector but with different template arguments,
		///		into a newly constructed Vector.
		/// </para>
		/// <para> This is only available for reference-containing Vectors, where has_alternative_representation is true. </para>
		/// <para> If there is no alternative representation, the input type for this constructor will be std::false_type. </para>
		/// </summary>
		/// <param name="to_move_">: EmuMath Vector to move into the newly constructed vector.</param>
		template<typename OnlyIfAlternativeRepExists_ = std::enable_if_t<has_alternative_representation>>
		constexpr inline NewVector(alternative_rep&& to_move_) noexcept : _data(std::move(to_move_._data))
		{
		}

		/// <summary>
		/// <para> Constructs a Vector with custom template arguments, where each argument is used to construct the respective element within the new Vector. </para>
		/// <para> Only 1 argument may be provided per element, and the provided number of arguments must be equal to this vector's size. </para>
		/// <para> Additionally, provided arguments must be valid for constructing this Vector's stored_type. </para>
		/// <para> Provided arguments represent elements in order from index 0 to the final index (e.g. 0, 1, 2...n-1 in a vector of size n). </para>
		/// </summary>
		/// <typeparam name="ConstructionArgs_">Types of all provided arguments provided for construction.</typeparam>
		/// <param name="construction_args_"> 
		///		: Ordered arguments representing respective elements within the constructed Vector, used to construct their respective element.
		/// </param>
		template
		<
			class...ConstructionArgs_,
			typename = std::enable_if_t<valid_template_construction_args<ConstructionArgs_...>()>
		>
		explicit constexpr inline NewVector(ConstructionArgs_&&...construction_args_) : 
			_data({ stored_type(std::forward<ConstructionArgs_>(construction_args_))... })
		{
		}

		/// <summary>
		/// <para> Constructs this Vector as a copy of the provided EmuMath Vector. </para>
		/// <para> If this Vector contains more elements than the passed Vector to_copy_, non-contained elements will be interpreted as implied zeroes. </para>
		/// <para> If this Vector contains references, the passed Vector to_copy_ must contain at least as many elements as this Vector. </para>
		/// </summary>
		/// <param name="to_copy_">: Non-constant reference to an EmuMath Vector to copy into the newly constructed Vector.</param>
		template
		<
			std::size_t OtherSize_,
			typename OtherT_,
			typename = std::enable_if_t<valid_template_vector_copy_construct_arg<OtherSize_, OtherT_>()>
		>
		explicit constexpr inline NewVector(EmuMath::NewVector<OtherSize_, OtherT_>& to_copy_) : NewVector(_dummy_arg_for_private_lazy_default())
		{
			EmuMath::Helpers::new_vector_set(*this, to_copy_);
		}

		/// <summary>
		/// <para> Constructs this Vector as a copy of the provided EmuMath Vector. </para>
		/// <para> If this Vector contains more elements than the passed Vector to_copy_, non-contained elements will be interpreted as implied zeroes. </para>
		/// <para> If this Vector contains references, the passed Vector to_copy_ must contain at least as many elements as this Vector. </para>
		/// <para> This constructor is not available for Vectors which contain non-const references.</para>
		/// </summary>
		/// <param name="to_copy_">: Constant reference to an EmuMath Vector to copy into the newly constructed Vector.</param>
		template
		<
			std::size_t OtherSize_,
			typename OtherT_,
			typename = std::enable_if_t<valid_template_vector_const_copy_construct_arg<OtherSize_, OtherT_>() && !contains_non_const_ref>
		>
		explicit constexpr inline NewVector(const EmuMath::NewVector<OtherSize_, OtherT_>& to_copy_) : NewVector(_dummy_arg_for_private_lazy_default())
		{
			EmuMath::Helpers::new_vector_set(*this, to_copy_);
		}

		/// <summary>
		/// <para> Constructs this Vector as a copy of the provided EmuMath Vector, which attempts to move its contained elements. </para>
		/// <para> If this Vector contains more elements than the passed Vector to_move_, non-contained elements will be interpreted as implied zeroes. </para>
		/// <para> If this Vector contains references, the passed Vector to_move_ must contain at least as many elements as this Vector. </para>
		/// <para> This constructor is not available for Vectors which contain non-const references. </para>
		/// </summary>
		/// <param name="to_move_">: rvalue reference to an EmuMath Vector to copy into the newly constructed Vector, with attempts to move used elements.</param>
		template
		<
			std::size_t OtherSize_,
			typename OtherT_,
			typename = std::enable_if_t<valid_template_vector_move_construct_arg<OtherSize_, OtherT_>()>
		>
		explicit constexpr inline NewVector(EmuMath::NewVector<OtherSize_, OtherT_>&& to_move_) : NewVector(_dummy_arg_for_private_lazy_default())
		{
			// Checks are here so that temporaries aren't resolved to the const copy constructor
			// --- This comes with the unfortunate effect that this constructor may appear usable in TMP in situations where it is not
			// ------ This is, however, considered better than allowing silent dangling references to form
			if constexpr (contains_ref)
			{
				if constexpr (!EmuMath::NewVector<OtherSize_, OtherT_>::contains_ref)
				{
					static_assert(false, "Attempted to construct a reference-containing EmuMath Vector via a temporary EmuMath Vector that does not contain references. This behaviour will result in dangling references, and has been prohibited as a result.");
				}
				else
				{
					EmuMath::Helpers::new_vector_set(*this, std::move(to_move_));
				}
			}
			else
			{
				EmuMath::Helpers::new_vector_set(*this, std::move(to_move_));
			}
		}

		template
		<
			typename InT_,
			typename = std::enable_if_t<is_valid_lone_type_for_set_all_construction<InT_&&>()>
		>
		explicit constexpr inline NewVector(InT_&& to_set_all_to_) : NewVector(_dummy_arg_for_private_lazy_default())
		{
			SetAll(std::forward<InT_>(to_set_all_to_));
		}

		template
		<
			typename InT_,
			typename = std::enable_if_t<is_valid_lone_type_for_set_all_construction<InT_&>()>
		>
		explicit constexpr inline NewVector(InT_& to_set_all_to_) : NewVector(_dummy_arg_for_private_lazy_default())
		{
			SetAll(to_set_all_to_);
		}

		template
		<
			typename InT_,
			typename = std::enable_if_t<is_valid_lone_type_for_set_all_construction<const InT_&>()>
		>
		explicit constexpr inline NewVector(const InT_& to_set_all_to_) : NewVector(_dummy_arg_for_private_lazy_default())
		{
			SetAll(to_set_all_to_);
		}

	private:
		// Empty constructor used to perform a lazy-default when construction is executed within the constructor body; inaccessible out of this struct
		// --- Disable warning about uninitialised data since that's the point of this constructor
#pragma warning(disable : 26495)
		explicit constexpr inline NewVector(_dummy_arg_for_private_lazy_default dummy_arg_)
		{
		}
#pragma endregion

#pragma region ACCESS
	public:
		/// <summary>
		/// <para> Provides safe access to the provided Index_ within this Vector. If the Index_ is invalid, a compile-time error will be generated. </para>
		/// </summary>
		/// <returns>Reference to the element at the provided index within this Vector.</returns>
		template<std::size_t Index_>
		[[nodiscard]] constexpr inline value_type& at()
		{
			if constexpr (Index_ < size)
			{
				return std::get<Index_>(_data);
			}
			else
			{
				static_assert(false, "Attempted to access an element at an invalid Index_ within an EmuMath Vector via its template `at<Index_>` member. Valid indices are in the inclusive range 0:size.");
			}
		}
		/// <summary>
		/// <para> Provides safe const access to the provided Index_ within this Vector. If the Index_ is invalid, a compile-time error will be generated. </para>
		/// </summary>
		/// <returns>Const reference to the element at the provided index within this Vector.</returns>
		template<std::size_t Index_>
		[[nodiscard]] constexpr inline const value_type& at() const
		{
			return const_cast<this_type*>(this)->template at<Index_>();
		}

		/// <summary>
		/// <para> Provides access to the provided Index_ within this Vector. If the Index_ is invalid, behaviour is undefined. </para>
		/// <para> If the provided index_ is known at compile-time, it is recommended to use the template version of this function to enforce index safety. </para>
		/// </summary>
		/// <returns>Reference to the element at the provided index within this Vector.</returns>
		[[nodiscard]] constexpr inline value_type& at(const std::size_t index_)
		{
			return _data.at(index_);
		}
		/// <summary>
		/// <para> Provides const access to the provided Index_ within this Vector. If the Index_ is invalid, behaviour is undefined. </para>
		/// <para> If the provided index_ is known at compile-time, it is recommended to use the template version of this function to enforce index safety. </para>
		/// </summary>
		/// <returns>Reference to the element at the provided index within this Vector.</returns>
		[[nodiscard]] constexpr inline const value_type& at(const std::size_t index_) const
		{
			return const_cast<this_type*>(this)->at(index_);
		}
		/// <summary>
		/// <para> Provides access to the provided Index_ within this Vector. If the Index_ is invalid, behaviour is undefined. </para>
		/// <para> If the provided index_ is known at compile-time, it is recommended to use the template version of the `at` function to enforce index safety. </para>
		/// </summary>
		/// <returns>Reference to the element at the provided index within this Vector.</returns>
		[[nodiscard]] constexpr inline value_type& operator[](const std::size_t index_)
		{
			return at(index_);
		}
		/// <summary>
		/// <para> Provides const access to the provided Index_ within this Vector. If the Index_ is invalid, behaviour is undefined. </para>
		/// <para> If the provided index_ is known at compile-time, it is recommended to use the template version of the `at` function to enforce index safety. </para>
		/// </summary>
		/// <returns>Reference to the element at the provided index within this Vector.</returns>
		[[nodiscard]] constexpr inline const value_type& operator[](const std::size_t index_) const
		{
			return at(index_);
		}

		/// <summary>
		/// <para> Returns the item theoretically stored at the provided index within this Vector. </para>
		/// <para> If Index_ is a valid contained index within this Vector (0:size-1, inclusive): Returns a value_type reference to the item at the provided Index_. </para>
		/// <para> If none of the above is true: Returns an implied-zero, newly constructed value_type_uq. </para>
		/// </summary>
		/// <returns>Result of `at&lt;Index_&gt;()` if Index_ is a valid contained index in this Vector; otherwise, result of `get_implied_zero()`.</returns>
		template<std::size_t Index_>
		[[nodiscard]] constexpr inline EmuMath::TMP::emu_vector_theoretical_return_t<Index_, this_type> AtTheoretical()
		{
			return EmuMath::Helpers::new_vector_get_theoretical<Index_>(*this);
		}
		/// <summary>
		/// <para> Returns the item theoretically stored at the provided index within this Vector. </para>
		/// <para> If Index_ is a valid contained index within this Vector (0:size-1, inclusive): Returns a const value_type reference to the item at the provided Index_. </para>
		/// <para> If none of the above is true: Returns an implied-zero, newly constructed value_type_uq. </para>
		/// </summary>
		/// <returns>Result of `at&lt;Index_&gt;()` if Index_ is a valid contained index in this Vector; otherwise, result of `get_implied_zero()`.</returns>
		template<std::size_t Index_>
		[[nodiscard]] constexpr inline EmuMath::TMP::emu_vector_theoretical_return_t<Index_, const this_type> AtTheoretical() const
		{
			return EmuMath::Helpers::new_vector_get_theoretical<Index_>(*this);
		}

		/// <summary>
		/// <para> Attempts to retrieve the specified index_ within this Vector, outputting the element via out_ if the index_ is valid. </para>
		/// <para>
		///		Out_ must be assignable, convertible-to, or constructible from a reference to this Vector's value_type. 
		///		Assignment will be prioritised over conversion, and conversion will be prioritised over construction.
		/// </para>
		/// </summary>
		/// <typeparam name="Out_">Type of reference provided to output to via out_.</typeparam>
		/// <param name="index_">: Index to try and retrieve an element from within this Vector.</param>
		/// <param name="out_"> 
		///		: Reference to output to if the get is successful. Must be assignable, convertible-to, or constructible from a reference to this Vector's value_type.
		/// </param>
		/// <returns>True if the provided index is valid, otherwise false.</returns>
		template<typename Out_, typename = std::enable_if_t<is_valid_try_get_output_ref<Out_, false>()>>
		[[nodiscard]] constexpr inline bool TryAt(const std::size_t index_, Out_& out_)
		{
			return EmuMath::Helpers::vector_try_get<Out_, Size_, T_>(*this, index_, out_);
		}
		/// <summary>
		/// <para> Attempts to retrieve the specified index_ within this Vector, outputting the element via out_ if the index_ is valid. </para>
		/// <para>
		///		Out_ must be assignable, convertible-to, or constructible from a reference to this Vector's value_type. 
		///		Assignment will be prioritised over conversion, and conversion will be prioritised over construction.
		/// </para>
		/// </summary>
		/// <typeparam name="Out_">Type of reference provided to output to via out_.</typeparam>
		/// <param name="index_">: Index to try and retrieve an element from within this Vector.</param>
		/// <param name="out_"> 
		///		: Reference to output to if the get is successful. Must be assignable, convertible-to, or constructible from a const reference to this Vector's value_type.
		/// </param>
		/// <returns>True if the provided index is valid, otherwise false.</returns>
		template<typename Out_, typename = std::enable_if_t<is_valid_try_get_output_ref<Out_, true>()>>
		[[nodiscard]] constexpr inline bool TryAt(const std::size_t index_, Out_& out_) const
		{
			return EmuMath::Helpers::vector_try_get<Out_, Size_, T_>(*this, index_, out_);
		}

		/// <summary>
		/// <para> 
		///		Attempts to retrieve the specified index_ within this Vector,
		///		outputting a pointer to the element to the pointer pointed to by pp_out_
		/// </para>
		/// <para> If index_ is a valid index: The pointer pointed to by pp_out_ will be set to point to the element at the provided index in this Vector. </para>
		/// <para> If index_ is an invalid index: The pointer pointed to by pp_out_ will be set to nullptr if NullptrIfFailed_ is true; otherwise it will be unmodified. </para>
		/// </summary>
		/// <param name="index_">: Index to try and retrieve a pointer to within this Vector.</param>
		/// <param name="pp_out_">Non-const pointer to the pointer to output to.</param>
		/// <returns>True if the provided index is valid, otherwise false.</returns>
		template<bool NullptrIfFailed_ = false>
		[[nodiscard]] constexpr inline bool TryAt(const std::size_t index_, value_type** pp_out_)
		{
			return EmuMath::Helpers::vector_try_get<NullptrIfFailed_, Size_, T_>(*this, index_, pp_out_);
		}
		/// <summary>
		/// <para> 
		///		Attempts to retrieve the specified index_ within this Vector,
		///		outputting a const pointer to the element to the pointer pointed to by pp_const_out_.
		/// </para>
		/// <para> If index_ is a valid index: The const pointer pointed to by pp_const_out_ will be set to point to the element at the provided index in this Vector. </para>
		/// <para> 
		///		If index_ is an invalid index: The const pointer pointed to by pp_const_out_ will be set to nullptr if NullptrIfFailed_ is true; 
		///		otherwise it will be unmodified.
		/// </para>
		/// </summary>
		/// <param name="index_">: Index to try and retrieve a constant pointer to within this Vector.</param>
		/// <param name="pp_const_out_">Const pointer to the pointer to output to.</param>
		/// <returns>True if the provided index is valid, otherwise false.</returns>
		template<bool NullptrIfFailed_ = false>
		[[nodiscard]] constexpr inline bool TryAt(const std::size_t index_, const value_type** pp_const_out_) const
		{
			return EmuMath::Helpers::vector_try_get<NullptrIfFailed_, Size_, T_>(*this, index_, pp_const_out_);
		}

		/// <summary>
		/// <para> Shorthand for `TryAt` with the same arguments and const state. </para>
		/// <para> Attempts to retrieve the specified index_ within this Vector, outputting the element via out_ if the index_ is valid. </para>
		/// <para>
		///		Out_ must be assignable, convertible-to, or constructible from a reference to this Vector's value_type. 
		///		Assignment will be prioritised over conversion, and conversion will be prioritised over construction.
		/// </para>
		/// </summary>
		/// <typeparam name="Out_">Type of reference provided to output to via out_.</typeparam>
		/// <param name="index_">: Index to try and retrieve an element from within this Vector.</param>
		/// <param name="out_"> 
		///		: Reference to output to if the get is successful. Must be assignable, convertible-to, or constructible from a reference to this Vector's value_type.
		/// </param>
		/// <returns>True if the provided index is valid, otherwise false.</returns>
		template<typename Out_, typename = std::enable_if_t<is_valid_try_get_output_ref<Out_, false>()>>
		[[nodiscard]] constexpr inline bool operator()(const std::size_t index_, Out_& out_)
		{
			return TryAt(index_, out_);
		}
		/// <summary>
		/// <para> Shorthand for `TryAt` with the same arguments and const state. </para>
		/// <para> Attempts to retrieve the specified index_ within this Vector, outputting the element via out_ if the index_ is valid. </para>
		/// <para>
		///		Out_ must be assignable, convertible-to, or constructible from a reference to this Vector's value_type. 
		///		Assignment will be prioritised over conversion, and conversion will be prioritised over construction.
		/// </para>
		/// </summary>
		/// <typeparam name="Out_">Type of reference provided to output to via out_.</typeparam>
		/// <param name="index_">: Index to try and retrieve an element from within this Vector.</param>
		/// <param name="out_"> 
		///		: Reference to output to if the get is successful. Must be assignable, convertible-to, or constructible from a const reference to this Vector's value_type.
		/// </param>
		/// <returns>True if the provided index is valid, otherwise false.</returns>
		template<typename Out_, typename = std::enable_if_t<is_valid_try_get_output_ref<Out_, true>()>>
		[[nodiscard]] constexpr inline bool operator()(const std::size_t index_, Out_& out_) const
		{
			return TryAt(index_, out_);
		}

		/// <summary>
		/// <para> Shorthand for `TryAt` with the same arguments. </para>
		/// <para> 
		///		Attempts to retrieve the specified index_ within this Vector,
		///		outputting a pointer to the element to the pointer pointed to by pp_out_
		/// </para>
		/// <para> If index_ is a valid index: The pointer pointed to by pp_out_ will be set to point to the element at the provided index in this Vector. </para>
		/// <para> If index_ is an invalid index: The pointer pointed to by pp_out_ will be set to nullptr if NullptrIfFailed_ is true; otherwise it will be unmodified. </para>
		/// </summary>
		/// <param name="index_">: Index to try and retrieve a pointer to within this Vector.</param>
		/// <param name="pp_out_">Non-const pointer to the pointer to output to.</param>
		/// <returns>True if the provided index is valid, otherwise false.</returns>
		template<bool NullptrIfFailed_ = false>
		[[nodiscard]] constexpr inline bool operator()(const std::size_t index_, value_type** pp_out_)
		{
			return TryAt<NullptrIfFailed_>(index_, pp_out_);
		}
		/// <summary>
		/// <para> Shorthand for `TryAt` with the same arguments. </para>
		/// <para> 
		///		Attempts to retrieve the specified index_ within this Vector,
		///		outputting a const pointer to the element to the pointer pointed to by pp_const_out_.
		/// </para>
		/// <para> If index_ is a valid index: The const pointer pointed to by pp_const_out_ will be set to point to the element at the provided index in this Vector. </para>
		/// <para> 
		///		If index_ is an invalid index: The const pointer pointed to by pp_const_out_ will be set to nullptr if NullptrIfFailed_ is true; 
		///		otherwise it will be unmodified.
		/// </para>
		/// </summary>
		/// <param name="index_">: Index to try and retrieve a constant pointer to within this Vector.</param>
		/// <param name="pp_const_out_">Const pointer to the pointer to output to.</param>
		/// <returns>True if the provided index is valid, otherwise false.</returns>
		template<bool NullptrIfFailed_ = false>
		[[nodiscard]] constexpr inline bool operator()(const std::size_t index_, const value_type** pp_const_out_) const
		{
			return TryAt<NullptrIfFailed_>(index_, pp_const_out_);
		}

		/// <summary>
		/// <para> Provides a pointer to the start of contiguous data within this Vector. </para>
		/// <para> If this Vector contains references, this will generate a compile-time error, since contiguous data is not guaranteed to be referenced. </para>
		/// </summary>
		/// <returns>Pointer to the 0th element within this Vector.</returns>
		[[nodiscard]] constexpr inline stored_type* data()
		{
			if constexpr (!contains_ref)
			{
				return _data.data();
			}
			else
			{
				static_assert(false, "Attempted to access a contiguous data pointer of an EmuMath Vector which contains references. This behaviour is prohibited.");
			}
		}
		/// <summary>
		/// <para> Provides a const pointer to the start of contiguous data within this Vector. </para>
		/// <para> If this Vector contains references, this will generate a compile-time error, since contiguous data is not guaranteed to be referenced. </para>
		/// </summary>
		/// <returns>Const pointer to the 0th element within this Vector.</returns>
		[[nodiscard]] constexpr inline const stored_type* data() const
		{
			return const_cast<this_type*>(this)->data();
		}

		/// <summary>
		/// <para> Provides a pointer to the start of contiguous data within this Vector from the specified Index_. </para>
		/// <para> If this Vector contains references, this will generate a compile-time error, since contiguous data is not guaranteed to be referenced. </para>
		/// </summary>
		/// <returns>Pointer to the start of the element within this Vector at the provided Index_.</returns>
		template<std::size_t Index_>
		[[nodiscard]] constexpr inline stored_type* data()
		{
			if constexpr (Index_ < size)
			{
				return data() + Index_;
			}
			else
			{
				static_assert(false, "Attempted to access a contiguous data pointer of an EmuMath Vector from a specified Index_, but the provided Index_ was invalid. The valid index range is 0:size-1 (inclusive).");
			}
		}
		/// <summary>
		/// <para> Provides a const pointer to the start of contiguous data within this Vector from the specified Index_. </para>
		/// <para> If this Vector contains references, this will generate a compile-time error, since contiguous data is not guaranteed to be referenced. </para>
		/// </summary>
		/// <returns>Const pointer to the start of the element within this Vector at the provided Index_.</returns>
		template<std::size_t Index_>
		[[nodiscard]] constexpr inline const stored_type* data() const
		{
			return const_cast<this_type*>(this)->template data<Index_>();
		}
#pragma endregion

#pragma region ASSIGNMENT_OPERATORS
		constexpr inline this_type& operator=(this_type&& to_move_) noexcept
		{
			_data = std::move(to_move_._data);
			return *this;
		}

		template<typename = std::enable_if_t<has_alternative_representation>>
		constexpr inline this_type& operator=(alternative_rep&& to_move_) noexcept
		{
			_data = std::move(to_move_._data);
			return *this;
		}

		constexpr inline this_type& operator=(this_type& to_copy_)
		{
			if constexpr (contains_ref)
			{
				Copy(to_copy_);
			}
			else
			{
				_data = to_copy_._data;
			}
			return *this;
		}
		template<typename = std::enable_if_t<has_alternative_representation>>
		constexpr inline this_type& operator=(alternative_rep& to_copy_)
		{
			if constexpr (contains_ref)
			{
				Copy(to_copy_);
			}
			else
			{
				_data = to_copy_._data;
			}
			return *this;
		}

		constexpr inline this_type& operator=(const this_type& to_copy_)
		{
			if constexpr (contains_ref)
			{
				Copy(to_copy_);
			}
			else
			{
				_data = to_copy_._data;
			}
			return *this;
		}
		template<typename = std::enable_if_t<has_alternative_representation>>
		constexpr inline this_type& operator=(const alternative_rep& to_copy_)
		{
			if constexpr (contains_ref)
			{
				Copy(to_copy_);
			}
			else
			{
				_data = to_copy_._data;
			}
			return *this;
		}

		template<class Arg_, typename = std::enable_if_t<is_valid_template_assign_arg<Arg_>()>>
		constexpr inline this_type& operator=(Arg_& to_copy_)
		{
			Copy(to_copy_);
			return *this;
		}
		template<class Arg_, typename = std::enable_if_t<is_valid_template_assign_arg<const Arg_>()>>
		constexpr inline this_type& operator=(const Arg_& to_copy_)
		{
			Copy(to_copy_);
			return *this;
		}
#pragma endregion

#pragma region CONVERSIONS
		/// <summary>
		/// <para> Converts this Vector to its alternative template representation, if it has one. </para>
		/// <para> This is purely to convert reference-containing vectors between their `T_&amp;` and `internal_vector_reference&lt;T_&gt;` variants. </para>
		/// <para>
		///		For example, `Vector&lt;size, float&amp;&gt;` instantiates an identical type to `Vector&lt;size, internal_vector_reference&lt;float&gt;&gt;`,
		///		in terms of implementation and functionality; the only difference is the type in the template signature.
		/// </para>
		/// <para> This is not available for Vectors that do not have an alternative template representation. </para>
		/// </summary>
		/// <returns>Alternative template representation of this Vector to create the same underlying structure, (non-const) copying this Vector's internals.</returns>
		template<typename = std::enable_if_t<has_alternative_representation>>
		[[nodiscard]] constexpr inline alternative_rep AsAlternativeRep()
		{
			return alternative_rep(*this);
		}

		/// <summary>
		/// <para> Converts this Vector to its alternative template representation, if it has one. </para>
		/// <para> This is purely to convert reference-containing vectors between their `T_&amp;` and `internal_vector_reference&lt;T_&gt;` variants. </para>
		/// <para>
		///		For example, `Vector&lt;size, float&amp;&gt;` instantiates an identical type to `Vector&lt;size, internal_vector_reference&lt;float&gt;&gt;`,
		///		in terms of implementation and functionality; the only difference is the type in the template signature.
		/// </para>
		/// <para> This is not available for Vectors that do not have an alternative template representation. </para>
		/// <para> This const variant is further not available for Vectors that contain non-const references. </para>
		/// </summary>
		/// <returns>Alternative template representation of this Vector to create the same underlying structure, (const) copying this Vector's internals.</returns>
		template<typename = std::enable_if_t<has_alternative_representation && !contains_non_const_ref>>
		[[nodiscard]] constexpr inline alternative_rep AsAlternativeRep() const
		{
			return alternative_rep(*this);
		}
#pragma endregion

#pragma region COPIES
		/// <summary>
		/// <para> Copies the provided argument to this Vector's elements. </para>
		/// <para> If this Vector contains references, this will copy the provided Arg_ to the referenced value_types. </para>
		/// <para>
		///		If to_copy_ is an EmuMath Vector: Respective indices will be copied (e.g. this[1] = to_copy_[1]).
		///		Non-contained elements will be interpreted as implied-zeroes.
		/// </para>
		/// <para> If to_copy_ is none of the above: All indices will be set as a copy of to_copy_. </para>
		/// </summary>
		/// <param name="to_copy_">Argument to copy to indices as described.</param>
		template<typename Arg_, typename = std::enable_if_t<is_valid_template_copy_arg<Arg_&>()>>
		constexpr inline void Copy(Arg_& to_copy_)
		{
			EmuMath::Helpers::new_vector_copy<Arg_>(*this, to_copy_);
		}
		template<typename Arg_, typename = std::enable_if_t<is_valid_template_copy_arg<Arg_&>()>>
		constexpr inline void Copy(const Arg_& to_copy_)
		{
			EmuMath::Helpers::new_vector_copy<Arg_>(*this, to_copy_);
		}

		/// <summary>
		/// <para> Copies the provided argument to this Vector's elements within the provided index range. </para>
		/// <para> If this Vector contains references, this will copy the provided Arg_ to the referenced value_types. </para>
		/// <para>
		///		If to_copy_ is an EmuMath Vector: Respective indices will be copied (e.g. this[1] = to_copy_[1]).
		///		Non-contained elements will be interpreted as implied-zeroes.
		/// </para>
		/// <para> If to_copy_ is none of the above: All indices will be set as a copy of to_copy_. </para>
		/// </summary>
		/// <param name="to_copy_">Argument to copy to the provided index range as described.</param>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Arg_>
		constexpr inline void Copy(Arg_& to_copy_)
		{
			EmuMath::Helpers::new_vector_copy<BeginIndex_, EndIndex_, Arg_>(*this, to_copy_);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Arg_>
		constexpr inline void Copy(const Arg_& to_copy_)
		{
			EmuMath::Helpers::new_vector_copy<BeginIndex_, EndIndex_, Arg_>(*this, to_copy_);
		}

		/// <summary>
		/// <para> Copies the provided argument to this Vector's elements within the provided index range. </para>
		/// <para> If this Vector contains references, this will copy the provided Arg_ to the referenced value_types. </para>
		/// <para>
		///		If to_copy_ is an EmuMath Vector: Respective indices will be copied (e.g. this[1] = to_copy_[1]).
		///		Non-contained elements will be interpreted as implied-zeroes if CopyNonContained_ is true; otherwise, non-shared indices will not be modified.
		/// </para>
		/// <para> If to_copy_ is none of the above: All indices will be set as a copy of to_copy_. </para>
		/// </summary>
		/// <param name="to_copy_">Argument to copy to the provided index range as described.</param>
		template<bool CopyNonContained_, typename Arg_>
		constexpr inline void Copy(Arg_& to_copy_)
		{
			EmuMath::Helpers::new_vector_copy<CopyNonContained_, Arg_>(*this, to_copy_);
		}
		template<bool CopyNonContained_, typename Arg_>
		constexpr inline void Copy(const Arg_& to_copy_)
		{
			EmuMath::Helpers::new_vector_copy<CopyNonContained_, Arg_>(*this, to_copy_);
		}

		/// <summary>
		/// <para> Copies the provided argument to this Vector's elements within the provided index range. </para>
		/// <para> If this Vector contains references, this will copy the provided Arg_ to the referenced value_types. </para>
		/// <para>
		///		If to_copy_ is an EmuMath Vector: Progressively iterating indices from 0 will be copied (e.g. this[BeginIndex_ + 1] = to_copy_[1]).
		///		Non-contained elements will be interpreted as implied-zeroes. 
		///		Reading of to_copy_ will start at index 0; to begin reading from BeginIndex_, use `Copy`.
		/// </para>
		/// <para> If to_copy_ is none of the above: All indices will be set as a copy of to_copy_. </para>
		/// </summary>
		/// <param name="to_copy_">Argument to copy to the provided index range as described.</param>
		template<std::size_t BeginIndex_, std::size_t EndIndex_ = size, typename Arg_>
		constexpr inline void CopyFromStart(Arg_& to_copy_)
		{
			EmuMath::Helpers::new_vector_copy_from_start<BeginIndex_, EndIndex_, Arg_>(*this, to_copy_);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_ = size, typename Arg_>
		constexpr inline void CopyFromStart(const Arg_& to_copy_)
		{
			EmuMath::Helpers::new_vector_copy_from_start<BeginIndex_, EndIndex_, Arg_>(*this, to_copy_);
		}

		/// <summary>
		/// <para> Copies the provided argument to this Vector's elements within the provided index range. </para>
		/// <para> If this Vector contains references, this will copy the provided Arg_ to the referenced value_types. </para>
		/// <para>
		///		If to_copy_ is an EmuMath Vector: Progressively iterating indices from 0 will be copied (e.g. this[BeginIndex_ + 1] = to_copy_[1]).
		///		Non-shared indices will not be modified. 
		///		Reading of to_copy_ will start at index 0; to begin reading from BeginIndex_, use `Copy`.
		/// </para>
		/// <para> If to_copy_ is none of the above: All indices will be set as a copy of to_copy_. </para>
		/// </summary>
		/// <param name="to_copy_">Argument to copy to the provided index range as described.</param>
		template<std::size_t BeginIndex_, std::size_t EndIndex_ = size, typename Arg_>
		constexpr inline void CopyFromStartContainedOnly(Arg_& to_copy_)
		{
			EmuMath::Helpers::new_vector_copy_from_start_contained_only<BeginIndex_, EndIndex_, Arg_>(*this, to_copy_);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_ = size, typename Arg_>
		constexpr inline void CopyFromStartContainedOnly(const Arg_& to_copy_)
		{
			EmuMath::Helpers::new_vector_copy_from_start_contained_only<BeginIndex_, EndIndex_, Arg_>(*this, to_copy_);
		}
#pragma endregion

#pragma region SETS
		/// <summary>
		/// <para> Sets the stored elements of this Vector to via moving respective elements in the passed Vector. </para>
		/// <para> If to_move_set_ contains less elements than this Vector, non-contained elements will be interpreted as implied zeroes. </para>
		/// <para> If this Vector contains references, this will update what is referenced by respective references. </para>
		/// </summary>
		/// <param name="to_move_set_">EmuMath Vector to move stored elements from when assigning this Vector's stored elements.</param>
		template
		<
			std::size_t InSize_,
			typename InT_,
			typename = std::enable_if_t<is_valid_vector_for_set<InSize_, InT_, false, true>()>
		>
		constexpr inline void Set(EmuMath::NewVector<InSize_, InT_>&& to_move_set_)
		{
			EmuMath::Helpers::new_vector_set<T_, Size_, InSize_, InT_>(*this, std::move(to_move_set_));
		}

		/// <summary>
		/// <para> Sets the stored elements of this Vector to via moving respective elements in the passed Vector. </para>
		/// <para> If to_move_set_ contains less elements than this Vector, non-contained elements will be interpreted as implied zeroes. </para>
		/// <para> If this Vector contains references, this will update what is referenced by respective references. </para>
		/// </summary>
		/// <param name="to_move_set_">EmuMath Vector to move stored elements from when assigning this Vector's stored elements.</param>
		template
		<
			std::size_t InSize_,
			typename InT_,
			typename = std::enable_if_t<is_valid_vector_for_set<InSize_, InT_, true, true>()>
		>
		constexpr inline void Set(const EmuMath::NewVector<InSize_, InT_>&& to_move_set_)
		{
			EmuMath::Helpers::new_vector_set<T_, Size_, InSize_, InT_>(*this, std::move(to_move_set_));
		}

		/// <summary>
		/// <para> Sets the stored elements of this Vector to via copying respective elements in the passed Vector. </para>
		/// <para> If to_copy_set_ contains less elements than this Vector, non-contained elements will be interpreted as implied zeroes. </para>
		/// <para> If this Vector contains references, this will update what is referenced by respective references. </para>
		/// </summary>
		/// <param name="to_copy_set_">EmuMath Vector to copy stored elements from when assigning this Vector's stored elements.</param>
		template
		<
			std::size_t InSize_,
			typename InT_,
			typename = std::enable_if_t<is_valid_vector_for_set<InSize_, InT_, false, false>()>
		>
		constexpr inline void Set(EmuMath::NewVector<InSize_, InT_>& to_copy_set_)
		{
			EmuMath::Helpers::new_vector_set<T_, Size_, InSize_, InT_>(*this, to_copy_set_);
		}

		/// <summary>
		/// <para> Sets the stored elements of this Vector to via copying respective elements in the passed Vector. </para>
		/// <para> If to_copy_set_ contains less elements than this Vector, non-contained elements will be interpreted as implied zeroes. </para>
		/// <para> If this Vector contains references, this will update what is referenced by respective references. </para>
		/// </summary>
		/// <param name="to_copy_set_">EmuMath Vector to copy stored elements from when assigning this Vector's stored elements.</param>
		template
		<
			std::size_t InSize_,
			typename InT_,
			typename = std::enable_if_t<is_valid_vector_for_set<InSize_, InT_, true, false>()>
		>
		constexpr inline void Set(const EmuMath::NewVector<InSize_, InT_>& to_copy_set_)
		{
			EmuMath::Helpers::new_vector_set<T_, Size_, InSize_, InT_>(*this, to_copy_set_);
		}

		/// <summary>
		/// <para> Sets the stored elements of this Vector to via moving respective elements in the passed Vector. </para>
		/// <para> If to_move_set_ contains less elements than this Vector, elements in non-shared indices will not be modified. </para>
		/// <para> If this Vector contains references, this will update what is referenced by respective references. </para>
		/// </summary>
		/// <param name="to_move_set_">EmuMath Vector to move stored elements from when assigning this Vector's stored elements.</param>
		template
		<
			std::size_t InSize_,
			typename InT_,
			typename = std::enable_if_t<is_valid_vector_for_set<InSize_, InT_, false, true>()>
		>
		constexpr inline void SetContainedOnly(EmuMath::NewVector<InSize_, InT_>&& to_move_set_)
		{
			EmuMath::Helpers::new_vector_set_contained_only<T_, Size_, InSize_, InT_>(*this, std::move(to_move_set_));
		}

		/// <summary>
		/// <para> Sets the stored elements of this Vector to via moving respective elements in the passed Vector. </para>
		/// <para> If to_move_set_ contains less elements than this Vector, elements in non-shared indices will not be modified. </para>
		/// <para> If this Vector contains references, this will update what is referenced by respective references. </para>
		/// </summary>
		/// <param name="to_move_set_">EmuMath Vector to move stored elements from when assigning this Vector's stored elements.</param>
		template
		<
			std::size_t InSize_,
			typename InT_,
			typename = std::enable_if_t<is_valid_vector_for_set<InSize_, InT_, true, true>()>
		>
		constexpr inline void SetContainedOnly(const EmuMath::NewVector<InSize_, InT_>&& to_move_set_)
		{
			EmuMath::Helpers::new_vector_set_contained_only<T_, Size_, InSize_, InT_>(*this, std::move(to_move_set_));
		}

		/// <summary>
		/// <para> Sets the stored elements of this Vector to via copying respective elements in the passed Vector. </para>
		/// <para> If to_move_set_ contains less elements than this Vector, elements in non-shared indices will not be modified. </para>
		/// <para> If this Vector contains references, this will update what is referenced by respective references. </para>
		/// </summary>
		/// <param name="to_copy_set_">EmuMath Vector to copy stored elements from when assigning this Vector's stored elements.</param>
		template
		<
			std::size_t InSize_,
			typename InT_,
			typename = std::enable_if_t<is_valid_vector_for_set<InSize_, InT_, false, false>()>
		>
		constexpr inline void SetContainedOnly(EmuMath::NewVector<InSize_, InT_>& to_copy_set_)
		{
			EmuMath::Helpers::new_vector_set_contained_only<T_, Size_, InSize_, InT_>(*this, to_copy_set_);
		}

		/// <summary>
		/// <para> Sets the stored elements of this Vector to via copying respective elements in the passed Vector. </para>
		/// <para> If to_move_set_ contains less elements than this Vector, elements in non-shared indices will not be modified. </para>
		/// <para> If this Vector contains references, this will update what is referenced by respective references. </para>
		/// </summary>
		/// <param name="to_copy_set_">EmuMath Vector to copy stored elements from when assigning this Vector's stored elements.</param>
		template
		<
			std::size_t InSize_,
			typename InT_,
			typename = std::enable_if_t<is_valid_vector_for_set<InSize_, InT_, true, false>()>
		>
		constexpr inline void SetContainedOnly(const EmuMath::NewVector<InSize_, InT_>& to_copy_set_)
		{
			EmuMath::Helpers::new_vector_set_contained_only<T_, Size_, InSize_, InT_>(*this, to_copy_set_);
		}

		/// <summary>
		/// <para> Sets the stored_type at the provided Index_ within this Vector via the provided arg_. </para>
		/// <para> If this Vector contains references, this will update what is referenced by said reference. </para>
		/// <para> If multiple arguments are provided, this will attempt to construct the stored_type via the provided args_. </para>
		/// </summary>
		/// <param name="arg_">Argument to set the stored_type at the provided Index_ via.</param>
		template
		<
			std::size_t Index_,
			typename Arg_,
			typename = std::enable_if_t<is_valid_type_for_single_set<Arg_>()>
		>
		constexpr inline void Set(Arg_&& arg_)
		{
			if constexpr (Index_ < size)
			{
				if constexpr (std::is_assignable_v<stored_type, Arg_>)
				{
					std::get<Index_>(_data) = std::forward<Arg_>(arg_);
				}
				else if constexpr (std::is_convertible_v<Arg_, stored_type>)
				{
					std::get<Index_>(_data) = static_cast<stored_type>(arg_);
				}
				else if constexpr (std::is_constructible_v<stored_type, Arg_>)
				{
					std::get<Index_>(_data) = stored_type(std::forward<Arg_>(arg_));
				}
				else
				{
					static_assert(false, "Attempted to `Set` an Index_ within an EmuMath Vector, but the provided Arg_ cannot be used to assign, construct, or convert-to the Vector's stored_type.");
				}
			}
			else
			{
				static_assert(false, "Attempted to `Set` an invalid Index_ within an EmuMath Vector.");
			}
		}

		/// <summary>
		/// <para> Constructs a stored_type via the provided construction_args_ and sets the stored_type at the provided index via it. </para>
		/// <para> If this Vector contains references, this will update what is referenced by said reference. </para>
		/// </summary>
		/// <param name="construction_args_">Arguments to construct an instance of this Vector's stored_type.</param>
		template
		<
			std::size_t Index_,
			typename...Args_,
			typename = std::enable_if_t<(sizeof...(Args_) > 1) && std::is_constructible_v<stored_type, Args_...>>
		>
		constexpr inline void Set(Args_&&...construction_args_)
		{
			if constexpr (Index_ < size)
			{
				if constexpr (std::is_constructible_v<stored_type, Args_...>)
				{
					std::get<Index_>(_data) = stored_type(std::forward<Args_>(construction_args_)...);
				}
				else
				{
					static_assert(false, "Attempted to `Set` an Index_ within an EmuMath Vector with multiple arguments, but the stored_type cannot be constructed from the provided arguments.");
				}
			}
			else
			{
				static_assert(false, "Attempted to `Set` an invalid Index_ within an EmuMath Vector.");
			}
		}

		/// <summary>
		/// <para> Sets all stored_types at indices in the specified range within this Vector via the provided arg_. </para>
		/// <para> If this Vector contains references, this will update what is referenced by all references. </para>
		/// <para> BeginIndex_ indicates the inclusive index to start setting stored elements from. This defaults to 0.</para>
		/// <para> EndIndex_ indicates the exclusive index to stop setting stored elements at. This defaults to the size of this Vector. </para>
		/// </summary>
		/// <param name="arg_">Argument to set all stored_types in the specified index range within this Vector via.</param>
		template
		<
			std::size_t BeginIndex_ = 0,
			std::size_t EndIndex_ = size,
			typename Arg_,
			typename = std::enable_if_t<is_valid_type_for_set_all<Arg_&&>()>
		>
		constexpr inline void SetAll(Arg_&& arg_)
		{
			EmuMath::Helpers::new_vector_set_all<BeginIndex_, EndIndex_>(*this, std::move(arg_));
		}

		/// <summary>
		/// <para> Sets all stored_types at indices in the specified range within this Vector via the provided arg_. </para>
		/// <para> If this Vector contains references, this will update what is referenced by all references. </para>
		/// <para> BeginIndex_ indicates the inclusive index to start setting stored elements from. This defaults to 0.</para>
		/// <para> EndIndex_ indicates the exclusive index to stop setting stored elements at. This defaults to the size of this Vector. </para>
		/// </summary>
		/// <param name="arg_">Argument to set all stored_types in the specified index range within this Vector via.</param>
		template
		<
			std::size_t BeginIndex_ = 0,
			std::size_t EndIndex_ = size,
			typename Arg_,
			typename = std::enable_if_t<is_valid_type_for_set_all<Arg_&>()>
		>
		constexpr inline void SetAll(Arg_& arg_)
		{
			EmuMath::Helpers::new_vector_set_all<BeginIndex_, EndIndex_>(*this, arg_);
		}

		/// <summary>
		/// <para> Sets all stored_types at indices in the specified range within this Vector via the provided arg_. </para>
		/// <para> If this Vector contains references, this will update what is referenced by all references. </para>
		/// <para> BeginIndex_ indicates the inclusive index to start setting stored elements from. This defaults to 0.</para>
		/// <para> EndIndex_ indicates the exclusive index to stop setting stored elements at. This defaults to the size of this Vector. </para>
		/// </summary>
		/// <param name="arg_">Argument to set all stored_types in the specified index range within this Vector via.</param>
		template
		<
			std::size_t BeginIndex_ = 0,
			std::size_t EndIndex_ = size,
			typename Arg_,
			typename = std::enable_if_t<is_valid_type_for_set_all<const Arg_&>()>
		>
		constexpr inline void SetAll(const Arg_& arg_)
		{
			EmuMath::Helpers::new_vector_set_all<BeginIndex_, EndIndex_>(*this, arg_);
		}
#pragma endregion

	private:
		data_storage_type _data;
	};
}

#endif
