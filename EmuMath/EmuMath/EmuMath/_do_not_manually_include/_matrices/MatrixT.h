#ifndef EMU_MATH_MATRIX_T_H_INC_
#define EMU_MATH_MATRIX_T_H_INC_

#include "MatrixHelpers.h"
#include "MatrixInfo.h"

namespace EmuMath
{
	/// <summary>
	/// <para> Template matrix type used for arbitrarily sized matrices containing any arithmetic type, stored in order of columns or rows. </para>
	/// <para>
	///		NOTE: The ColumnMajor_ bool affects only the memory layout of a matrix. 
	///		Positions of elements, such as when generating transformation matrices, will always be at the same column and row indices regardless of major order. 
	/// </para>
	/// <para>
	///		All default arguments where a matrix is provided will use that matrix's major order. 
	///		Otherwise, if no matrix is available to copy, the default argument will always be for column major (true).
	/// </para>
	/// </summary>
	/// <typeparam name="T_"></typeparam>
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_ = true>
	struct Matrix
	{
	private:
		// Formed using decltype on a constructor call in order to trigger an assertion before doing anything further
		using _matrix_assert = decltype(EmuMath::_underlying_components::MatrixAssert<NumColumns_, NumRows_, T_, ColumnMajor_>());

	public:
		/// <summary> Underlying default MatrixInfo regarding this matrix's static information, including common type aliases. </summary>
		using matrix_info = EmuMath::_underlying_components::MatrixInfo<NumColumns_, NumRows_, T_, ColumnMajor_>;

		/// <summary> The number of columns contained in this matrix. </summary>
		static constexpr std::size_t num_columns = matrix_info::num_columns;
		/// <summary> The number of rows contained in this matrix. </summary>
		static constexpr std::size_t num_rows = matrix_info::num_rows;
		/// <summary> The total number of elements contained in this matrix. This is not the memory-size of this matrix acquired via sizeof. </summary>
		static constexpr std::size_t size = matrix_info::size;
		/// <summary> Boolean indicating if this matrix's elements are stored contiguously as columns. Mutually exclusive with is_row_major. </summary>
		static constexpr bool is_column_major = matrix_info::is_column_major;
		/// <summary> Boolean indicating if this matrix's elements are stored contiguously as rows. Mutually exclusive with is_column_major. </summary>
		static constexpr bool is_row_major = matrix_info::is_row_major;
		/// <summary> Boolean indicating if this is a matrix with an equal number of columns and rows. </summary>
		static constexpr bool is_square = matrix_info::is_square;

		/// <summary> The number of major elements in this matrix (i.e. num_columns if column-major, or num_rows if row-major). </summary>
		static constexpr std::size_t num_major_elements = matrix_info::num_major_elements;
		/// <summary> The number of non-major elements in this matrix (i.e. num_rows if column-major, or num_columns if row-major). </summary>
		static constexpr std::size_t num_non_major_elements = matrix_info::num_non_major_elements;

		/// <summary> The type contained within this matrix. </summary>
		using contained_type = typename matrix_info::contained_type;
		/// <summary> Boolean indicating if this matrix contains reference wrapping types. </summary>
		static constexpr bool contains_reference_wrappers = matrix_info::contains_reference_wrappers;
		/// <summary> The raw value_type within this matrix before its const qualifier is forcibly removed. </summary>
		using raw_value_type = typename matrix_info::raw_value_type;
		/// <summary> Value type of the items stored within this matrix, without const qualifiers where applicable. </summary>
		using value_type = typename matrix_info::value_type;
		/// <summary> The preferred floating point type for this matrix. Float if this matrix contains non-floating-point types, otherwise matches value_type. </summary>
		using preferred_floating_point = typename matrix_info::preferred_floating_point;
		/// <summary> Boolean indicating if the reference wrappers within this matrix contain constant references. Always false if contains_reference_wrappers is false. </summary>
		static constexpr bool contains_const_reference_wrappers = matrix_info::contains_const_reference_wrappers;
		/// <summary> Boolean indicating if the reference wrappers within this matrix contain non-constant references. Always false if contains_reference_wrappers is false. </summary>
		static constexpr bool contains_non_const_reference_wrappers = matrix_info::contains_non_const_reference_wrappers;

		/// <summary> Boolean indcating if this matrix's values are integral. </summary>
		static constexpr bool has_integral_elements = matrix_info::has_integral_elements;
		/// <summary> Boolean indcating if this matrix's values are floating-points. </summary>
		static constexpr bool has_floating_point_elements = matrix_info::has_floating_point_elements;
		/// <summary> Boolean indicating if this matrix's values are constant. </summary>
		static constexpr bool has_const_values = matrix_info::has_const_values;

		/// <summary> The type used to store this matrix's underlying data. Effectively a vector of vectors. </summary>
		using data_storage_type = typename matrix_info::data_storage_type;

		/// <summary> Type used to randomly access a row referencing this matrix. </summary>
		using random_access_row = typename matrix_info::random_access_row;
		/// <summary> Type used to randomly access a column referencing this matrix. </summary>
		using random_access_column = typename matrix_info::random_access_column;
		/// <summary> Type used to randomly access a row referencing this matrix with constant constraints. </summary>
		using const_random_access_row = typename matrix_info::const_random_access_row;
		/// <summary> Type used to randomly access a column referencing this matrix with constant constraints. </summary>
		using const_random_access_column = typename matrix_info::const_random_access_column;
		using major_storage_type = typename matrix_info::major_storage_type;

		/// <summary> This matrix type. </summary>
		using this_type = EmuMath::Matrix<num_columns, num_rows, contained_type, is_column_major>;
		/// <summary> Type used to receive a copy of this matrix. This is the same as this_type normally, but will remove qualifiers and references where applicable. </summary>
		using copy_type = EmuMath::Matrix<num_columns, num_rows, value_type, is_column_major>;
		/// <summary> Type used to receive a copy of this matrix. This is the same as this_type normally, but with references removed if it is a reference wrapper. </summary>
		using raw_copy_type = EmuMath::Matrix<num_columns, num_rows, raw_value_type, is_column_major>;

#pragma region CONSTRUCTORS
		constexpr Matrix() : data_()
		{
		}
		constexpr Matrix(data_storage_type& toCopy_) : data_(toCopy_)
		{
		}
		constexpr Matrix(const data_storage_type& toCopy_) : data_(toCopy_)
		{
		}
		constexpr Matrix(this_type& toCopy_) : data_(toCopy_.data_)
		{
		}
		template<std::size_t InNumColumns_, std::size_t InNumRows_, typename in_contained_type, bool InColumnMajor_>
		explicit constexpr Matrix(const EmuMath::Matrix<InNumColumns_, InNumRows_, in_contained_type, InColumnMajor_>& to_copy_) : data_()
		{
			EmuMath::Helpers::MatrixCopy<this_type, EmuMath::Matrix<InNumColumns_, InNumRows_, in_contained_type, InColumnMajor_>>(*this, to_copy_);
		}
		template<typename NotAvailableIfContainsNonConstReferenceWrappers = std::enable_if_t<!contains_non_const_reference_wrappers>>
		constexpr Matrix(const this_type& toCopy_) : data_(toCopy_.data_)
		{
		}
		template<std::size_t...Sizes_, typename...Ts_>
		constexpr Matrix(EmuMath::Vector<Sizes_, Ts_>&&...major_vectors_) : data_(std::forward<EmuMath::Vector<Sizes_, Ts_>>(major_vectors_)...)
		{
			static_assert(std::is_constructible_v<data_storage_type, EmuMath::Vector<Sizes_, Ts_>...>, "Attempted to construct an EmuMath matrix via a template constructor, using Vector data which cannot be used to construct the matrix's underlying data.");
		}
		/// <summary>
		/// <para> Template constructor to create this matrix type via scalar arguments. </para>
		/// <para> Arguments are taken in contiguous order within this matrix. </para>
		/// <para>
		///		Passed arguments must be valid types for constructing this matrix's contained_type, 
		///		and the number of arguments must be equal to the total number of elements within this matrix.
		/// </para>
		/// </summary>
		/// <typeparam name="ScalarArgs_">Types of scalars to form this matrix with. Must be valid individual types to construct this matrix's contained_type.</typeparam>
		/// <param name="contiguous_scalar_args_">Scalars to form this matrix with. Must be valid individual types to construct this matrix's contained_type.</param>
		template
		<
			typename...ScalarArgs_,
			typename RequiresNumberOfValidArgsEqualToSize = std::enable_if_t
			<
				EmuCore::TMPHelpers::are_all_comparisons_true<std::is_constructible, contained_type, ScalarArgs_...>::value &&
				sizeof...(ScalarArgs_) == size
			>
		>
		constexpr Matrix(ScalarArgs_&&...contiguous_scalar_args_) : Matrix()
		{
			if constexpr (sizeof...(ScalarArgs_) == size)
			{
				if constexpr (EmuCore::TMPHelpers::are_all_comparisons_true<std::is_constructible, contained_type, ScalarArgs_...>::value)
				{
					EmuMath::Helpers::_underlying_matrix_funcs::_matrix_maker<this_type>()(*this, std::make_index_sequence<size>(), contiguous_scalar_args_...);
				}
				else
				{
					static_assert(false, "Attempted to construct an EmuMath matrix using scalar arguments, but at least one of the provided arguments could not be used to construct an element within the matrix.");
				}
			}
			else
			{
				static_assert(false, "Attempted to construct an EmuMath matrix using scalar arguments, but the provided number of arguments did not match the number of elements within the matrix.");
			}
		}
#pragma endregion

#pragma region RANDOM_ACCESS
		template<std::size_t ColumnIndex_, std::size_t RowIndex_>
		[[nodiscard]] constexpr inline raw_value_type& at()
		{
			if constexpr (_valid_static_indices<ColumnIndex_, RowIndex_>())
			{
				return _get_index<ColumnIndex_, RowIndex_>();
			}
			else
			{
				static_assert(false, "Failed to retrieve an EmuMath matrix element due to invalid indices being provided.");
			}
		}
		template<std::size_t ColumnIndex_, std::size_t RowIndex_>
		[[nodiscard]] constexpr inline const raw_value_type& at() const
		{
			if constexpr (_valid_static_indices<ColumnIndex_, RowIndex_>())
			{
				return _get_index<ColumnIndex_, RowIndex_>();
			}
			else
			{
				static_assert(false, "Failed to retrieve an EmuMath matrix element due to invalid indices being provided.");
			}
		}
		[[nodiscard]] constexpr inline raw_value_type& at(const std::size_t columnIndex_, const std::size_t rowIndex_)
		{
			return _get_index(columnIndex_, rowIndex_);
		}
		[[nodiscard]] constexpr inline const raw_value_type& at(const std::size_t columnIndex_, const std::size_t rowIndex_) const
		{
			return _get_index(columnIndex_, rowIndex_);
		}

		template<std::size_t MajorIndex_>
		[[nodiscard]] constexpr inline EmuMath::Vector<num_non_major_elements, contained_type>& at()
		{
			return this->template GetMajor<MajorIndex_>();
		}
		template<std::size_t MajorIndex_>
		[[nodiscard]] constexpr inline const EmuMath::Vector<num_non_major_elements, contained_type>& at() const
		{
			return this->template GetMajor<MajorIndex_>();
		}
		[[nodiscard]] constexpr inline EmuMath::Vector<num_non_major_elements, contained_type>& at(const std::size_t majorIndex_)
		{
			return this->GetMajor(majorIndex_);
		}
		[[nodiscard]] constexpr inline const EmuMath::Vector<num_non_major_elements, contained_type>& at(const std::size_t majorIndex_) const
		{
			return this->GetMajor(majorIndex_);
		}

		[[nodiscard]] constexpr inline EmuMath::Vector<num_non_major_elements, contained_type>& operator[](const std::size_t majorIndex_)
		{
			return this->at(majorIndex_);
		}
		[[nodiscard]] constexpr inline const EmuMath::Vector<num_non_major_elements, contained_type>& operator[](const std::size_t majorIndex_) const
		{
			return this->at(majorIndex_);
		}

