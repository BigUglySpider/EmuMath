#ifndef EMU_MATH_MATRIX_TMP_H_INC_
#define EMU_MATH_MATRIX_TMP_H_INC_ 1

#include "../../../../EmuCore/TMPHelpers/TypeConvertors.h"
#include <type_traits>

namespace EmuMath
{
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_ = true>
	struct Matrix;
}

namespace EmuMath::TMP
{
	/// <summary>
	/// <para> Type to determine if the passed T_ is a type of EmuMath Matrix. </para>
	/// <para> The value will be true if T_ is a reference to an EmuMath Matrix, and ignores const/ref qualifiers. </para>
	/// </summary>
	template<typename T_>
	struct is_emu_matrix
	{
		static constexpr bool value = std::conditional_t
		<
			std::is_same_v<T_, EmuCore::TMP::remove_ref_cv_t<T_>>,
			std::false_type,
			is_emu_matrix<EmuCore::TMP::remove_ref_cv_t<T_>>
		>::value;
	};
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	struct is_emu_matrix<EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>
	{
		static constexpr bool value = true;
	};
	template<typename T_>
	static constexpr bool is_emu_matrix_v = is_emu_matrix<T_>::value;

	/// <summary>
	/// <para> Type to determine the transposed type of an EmuMath Matrix. </para>
	/// <para> If Matrix_ is not an EmuMath Matrix: type will be void. </para>
	/// <para> If OutT_ is void, the T_ argument for type will be the value_type_uq of the input Matrix_. </para>
	/// <para> The column-major memory order of type is determined by OutColumnMajor_. </para>
	/// <para>
	///		Where successful, type will be an EmuMath Matrix with a number of columns equal to Matrix_::num_rows, 
	///		and a number of rows equal to Matrix_::num_columns.
	/// </para>
	/// </summary>
	template<class Matrix_, typename OutT_, bool OutColumnMajor_>
	struct emu_matrix_transpose
	{
	private:
		template<typename In_, bool IsMatrix_ = EmuMath::TMP::is_emu_matrix_v<In_>>
		struct _transposer
		{
			using type = void;
		};
		template<typename In_>
		struct _transposer<In_, true>
		{
		private:
			using in_uq = EmuCore::TMP::remove_ref_cv_t<In_>;
			using out_t = std::conditional_t<std::is_void_v<OutT_>, typename in_uq::value_type_uq, OutT_>;

		public:
			using type = EmuMath::Matrix<in_uq::num_rows, in_uq::num_columns, OutT_, OutColumnMajor_>;
		};

	public:
		using type = typename _transposer<Matrix_>::type;
	};
	template<class Matrix_, typename OutT_, bool OutColumnMajor_>
	using emu_matrix_transpose_t = typename emu_matrix_transpose<Matrix_, OutT_, OutColumnMajor_>::type;

	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class Matrix_>
	struct is_theoretical_matrix_index
	{
	private:
		template<class In_, bool IsMatrix_ = EmuMath::TMP::is_emu_matrix_v<In_>>
		struct _value_finder_template
		{
			static constexpr bool valid_column_index = false;
			static constexpr bool valid_row_index = false;
			static constexpr bool is_theoretical_index = false;
		};

		template<class In_>
		struct _value_finder_template<In_, true>
		{
		private:
			using _in_uq = EmuCore::TMP::remove_ref_cv_t<In_>;

		public:
			static constexpr bool valid_column_index = ColumnIndex_ < _in_uq::num_columns;
			static constexpr bool valid_row_index = RowIndex_ < _in_uq::num_rows;
			static constexpr bool is_theoretical_index = !(valid_column_index && valid_row_index);
		};

		using _value_finder = _value_finder_template<Matrix_>;

	public:
		static constexpr bool valid_column_index = _value_finder::valid_column_index;
		static constexpr bool valid_row_index = _value_finder::valid_row_index;
		static constexpr bool value = _value_finder::is_theoretical_index;
	};

	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class Matrix_>
	struct matrix_theoretical_get_result
	{
	private:
		template<class In_, bool IsMatrix_ = EmuMath::TMP::is_emu_matrix_v<In_>>
		struct _type_finder_template
		{
			static constexpr bool valid_column_index = false;
			static constexpr bool valid_row_index = false;
			static constexpr bool is_theoretical_index = false;
			using type = void;
		};

		template<class In_>
		struct _type_finder_template<In_, true>
		{
		private:
			using _in_uq = EmuCore::TMP::remove_ref_cv_t<In_>;
			using _is_theoretical = EmuMath::TMP::is_theoretical_matrix_index<ColumnIndex_, RowIndex_, _in_uq>;

		public:
			static constexpr bool valid_column_index = _is_theoretical::valid_column_index;
			static constexpr bool valid_row_index = _is_theoretical::valid_row_index;
			static constexpr bool is_theoretical_index = _is_theoretical::value;
			using type = typename std::conditional
			<
				is_theoretical_index,
				typename _in_uq::value_type_uq,
				typename EmuCore::TMP::conditional_const<std::is_const_v<std::remove_reference_t<In_>>, typename _in_uq::value_type&>::type
			>::type;
		};

		using _type_finder = _type_finder_template<Matrix_>;

	public:
		static constexpr bool valid_column_index = _type_finder::valid_column_index;
		static constexpr bool valid_row_index = _type_finder::valid_row_index;
		static constexpr bool is_theoretical_index = _type_finder::is_theoretical_index;

		using type = typename _type_finder::type;
	};

	template<std::size_t FlattenedIndex_, class Matrix_>
	struct is_theoretical_flattened_matrix_index
	{
	private:
		template<class In_, bool IsMatrix_ = EmuMath::TMP::is_emu_matrix_v<Matrix_>>
		struct _value_finder
		{
			static constexpr bool value = false;
		};

		template<class In_>
		struct _value_finder<In_, true>
		{
			static constexpr bool value = FlattenedIndex_ > EmuCore::TMP::remove_ref_cv_t<In_>::size;
		};

	public:
		static constexpr bool value = _value_finder<Matrix_>::value;
	};

	template<std::size_t FlattenedIndex_, class Matrix_>
	struct matrix_flattened_theoretical_get_result
	{
	private:
		template<class In_, bool = EmuMath::TMP::is_emu_matrix_v<In_>>
		struct _type_finder_template
		{
			static constexpr bool is_theoretical_index = false;
			using type = void;
		};

		template<class In_>
		struct _type_finder_template<In_, true>
		{
		private:
			using _in_uq = EmuCore::TMP::remove_ref_cv_t<In_>;

		public:
			static constexpr bool is_theoretical_index = is_theoretical_flattened_matrix_index<FlattenedIndex_, In_>::value;
			using type = typename std::conditional
			<
				is_theoretical_index,
				typename _in_uq::value_type_uq,
				typename EmuCore::TMP::conditional_const<std::is_const_v<std::remove_reference_t<In_>>, typename _in_uq::value_type&>::type
			>::type;
		};

		using _type_finder = _type_finder_template<Matrix_>;

	public:
		static constexpr bool is_theoretical_index = _type_finder::is_theoretical_index;
		using type = typename _type_finder::type;
	};
}

#endif