		[[nodiscard]] constexpr inline raw_value_type& operator()(const std::size_t columnIndex_, const std::size_t rowIndex_)
		{
			return this->at(columnIndex_, rowIndex_);
		}
		[[nodiscard]] constexpr inline const raw_value_type& operator()(const std::size_t columnIndex_, const std::size_t rowIndex_) const
		{
			return this->at(columnIndex_, rowIndex_);
		}

		template<std::size_t MajorIndex_>
		[[nodiscard]] constexpr inline EmuMath::Vector<num_non_major_elements, contained_type>& GetMajor()
		{
			if constexpr (MajorIndex_ < num_major_elements)
			{
				return data_.template at<MajorIndex_>();
			}
			else
			{
				static_assert(false, "Attempted to access a major element within an EmuMath matrix using an invalid MajorIndex_.");
			}
		}
		template<std::size_t MajorIndex_>
		[[nodiscard]] constexpr inline const EmuMath::Vector<num_non_major_elements, contained_type>& GetMajor() const
		{
			if constexpr (MajorIndex_ < num_major_elements)
			{
				return data_.template at<MajorIndex_>();
			}
			else
			{
				static_assert(false, "Attempted to access a major element within an EmuMath matrix using an invalid MajorIndex_.");
			}
		}

		[[nodiscard]] constexpr inline EmuMath::Vector<num_non_major_elements, contained_type>& GetMajor(const std::size_t majorIndex_)
		{
			return data_.at(majorIndex_);
		}
		[[nodiscard]] constexpr inline const EmuMath::Vector<num_non_major_elements, contained_type>& GetMajor(const std::size_t majorIndex_) const
		{
			return data_.at(majorIndex_);
		}

		template<std::size_t RowIndex_>
		[[nodiscard]] constexpr inline random_access_row GetRow()
		{
			return EmuMath::Helpers::MatrixGetRow<RowIndex_, this_type>(*this);
		}
		template<std::size_t RowIndex_>
		[[nodiscard]] constexpr inline const_random_access_row GetRow() const
		{
			return EmuMath::Helpers::MatrixGetRow<RowIndex_, this_type>(*this);
		}
		template<std::size_t RowIndex_>
		[[nodiscard]] constexpr inline const_random_access_row GetRowConst() const
		{
			return EmuMath::Helpers::MatrixGetRow<RowIndex_, this_type>(*this);
		}

		template<std::size_t ColumnIndex_>
		[[nodiscard]] constexpr inline random_access_column GetColumn()
		{
			return EmuMath::Helpers::MatrixGetColumn<ColumnIndex_, this_type>(*this);
		}
		template<std::size_t ColumnIndex_>
		[[nodiscard]] constexpr inline const_random_access_column GetColumn() const
		{
			return EmuMath::Helpers::MatrixGetColumn<ColumnIndex_, this_type>(*this);
		}
		template<std::size_t ColumnIndex_>
		[[nodiscard]] constexpr inline const_random_access_column GetColumnConst() const
		{
			return EmuMath::Helpers::MatrixGetColumn<ColumnIndex_, this_type>(*this);
		}

		/// <summary> Provides a pointer to this matrix's underlying data. </summary>
		/// <returns>Non-const pointer to this matrix's data_storage_type; likely to an EmuMath vector of its major size containing vectors of its non-major size.</returns>
		[[nodiscard]] constexpr inline data_storage_type* data()
		{
			return &data_;
		}
		/// <summary> Provides a pointer to this matrix's underlying data. </summary>
		/// <returns>Const pointer to this matrix's data_storage_type; likely to an EmuMath vector of its major size containing vectors of its non-major size.</returns>
		[[nodiscard]] constexpr inline const data_storage_type* data() const
		{
			return &data_;
		}
#pragma endregion

#pragma region CONST_OPERATORS
		template<bool TestAllIndices_ = false, std::size_t LhsNumColumns_, std::size_t RhsNumColumns_, typename rhs_contained_type, bool RhsColumnMajor_>
		[[nodiscard]] constexpr inline bool operator==(const EmuMath::Matrix<LhsNumColumns_, RhsNumColumns_, rhs_contained_type, RhsColumnMajor_>& rhs_) const
		{
			return EmuMath::Helpers::MatrixCmpEqual<TestAllIndices_, this_type, EmuMath::Matrix<LhsNumColumns_, RhsNumColumns_, rhs_contained_type, RhsColumnMajor_>>
			(
				*this,
				rhs_
			);
		}

		template<bool TestAllIndices_ = false, std::size_t LhsNumColumns_, std::size_t RhsNumColumns_, typename rhs_contained_type, bool RhsColumnMajor_>
		[[nodiscard]] constexpr inline bool operator!=(const EmuMath::Matrix<LhsNumColumns_, RhsNumColumns_, rhs_contained_type, RhsColumnMajor_>& rhs_) const
		{
			return EmuMath::Helpers::MatrixCmpNotEqual<TestAllIndices_, this_type, EmuMath::Matrix<LhsNumColumns_, RhsNumColumns_, rhs_contained_type, RhsColumnMajor_>>
			(
				*this,
				rhs_
			);
		}

		template<typename Rhs_>
		[[nodiscard]] constexpr inline copy_type operator+(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixAdd<num_columns, num_rows, value_type, is_column_major, this_type, Rhs_>(*this, rhs_);
		}
		[[nodiscard]] constexpr inline copy_type operator+() const
		{
			return EmuMath::Helpers::MatrixAs<num_columns, num_rows, value_type, is_column_major, this_type>(*this);
		}

		template<typename Rhs_>
		[[nodiscard]] constexpr inline copy_type operator-(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixSubtract<num_columns, num_rows, value_type, is_column_major, this_type, Rhs_>(*this, rhs_);
		}
		[[nodiscard]] constexpr inline copy_type operator-() const
		{
			return EmuMath::Helpers::MatrixNegate<num_columns, num_rows, value_type, is_column_major, this_type>(*this);
		}

		template<typename Rhs_>
		[[nodiscard]] constexpr inline auto operator*(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixMultiply(*this, rhs_);
		}

		template<typename Rhs_>
		[[nodiscard]] constexpr inline copy_type operator/(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixDivideBasic<num_columns, num_rows, value_type, is_column_major, this_type, Rhs_>(*this, rhs_);
		}

		template<typename Rhs_>
		[[nodiscard]] constexpr inline copy_type operator%(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixModBasic<num_columns, num_rows, value_type, is_column_major, this_type, Rhs_>(*this, rhs_);
		}

		template<typename Rhs_>
		[[nodiscard]] constexpr inline copy_type operator&(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixAnd<num_columns, num_rows, value_type, is_column_major, this_type, Rhs_>(*this, rhs_);
		}

		template<typename Rhs_>
		[[nodiscard]] constexpr inline copy_type operator|(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixOr<num_columns, num_rows, value_type, is_column_major, this_type, Rhs_>(*this, rhs_);
		}

		template<typename Rhs_>
		[[nodiscard]] constexpr inline copy_type operator^(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixXor<num_columns, num_rows, value_type, is_column_major, this_type, Rhs_>(*this, rhs_);
		}

		template<typename Shifts_>
		[[nodiscard]] constexpr inline copy_type operator<<(const Shifts_& num_shifts_) const
		{
			return EmuMath::Helpers::MatrixShiftLeft<num_columns, num_rows, value_type, is_column_major, this_type, Shifts_>(*this, num_shifts_);
		}

		template<typename Shifts_>
		[[nodiscard]] constexpr inline copy_type operator>>(const Shifts_& num_shifts_) const
		{
			return EmuMath::Helpers::MatrixShiftRight<num_columns, num_rows, value_type, is_column_major, this_type, Shifts_>(*this, num_shifts_);
		}

		[[nodiscard]] constexpr inline copy_type operator~() const
		{
			return EmuMath::Helpers::MatrixNot<num_columns, num_rows, value_type, is_column_major, this_type>(*this);
		}
#pragma endregion

#pragma region NON_CONST_OPERATORS
		template<typename Rhs_>
		constexpr inline this_type& operator=(const Rhs_& to_copy_)
		{
			return EmuMath::Helpers::MatrixCopy(*this, to_copy_);
		}

		template<typename Rhs_>
		constexpr inline this_type& operator+=(const Rhs_& rhs_)
		{
			return this->operator=(this->operator+(rhs_));
		}

		template<typename Rhs_>
		constexpr inline this_type& operator-=(const Rhs_& rhs_)
		{
			return this->operator=(this->operator-(rhs_));
		}

		template
		<
			typename Rhs_,
			typename RequiresRhsWhichResultsInMatchingMatrixDimensions = std::enable_if_t<EmuMath::TMP::is_matching_size_matrix_multiply_result_v<this_type, Rhs_>>
		>
		constexpr inline this_type& operator*=(const Rhs_& rhs_)
		{
			return this->operator=(this->operator*(rhs_));
		}

		template<typename Rhs_>
		constexpr inline this_type& operator/=(const Rhs_& rhs_)
		{
			return this->operator=(this->operator/(rhs_));
		}

		template<typename Rhs_>
		constexpr inline this_type& operator%=(const Rhs_& rhs_)
		{
			return this->operator=(this->operator%(rhs_));
		}

		template<typename Rhs_>
		constexpr inline this_type& operator&=(const Rhs_& rhs_)
		{
			return this->operator=(this->operator&(rhs_));
		}

		template<typename Rhs_>
		constexpr inline this_type& operator|=(const Rhs_& rhs_)
		{
			return this->operator=(this->operator|(rhs_));
		}

		template<typename Rhs_>
		constexpr inline this_type& operator^=(const Rhs_& rhs_)
		{
			return this->operator=(this->operator^(rhs_));
		}

		template<typename Shifts_>
		constexpr inline this_type& operator<<=(const Shifts_& num_shifts_)
		{
			return this->operator=(this->operator<<(num_shifts_));
		}

		template<typename Shifts_>
		constexpr inline this_type& operator>>=(const Shifts_& num_shifts_)
		{
			return this->operator=(this->operator>>(num_shifts_));
		}
#pragma endregion

#pragma region MATRIX_OPERATIONS
		/// <summary>
		/// <para> Crreate a new EmuMath matrix containing copies of mutated respective elements within this matrix. </para>
		/// <para>
		///		Invocations of func_ will always be in column-major order; all elements in a column will be passed before the next column, until all columns are complete.
		/// </para>
		/// </summary>
		/// <typeparam name="Func_">Type to invoke for every element.</typeparam>
		/// <param name="func_">Invocable item which will be invoked for every element to mutate said element in the output matrix.</param>
		/// <returns>Copy of this matrix with its elements mutated via the provided func_.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class Func_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> Mutate(Func_ func_) const
		{
			return EmuMath::Helpers::MatrixMutate<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_, Func_&, this_type>(*this, func_);
		}
		template<typename out_contained_type, bool OutColumnMajor_, class Func_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, out_contained_type, OutColumnMajor_> Mutate(Func_ func_) const
		{
			return EmuMath::Helpers::MatrixMutate<num_columns, num_rows, out_contained_type, OutColumnMajor_, Func_&, this_type>(*this, func_);
		}
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class Func_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_> Mutate(Func_ func_) const
		{
			return EmuMath::Helpers::MatrixMutate<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_, Func_&, this_type>(*this, func_);
		}
		template<bool OutColumnMajor_, class Func_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type, OutColumnMajor_> Mutate(Func_ func_) const
		{
			return EmuMath::Helpers::MatrixMutate<num_columns, num_rows, value_type, OutColumnMajor_, Func_&, this_type>(*this, func_);
		}
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class Func_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, is_column_major> Mutate(Func_ func_) const
		{
			return EmuMath::Helpers::MatrixMutate<OutNumColumns_, OutNumRows_, out_contained_type, is_column_major, Func_&, this_type>(*this, func_);
		}
		template<typename out_contained_type, class Func_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, out_contained_type, is_column_major> Mutate(Func_ func_) const
		{
			return EmuMath::Helpers::MatrixMutate<num_columns, num_rows, out_contained_type, is_column_major, Func_&, this_type>(*this, func_);
		}
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class Func_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, value_type, is_column_major> Mutate(Func_ func_) const
		{
			return EmuMath::Helpers::MatrixMutate<OutNumColumns_, OutNumRows_, value_type, is_column_major, Func_&, this_type>(*this, func_);
		}
		template<class Func_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type, is_column_major> Mutate(Func_ func_) const
		{
			return EmuMath::Helpers::MatrixMutate<num_columns, num_rows, value_type, is_column_major, Func_&, this_type>(*this, func_);
		}

		/// <summary>
		/// <para> Transposes this matrix, effectively turning columns into rows and vice versa. </para>
		/// <para> The output matrix will always be of dimensions [Y, X], where X=this_matrix::num_columns, and Y=this_matrix::num_rows. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained in the output transpose matrix.</typeparam>
		/// <returns>Tranposed form of this matrix.</returns>
		template<typename out_contained_type = value_type, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline typename EmuMath::TMP::emu_matrix_transpose<out_contained_type, OutColumnMajor_, this_type>::type Transpose() const
		{
			return EmuMath::Helpers::MatrixTranspose<out_contained_type, OutColumnMajor_, this_type>(*this);
		}

		/// <summary>
		/// <para> Calculates the trace of this matrix (i.e. the sum of all diagonal elements from the top-left to the bottom right). </para>
		/// <para> The trace is only defined for a square matrix, and as such this function may only be validly executed on square matrices. </para>
		/// </summary>
		/// <typeparam name="OutT_">Type to output the trace as.</typeparam>
		/// <returns>Trace of this matrix, represented as the provided OutT_.</returns>
		template<typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline OutT_ Trace() const
		{
			return EmuMath::Helpers::MatrixTrace<OutT_, this_type>(*this);
		}

		/// <summary>
		/// <para> Retrieves a smaller matrix from within this matrix, which is formed of all elements excluding those in the provided row and column. </para>
		/// <para> This will always yield a matrix of size [X-1, Y-1], where X=this_matrix::num_columns, and Y=this_matrix::num_rows. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained in the output submatrix.</typeparam>
		/// <returns>Copy of the submatrix within the this matrix, formed of all elements excluding those in the provided column or row indices.</returns>
		template<std::size_t ExcludeColumn_, std::size_t ExcludeRow_, typename out_contained_type = value_type, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline typename EmuMath::TMP::emu_matrix_submatrix_excluding_element_region<out_contained_type, OutColumnMajor_, this_type>::type
		ExclusiveSubmatrix()
		{
			return EmuMath::Helpers::MatrixExclusiveSubmatrix<ExcludeColumn_, ExcludeRow_, out_contained_type, OutColumnMajor_, this_type>(*this);
		}
		template<std::size_t ExcludeColumn_, std::size_t ExcludeRow_, typename out_contained_type = value_type, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline typename EmuMath::TMP::emu_matrix_submatrix_excluding_element_region<out_contained_type, OutColumnMajor_, this_type>::type
		ExclusiveSubmatrix() const
		{
			return EmuMath::Helpers::MatrixExclusiveSubmatrix<ExcludeColumn_, ExcludeRow_, out_contained_type, OutColumnMajor_, const this_type>(*this);
		}

		/// <summary>
		/// <para> Calculates the determinant of this matrix using Laplace Expansion. </para>
		/// <para> NOTE: Laplace Expansion grows exponentially more expensive as the size of a matrix increases. </para>
		/// </summary>
		/// <typeparam name="OutDet_">Type to output the passed matrix's determinant as.</typeparam>
		/// <returns>Determinant of this matrix, represented as the provided OutDet_ type.</returns>
		template<typename OutDet_ = preferred_floating_point>
		[[nodiscard]] constexpr inline OutDet_ DeterminantLaplace() const
		{
			return EmuMath::Helpers::MatrixDeterminantLaplace<OutDet_, this_type>(*this);
		}

		/// <summary>
		/// <para> Calculates the matrix of minors this matrix using Laplace Expansion. </para>
		/// <para> Each element in the output matrix may be summarised as the determinant of the submatrix which excludes said element's column and row. </para>
		/// <para> NOTE: Laplace Expansion grows exponentially more expensive as the size of a matrix increases. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained in the output minor matrix.</typeparam>
		/// <returns>Matrix of minors to this matrix.</returns>
		template<typename out_contained_type = preferred_floating_point, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, out_contained_type, OutColumnMajor_> MatrixOfMinorsLaplace() const
		{
			return EmuMath::Helpers::MatrixOfMinorsLaplace<out_contained_type, OutColumnMajor_, this_type>(*this);
		}

		/// <summary>
		/// <para> Calculates the matrix of cofactors to this matrix using Laplace Expansion. </para>
		/// <para> NOTE: Laplace Expansion grows exponentially more expensive as the size of a matrix increases. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained in the output cofactor matrix.</typeparam>
		/// <returns>Matrix of cofactors to this matrix.</returns>
		template<typename out_contained_type = preferred_floating_point, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, out_contained_type, OutColumnMajor_> MatrixOfCofactorsLaplace() const
		{
			return EmuMath::Helpers::MatrixOfCofactorsLaplace<out_contained_type, OutColumnMajor_, this_type>(*this);
		}

		/// <summary>
		/// <para> Calculates the adjugate matrix to this matrix using Laplace Expansion. </para>
		/// <para> The resulting matrix can be summarised as the transpose to this matrix's matrix of cofactors. </para>
		/// <para> NOTE: Laplace Expansion grows exponentially more expensive as the size of a matrix increases. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained in the output adjugate matrix.</typeparam>
		/// <returns>Adjugate matrix to this matrix.</returns>
		template<typename out_contained_type = preferred_floating_point, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline typename EmuMath::TMP::emu_matrix_transpose<out_contained_type, OutColumnMajor_, this_type>::type AdjugateLaplace() const
		{
			return EmuMath::Helpers::MatrixAdjugateLaplace<out_contained_type, OutColumnMajor_, this_type>(*this);
		}

		/// <summary>
		/// <para> Calculates the inverse to this matrix using Laplace Expansion. May optionally output the determinant as a customisable type. </para>
		/// <para>
		///		Note that this operation does not check that the determinant is not 0. As matrices with a determinant of 0 have no inverse, it is recommended to 
		///		use the outDeterminant argument to test if the output matrix is valid if there should there be a chance that the passed matrix's determinant will be 0.
		/// </para>
		/// <para> NOTE: Laplace Expansion grows exponentially more expensive as the size of a matrix increases. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained in the output inverse matrix.</typeparam>
		/// <typeparam name="OutDeterminant_">Type to optionally output the matrix's determinant as.</typeparam>
		/// <param name="matrix_">EmuMath matrix to find the inverse of.</param>
		/// <param name="outDeterminant_">
		///		Optional reference to output the passed matrix's determinant to. 
		///		Useful to test if the determinant is 0 in cases where a non-invertible matrix may potentially be passed.
		/// </param>
		/// <returns>Inverted version of this matrix if it is invertible. Otherwise, a matrix containing the results of multiplying its adjugate by (1/0).</returns>
		template<typename out_contained_type = preferred_floating_point, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline typename EmuMath::TMP::emu_matrix_transpose<out_contained_type, OutColumnMajor_, this_type>::type InverseLaplace() const
		{
			return EmuMath::Helpers::MatrixInverseLaplace<out_contained_type, OutColumnMajor_, this_type>(*this);
		}
		template<typename out_contained_type = preferred_floating_point, bool OutColumnMajor_ = is_column_major, typename OutDeterminant_>
		[[nodiscard]] constexpr inline typename EmuMath::TMP::emu_matrix_transpose<out_contained_type, OutColumnMajor_, this_type>::type InverseLaplace
		(
			OutDeterminant_& out_determinant_
		) const
		{
			return EmuMath::Helpers::MatrixInverseLaplace<out_contained_type, OutColumnMajor_, this_type, OutDeterminant_>(*this, out_determinant_);
		}
#pragma endregion

#pragma region REINTERPRETATIONS
		/// <summary>
		/// <para> Casts this matrix to an alternative matrix type with the provided template arguments. </para>
		/// <para> Template arguments must be in order of the arguments provided to instantiate an EmuMath::Matrix type. </para>
		/// <para>
		///		Arguments may be omitted. Where omitted, they will be automatically matched up to this matrix's own arguments, 
		///		with the exception of out_contained_type which will be this matrix's value_type instead.
		/// </para>
		/// <para> To easily convert straight to an existing EmuMath::Matrix type, use AsMatrix instead, which takes a single EmuMath::Matrix template argument. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained in the output matrix.</typeparam>
		/// <returns>This matrix cast to an EmuMath matrix instantiated with the provided template arguments.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> As() const
		{
			return EmuMath::Helpers::MatrixAs<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_, this_type>(*this);
		}
		template<typename out_contained_type, bool OutColumnMajor_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, out_contained_type, OutColumnMajor_> As() const
		{
			return EmuMath::Helpers::MatrixAs<num_columns, num_rows, out_contained_type, OutColumnMajor_, this_type>(*this);
		}
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_> As() const
		{
			return EmuMath::Helpers::MatrixAs<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_, this_type>(*this);
		}
		template<bool OutColumnMajor_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, typename value_type, OutColumnMajor_> As() const
		{
			return EmuMath::Helpers::MatrixAs<num_columns, num_rows, value_type, OutColumnMajor_, this_type>(*this);
		}
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, is_column_major> As() const
		{
			return EmuMath::Helpers::MatrixAs<OutNumColumns_, OutNumRows_, out_contained_type, is_column_major, this_type>(*this);
		}
		template<typename out_contained_type>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, out_contained_type, is_column_major> As() const
		{
			return EmuMath::Helpers::MatrixAs<num_columns, num_rows, out_contained_type, is_column_major, this_type>(*this);
		}
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, value_type, is_column_major> As() const
		{
			return EmuMath::Helpers::MatrixAs<OutNumColumns_, OutNumRows_, value_type, is_column_major, this_type>(*this);
		}

		/// <summary>
		/// <para> Casts this matrix to the provided EmuMath matrix template argument type. </para>
		/// <para> 
		///		Note that reference casts are not provided by this function; 
		///		output will be the provided matrix's raw_copy_type, which is the same type for non-ref matrices.
		/// </para>
		/// </summary>
		/// <typeparam name="TargetCastMatrix_">Type of matrix to cast this matrix to. Note that the cast will effectively be a raw copy type.</typeparam>
		/// <returns>This matrix cast to the raw_copy_type of the passed EmuMath matrix template argument.</returns>
		template<typename TargetCastMatrix_>
		[[nodiscard]] constexpr inline typename TargetCastMatrix_::raw_copy_type AsMatrix() const
		{
			if constexpr (EmuMath::TMP::is_emu_matrix_v<TargetCastMatrix_>)
			{
				using cast_raw_copy_type = typename TargetCastMatrix_::raw_copy_type;
				return As<cast_raw_copy_type::num_columns, cast_raw_copy_type::num_rows, cast_raw_copy_type::contained_type, cast_raw_copy_type::is_column_major>();
			}
			else
			{
				static_assert(false, "Attempted to convert an EmuMath matrix to another matrix type via AsMatrix, but the provided TargetCastMatrix_ type was not an EmuMath matrix.");
			}
		}
#pragma endregion

#pragma region STATIC OPERATIONS
		/// <summary> Provides the identity matrix to this matrix type, assuming it is a square matrix. </summary>
		/// <returns>Identity to this matrix type.</returns>
		[[nodiscard]] constexpr static inline copy_type Identity()
		{
			return EmuMath::Helpers::MatrixIdentity<this_type>();
		}
#pragma endregion

#pragma region ARITHMETIC_FUNCTIONS
		/// <summary>
		/// <para> Performs an addition operation on this matrix using the passed rhs_. </para>
		/// <para> If the passed rhs_ is a matrix, respective indices in each matrix will be added. Otherwise, each index in this matrix will have Rhs_ added to it. </para>
		/// <para>
		///		Template arguments are in the same order as when defining an EmuMath::Matrix. Arguments may be omitted to use the same as this matrix's arguments, 
		///		with the exception of out_contained_type, which will be this matrix's value_type.
		/// </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained within the result matrix.</typeparam>
		/// <typeparam name="Rhs_">Type of matrix or scalar appearing on the right-hand side of addition.</typeparam>
		/// <param name="rhs_">EmuMath matrix or scalar appearing on the right-hand side of addition.</param>
		/// <returns>Matrix containing the results of adding rhs_ to this matrix as defined above.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> Add(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixAdd<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_> Add(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixAdd<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}
		template<typename out_contained_type, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, out_contained_type, OutColumnMajor_> Add(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixAdd<num_columns, num_rows, out_contained_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}
		template<bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type, OutColumnMajor_> Add(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixAdd<num_columns, num_rows, value_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para> Performs a subtraction operation on this matrix using the passed rhs_. </para>
		/// <para>
		///		If the passed rhs_ is a matrix, respective indices in each matrix will be subtracted.
		///		Otherwise, each index in this matrix will have Rhs_ subtracted from it.
		/// </para>
		/// <para>
		///		Template arguments are in the same order as when defining an EmuMath::Matrix. Arguments may be omitted to use the same as this matrix's arguments, 
		///		with the exception of out_contained_type, which will be this matrix's value_type.
		/// </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained within the result matrix.</typeparam>
		/// <typeparam name="Rhs_">Type of matrix or scalar appearing on the right-hand side of subtraction.</typeparam>
		/// <param name="rhs_">EmuMath matrix or scalar appearing on the right-hand side of subtraction.</param>
		/// <returns>Matrix containing the results of subtracting rhs_ from this matrix as defined above.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> Subtract(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixSubtract<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_> Subtract(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixSubtract<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}
		template<typename out_contained_type, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, out_contained_type, OutColumnMajor_> Subtract(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixSubtract<num_columns, num_rows, out_contained_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}
		template<bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type, OutColumnMajor_> Subtract(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixSubtract<num_columns, num_rows, value_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para> Performs a basic multiplication operation on this matrix using the passed rhs_. </para>
		/// <para>
		///		If the passed rhs_ is a matrix, respective indices in each matrix will be multiplied.
		///		Otherwise, each index in this matrix will be multiplied by rhs_.
		/// </para>
		/// <para>
		///		Template arguments are in the same order as when defining an EmuMath::Matrix. Arguments may be omitted to use the same as this matrix's arguments, 
		///		with the exception of out_contained_type, which will be this matrix's value_type.
		/// </para>
		/// <para> Note that this is not a standard matrix multiplication. For standard matrix multiplication, use Multiply. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained within the result matrix.</typeparam>
		/// <typeparam name="Rhs_">Type of matrix or scalar appearing on the right-hand side of multiplication.</typeparam>
		/// <param name="rhs_">EmuMath matrix or scalar appearing on the right-hand side of multiplication.</param>
		/// <returns>Matrix containing the results of multiplying this matrix by rhs_ as defined above.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MultiplyBasic(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixMultiplyBasic<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_> MultiplyBasic(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixMultiplyBasic<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}
		template<typename out_contained_type, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, out_contained_type, OutColumnMajor_> MultiplyBasic(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixMultiplyBasic<num_columns, num_rows, out_contained_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}
		template<bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type, OutColumnMajor_> MultiplyBasic(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixMultiplyBasic<num_columns, num_rows, value_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para> Performs a basic division operation on this matrix using the passed rhs_. </para>
		/// <para>
		///		If the passed rhs_ is a matrix, respective indices in each matrix will be divided.
		///		Otherwise, each index in this matrix will be divided by rhs_.
		/// </para>
		/// <para>
		///		Template arguments are in the same order as when defining an EmuMath::Matrix. Arguments may be omitted to use the same as this matrix's arguments, 
		///		with the exception of out_contained_type, which will be this matrix's value_type.
		/// </para>
		/// <para> Note that this is not a standard matrix division, as such a thing is mathematically undefined. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained within the result matrix.</typeparam>
		/// <typeparam name="Rhs_">Type of matrix or scalar appearing on the right-hand side of division.</typeparam>
		/// <param name="rhs_">EmuMath matrix or scalar appearing on the right-hand side of division.</param>
		/// <returns>Matrix containing the results of dividing this matrix by rhs_ as defined above.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> DivideBasic(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixDivideBasic<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_> DivideBasic(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixDivideBasic<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}
		template<typename out_contained_type, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, out_contained_type, OutColumnMajor_> DivideBasic(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixDivideBasic<num_columns, num_rows, out_contained_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}
		template<bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type, OutColumnMajor_> DivideBasic(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixDivideBasic<num_columns, num_rows, value_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para> Performs a basic modulo division operation on this matrix using the passed rhs_. </para>
		/// <para>
		///		If the passed rhs_ is a matrix, respective indices in each matrix will be divided.
		///		Otherwise, each index in this matrix will be divided by rhs_.
		/// </para>
		/// <para>
		///		Template arguments are in the same order as when defining an EmuMath::Matrix. Arguments may be omitted to use the same as this matrix's arguments, 
		///		with the exception of out_contained_type, which will be this matrix's value_type.
		/// </para>
		/// <para> Note that this is not a standard matrix modulo division, as such a thing is mathematically undefined. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained within the result matrix.</typeparam>
		/// <typeparam name="Rhs_">Type of matrix or scalar appearing on the right-hand side of division.</typeparam>
		/// <param name="rhs_">EmuMath matrix or scalar appearing on the right-hand side of division.</param>
		/// <returns>Matrix containing the results of modulo division of this matrix by rhs_ as defined above.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> ModBasic(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixModBasic<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_> ModBasic(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixModBasic<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}
		template<typename out_contained_type, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, out_contained_type, OutColumnMajor_> ModBasic(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixModBasic<num_columns, num_rows, out_contained_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}
		template<bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type, OutColumnMajor_> ModBasic(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixModBasic<num_columns, num_rows, value_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para>
		///		Returns a resulting EmuMath vector from a multiplication between this matrix and rhs_vector_, 
		///		where rhs_vector_ is interpreted as a single-column matrix.
		/// </para>
		/// <para> The provided vector requires one of two specific sizes in order to be valid: </para>
		/// <para> 1. Equal to the number of rows within this matrix. </para>
		/// <para> 2. Equal to the number of rows within this matrix - 1. The non-contained element will be implicitly considered to be 1. </para>
		/// <para> Condition 2. allows spatial transformation multiplications to be performed, such as transforming 3D vectors with a 4x4 transformation matrix. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained within the output vector.</typeparam>
		/// <typeparam name="RhsVector_">Type of vector appearing on the right of multiplication.</typeparam>
		/// <param name="rhs_vector_">EmuMath vector appearing on the right of multiplication.</param>
		/// <returns>
		///		EmuMath vector of the passed vector's size containing the results of matrix multiplication, where rhs_vector_ is interpreted as a single-column matrix.
		/// </returns>
		template<typename out_contained_type, class RhsVector_>
		[[nodiscard]] constexpr inline EmuMath::Vector<RhsVector_::size, out_contained_type> MultiplyVector(const RhsVector_& rhs_vector_) const
		{
			return EmuMath::Helpers::MatrixMultiplyVector<out_contained_type, this_type, RhsVector_>(*this, rhs_vector_);
		}
		template<class RhsVector_>
		[[nodiscard]] constexpr inline EmuMath::Vector<RhsVector_::size, typename RhsVector_::value_type> MultiplyVector(const RhsVector_& rhs_vector_) const
		{
			return EmuMath::Helpers::MatrixMultiplyVector<typename RhsVector_::value_type, this_type, RhsVector_>(*this, rhs_vector_);
		}

		/// <summary>
		/// <para> Performs a multiplication operation on this matrix using the passed rhs_. </para>
		/// <para> If the passed rhs_ is a matrix, the resulting matrix will be that of a standard matrix multiplication. </para>
		/// <para> If rhs_ is an EmuMath vector, it will be interpreted as a single-column matrix. Refer to MultiplyVector for more information. </para>
		/// <para> If rhs_ is anything else, all elements in this matrix are multiplied by rhs_. </para>
		/// <para> This is a standard matrix multiplication operation. To instead multiply respective matrix indices, use MultiplyBasic. </para>
		/// <para>
		///		Template arguments define the output contained type and column major order. The contained type defaults to this matrix's preferred_floating_point, 
		///		and column major order defaults to that of this matrix. Note that column major order is unused if the output result is not a matrix.
		/// </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained within the result matrix.</typeparam>
		/// <typeparam name="Rhs_">Type of matrix, vector, or scalar appearing on the right-hand side of multiplication.</typeparam>
		/// <param name="rhs_">EmuMath matrix, EmuMath vector, or scalar appearing on the right-hand side of multiplication.</param>
		/// <returns>Result of performing standard matrix multiplication on this matrix by the provided rhs_.</returns>
		template<typename out_contained_type = preferred_floating_point, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline auto Multiply(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixMultiply<out_contained_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para> Negates all elements within this matrix and outputs the results to a matrix defined with the provided template arguments. </para>
		/// <para>
		///		Template arguments are in the same order as when defining an EmuMath::Matrix. Arguments may be omitted to use the same as this matrix's arguments, 
		///		with the exception of out_contained_type, which will be this matrix's value_type.
		/// </para>
		/// </summary>
		/// <returns>Copy of this matrix after its elements have been negated.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> Negate() const
		{
			return EmuMath::Helpers::MatrixNegate<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_, this_type>(*this);
		}
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_> Negate() const
		{
			return EmuMath::Helpers::MatrixNegate<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_, this_type>(*this);
		}
		template<typename out_contained_type, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, out_contained_type, OutColumnMajor_> Negate() const
		{
			return EmuMath::Helpers::MatrixNegate<num_columns, num_rows, out_contained_type, OutColumnMajor_, this_type>(*this);
		}
		template<bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type, OutColumnMajor_> Negate() const
		{
			return EmuMath::Helpers::MatrixNegate<num_columns, num_rows, value_type, OutColumnMajor_, this_type>(*this);
		}

		/// <summary>
		/// <para> Floors all elements of this matrix, rounding them toward negative infinity. </para>
		/// <para>
		///		Template arguments are in the same order as when defining an EmuMath::Matrix. Arguments may be omitted to use the same as this matrix's arguments, 
		///		with the exception of out_contained_type, which will be this matrix's value_type.
		/// </para>
		/// </summary>
		/// <returns>Copy of this matrix with its elements rounded toward negative infinity.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> Floor() const
		{
			return EmuMath::Helpers::MatrixFloor<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_, this_type>(*this);
		}
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_> Floor() const
		{
			return EmuMath::Helpers::MatrixFloor<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_, this_type>(*this);
		}
		template<typename out_contained_type, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, out_contained_type, OutColumnMajor_> Floor() const
		{
			return EmuMath::Helpers::MatrixFloor<num_columns, num_rows, out_contained_type, OutColumnMajor_, this_type>(*this);
		}
		template<bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type, OutColumnMajor_> Floor() const
		{
			return EmuMath::Helpers::MatrixFloor<num_columns, num_rows, value_type, OutColumnMajor_, this_type>(*this);
		}

		/// <summary>
		/// <para> Ceils all elements of this matrix, rounding them toward positive infinity. </para>
		/// <para>
		///		Template arguments are in the same order as when defining an EmuMath::Matrix. Arguments may be omitted to use the same as this matrix's arguments, 
		///		with the exception of out_contained_type, which will be this matrix's value_type.
		/// </para>
		/// </summary>
		/// <returns>Copy of this matrix with its elements rounded toward positive infinity.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> Ceil() const
		{
			return EmuMath::Helpers::MatrixCeil<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_, this_type>(*this);
		}
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_> Ceil() const
		{
			return EmuMath::Helpers::MatrixCeil<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_, this_type>(*this);
		}
		template<typename out_contained_type, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, out_contained_type, OutColumnMajor_> Ceil() const
		{
			return EmuMath::Helpers::MatrixCeil<num_columns, num_rows, out_contained_type, OutColumnMajor_, this_type>(*this);
		}
		template<bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type, OutColumnMajor_> Ceil() const
		{
			return EmuMath::Helpers::MatrixCeil<num_columns, num_rows, value_type, OutColumnMajor_, this_type>(*this);
		}

		/// <summary>
		/// <para> Truncates all elements of this matrix, rounding them toward 0. </para>
		/// <para>
		///		Template arguments are in the same order as when defining an EmuMath::Matrix. Arguments may be omitted to use the same as this matrix's arguments, 
		///		with the exception of out_contained_type, which will be this matrix's value_type.
		/// </para>
		/// </summary>
		/// <returns>Copy of this matrix with its elements rounded toward 0.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> Trunc() const
		{
			return EmuMath::Helpers::MatrixTrunc<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_, this_type>(*this);
		}
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_> Trunc() const
		{
			return EmuMath::Helpers::MatrixTrunc<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_, this_type>(*this);
		}
		template<typename out_contained_type, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, out_contained_type, OutColumnMajor_> Trunc() const
		{
			return EmuMath::Helpers::MatrixTrunc<num_columns, num_rows, out_contained_type, OutColumnMajor_, this_type>(*this);
		}
		template<bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type, OutColumnMajor_> Trunc() const
		{
			return EmuMath::Helpers::MatrixTrunc<num_columns, num_rows, value_type, OutColumnMajor_, this_type>(*this);
		}

		/// <summary>
		/// <para> Finds the smallest respective value for each element of this matrix and rhs_. </para>
		/// <para> If rhs_ is an EmuMath matrix: Determined min elements will be for respective elements in this matrix and rhs_. </para>
		/// <para> If rhs_ is none of the above: Determined min elements will be for respective elements in this matrix and the value of rhs_. </para>
		/// <para>
		///		Template arguments are in the same order as when defining an EmuMath::Matrix. Arguments may be omitted to use the same as this matrix's arguments, 
		///		with the exception of out_contained_type, which will be this matrix's value_type.
		/// </para>
		/// </summary>
		/// <typeparam name="Rhs_">Type of item appearing as the right-hand argument.</typeparam>
		/// <param name="lhs_matrix_">Item appearing as the right-hand argument.</param>
		/// <returns>Matrix containing the minimum values for respective elements betweeen this matrix and rhs_.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> Min(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixMin<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_> Min(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixMin<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}
		template<typename out_contained_type, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, out_contained_type, OutColumnMajor_> Min(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixMin<num_columns, num_rows, out_contained_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}
		template<bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type, OutColumnMajor_> Min(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixMin<num_columns, num_rows, value_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para> Returns the index of the lowest element within this matrix. </para>
		/// <para> In the returned vector, element 0 represents the column index, and element 1 represents the row index. </para>
		/// </summary>
		/// <typeparam name="Matrix_">Matrix to find the highest element of.</typeparam>
		/// <returns>EmuMath vector containing the column and row index of the lowest element within this matrix.</returns>
		[[nodiscard]] constexpr EmuMath::Vector<2, std::size_t> MinIndex() const
		{
			return EmuMath::Helpers::MatrixMinIndex<this_type>(*this);
		}

		/// <summary>
		/// <para> Returns the lowest element within this matrix. </para>
		/// <para> The output type is customisable, but defaults to a suitable reference to the element within this matrix. </para>
		/// </summary>
		/// <typeparam name="Matrix_">Matrix to find the highest element of.</typeparam>
		/// <returns>The lowest element within this matrix as is suitable for the provided Out_ type.</returns>
		template<typename Out_ = raw_value_type&>
		[[nodiscard]] constexpr inline Out_ Min()
		{
			return EmuMath::Helpers::MatrixMin<Out_, this_type>(*this);
		}
		template<typename Out_ = const raw_value_type&>
		[[nodiscard]] constexpr inline Out_ Min() const
		{
			return EmuMath::Helpers::MatrixMin<Out_, const this_type>(*this);
		}

		/// <summary>
		/// <para> Finds the largest respective value for each element of this matrix and rhs_. </para>
		/// <para> If rhs_ is an EmuMath matrix: Determined max elements will be for respective elements in this matrix and rhs_. </para>
		/// <para> If rhs_ is none of the above: Determined max elements will be for respective elements in this matrix and the value of rhs_. </para>
		/// <para>
		///		Template arguments are in the same order as when defining an EmuMath::Matrix. Arguments may be omitted to use the same as this matrix's arguments, 
		///		with the exception of out_contained_type, which will be this matrix's value_type.
		/// </para>
		/// </summary>
		/// <typeparam name="Rhs_">Type of item appearing as the right-hand argument.</typeparam>
		/// <param name="lhs_matrix_">Item appearing as the right-hand argument.</param>
		/// <returns>Matrix containing the maximum values for respective elements betweeen this matrix and rhs_.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> Max(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixMax<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_> Max(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixMax<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}
		template<typename out_contained_type, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, out_contained_type, OutColumnMajor_> Max(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixMax<num_columns, num_rows, out_contained_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}
		template<bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type, OutColumnMajor_> Max(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixMax<num_columns, num_rows, value_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para> Returns the index of the highest element within this matrix. </para>
		/// <para> In the returned vector, element 0 represents the column index, and element 1 represents the row index. </para>
		/// </summary>
		/// <typeparam name="Matrix_">Matrix to find the highest element of.</typeparam>
		/// <returns>EmuMath vector containing the column and row index of the highest element within this matrix.</returns>
		[[nodiscard]] constexpr EmuMath::Vector<2, std::size_t> MaxIndex() const
		{
			return EmuMath::Helpers::MatrixMaxIndex<this_type>(*this);
		}

		/// <summary>
		/// <para> Returns the highest element within this matrix. </para>
		/// <para> The output type is customisable, but defaults to a suitable reference to the element within this matrix. </para>
		/// </summary>
		/// <typeparam name="Matrix_">Matrix to find the highest element of.</typeparam>
		/// <returns>The highest element within this matrix as is suitable for the provided Out_ type.</returns>
		template<typename Out_ = raw_value_type&>
		[[nodiscard]] constexpr inline Out_ Max()
		{
			return EmuMath::Helpers::MatrixMax<Out_, this_type>(*this);
		}
		template<typename Out_ = const raw_value_type&>
		[[nodiscard]] constexpr inline Out_ Max() const
		{
			return EmuMath::Helpers::MatrixMax<Out_, const this_type>(*this);
		}

		/// <summary>
		/// <para> Clamps this matrix so that none of its elements compare less than min_. </para>
		/// <para> If min_ is an EmuMath matrix: Elements in this matrix are clamped to a minimum of the respective element in min_. </para>
		/// <para> If min_ is none of the above: All elements in this matrix are clamped to a minimum of the value of min_. </para>
		/// <para>
		///		Template arguments are in the same order as when defining an EmuMath::Matrix. Arguments may be omitted to use the same as this matrix's arguments, 
		///		with the exception of out_contained_type, which will be this matrix's value_type.
		/// </para>
		/// </summary>
		/// <typeparam name="Min_">Type used as the minimum value to clamp to.</typeparam>
		/// <param name="min_">Item to clamp the matrix's minimum values to.</param>
		/// <returns>EmuMath matrix copy of this matrix with its elements clamped to a minimum via the passed min_ as defined above.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_ = is_column_major, class Min_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> ClampMin(const Min_& min_) const
		{
			return EmuMath::Helpers::MatrixClampMin<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_, this_type, Min_>(*this, min_);
		}
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_ = is_column_major, class Min_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_> ClampMin(const Min_& min_) const
		{
			return EmuMath::Helpers::MatrixClampMin<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_, this_type, Min_>(*this, min_);
		}
		template<typename out_contained_type, bool OutColumnMajor_ = is_column_major, class Min_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, out_contained_type, OutColumnMajor_> ClampMin(const Min_& min_) const
		{
			return EmuMath::Helpers::MatrixClampMin<num_columns, num_rows, out_contained_type, OutColumnMajor_, this_type, Min_>(*this, min_);
		}
		template<bool OutColumnMajor_ = is_column_major, class Min_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type, OutColumnMajor_> ClampMin(const Min_& min_) const
		{
			return EmuMath::Helpers::MatrixClampMin<num_columns, num_rows, value_type, OutColumnMajor_, this_type, Min_>(*this, min_);
		}

		/// <summary>
		/// <para> Clamps this matrix so that none of its elements compare greater than min_. </para>
		/// <para> If min_ is an EmuMath matrix: Elements in this matrix are clamped to a maximum of the respective element in min_. </para>
		/// <para> If min_ is none of the above: All elements in this matrix are clamped to a maximum of the value of min_. </para>
		/// <para>
		///		Template arguments are in the same order as when defining an EmuMath::Matrix. Arguments may be omitted to use the same as this matrix's arguments, 
		///		with the exception of out_contained_type, which will be this matrix's value_type.
		/// </para>
		/// </summary>
		/// <typeparam name="Max_">Type used as the maximum value to clamp to.</typeparam>
		/// <param name="max_">Item to clamp the matrix's maximum values to.</param>
		/// <returns>EmuMath matrix copy of this matrix with its elements clamped to a maximum via the passed max_ as defined above.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_ = is_column_major, class Max_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> ClampMax(const Max_& max_) const
		{
			return EmuMath::Helpers::MatrixClampMax<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_, this_type, Max_>(*this, max_);
		}
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_ = is_column_major, class Max_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_> ClampMax(const Max_& max_) const
		{
			return EmuMath::Helpers::MatrixClampMax<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_, this_type, Max_>(*this, max_);
		}
		template<typename out_contained_type, bool OutColumnMajor_ = is_column_major, class Max_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, out_contained_type, OutColumnMajor_> ClampMax(const Max_& max_) const
		{
			return EmuMath::Helpers::MatrixClampMax<num_columns, num_rows, out_contained_type, OutColumnMajor_, this_type, Max_>(*this, max_);
		}
		template<bool OutColumnMajor_ = is_column_major, class Max_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type, OutColumnMajor_> ClampMax(const Max_& max_) const
		{
			return EmuMath::Helpers::MatrixClampMax<num_columns, num_rows, value_type, OutColumnMajor_, this_type, Max_>(*this, max_);
		}

		/// <summary>
		/// <para> Clamps the passed matrix_ so that none of its elements compares less than min_ or greater than max_. </para>
		/// <para> If min_ is an EmuMath matrix: Elements in this matrix are clamped to a minimum of the respective element in min_. </para>
		/// <para> If min_ is none of the above: All elements in this matrix are clamped to a minimum of the value of min_. </para>
		/// <para> If max_ is an EmuMath matrix: Elements in this matrix are clamped to a maximum of the respective element in max_. </para>
		/// <para> If max_ is none of the above: All elements in this matrix are clamped to a maximum of the value of max_. </para>
		/// <para> Both min_ and max_ are assumed to be logically correct (i.e. min_ &lt;= max_, or compared respective elements where either min_ and/or max_ is a matrix). </para>
		/// </summary>
		/// <typeparam name="Min_">Type used as the minimum value to clamp to.</typeparam>
		/// <typeparam name="Max_">Type used as the minimum value to clamp to.</typeparam>
		/// <param name="min_">Item to clamp this matrix's minimum values to.</param>
		/// <param name="max_">Item to clamp this matrix's maximum values to.</param>
		/// <returns>EmuMath matrix copy of this matrix with its elements between the provided min_ and max_ as defined above.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_ = is_column_major, class Min_, class Max_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> Clamp(const Min_& min_, const Max_& max_) const
		{
			return EmuMath::Helpers::MatrixClamp<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_, this_type, Min_, Max_>(*this, min_, max_);
		}
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_ = is_column_major, class Min_, class Max_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_> Clamp(const Min_& min_, const Max_& max_) const
		{
			return EmuMath::Helpers::MatrixClamp<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_, this_type, Min_, Max_>(*this, min_, max_);
		}
		template<typename out_contained_type, bool OutColumnMajor_ = is_column_major, class Min_, class Max_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, out_contained_type, OutColumnMajor_> Clamp(const Min_& min_, const Max_& max_) const
		{
			return EmuMath::Helpers::MatrixClamp<num_columns, num_rows, out_contained_type, OutColumnMajor_, this_type, Min_, Max_>(*this, min_, max_);
		}
		template<bool OutColumnMajor_ = is_column_major, class Min_, class Max_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type, OutColumnMajor_> Clamp(const Min_& min_, const Max_& max_) const
		{
			return EmuMath::Helpers::MatrixClamp<num_columns, num_rows, value_type, OutColumnMajor_, this_type, Min_, Max_>(*this, min_, max_);
		}

		/// <summary>
		/// <para>
		///		Linearly interpolates the elements of this matrix using the target b_ and weighting t_. 
		///		Result may be summarised as a + ((b - a) * t), where this matrix is a.
		/// </para>
		/// <para> If b_ is an EmuMath matrix, elements in this matrix will be interpolated with respective elements of b_ used as targets. </para>
		/// <para> If b_ is none of the above: elements in this matrix will all be interpolated with a target of the value of b_. </para>
		/// <para> If t_ is an EmuMath matrix, elements in this matrix will be interpolated with respective elements of t_ used as weightings. </para>
		/// <para> If b_ is none of the above: elements in this matrix will all be interpolated with a target of the value of t_. </para>
		/// </summary>
		/// <typeparam name="B_">Type representing the target for interpolation.</typeparam>
		/// <typeparam name="T_">Type representing the weighting for interpolation.</typeparam>
		/// <param name="b_">Item to provide a target for elements of this matrix to interpolate towards.</param>
		/// <param name="t_">Item to provide the weightings for how much this matrix's elements should interpolate towards their target.</param>
		/// <returns>Resulting matrix from linear interpolation using the provided arguments as defined above.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_ = is_column_major, class B_, class T__>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> Lerp(const B_& b_, const T__& t_) const
		{
			return EmuMath::Helpers::MatrixLerp<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_, this_type, B_, T__>(*this, b_, t_);
		}
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_ = is_column_major, class B_, class T__>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_> Lerp(const B_& b_, const T__& t_) const
		{
			return EmuMath::Helpers::MatrixLerp<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_, this_type, B_, T__>(*this, b_, t_);
		}
		template<typename out_contained_type, bool OutColumnMajor_ = is_column_major, class B_, class T__>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, out_contained_type, OutColumnMajor_> Lerp(const B_& b_, const T__& t_) const
		{
			return EmuMath::Helpers::MatrixLerp<num_columns, num_rows, out_contained_type, OutColumnMajor_, this_type, B_, T__>(*this, b_, t_);
		}
		template<bool OutColumnMajor_ = is_column_major, class B_, class T__>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type, OutColumnMajor_> Lerp(const B_& b_, const T__& t_) const
		{
			return EmuMath::Helpers::MatrixLerp<num_columns, num_rows, value_type, OutColumnMajor_, this_type, B_, T__>(*this, b_, t_);
		}
#pragma endregion

#pragma region BITWISE_FUNCTIONS
		/// <summary>
		/// <para> Performs a bitwise AND operation on the elements of this matrix with the provided rhs_. </para>
		/// <para> If rhs_ is an EmuMath matrix: Respective elements will be ANDed. </para>
		/// <para> If rhs_ is none of the above: All elements within this matrix will be ANDed with the value of rhs_. </para>
		/// <para>
		///		Template arguments are in the same order as when defining an EmuMath::Matrix. Arguments may be omitted to use the same as this matrix's arguments, 
		///		with the exception of out_contained_type, which will be this matrix's value_type.
		/// </para>
		/// </summary>
		/// <typeparam name="Rhs_">Type appearing of the right of a bitwise AND.</typeparam>
		/// <param name="rhs_">Item appearing on the right of a bitwise AND.</param>
		/// <returns>Matrix resulting from a bitwise AND between this matrix and rhs_.</returns>
		template<std::size_t OutNumColumns, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns, OutNumRows_, out_contained_type, OutColumnMajor_> And(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixAnd<OutNumColumns, OutNumRows_, out_contained_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}
		template<std::size_t OutNumColumns, std::size_t OutNumRows_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns, OutNumRows_, value_type, OutColumnMajor_> And(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixAnd<OutNumColumns, OutNumRows_, value_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}
		template<typename out_contained_type, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, out_contained_type, OutColumnMajor_> And(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixAnd<num_columns, num_rows, out_contained_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}
		template<bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type, OutColumnMajor_> And(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixAnd<num_columns, num_rows, value_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para> Performs a bitwise OR operation on the elements of this matrix with the provided rhs_. </para>
		/// <para> If rhs_ is an EmuMath matrix: Respective elements will be ORed. </para>
		/// <para> If rhs_ is none of the above: All elements within this matrix will be ORed with the value of rhs_. </para>
		/// <para>
		///		Template arguments are in the same order as when defining an EmuMath::Matrix. Arguments may be omitted to use the same as this matrix's arguments, 
		///		with the exception of out_contained_type, which will be this matrix's value_type.
		/// </para>
		/// </summary>
		/// <typeparam name="Rhs_">Type appearing of the right of a bitwise OR.</typeparam>
		/// <param name="rhs_">Item appearing on the right of a bitwise OR.</param>
		/// <returns>Matrix resulting from a bitwise OR between this matrix and rhs_.</returns>
		template<std::size_t OutNumColumns, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns, OutNumRows_, out_contained_type, OutColumnMajor_> Or(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixOr<OutNumColumns, OutNumRows_, out_contained_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}
		template<std::size_t OutNumColumns, std::size_t OutNumRows_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns, OutNumRows_, value_type, OutColumnMajor_> Or(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixOr<OutNumColumns, OutNumRows_, value_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}
		template<typename out_contained_type, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, out_contained_type, OutColumnMajor_> Or(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixOr<num_columns, num_rows, out_contained_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}
		template<bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type, OutColumnMajor_> Or(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixOr<num_columns, num_rows, value_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para> Performs a bitwise XOR operation on the elements of this matrix with the provided rhs_. </para>
		/// <para> If rhs_ is an EmuMath matrix: Respective elements will be XORed. </para>
		/// <para> If rhs_ is none of the above: All elements within this matrix will be XORed with the value of rhs_. </para>
		/// <para>
		///		Template arguments are in the same order as when defining an EmuMath::Matrix. Arguments may be omitted to use the same as this matrix's arguments, 
		///		with the exception of out_contained_type, which will be this matrix's value_type.
		/// </para>
		/// </summary>
		/// <typeparam name="Rhs_">Type appearing of the right of a bitwise XOR.</typeparam>
		/// <param name="rhs_">Item appearing on the right of a bitwise XOR.</param>
		/// <returns>Matrix resulting from a bitwise XOR between this matrix and rhs_.</returns>
		template<std::size_t OutNumColumns, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns, OutNumRows_, out_contained_type, OutColumnMajor_> Xor(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixXor<OutNumColumns, OutNumRows_, out_contained_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}
		template<std::size_t OutNumColumns, std::size_t OutNumRows_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns, OutNumRows_, value_type, OutColumnMajor_> Xor(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixXor<OutNumColumns, OutNumRows_, value_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}
		template<typename out_contained_type, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, out_contained_type, OutColumnMajor_> Xor(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixXor<num_columns, num_rows, out_contained_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}
		template<bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type, OutColumnMajor_> Xor(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixXor<num_columns, num_rows, value_type, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para> Performs a bitwise NOT operation on the elements of this matrix. </para>
		/// <para>
		///		Template arguments are in the same order as when defining an EmuMath::Matrix. Arguments may be omitted to use the same as this matrix's arguments, 
		///		with the exception of out_contained_type, which will be this matrix's value_type.
		/// </para>
		/// </summary>
		/// <returns>Copy of this matrix with a bitwise NOT performed on it.</returns>
		template<std::size_t OutNumColumns, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns, OutNumRows_, out_contained_type, OutColumnMajor_> Not() const
		{
			return EmuMath::Helpers::MatrixNot<OutNumColumns, OutNumRows_, out_contained_type, OutColumnMajor_, this_type>(*this);
		}
		template<std::size_t OutNumColumns, std::size_t OutNumRows_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns, OutNumRows_, value_type, OutColumnMajor_> Not() const
		{
			return EmuMath::Helpers::MatrixNot<OutNumColumns, OutNumRows_, value_type, OutColumnMajor_, this_type>(*this);
		}
		template<typename out_contained_type, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, out_contained_type, OutColumnMajor_> Not() const
		{
			return EmuMath::Helpers::MatrixNot<num_columns, num_rows, out_contained_type, OutColumnMajor_, this_type>(*this);
		}
		template<bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type, OutColumnMajor_> Not() const
		{
			return EmuMath::Helpers::MatrixNot<num_columns, num_rows, value_type, OutColumnMajor_, this_type>(*this);
		}

		/// <summary>
		/// <para> Shifts all elements of this matrix to the left the specified number of times within num_shifts_. </para>
		/// <para> If num_shifts_ is an EmuMath matrix: each element of this matrix will be shifted by the respective element in num_shifts_. </para>
		/// <para> If num_shifts_ is none of the above: every element of this matrix will be shifted by the value of num_shifts_. </para>
		/// <para>
		///		Template arguments are in the same order as when defining an EmuMath::Matrix. Arguments may be omitted to use the same as this matrix's arguments, 
		///		with the exception of out_contained_type, which will be this matrix's value_type.
		/// </para>
		/// </summary>
		/// <typeparam name="Shifts_">Type of argument indicating the number of shifts.</typeparam>
		/// <param name="num_shifts_">Number of shifts to perform on this matrix as defined above.</param>
		/// <returns>EmuMath matrix copy of this matrix with each element shifted to the left a number of times indicated by num_shifts_.</returns>
		template<std::size_t OutNumColumns, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_ = is_column_major, class Shifts_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns, OutNumRows_, out_contained_type, OutColumnMajor_> ShiftLeft(const Shifts_& num_shifts_) const
		{
			return EmuMath::Helpers::MatrixShiftLeft<OutNumColumns, OutNumRows_, out_contained_type, OutColumnMajor_, this_type, Shifts_>(*this, num_shifts_);
		}
		template<std::size_t OutNumColumns, std::size_t OutNumRows_, bool OutColumnMajor_ = is_column_major, class Shifts_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns, OutNumRows_, value_type, OutColumnMajor_> ShiftLeft(const Shifts_& num_shifts_) const
		{
			return EmuMath::Helpers::MatrixShiftLeft<OutNumColumns, OutNumRows_, value_type, OutColumnMajor_, this_type, Shifts_>(*this, num_shifts_);
		}
		template<typename out_contained_type, bool OutColumnMajor_ = is_column_major, class Shifts_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, out_contained_type, OutColumnMajor_> ShiftLeft(const Shifts_& num_shifts_) const
		{
			return EmuMath::Helpers::MatrixShiftLeft<num_columns, num_rows, out_contained_type, OutColumnMajor_, this_type, Shifts_>(*this, num_shifts_);
		}
		template<bool OutColumnMajor_ = is_column_major, class Shifts_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type, OutColumnMajor_> ShiftLeft(const Shifts_& num_shifts_) const
		{
			return EmuMath::Helpers::MatrixShiftLeft<num_columns, num_rows, value_type, OutColumnMajor_, this_type, Shifts_>(*this, num_shifts_);
		}

		/// <summary>
		/// <para> Shifts all elements of this matrix to the right the specified number of times within num_shifts_. </para>
		/// <para> If num_shifts_ is an EmuMath matrix: each element of this matrix will be shifted by the respective element in num_shifts_. </para>
		/// <para> If num_shifts_ is none of the above: every element of this matrix will be shifted by the value of num_shifts_. </para>
		/// <para>
		///		Template arguments are in the same order as when defining an EmuMath::Matrix. Arguments may be omitted to use the same as this matrix's arguments, 
		///		with the exception of out_contained_type, which will be this matrix's value_type.
		/// </para>
		/// </summary>
		/// <typeparam name="Shifts_">Type of argument indicating the number of shifts.</typeparam>
		/// <param name="num_shifts_">Number of shifts to perform on this matrix as defined above.</param>
		/// <returns>EmuMath matrix copy of this matrix with each element shifted to the right a number of times indicated by num_shifts_.</returns>
		template<std::size_t OutNumColumns, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_ = is_column_major, class Shifts_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns, OutNumRows_, out_contained_type, OutColumnMajor_> ShiftRight(const Shifts_& num_shifts_) const
		{
			return EmuMath::Helpers::MatrixShiftRight<OutNumColumns, OutNumRows_, out_contained_type, OutColumnMajor_, this_type, Shifts_>(*this, num_shifts_);
		}
		template<std::size_t OutNumColumns, std::size_t OutNumRows_, bool OutColumnMajor_ = is_column_major, class Shifts_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns, OutNumRows_, value_type, OutColumnMajor_> ShiftRight(const Shifts_& num_shifts_) const
		{
			return EmuMath::Helpers::MatrixShiftRight<OutNumColumns, OutNumRows_, value_type, OutColumnMajor_, this_type, Shifts_>(*this, num_shifts_);
		}
		template<typename out_contained_type, bool OutColumnMajor_ = is_column_major, class Shifts_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, out_contained_type, OutColumnMajor_> ShiftRight(const Shifts_& num_shifts_) const
		{
			return EmuMath::Helpers::MatrixShiftRight<num_columns, num_rows, out_contained_type, OutColumnMajor_, this_type, Shifts_>(*this, num_shifts_);
		}
		template<bool OutColumnMajor_ = is_column_major, class Shifts_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type, OutColumnMajor_> ShiftRight(const Shifts_& num_shifts_) const
		{
			return EmuMath::Helpers::MatrixShiftRight<num_columns, num_rows, value_type, OutColumnMajor_, this_type, Shifts_>(*this, num_shifts_);
		}
#pragma endregion

#pragma region COMPARISON_FUNCTIONS
		/// <summary>
		/// <para> Compares the equality of each element in this matrix to rhs_ and returns the results of comparisons in respective indices of a matrix of booleans. </para>
		/// <para> If rhs_ is an EmuMath matrix: Comparisons for elements in this matrix will be performed with respective elements in rhs_. </para>
		/// <para> If rhs_ is none of the above: Comparisons for elements in this matrix will all be performed with the value of rhs_. </para>
		/// </summary>
		/// <typeparam name="Rhs_">Type of item appearing on the right-hand side of comparisons.</typeparam>
		/// <param name="rhs_">Item appearing on the right-hand side of comparisons.</param>
		/// <returns>Matrix of booleans containing the results of comparisons of each respective element in this matrix with rhs_ as defined above.</returns>
		template<std::size_t NumColumnsToTest_ = num_columns, std::size_t NumRowsToTest_ = num_rows, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, OutColumnMajor_> CmpPerElementEqual(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixCmpPerElementEqual<NumColumnsToTest_, NumRowsToTest_, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}
		/// <summary>
		/// <para> Compares the inequality of each element in this matrix to rhs_ and returns the results of comparisons in respective indices of a matrix of booleans. </para>
		/// <para> If rhs_ is an EmuMath matrix: Comparisons for elements in this matrix will be performed with respective elements in rhs_. </para>
		/// <para> If rhs_ is none of the above: Comparisons for elements in this matrix will all be performed with the value of rhs_. </para>
		/// </summary>
		/// <typeparam name="Rhs_">Type of item appearing on the right-hand side of comparisons.</typeparam>
		/// <param name="rhs_">Item appearing on the right-hand side of comparisons.</param>
		/// <returns>Matrix of booleans containing the results of comparisons of each respective element in this matrix with rhs_ as defined above.</returns>
		template<std::size_t NumColumnsToTest_ = num_columns, std::size_t NumRowsToTest_ = num_rows, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, OutColumnMajor_> CmpPerElementNotEqual(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixCmpPerElementNotEqual<NumColumnsToTest_, NumRowsToTest_, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}
		/// <summary>
		/// <para> Compares the magnitude of each element in this matrix to rhs_ and returns the results of comparisons in respective indices of a matrix of booleans. </para>
		/// <para> If rhs_ is an EmuMath matrix: Comparisons for elements in this matrix will be performed with respective elements in rhs_. </para>
		/// <para> If rhs_ is none of the above: Comparisons for elements in this matrix will all be performed with the value of rhs_. </para>
		/// </summary>
		/// <typeparam name="Rhs_">Type of item appearing on the right-hand side of comparisons.</typeparam>
		/// <param name="rhs_">Item appearing on the right-hand side of comparisons.</param>
		/// <returns>Matrix of booleans containing the results of magntidue of each respective element in this matrix with rhs_ as defined above.</returns>
		template<std::size_t NumColumnsToTest_ = num_columns, std::size_t NumRowsToTest_ = num_rows, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, OutColumnMajor_> CmpPerElementGreater(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixCmpPerElementGreater<NumColumnsToTest_, NumRowsToTest_, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}
		/// <summary>
		/// <para> Compares the magnitude of each element in this matrix to rhs_ and returns the results of comparisons in respective indices of a matrix of booleans. </para>
		/// <para> If rhs_ is an EmuMath matrix: Comparisons for elements in this matrix will be performed with respective elements in rhs_. </para>
		/// <para> If rhs_ is none of the above: Comparisons for elements in this matrix will all be performed with the value of rhs_. </para>
		/// </summary>
		/// <typeparam name="Rhs_">Type of item appearing on the right-hand side of comparisons.</typeparam>
		/// <param name="rhs_">Item appearing on the right-hand side of comparisons.</param>
		/// <returns>Matrix of booleans containing the results of magntidue of each respective element in this matrix with rhs_ as defined above.</returns>
		template<std::size_t NumColumnsToTest_ = num_columns, std::size_t NumRowsToTest_ = num_rows, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, OutColumnMajor_> CmpPerElementLess(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixCmpPerElementLess<NumColumnsToTest_, NumRowsToTest_, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}
		/// <summary>
		/// <para> Compares the magnitude of each element in this matrix to rhs_ and returns the results of comparisons in respective indices of a matrix of booleans. </para>
		/// <para> If rhs_ is an EmuMath matrix: Comparisons for elements in this matrix will be performed with respective elements in rhs_. </para>
		/// <para> If rhs_ is none of the above: Comparisons for elements in this matrix will all be performed with the value of rhs_. </para>
		/// </summary>
		/// <typeparam name="Rhs_">Type of item appearing on the right-hand side of comparisons.</typeparam>
		/// <param name="rhs_">Item appearing on the right-hand side of comparisons.</param>
		/// <returns>Matrix of booleans containing the results of magntidue of each respective element in this matrix with rhs_ as defined above.</returns>
		template<std::size_t NumColumnsToTest_ = num_columns, std::size_t NumRowsToTest_ = num_rows, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, OutColumnMajor_> CmpPerElementGreaterEqual(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixCmpPerElementGreaterEqual<NumColumnsToTest_, NumRowsToTest_, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}
		/// <summary>
		/// <para> Compares the magnitude of each element in this matrix to rhs_ and returns the results of comparisons in respective indices of a matrix of booleans. </para>
		/// <para> If rhs_ is an EmuMath matrix: Comparisons for elements in this matrix will be performed with respective elements in rhs_. </para>
		/// <para> If rhs_ is none of the above: Comparisons for elements in this matrix will all be performed with the value of rhs_. </para>
		/// </summary>
		/// <typeparam name="Rhs_">Type of item appearing on the right-hand side of comparisons.</typeparam>
		/// <param name="rhs_">Item appearing on the right-hand side of comparisons.</param>
		/// <returns>Matrix of booleans containing the results of magntidue of each respective element in this matrix with rhs_ as defined above.</returns>
		template<std::size_t NumColumnsToTest_ = num_columns, std::size_t NumRowsToTest_ = num_rows, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, OutColumnMajor_> CmpPerElementLessEqual(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixCmpPerElementLessEqual<NumColumnsToTest_, NumRowsToTest_, OutColumnMajor_, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para> Returns true if all equal_to comparisons between this matrix and rhs_ return true. </para>
		/// <para> 
		///		If rhs_ is an EmuMath matrix: respective elements within the two matrices will be compared. 
		///		If this is the case, comparisons will only be performed on shared elements by default. To test all elements regardless of size, set TestAllIndices_ to true.
		/// </para>
		/// </summary>
		/// <typeparam name="Rhs_">Item appearing on the right-hand side of equal_to comparisons.</typeparam>
		/// <param name="rhs_">Item appearing on the right-hand side of equal_to comparisons.</param>
		/// <returns>Boolean indcating if comparisons on all elements within this matrix with rhs_ as defined above returned true.</returns>
		template<bool TestAllIndices_ = false, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAllEqual(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixCmpAllEqual<TestAllIndices_, this_type, Rhs_>(*this, rhs_);
		}
		/// <summary>
		/// <para> Returns true if all not_equal_to comparisons between this matrix and rhs_ return true. </para>
		/// <para> 
		///		If rhs_ is an EmuMath matrix: respective elements within the two matrices will be compared. 
		///		If this is the case, comparisons will only be performed on shared elements by default. To test all elements regardless of size, set TestAllIndices_ to true.
		/// </para>
		/// </summary>
		/// <typeparam name="Rhs_">Item appearing on the right-hand side of equal_to comparisons.</typeparam>
		/// <param name="rhs_">Item appearing on the right-hand side of equal_to comparisons.</param>
		/// <returns>Boolean indcating if comparisons on all elements within this matrix with rhs_ as defined above returned true.</returns>
		template<bool TestAllIndices_ = false, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAllNotEqual(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixCmpAllNotEqual<TestAllIndices_, this_type, Rhs_>(*this, rhs_);
		}
		/// <summary>
		/// <para> Returns true if all greater_than comparisons between this matrix and rhs_ return true. </para>
		/// <para> 
		///		If rhs_ is an EmuMath matrix: respective elements within the two matrices will be compared. 
		///		If this is the case, comparisons will only be performed on shared elements by default. To test all elements regardless of size, set TestAllIndices_ to true.
		/// </para>
		/// </summary>
		/// <typeparam name="Rhs_">Item appearing on the right-hand side of equal_to comparisons.</typeparam>
		/// <param name="rhs_">Item appearing on the right-hand side of equal_to comparisons.</param>
		/// <returns>Boolean indcating if comparisons on all elements within this matrix with rhs_ as defined above returned true.</returns>
		template<bool TestAllIndices_ = false, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAllGreater(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixCmpAllGreater<TestAllIndices_, this_type, Rhs_>(*this, rhs_);
		}
		/// <summary>
		/// <para> Returns true if all less_than comparisons between this matrix and rhs_ return true. </para>
		/// <para> 
		///		If rhs_ is an EmuMath matrix: respective elements within the two matrices will be compared. 
		///		If this is the case, comparisons will only be performed on shared elements by default. To test all elements regardless of size, set TestAllIndices_ to true.
		/// </para>
		/// </summary>
		/// <typeparam name="Rhs_">Item appearing on the right-hand side of equal_to comparisons.</typeparam>
		/// <param name="rhs_">Item appearing on the right-hand side of equal_to comparisons.</param>
		/// <returns>Boolean indcating if comparisons on all elements within this matrix with rhs_ as defined above returned true.</returns>
		template<bool TestAllIndices_ = false, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAllLess(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixCmpAllLess<TestAllIndices_, this_type, Rhs_>(*this, rhs_);
		}
		/// <summary>
		/// <para> Returns true if all greater_equal comparisons between this matrix and rhs_ return true. </para>
		/// <para> 
		///		If rhs_ is an EmuMath matrix: respective elements within the two matrices will be compared. 
		///		If this is the case, comparisons will only be performed on shared elements by default. To test all elements regardless of size, set TestAllIndices_ to true.
		/// </para>
		/// </summary>
		/// <typeparam name="Rhs_">Item appearing on the right-hand side of equal_to comparisons.</typeparam>
		/// <param name="rhs_">Item appearing on the right-hand side of equal_to comparisons.</param>
		/// <returns>Boolean indcating if comparisons on all elements within this matrix with rhs_ as defined above returned true.</returns>
		template<bool TestAllIndices_ = false, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAllGreaterEqual(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixCmpAllGreaterEqual<TestAllIndices_, this_type, Rhs_>(*this, rhs_);
		}
		/// <summary>
		/// <para> Returns true if all less_equal comparisons between this matrix and rhs_ return true. </para>
		/// <para> 
		///		If rhs_ is an EmuMath matrix: respective elements within the two matrices will be compared. 
		///		If this is the case, comparisons will only be performed on shared elements by default. To test all elements regardless of size, set TestAllIndices_ to true.
		/// </para>
		/// </summary>
		/// <typeparam name="Rhs_">Item appearing on the right-hand side of equal_to comparisons.</typeparam>
		/// <param name="rhs_">Item appearing on the right-hand side of equal_to comparisons.</param>
		/// <returns>Boolean indcating if comparisons on all elements within this matrix with rhs_ as defined above returned true.</returns>
		template<bool TestAllIndices_ = false, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAllLessEqual(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixCmpAllLessEqual<TestAllIndices_, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para> Returns true if at least one equal_to comparison between this matrix and rhs_ returns true. </para>
		/// <para> 
		///		If rhs_ is an EmuMath matrix: respective elements within the two matrices will be compared. 
		///		If this is the case, comparisons will only be performed on shared elements by default. To test all elements regardless of size, set TestAllIndices_ to true.
		/// </para>
		/// </summary>
		/// <typeparam name="Rhs_">Item appearing on the right-hand side of equal_to comparisons.</typeparam>
		/// <param name="rhs_">Item appearing on the right-hand side of equal_to comparisons.</param>
		/// <returns>Boolean indcating if comparisons on any elements within this matrix with rhs_ as defined above returned true.</returns>
		template<bool TestAllIndices_ = false, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAnyEqual(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixCmpAnyEqual<TestAllIndices_, this_type, Rhs_>(*this, rhs_);
		}
		/// <summary>
		/// <para> Returns true if at least one not_equal_to comparison between this matrix and rhs_ returns true. </para>
		/// <para> 
		///		If rhs_ is an EmuMath matrix: respective elements within the two matrices will be compared. 
		///		If this is the case, comparisons will only be performed on shared elements by default. To test all elements regardless of size, set TestAllIndices_ to true.
		/// </para>
		/// </summary>
		/// <typeparam name="Rhs_">Item appearing on the right-hand side of equal_to comparisons.</typeparam>
		/// <param name="rhs_">Item appearing on the right-hand side of equal_to comparisons.</param>
		/// <returns>Boolean indcating if comparisons on any elements within this matrix with rhs_ as defined above returned true.</returns>
		template<bool TestAllIndices_ = false, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAnyNotEqual(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixCmpAnyNotEqual<TestAllIndices_, this_type, Rhs_>(*this, rhs_);
		}
		/// <summary>
		/// <para> Returns true if at least one greater_than comparison between this matrix and rhs_ returns true. </para>
		/// <para> 
		///		If rhs_ is an EmuMath matrix: respective elements within the two matrices will be compared. 
		///		If this is the case, comparisons will only be performed on shared elements by default. To test all elements regardless of size, set TestAllIndices_ to true.
		/// </para>
		/// </summary>
		/// <typeparam name="Rhs_">Item appearing on the right-hand side of equal_to comparisons.</typeparam>
		/// <param name="rhs_">Item appearing on the right-hand side of equal_to comparisons.</param>
		/// <returns>Boolean indcating if comparisons on any elements within this matrix with rhs_ as defined above returned true.</returns>
		template<bool TestAllIndices_ = false, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAnyGreater(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixCmpAnyGreater<TestAllIndices_, this_type, Rhs_>(*this, rhs_);
		}
		/// <summary>
		/// <para> Returns true if at least one less_than comparison between this matrix and rhs_ returns true. </para>
		/// <para> 
		///		If rhs_ is an EmuMath matrix: respective elements within the two matrices will be compared. 
		///		If this is the case, comparisons will only be performed on shared elements by default. To test all elements regardless of size, set TestAllIndices_ to true.
		/// </para>
		/// </summary>
		/// <typeparam name="Rhs_">Item appearing on the right-hand side of equal_to comparisons.</typeparam>
		/// <param name="rhs_">Item appearing on the right-hand side of equal_to comparisons.</param>
		/// <returns>Boolean indcating if comparisons on any elements within this matrix with rhs_ as defined above returned true.</returns>
		template<bool TestAllIndices_ = false, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAnyLess(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixCmpAnyLess<TestAllIndices_, this_type, Rhs_>(*this, rhs_);
		}
		/// <summary>
		/// <para> Returns true if at least one greater_equal comparison between this matrix and rhs_ returns true. </para>
		/// <para> 
		///		If rhs_ is an EmuMath matrix: respective elements within the two matrices will be compared. 
		///		If this is the case, comparisons will only be performed on shared elements by default. To test all elements regardless of size, set TestAllIndices_ to true.
		/// </para>
		/// </summary>
		/// <typeparam name="Rhs_">Item appearing on the right-hand side of equal_to comparisons.</typeparam>
		/// <param name="rhs_">Item appearing on the right-hand side of equal_to comparisons.</param>
		/// <returns>Boolean indcating if comparisons on any elements within this matrix with rhs_ as defined above returned true.</returns>
		template<bool TestAllIndices_ = false, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAnyGreaterEqual(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixCmpAnyGreaterEqual<TestAllIndices_, this_type, Rhs_>(*this, rhs_);
		}
		/// <summary>
		/// <para> Returns true if at least one less_equal comparison between this matrix and rhs_ returns true. </para>
		/// <para> 
		///		If rhs_ is an EmuMath matrix: respective elements within the two matrices will be compared. 
		///		If this is the case, comparisons will only be performed on shared elements by default. To test all elements regardless of size, set TestAllIndices_ to true.
		/// </para>
		/// </summary>
		/// <typeparam name="Rhs_">Item appearing on the right-hand side of equal_to comparisons.</typeparam>
		/// <param name="rhs_">Item appearing on the right-hand side of equal_to comparisons.</param>
		/// <returns>Boolean indcating if comparisons on any elements within this matrix with rhs_ as defined above returned true.</returns>
		template<bool TestAllIndices_ = false, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAnyLessEqual(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixCmpAnyLessEqual<TestAllIndices_, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para> Returns true if the passed matrix is equal to this matrix. </para>
		/// <para>
		///		By default, only the lowest-sized matrix indices are compared.
		///		To compare even non-existent indices, set the TestAllIndices_ template argument to true.
		/// </para>
		/// <para> This is effectively shorthand for calling CmpAllEqual with a matrix rhs_, but also enforces a guarantee that rhs_ will be a matrix. </para>
		/// </summary>
		/// <typeparam name="RhsMatrix_">Type of matrix appearing on the right of the comparison.</typeparam>
		/// <param name="rhs_matrix_">EmuMath matrix appearing on the right of the comparison.</param>
		/// <returns>True if all respective elements (overall or smallest-size, depending on TestAllIndices_ value) of the matrices are equal; otherwise false.</returns>
		template<bool TestAllIndices_ = false, class RhsMatrix_>
		[[nodiscard]] constexpr inline bool CmpEqual(const RhsMatrix_& rhs_matrix_) const
		{
			return EmuMath::Helpers::MatrixCmpEqual<TestAllIndices_, this_type, RhsMatrix_>(*this, rhs_matrix_);
		}
		/// <summary>
		/// <para> Returns true if the passed matrix is not equal to this matrix. </para>
		/// <para>
		///		By default, only the lowest-sized matrix indices are compared.
		///		To compare even non-existent indices, set the TestAllIndices_ template argument to true.
		/// </para>
		/// <para> This is effectively shorthand for calling CmpAnyNotEqual with a matrix rhs_, but also enforces a guarantee that rhs_ will be a matrix. </para>
		/// </summary>
		/// <typeparam name="RhsMatrix_">Type of matrix appearing on the right of the comparison.</typeparam>
		/// <param name="rhs_matrix_">EmuMath matrix appearing on the right of the comparison.</param>
		/// <returns>True if any respective elements (overall or smallest-size, depending on TestAllIndices_ value) of the matrices are not equal; otherwise false.</returns>
		template<bool TestAllIndices_ = false, class RhsMatrix_>
		[[nodiscard]] constexpr inline bool CmpNotEqual(const RhsMatrix_& rhs_matrix_) const
		{
			return EmuMath::Helpers::MatrixCmpNotEqual<TestAllIndices_, this_type, RhsMatrix_>(*this, rhs_matrix_);
		}
#pragma endregion

	private:
		data_storage_type data_;
#pragma region SELF_HELPERS
		template<std::size_t ColumnIndex_, std::size_t RowIndex_>
		static constexpr inline bool _valid_static_indices()
		{
			if constexpr (ColumnIndex_ < num_columns)
			{
				if constexpr (RowIndex_ < num_rows)
				{
					return true;
				}
				else
				{
					static_assert(false, "Provided an invalid ColumnIndex_ when attempting to access a row of an EmuMath matrix.");
					return false;
				}
			}
			else
			{
				static_assert(false, "Provided an invalid ColumnIndex_ when attempting to access a column of an EmuMath matrix.");
				return false;
			}
		}

		template<std::size_t ColumnIndex_, std::size_t RowIndex_>
		constexpr inline raw_value_type& _get_index()
		{
			if constexpr (is_column_major)
			{
				return data_.template at<ColumnIndex_>().template at<RowIndex_>();
			}
			else
			{
				return data_.template at<RowIndex_>().template at<ColumnIndex_>();
			}
		}
		template<std::size_t ColumnIndex_, std::size_t RowIndex_>
		constexpr inline const raw_value_type& _get_index() const
		{
			if constexpr (is_column_major)
			{
				return data_.template at<ColumnIndex_>().template at<RowIndex_>();
			}
			else
			{
				return data_.template at<RowIndex_>().template at<ColumnIndex_>();
			}
		}

		constexpr inline raw_value_type& _get_index(const std::size_t columnIndex_, std::size_t rowIndex_)
		{
			if constexpr (is_column_major)
			{
				return data_.at(columnIndex_).at(rowIndex_);
			}
			else
			{
				return data_.at(rowIndex_).at(columnIndex_);
			}
		}
		constexpr inline const raw_value_type& _get_index(const std::size_t columnIndex_, std::size_t rowIndex_) const
		{
			if constexpr (is_column_major)
			{
				return data_.at(columnIndex_).at(rowIndex_);
			}
			else
			{
				return data_.at(rowIndex_).at(columnIndex_);
			}
		}

		template<std::size_t NonMajorIndex_, std::size_t MajorIndex_, typename Out_>
		constexpr inline void _assign_non_major_reference(Out_& out_)
		{
			if constexpr (MajorIndex_ < num_major_elements)
			{
				out_.template Set<MajorIndex_>(data_.template at<MajorIndex_>().template at<NonMajorIndex_>());
				_assign_non_major_reference<NonMajorIndex_, MajorIndex_ + 1, Out_>(out_);
			}
		}
		template<std::size_t NonMajorIndex_, std::size_t MajorIndex_, typename Out_>
		constexpr inline void _assign_non_major_reference(Out_& out_) const
		{
			if constexpr (MajorIndex_ < num_major_elements)
			{
				out_.template Set<MajorIndex_>(data_.template at<MajorIndex_>().template at<NonMajorIndex_>());
				_assign_non_major_reference<NonMajorIndex_, MajorIndex_ + 1, Out_>(out_);
			}
		}
#pragma endregion
	};
}

template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_, std::size_t Index_ = 0>
inline std::ostream& operator<<(std::ostream& str_, const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
{
	if constexpr (Index_ < EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::num_rows)
	{
		str_ << matrix_.GetRowConst<Index_>();
		if constexpr ((Index_ + 1) < EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::num_rows)
		{
			str_ << "\n";
			return operator<<<NumColumns_, NumRows_, T_, ColumnMajor_, Index_ + 1>(str_, matrix_);
		}
		else
		{
			return str_;
		}
	}
	else
	{
		return str_;
	}
}

template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_, std::size_t Index_ = 0>
inline std::wostream& operator<<(std::wostream& str_, const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
{
	if constexpr (Index_ < EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::num_rows)
	{
		str_ << matrix_.GetRowConst<Index_>();
		if constexpr ((Index_ + 1) < EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::num_rows)
		{
			str_ << L"\n";
			return operator<<<NumColumns_, NumRows_, T_, ColumnMajor_, Index_ + 1>(str_, matrix_);
		}
		else
		{
			return str_;
		}
	}
	else
	{
		return str_;
	}
}

#endif
