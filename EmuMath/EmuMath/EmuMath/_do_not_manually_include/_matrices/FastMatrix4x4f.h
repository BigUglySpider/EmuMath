#ifndef EMU_MATH_FAST_MATRIX_4X4_H_INC_
#define EMU_MATH_FAST_MATRIX_4X4_H_INC_ 1

#include "../../Matrix.h"
#include "../../SIMDHelpers.h"
#include "../../FastVector.h"

namespace EmuMath
{
	/// <summary> 4x4 matrix of floating points which makes use of SIMD intrinsics. Uses column-major storage. </summary>
	struct FastMatrix4x4f_CM
	{
	public:
#pragma region CONSTRUCTORS
		/// <summary> Creates a 4x4 column-major matrix with default-constructed registers. </summary>
		FastMatrix4x4f_CM() : column0(), column1(), column2(), column3()
		{
		}
		/// <summary> Creates a 4x4 column-major matrix which has columns matching the respective input registers. </summary>
		/// <param name="column_0_">Register to copy to this matrix's 0th column.</param>
		/// <param name="column_1_">Register to copy to this matrix's 1st column.</param>
		/// <param name="column_2_">Register to copy to this matrix's 2nd column.</param>
		/// <param name="column_3_">Register to copy to this matrix's 3rd column.</param>
		FastMatrix4x4f_CM(__m128 column_0_, __m128 column_1_, __m128 column_2_, __m128 column_3_) :
			column0(column_0_),
			column1(column_1_),
			column2(column_2_),
			column3(column_3_)
		{
		}
		/// <summary> Creates a 4x4 column-major matrix which copies the respective columns of the passed matrix. </summary>
		/// <param name="to_copy_">Matrix to copy the columns of.</param>
		FastMatrix4x4f_CM(const FastMatrix4x4f_CM& to_copy_) :
			column0(to_copy_.column0),
			column1(to_copy_.column1),
			column2(to_copy_.column2),
			column3(to_copy_.column3)
		{
		}
		/// <summary>
		/// <para> Creates a 4x4 column-major matrix which loads the passed pointed-to floats directly into their respective column registers. </para>
		/// <para> Behaviour is undefined if any of the passed pointers are not contiguous for at least 4 floats. </para>
		/// </summary>
		/// <param name="p_column_0_contiguous_4_floats_">Pointer to 4 contiguous floats to load into this matrix's 0th column.</param>
		/// <param name="p_column_1_contiguous_4_floats_">Pointer to 4 contiguous floats to load into this matrix's 1st column.</param>
		/// <param name="p_column_2_contiguous_4_floats_">Pointer to 4 contiguous floats to load into this matrix's 2nd column.</param>
		/// <param name="p_column_3_contiguous_4_floats_">Pointer to 4 contiguous floats to load into this matrix's 3rd column.</param>
		FastMatrix4x4f_CM
		(
			const float* p_column_0_contiguous_4_floats_,
			const float* p_column_1_contiguous_4_floats_,
			const float* p_column_2_contiguous_4_floats_,
			const float* p_column_3_contiguous_4_floats_
		) :
			column0(_mm_load_ps(p_column_0_contiguous_4_floats_)),
			column1(_mm_load_ps(p_column_1_contiguous_4_floats_)),
			column2(_mm_load_ps(p_column_2_contiguous_4_floats_)),
			column3(_mm_load_ps(p_column_3_contiguous_4_floats_))
		{
		}
		/// <summary>
		/// <para>
		///		Creates a 4x4 column-major matrix which loads the pointed-to floats directly into its registers contiguously,
		///		where 4 sequential floats represent one column.
		/// </para>
		/// <para> Behaviour is undefined if the passed pointer is not contiguous for at least 16 floats. </para>
		/// </summary>
		/// <param name="p_16_contiguous_floats">Pointer to 16 contiguous floats to load into this matrix's data, starting from the 0th column.</param>
		explicit FastMatrix4x4f_CM(const float* p_16_contiguous_floats) :
			column0(_mm_load_ps(p_16_contiguous_floats)),
			column1(_mm_load_ps(p_16_contiguous_floats + 4)),
			column2(_mm_load_ps(p_16_contiguous_floats + 8)),
			column3(_mm_load_ps(p_16_contiguous_floats + 12))
		{
		}
		/// <summary> Creates a 4x4 column-major matrix from the theoretical data of the passed EmuMath matrix. </summary>
		/// <typeparam name="in_contained_type">Type contained within the provided matrix. Must be convertible to a float.</typeparam>
		/// <param name="to_copy_">EmuMath matrix to copy into this matrix's column registers.</param>
		template
		<
			typename std::size_t InColumns_,
			std::size_t InRows_,
			typename in_contained_type,
			bool InColumnMajor_,
			typename RequiresInContainedTypeCastableToFloat = std::enable_if_t<std::is_convertible_v<in_contained_type, float>>
		>
		explicit FastMatrix4x4f_CM(const EmuMath::Matrix<InColumns_, InRows_, in_contained_type, InColumnMajor_>& to_copy_) :
			column0
			(
				_mm_set_ps
				(
					EmuMath::Helpers::MatrixGetTheoretical<0, 3>(to_copy_),
					EmuMath::Helpers::MatrixGetTheoretical<0, 2>(to_copy_),
					EmuMath::Helpers::MatrixGetTheoretical<0, 1>(to_copy_),
					EmuMath::Helpers::MatrixGetTheoretical<0, 0>(to_copy_)
				)
			),
			column1
			(
				_mm_set_ps
				(
					EmuMath::Helpers::MatrixGetTheoretical<1, 3>(to_copy_),
					EmuMath::Helpers::MatrixGetTheoretical<1, 2>(to_copy_),
					EmuMath::Helpers::MatrixGetTheoretical<1, 1>(to_copy_),
					EmuMath::Helpers::MatrixGetTheoretical<1, 0>(to_copy_)
				)
			),
			column2
			(
				_mm_set_ps
				(
					EmuMath::Helpers::MatrixGetTheoretical<2, 3>(to_copy_),
					EmuMath::Helpers::MatrixGetTheoretical<2, 2>(to_copy_),
					EmuMath::Helpers::MatrixGetTheoretical<2, 1>(to_copy_),
					EmuMath::Helpers::MatrixGetTheoretical<2, 0>(to_copy_)
				)
			),
			column3
			(
				_mm_set_ps
				(
					EmuMath::Helpers::MatrixGetTheoretical<3, 3>(to_copy_),
					EmuMath::Helpers::MatrixGetTheoretical<3, 2>(to_copy_),
					EmuMath::Helpers::MatrixGetTheoretical<3, 1>(to_copy_),
					EmuMath::Helpers::MatrixGetTheoretical<3, 0>(to_copy_)
				)
			)
		{
		}
		/// <summary> Creates a 4x4 column-major matrix from the data of the passed 4x4 column-major EmuMath matrix, loading its data directly into column registers. </summary>
		/// <param name="to_load_">4x4 column-major EmuMath matrix containing floats to load the data of.</param>
		template<>
		explicit FastMatrix4x4f_CM(const EmuMath::Matrix<4, 4, float, true>& to_load_) :
			column0(_mm_load_ps(to_load_.at<0>().data())),
			column1(_mm_load_ps(to_load_.at<1>().data())),
			column2(_mm_load_ps(to_load_.at<2>().data())),
			column3(_mm_load_ps(to_load_.at<3>().data()))
		{
		}
		/// <summary> Creates a 4x4 column-major matrix using EmuMath vectors to create each respective column's data. </summary>
		/// <typeparam name="contained_type_0">Type contained in the vector used to create column 0.</typeparam>
		/// <typeparam name="contained_type_1">Type contained in the vector used to create column 1.</typeparam>
		/// <typeparam name="contained_type_2">Type contained in the vector used to create column 2.</typeparam>
		/// <typeparam name="contained_type_3">Type contained in the vector used to create column 3.</typeparam>
		/// <param name="column_0_">EmuMath vector used to create this matrix's 0th column.</param>
		/// <param name="column_1_">EmuMath vector used to create this matrix's 1st column.</param>
		/// <param name="column_2_">EmuMath vector used to create this matrix's 2nd column.</param>
		/// <param name="column_3_">EmuMath vector used to create this matrix's 3rd column.</param>
		template
		<
			std::size_t Size0_, typename contained_type_0,
			std::size_t Size1_, typename contained_type_1,
			std::size_t Size2_, typename contained_type_2,
			std::size_t Size3_, typename contained_type_3
		>
		FastMatrix4x4f_CM
		(
			const EmuMath::Vector<Size0_, contained_type_0>& column_0_,
			const EmuMath::Vector<Size1_, contained_type_1>& column_1_,
			const EmuMath::Vector<Size2_, contained_type_2>& column_2_,
			const EmuMath::Vector<Size3_, contained_type_3>& column_3_
		) : 
			column0(EmuMath::SIMD::m128_from_emu_math_vector(column_0_)),
			column1(EmuMath::SIMD::m128_from_emu_math_vector(column_1_)),
			column2(EmuMath::SIMD::m128_from_emu_math_vector(column_2_)),
			column3(EmuMath::SIMD::m128_from_emu_math_vector(column_3_))
		{
		}
		/// <summary> Creates a 4x4 column-major matrix using the registers of the passed vectors to create each respective column's data. </summary>
		/// <typeparam name="contained_type_0">Type contained in the vector used to create column 0.</typeparam>
		/// <typeparam name="contained_type_1">Type contained in the vector used to create column 1.</typeparam>
		/// <typeparam name="contained_type_2">Type contained in the vector used to create column 2.</typeparam>
		/// <typeparam name="contained_type_3">Type contained in the vector used to create column 3.</typeparam>
		/// <param name="column_0_">Vector used to create this matrix's 0th column.</param>
		/// <param name="column_1_">Vector used to create this matrix's 1st column.</param>
		/// <param name="column_2_">Vector used to create this matrix's 2nd column.</param>
		/// <param name="column_3_">Vector used to create this matrix's 3rd column.</param>
		FastMatrix4x4f_CM
		(
			const EmuMath::FastVector4f& column_0_,
			const EmuMath::FastVector4f& column_1_,
			const EmuMath::FastVector4f& column_2_,
			const EmuMath::FastVector4f& column_3_
		) :
			column0(column_0_.data_),
			column1(column_1_.data_),
			column2(column_2_.data_),
			column3(column_3_.data_)
		{
		}
		/// <summary>
		///		Creates a 4x4 column-major matrix using the passed data as contiguous initialisation values for its columns.
		///		Arguments are taken in column-major order.
		/// </summary>
		/// <typeparam name="C0R0_">Type used to provide this matrix's 0th column's 0th element.</typeparam>
		/// <typeparam name="C0R1_">Type used to provide this matrix's 0th column's 1st element.</typeparam>
		/// <typeparam name="C0R2_">Type used to provide this matrix's 0th column's 2nd element.</typeparam>
		/// <typeparam name="C0R3_">Type used to provide this matrix's 0th column's 3rd element.</typeparam>
		/// <typeparam name="C1R0_">Type used to provide this matrix's 1st column's 0th element.</typeparam>
		/// <typeparam name="C1R1_">Type used to provide this matrix's 1st column's 1st element.</typeparam>
		/// <typeparam name="C1R2_">Type used to provide this matrix's 1st column's 2nd element.</typeparam>
		/// <typeparam name="C1R3_">Type used to provide this matrix's 1st column's 3rd element.</typeparam>
		/// <typeparam name="C2R0_">Type used to provide this matrix's 2nd column's 0th element.</typeparam>
		/// <typeparam name="C2R1_">Type used to provide this matrix's 2nd column's 1st element.</typeparam>
		/// <typeparam name="C2R2_">Type used to provide this matrix's 2nd column's 2nd element.</typeparam>
		/// <typeparam name="C2R3_">Type used to provide this matrix's 2nd column's 3rd element.</typeparam>
		/// <typeparam name="C3R0_">Type used to provide this matrix's 3rd column's 0th element.</typeparam>
		/// <typeparam name="C3R1_">Type used to provide this matrix's 3rd column's 1st element.</typeparam>
		/// <typeparam name="C3R2_">Type used to provide this matrix's 3rd column's 2nd element.</typeparam>
		/// <typeparam name="C3R3_">Type used to provide this matrix's 3rd column's 3rd element.</typeparam>
		/// <param name="c0r0_">Value used to initialise this matrix's 0th column's 0th element.</param>
		/// <param name="c0r1_">Value used to initialise this matrix's 0th column's 1st element.</param>
		/// <param name="c0r2_">Value used to initialise this matrix's 0th column's 2nd element.</param>
		/// <param name="c0r3_">Value used to initialise this matrix's 0th column's 3rd element.</param>
		/// <param name="c1r0_">Value used to initialise this matrix's 1st column's 0th element.</param>
		/// <param name="c1r1_">Value used to initialise this matrix's 1st column's 1st element.</param>
		/// <param name="c1r2_">Value used to initialise this matrix's 1st column's 2nd element.</param>
		/// <param name="c1r3_">Value used to initialise this matrix's 1st column's 3rd element.</param>
		/// <param name="c2r0_">Value used to initialise this matrix's 2nd column's 0th element.</param>
		/// <param name="c2r1_">Value used to initialise this matrix's 2nd column's 1st element.</param>
		/// <param name="c2r2_">Value used to initialise this matrix's 2nd column's 2nd element.</param>
		/// <param name="c2r3_">Value used to initialise this matrix's 2nd column's 3rd element.</param>
		/// <param name="c3r0_">Value used to initialise this matrix's 3rd column's 0th element.</param>
		/// <param name="c3r1_">Value used to initialise this matrix's 3rd column's 1st element.</param>
		/// <param name="c3r2_">Value used to initialise this matrix's 3rd column's 2nd element.</param>
		/// <param name="c3r3_">Value used to initialise this matrix's 3rd column's 3rd element.</param>
		template
		<
			typename C0R0_, typename C0R1_, typename C0R2_, typename C0R3_,
			typename C1R0_, typename C1R1_, typename C1R2_, typename C1R3_,
			typename C2R0_, typename C2R1_, typename C2R2_, typename C2R3_,
			typename C3R0_, typename C3R1_, typename C3R2_, typename C3R3_
		>
		FastMatrix4x4f_CM
		(
			const C0R0_& c0r0_, const C0R1_& c0r1_, const C0R2_& c0r2_, const C0R3_& c0r3_,
			const C1R0_& c1r0_, const C1R1_& c1r1_, const C1R2_& c1r2_, const C1R3_& c1r3_,
			const C2R0_& c2r0_, const C2R1_& c2r1_, const C2R2_& c2r2_, const C2R3_& c2r3_,
			const C3R0_& c3r0_, const C3R1_& c3r1_, const C3R2_& c3r2_, const C3R3_& c3r3_
		) :
			column0(_mm_set_ps(static_cast<float>(c0r3_), static_cast<float>(c0r2_), static_cast<float>(c0r1_), static_cast<float>(c0r0_))),
			column1(_mm_set_ps(static_cast<float>(c1r3_), static_cast<float>(c1r2_), static_cast<float>(c1r1_), static_cast<float>(c1r0_))),
			column2(_mm_set_ps(static_cast<float>(c2r3_), static_cast<float>(c2r2_), static_cast<float>(c2r1_), static_cast<float>(c2r0_))),
			column3(_mm_set_ps(static_cast<float>(c3r3_), static_cast<float>(c3r2_), static_cast<float>(c3r1_), static_cast<float>(c3r0_)))
		{
		}
#pragma endregion

#pragma region EXTRACTION
		/// <summary> Returns a copy of the value at the provided column and row index. </summary>
		/// <returns>Copy of the element at the provided column and row index.</returns>
		template<std::size_t ColumnIndex_, std::size_t RowIndex_, typename Out_ = float>
		[[nodiscard]] Out_ at() const
		{
			if constexpr (_assert_valid_index<ColumnIndex_, RowIndex_>())
			{
				if constexpr (_assert_valid_cast_to<Out_>())
				{
					return static_cast<Out_>(EmuMath::SIMD::get_m128_index<RowIndex_>(GetColumn<ColumnIndex_>()));
				}
				else
				{
					static_assert(false, "Invalid Out_ type provided to EmuMath::FastMatrix4x4f_CM::at.");
				}
			}
			else
			{
				static_assert(false, "Invalid indices provided to EmuMath::FastMatrix4x4f_CM::at<ColumnIndex_, RowIndex_>.");
			}
		}
		/// <summary> Returns a copy of the major register at the provided major index. </summary>
		/// <returns>Register copy of the major register at the provided major index.</returns>
		template<std::size_t MajorIndex_>
		[[nodiscard]] __m128 at() const
		{
			if constexpr (_assert_valid_major_index<MajorIndex_>())
			{
				return GetColumn<MajorIndex_>();
			}
			else
			{
				static_assert(false, "Invalid Major Index provided to EmuMath::FastMatrix4x4f_CM::at<MajorIndex_>.");
			}
		}

		/// <summary>
		///	<para> Stores this matrix as an easily-readable 4x4 EmuMath matrix, with customisable contained types and major-order (defaults to the same as this matrix). </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained in the output EmuMath matrix.</typeparam>
		/// <returns>4x4 EmuMath matrix that may be easily read</returns>
		template<typename out_contained_type = float, bool OutColumnMajor_ = true>
		[[nodiscard]] EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> Store() const
		{
			if constexpr (std::is_same_v<out_contained_type, float> && OutColumnMajor_)
			{
				// Load data straight into output matrix since we can easily do so knowing major-order and type match.
				EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> out_;
				_mm_store_ps(out_.at<0>().data(), column0);
				_mm_store_ps(out_.at<1>().data(), column1);
				_mm_store_ps(out_.at<2>().data(), column2);
				_mm_store_ps(out_.at<3>().data(), column3);
				return out_;
			}
			else
			{
				if constexpr (_assert_valid_cast_to<out_contained_type>())
				{
					EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> out_;
					if constexpr (OutColumnMajor_)
					{
						// Copy each individual column into the output matrix, deferring conversions of one vector to another to EmuMath::Vector using readable columns.
						out_.at<0>() = GetColumnReadable<0>();
						out_.at<1>() = GetColumnReadable<1>();
						out_.at<2>() = GetColumnReadable<2>();
						out_.at<3>() = GetColumnReadable<3>();
					}
					else
					{
						// Same as above, but uses this matrix's transpose as we need to be feeding rows into major elements to produce the same matrix.
						// --- Using transpose columns instead of GetRowReadable allows us to avoid some unneeded shuffles
						FastMatrix4x4f_CM transpose_ = Transpose();
						out_.at<0>() = transpose_.GetColumnReadable<0>();
						out_.at<1>() = transpose_.GetColumnReadable<1>();
						out_.at<2>() = transpose_.GetColumnReadable<2>();
						out_.at<3>() = transpose_.GetColumnReadable<3>();
					}
					return out_;
				}
				else
				{
					static_assert(false, "Invalid out_contained_type provided to EmuMath::FastMatrix4x4f_CM::Store.");
				}
			}
		}

		/// <summary> Provides a 128-bit register copy of the column at the specified index. </summary>
		/// <returns>128-bit float register copy of the requested column within this matrix.</returns>
		template<std::size_t Column_>
		[[nodiscard]] __m128 GetColumn() const
		{
			if constexpr (Column_ == 0)
			{
				return column0;
			}
			else if constexpr (Column_ == 1)
			{
				return column1;
			}
			else if constexpr (Column_ == 2)
			{
				return column2;
			}
			else if constexpr (Column_ == 3)
			{
				return column3;
			}
			else
			{
				static_assert(false, "Attempted to get a column with an invalid index from an EmuMath::FastMatrix4x4f_CM.");
			}
		}
		/// <summary> Provides an easily-readable EmuMath vector representing the column at the provided index. </summary>
		/// <returns>EmuMath vector representing the requested column within this matrix.</returns>
		template<std::size_t Column_>
		[[nodiscard]] EmuMath::Vector<4, float> GetColumnReadable() const
		{
			EmuMath::Vector4<float> out_;
			_mm_store_ps(out_.data(), GetColumn<Column_>());
			return out_;
		}

		/// <summary> Provides a 128-bit register copy of the row at the specified index. As this matrix is column-major, this will require several shuffles. </summary>
		/// <returns>128-bit float register copy of the requested row within this matrix.</returns>
		template<std::size_t Row_>
		[[nodiscard]] __m128 GetRow() const
		{
			if constexpr (Row_ <= 3)
			{
				__m128 out_0_1 = EmuMath::SIMD::shuffle<Row_, 0, Row_, 0>(column0, column1);
				__m128 out_2_3 = EmuMath::SIMD::shuffle<Row_, 0, Row_, 0>(column2, column3);
				return EmuMath::SIMD::shuffle<0, 2, 0, 2>(out_0_1, out_2_3);
			}
			else
			{
				static_assert(false, "Attempted to get a column with an invalid index from an EmuMath::FastMatrix4x4f_CM.");
			}
		}
		/// <summary>
		///		Provides an easily-readable EmuMath vector representing the row at the provided index. 
		///		As this matrix is column-major, this will require several shuffles.
		/// </summary>
		/// <returns>EmuMath vector representing the requested row within this matrix.</returns>
		template<std::size_t Row_>
		[[nodiscard]] EmuMath::Vector<4, float> GetRowReadable() const
		{
			EmuMath::Vector4<float> out_;
			_mm_store_ps(out_.data(), GetRow<Row_>());
			return out_;
		}
#pragma endregion

#pragma region ARITHMETIC_FUNCS
		/// <summary>
		/// <para> Performs an addition operation between this matrix's columns and the provided column registers. </para>
		/// <para> The provided column registers are treated as the respective columns of a matrix. </para>
		/// </summary>
		/// <param name="rhs_column_0_">Column 0 of a matrix to add to this matrix.</param>
		/// <param name="rhs_column_1_">Column 1 of a matrix to add to this matrix.</param>
		/// <param name="rhs_column_2_">Column 2 of a matrix to add to this matrix.</param>
		/// <param name="rhs_column_3_">Column 3 of a matrix to add to this matrix.</param>
		/// <returns>Matrix containing the results of addition.</returns>
		inline FastMatrix4x4f_CM Add(__m128 rhs_column_0_, __m128 rhs_column_1_, __m128 rhs_column_2_, __m128 rhs_column_3_) const
		{
			return FastMatrix4x4f_CM
			(
				_mm_add_ps(column0, rhs_column_0_),
				_mm_add_ps(column1, rhs_column_1_),
				_mm_add_ps(column2, rhs_column_2_),
				_mm_add_ps(column3, rhs_column_3_)
			);
		}
		/// <summary> Adds the passed matrix to this matrix. </summary>
		/// <param name="rhs_">Matrix to add to this matrix.</param>
		/// <returns>Matrix containing the results of addition.</returns>
		inline FastMatrix4x4f_CM Add(const FastMatrix4x4f_CM& rhs_) const
		{
			return Add(rhs_.column0, rhs_.column1, rhs_.column2, rhs_.column3);
		}

		/// <summary>
		/// <para> Performs a subtraction operation between this matrix's columns and the provided column registers. </para>
		/// <para> The provided column registers are treated as the respective columns of a matrix. </para>
		/// </summary>
		/// <param name="rhs_column_0_">Column 0 of a matrix to subtract from this matrix.</param>
		/// <param name="rhs_column_1_">Column 1 of a matrix to subtract from this matrix.</param>
		/// <param name="rhs_column_2_">Column 2 of a matrix to subtract from this matrix.</param>
		/// <param name="rhs_column_3_">Column 3 of a matrix to subtract from this matrix.</param>
		/// <returns>Matrix containing the results of subtraction.</returns>
		inline FastMatrix4x4f_CM Subtract(__m128 rhs_column_0_, __m128 rhs_column_1_, __m128 rhs_column_2_, __m128 rhs_column_3_) const
		{
			return FastMatrix4x4f_CM
			(
				_mm_sub_ps(column0, rhs_column_0_),
				_mm_sub_ps(column1, rhs_column_1_),
				_mm_sub_ps(column2, rhs_column_2_),
				_mm_sub_ps(column3, rhs_column_3_)
			);
		}
		/// <summary> Subtracts the passed matrix from this matrix. </summary>
		/// <param name="rhs_">Matrix to subtract from this matrix.</param>
		/// <returns>Matrix containing the results of subtraction.</returns>
		inline FastMatrix4x4f_CM Subtract(const FastMatrix4x4f_CM& rhs_) const
		{
			return Subtract(rhs_.column0, rhs_.column1, rhs_.column2, rhs_.column3);
		}

		/// <summary>
		/// <para> Performs a basic multiplication where respective columns in this matrix are multiplied by the passed column registers. </para>
		/// <para> This is not a standard matrix multiplication. For such behaviour, use Multiply instead. </para>
		/// </summary>
		/// <param name="rhs_column_0_">Register to multiply this matrix's column0 by.</param>
		/// <param name="rhs_column_1_">Register to multiply this matrix's column1 by.</param>
		/// <param name="rhs_column_2_">Register to multiply this matrix's column2 by.</param>
		/// <param name="rhs_column_3_">Register to multiply this matrix's column3 by.</param>
		/// <returns>Resulting matrix after this matrix's columns are multiplied by the respective passed column registers.</returns>
		inline FastMatrix4x4f_CM MultiplyBasic(__m128 rhs_column_0_, __m128 rhs_column_1_, __m128 rhs_column_2_, __m128 rhs_column_3_) const
		{
			return FastMatrix4x4f_CM
			(
				_mm_mul_ps(column0, rhs_column_0_),
				_mm_mul_ps(column1, rhs_column_1_),
				_mm_mul_ps(column2, rhs_column_2_),
				_mm_mul_ps(column3, rhs_column_3_)
			);
		}
		/// <summary> Multiplies all columns in this matrix by the passed register. Useful for providing a blanket multiplication to each element on certain rows. </summary>
		/// <param name="mult_for_all_columns_">Register to multiply every column of this matrix via.</param>
		/// <returns>Resulting matrix after this matrix's columns are all multiplied by the passed register.</returns>
		inline FastMatrix4x4f_CM MultiplyBasic(__m128 mult_for_all_columns_) const
		{
			return FastMatrix4x4f_CM
			(
				_mm_mul_ps(column0, mult_for_all_columns_),
				_mm_mul_ps(column1, mult_for_all_columns_),
				_mm_mul_ps(column2, mult_for_all_columns_),
				_mm_mul_ps(column3, mult_for_all_columns_)
			);
		}
		/// <summary>
		/// <para> Performs a basic multiplication where respective columns in this matrix are multiplied by those in the passed matrix. </para>
		/// <para> This is not a standard matrix multiplication. For such behaviour, use Multiply instead. </para>
		/// </summary>
		/// <param name="rhs_">Matrix to multiply respective columns of this matrix by.</param>
		/// <returns>Resulting matrix after this matrix's columns are multiplied by the respective columns of the passed matrix.</returns>
		inline FastMatrix4x4f_CM MultiplyBasic(const FastMatrix4x4f_CM& rhs_) const
		{
			return MultiplyBasic(rhs_.column0, rhs_.column1, rhs_.column2, rhs_.column3);
		}
		/// <summary> Multiplies all elements within this matrix by the provided val_. The provided val_ must be castable to a float. </summary>
		/// <typeparam name="T_">Type to multiply by.</typeparam>
		/// <param name="val_">Value to multiply all elements of this matrix by.</param>
		/// <returns>Resulting matrix after multiply all of this matrix's elements by the passed val_.</returns>
		template<typename T_, typename RequiresTConvertibleToFloat = std::enable_if_t<std::is_convertible_v<T_, float>>>
		inline FastMatrix4x4f_CM MultiplyBasic(const T_& val_) const
		{
			return MultiplyBasic(_mm_set_ps1(static_cast<float>(val_)));
		}

		/// <summary>
		/// <para> Performs a standard matrix multiplication with the provided registers, which are interpreted as respective columns within a 4x4 matrix. </para>
		/// <para> This is a standard matrix multiplication. To perform a basic multiplication of respective columns, use MultiplyBasic. </para>
		/// </summary>
		/// <param name="rhs_column_0_">Column 0 of the matrix to multiply this matrix by.</param>
		/// <param name="rhs_column_1_">Column 1 of the matrix to multiply this matrix by.</param>
		/// <param name="rhs_column_2_">Column 2 of the matrix to multiply this matrix by.</param>
		/// <param name="rhs_column_3_">Column 3 of the matrix to multiply this matrix by.</param>
		/// <returns>Matrix result from multiplying this matrix by a matrix comprised of respective passed columns.</returns>
		inline FastMatrix4x4f_CM Multiply(__m128 rhs_column_0_, __m128 rhs_column_1_, __m128 rhs_column_2_, __m128 rhs_column_3_) const
		{
			return FastMatrix4x4f_CM
			(
				_std_mult_calculate_column(rhs_column_0_),
				_std_mult_calculate_column(rhs_column_1_),
				_std_mult_calculate_column(rhs_column_2_),
				_std_mult_calculate_column(rhs_column_3_)
			);
		}

		/// <summary> Multiplies the passed rhs_vector_ register with this matrix, treating it as a single column matrix. </summary>
		/// <param name="rhs_vector_">Vector to multiply. Used as-is.</param>
		/// <returns>Resulting vector from multiplying the passed vector by this matrix, interpreted as defined above.</returns>
		inline EmuMath::FastVector4f MultiplyVector4(__m128 rhs_vector_) const
		{
			return FastVector4f(_std_mult_calculate_column(rhs_vector_));
		}
		inline EmuMath::FastVector4f MultiplyVector4(const EmuMath::FastVector4f& rhs_vector_) const
		{
			return MultiplyVector4(rhs_vector_.data_);
		}
		/// <summary>
		/// <para> Multiplies the passed rhs_vector_ register with this matrix, treating it as a single column matrix. </para>
		/// <para> The rhs_vector_ is assumed to have a w value of 1, as per homogeneous coordinates. </para>
		/// </summary>
		/// <param name="rhs_vector_">Vector to multiply. The x, y, and z values of this vector will be used, and w will be interpreted as 1.</param>
		/// <returns>Resulting vector from multiplying the passed vector by this matrix, interpreted as defined above.</returns>
		inline EmuMath::FastVector4f MultiplyVector3(__m128 rhs_vector_) const
		{
			__m128 out_ = _mm_mul_ps(column0, EmuMath::SIMD::shuffle<0, 0, 0, 0>(rhs_vector_));
			out_ = _mm_add_ps(out_, _mm_mul_ps(column1, EmuMath::SIMD::shuffle<1, 1, 1, 1>(rhs_vector_)));
			out_ = _mm_add_ps(out_, _mm_mul_ps(column2, EmuMath::SIMD::shuffle<2, 2, 2, 2>(rhs_vector_)));

			// Add column3 to end result as we interpret the missing value to be 1 as per homogeneous coordinates default to
			return FastVector4f(_mm_add_ps(out_, column3));
		}
		inline EmuMath::FastVector4f MultiplyVector3(const EmuMath::FastVector4f& rhs_vector_) const
		{
			return MultiplyVector3(rhs_vector_.data_);
		}
		/// <summary>
		/// <para> Multiplies the passed rhs_vector_ register with this matrix, treating it as a single column matrix. </para>
		/// <para> The rhs_vector_ is assumed to have a z value of 0, as 2D space can be considered to have an implicit Z-coordinate of 0. </para>
		/// <para> The rhs_vector_ is assumed to have a w value of 1, as per homogeneous coordinates. </para>
		/// </summary>
		/// <param name="rhs_vector_">Vector to multiply. The x and y values of this vector will be used, z will be interpreted as 0, and w will be interpreted as 1.</param>
		/// <returns>Resulting vector from multiplying the passed vector by this matrix, interpreted as defined above. The output z will always be 0.</returns>
		inline EmuMath::FastVector4f MultiplyVector2(__m128 rhs_vector_) const
		{
			// Add column3 as we interpret the missing w value to be 1 as per homogeneous coordinates default to, 
			// and z is interpreted to be 0 since 2D space is implicitly at Z 0, so the resulting Z should always be 0.
			__m128 out_ = _mm_mul_ps(column0, EmuMath::SIMD::shuffle<0, 0, 0, 0>(rhs_vector_));
			out_ = _mm_add_ps(out_, _mm_mul_ps(column1, EmuMath::SIMD::shuffle<1, 1, 1, 1>(rhs_vector_)));
			out_ = _mm_add_ps(out_, column3);

			// AND out the z coord to maintain implicit Z 0, and continue to add homogeneous 
			return FastVector4f(_mm_and_ps(EmuMath::SIMD::index_mask_m128<true, true, false, true>(), out_));
		}
		inline EmuMath::FastVector4f MultiplyVector2(const EmuMath::FastVector4f& rhs_vector_) const
		{
			return MultiplyVector2(rhs_vector_.data_);
		}

		/// <summary>
		/// <para> Performs a standard matrix multiplication with the provided rhs_ matrix. </para>
		/// <para> This is a standard matrix multiplication. To perform a basic multiplication of respective columns, use MultiplyBasic. </para>
		/// </summary>
		/// <param name="rhs_">Matrix to multiply this matrix by.</param>
		/// <returns>Matrix result from multiplying this matrix by a matrix comprised of respective passed columns.</returns>
		inline FastMatrix4x4f_CM Multiply(const FastMatrix4x4f_CM& rhs_) const
		{
			return Multiply(rhs_.column0, rhs_.column1, rhs_.column2, rhs_.column3);
		}
		/// <summary>
		/// <para> Multiplies all columns in this matrix by the passed register. Useful for providing a blanket multiplication to each element on certain rows. </para>
		/// <para> This is the same as calling MultiplyBasic with the same argument. </para>
		/// <para> If the register is to be interpreted as a vector, use MultiplyVector. </para>
		/// </summary>
		/// <param name="mult_for_all_columns_">Register to multiply every column of this matrix via.</param>
		/// <returns>Resulting matrix after this matrix's columns are all multiplied by the passed register.</returns>
		inline FastMatrix4x4f_CM Multiply(__m128 mult_for_all_columns_) const
		{
			return MultiplyBasic(mult_for_all_columns_);
		}
		/// <summary>
		/// <para> Multiplies all elements within this matrix by the provided val_. The provided val_ must be castable to a float. </para>
		/// <para> This is the same as calling MultiplyBasic with the same argument. </para>
		/// </summary>
		/// <typeparam name="T_">Type to multiply by.</typeparam>
		/// <param name="val_">Value to multiply all elements of this matrix by.</param>
		/// <returns>Resulting matrix after multiply all of this matrix's elements by the passed val_.</returns>
		template<typename T_, typename RequiresTConvertibleToFloat = std::enable_if_t<std::is_convertible_v<T_, float>>>
		inline FastMatrix4x4f_CM Multiply(const T_& val_) const
		{
			return MultiplyBasic<T_>(val_);
		}

		/// <summary> Negates this matrix, setting every element to its negative form (e.g. [0][0] = -[0][0]). </summary>
		/// <returns>Negated form of this matrix.</returns>
		inline FastMatrix4x4f_CM Negate() const
		{
			__m128 zero_ = _mm_setzero_ps();
			return FastMatrix4x4f_CM
			(
				_mm_sub_ps(zero_, column0),
				_mm_sub_ps(zero_, column1),
				_mm_sub_ps(zero_, column2),
				_mm_sub_ps(zero_, column3)
			);
		}
#pragma endregion

#pragma region CONST_OPERATORS
		inline bool operator==(const FastMatrix4x4f_CM& rhs_) const
		{
			return
			(
				EmuMath::SIMD::all_equal(column0, rhs_.column0) &&
				EmuMath::SIMD::all_equal(column1, rhs_.column1) &&
				EmuMath::SIMD::all_equal(column2, rhs_.column2) &&
				EmuMath::SIMD::all_equal(column3, rhs_.column3)
			);
		}

		inline bool operator!=(const FastMatrix4x4f_CM& rhs_) const
		{
			return
			(
				EmuMath::SIMD::any_not_equal(column0, rhs_.column0) ||
				EmuMath::SIMD::any_not_equal(column1, rhs_.column1) ||
				EmuMath::SIMD::any_not_equal(column2, rhs_.column2) ||
				EmuMath::SIMD::any_not_equal(column3, rhs_.column3)
			);
		}

		inline FastMatrix4x4f_CM operator+(const FastMatrix4x4f_CM& rhs_) const
		{
			return Add(rhs_);
		}

		inline FastMatrix4x4f_CM operator-(const FastMatrix4x4f_CM& rhs_) const
		{
			return Subtract(rhs_);
		}
		inline FastMatrix4x4f_CM operator-() const
		{
			return Negate();
		}

		template<typename T_, typename RequiresTConvertibleToFloat = std::enable_if_t<std::is_convertible_v<T_, float>>>
		inline FastMatrix4x4f_CM operator*(const T_& rhs_) const
		{
			return MultiplyBasic<T_>(rhs_);
		}
		inline FastMatrix4x4f_CM operator*(const FastMatrix4x4f_CM& rhs_) const
		{
			return Multiply(rhs_);
		}
#pragma endregion

#pragma region MATRIX_OPERATIONS
		inline FastMatrix4x4f_CM Transpose() const
		{
			return FastMatrix4x4f_CM(GetRow<0>(), GetRow<1>(), GetRow<2>(), GetRow<3>());
		}

		/// <summary> Provides a fast vector containing the trace of this matrix within its data. </summary>
		/// <returns>Trace of this matrix represented as a FastVector4f.</returns>
		inline EmuMath::FastVector4f Trace() const
		{
			__m128 out_01_ = EmuMath::SIMD::shuffle<0, 0, 1, 1>(column0, column1);
			__m128 out_23_ = EmuMath::SIMD::shuffle<2, 2, 3, 3>(column2, column3);

			return EmuMath::FastVector4f(EmuMath::SIMD::shuffle<0, 2, 0, 2>(out_01_, out_23_));
		}
#pragma endregion

#pragma region STATIC_CONSTANTS
		/// <summary> Creates a 4x4 column-major identity matrix, which is all 0 except for its main diagonal (top left to bottom right), which is all 1. </summary>
		/// <returns>4x4 column-major identity matrix.</returns>
		static inline FastMatrix4x4f_CM Identity()
		{
			return FastMatrix4x4f_CM
			(
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			);
		}
#pragma endregion

#pragma region STATIC_TRANSFORMATIONS
		/// <summary>
		///		Creates a 4x4 column-major matrix which may be used to perform a translation of x_ in the X-direction, y_ in the Y-direction, and z_ in the Z-direction.
		/// </summary>
		/// <typeparam name="X_">Type used for the passed translation in the X-direction.</typeparam>
		/// <typeparam name="Y_">Type used for the passed translation in the Y-direction.</typeparam>
		/// <typeparam name="Z_">Type used for the passed translation in the Z-direction.</typeparam>
		/// <param name="x_">Translation in the X-direction.</param>
		/// <param name="y_">Translation in the Y-direction.</param>
		/// <param name="z_">Translation in the Z-direction.</param>
		/// <returns>4x4 column-major SIMD matrix that may be used to translate by the specified amounts in respective dimensions.</returns>
		template<typename X_, typename Y_, typename Z_>
		[[nodiscard]] static inline FastMatrix4x4f_CM Translation(const X_& x_, const Y_& y_, const Z_& z_)
		{
			return FastMatrix4x4f_CM
			(
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				x_,   y_,   z_,   1.0f
			);
		}

		/// <summary>
		///		Creates a 4x4 column-major matrix which may be used to perform a scale of x_ in the X-dimension, y_ in the Y-dimension, and z_ in the Z-dimension.
		/// </summary>
		/// <typeparam name="X_">Type used for the passed scale in the X-dimension.</typeparam>
		/// <typeparam name="Y_">Type used for the passed scale in the Y-dimension.</typeparam>
		/// <typeparam name="Z_">Type used for the passed scale in the Z-dimension.</typeparam>
		/// <param name="x_">Scale in the X-dimension.</param>
		/// <param name="y_">Scale in the Y-dimension.</param>
		/// <param name="z_">Scale in the Z-dimension.</param>
		/// <returns>4x4 column-major SIMD matrix that may be used to scale by the specified amounts in respective dimensions.</returns>
		template<typename X_, typename Y_, typename Z_>
		[[nodiscard]] static inline FastMatrix4x4f_CM Scale(const X_& x_, const Y_& y_, const Z_& z_)
		{
			return FastMatrix4x4f_CM
			(
				x_,   0.0f, 0.0f, 0.0f,
				0.0f, y_,   0.0f, 0.0f,
				0.0f, 0.0f, z_,   0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			);
		}

		/// <summary>
		/// <para> Creates a 4x4 column-major matrix which may used to perform about the X-axis by an angle of rot_x_. </para>
		/// <para> If the template argument RotIsRads_ is true, rot_x_ will be interpreted as radians; otherwise, rot_x_ will be interpreted as degrees. </para>
		/// </summary>
		/// <typeparam name="RotX_">Type used to provide the angle to rotate.</typeparam>
		/// <param name="rot_x_">Angle to rotate in either radians or degrees, depending on the RotIsRads_ template argument.</param>
		/// <returns>
		///		4x4 column-major SIMD matrix that may be used to rotate about the X-axis by rot_x_ radians or degrees, depending on the RotIsRads_ template argument.
		/// </returns>
		template<bool RotIsRads_ = true, typename RotX_>
		[[nodiscard]] static inline FastMatrix4x4f_CM RotationX(const RotX_& rot_x_)
		{
			if constexpr(RotIsRads_)
			{
				float cos_x_ = static_cast<float>(EmuCore::do_cos<RotX_>()(rot_x_));
				float sin_x_ = static_cast<float>(EmuCore::do_sin<RotX_>()(rot_x_));
				return FastMatrix4x4f_CM
				(
					1.0f, 0.0f,   0.0f,    0.0f,
					0.0f, cos_x_, -sin_x_, 0.0f,
					0.0f, sin_x_, cos_x_,  0.0f,
					0.0f, 0.0f,   0.0f,    1.0f
				);
			}
			else
			{
				using rot_x_fp = typename EmuCore::TMPHelpers::first_floating_point_t<RotX_, float>;
				return RotationX<true>(EmuCore::Pi::DegsToRads(static_cast<rot_x_fp>(rot_x_)));
			}
		}

		/// <summary>
		/// <para> Creates a 4x4 column-major matrix which may used to perform about the Y-axis by an angle of rot_y_. </para>
		/// <para> If the template argument RotIsRads_ is true, rot_y_ will be interpreted as radians; otherwise, rot_y_ will be interpreted as degrees. </para>
		/// </summary>
		/// <typeparam name="RotY_">Type used to provide the angle to rotate.</typeparam>
		/// <param name="rot_y_">Angle to rotate in either radians or degrees, depending on the RotIsRads_ template argument.</param>
		/// <returns>
		///		4x4 column-major SIMD matrix that may be used to rotate about the Y-axis by rot_y_ radians or degrees, depending on the RotIsRads_ template argument.
		/// </returns>
		template<bool RotIsRads_ = true, typename RotY_>
		[[nodiscard]] static inline FastMatrix4x4f_CM RotationY(const RotY_& rot_y_)
		{
			if constexpr(RotIsRads_)
			{
				float cos_y_ = static_cast<float>(EmuCore::do_cos<RotY_>()(rot_y_));
				float sin_y_ = static_cast<float>(EmuCore::do_sin<RotY_>()(rot_y_));
				return FastMatrix4x4f_CM
				(
					cos_y_,  0.0f, sin_y_, 0.0f,
					0.0f,    1.0f, 0.0f,   0.0f,
					-sin_y_, 0.0f, cos_y_, 0.0f,
					0.0f,    0.0f, 0.0f,   1.0f
				);
			}
			else
			{
				using rot_y_fp = typename EmuCore::TMPHelpers::first_floating_point_t<RotY_, float>;
				return RotationY<true>(EmuCore::Pi::DegsToRads(static_cast<rot_y_fp>(rot_y_)));
			}
		}

		/// <summary>
		/// <para> Creates a 4x4 column-major matrix which may used to perform about the Z-axis by an angle of rot_z_. </para>
		/// <para> If the template argument RotIsRads_ is true, rot_z_ will be interpreted as radians; otherwise, rot_z_ will be interpreted as degrees. </para>
		/// </summary>
		/// <typeparam name="RotZ_">Type used to provide the angle to rotate.</typeparam>
		/// <param name="rot_z_">Angle to rotate in either radians or degrees, depending on the RotIsRads_ template argument.</param>
		/// <returns>
		///		4x4 column-major SIMD matrix that may be used to rotate about the Z-axis by rot_z_ radians or degrees, depending on the RotIsRads_ template argument.
		/// </returns>
		template<bool RotIsRads_ = true, typename RotZ_>
		[[nodiscard]] static inline FastMatrix4x4f_CM RotationZ(const RotZ_& rot_z_)
		{
			if constexpr(RotIsRads_)
			{
				float cos_z_ = static_cast<float>(EmuCore::do_cos<RotZ_>()(rot_z_));
				float sin_z_ = static_cast<float>(EmuCore::do_sin<RotZ_>()(rot_z_));
				return FastMatrix4x4f_CM
				(
					cos_z_,  sin_z_, 0.0f, 0.0f,
					-sin_z_, cos_z_, 0.0f, 0.0f,
					0.0f,    0.0f,   1.0f, 0.0f,
					0.0f,    0.0f,   0.0f, 1.0f
				);
			}
			else
			{
				using rot_z_fp = typename EmuCore::TMPHelpers::first_floating_point_t<RotZ_, float>;
				return RotationZ<true>(EmuCore::Pi::DegsToRads(static_cast<rot_z_fp>(rot_z_)));
			}
		}
#pragma endregion

#pragma region STATIC_PROJECTIONS
		template<typename Near_, typename Far_, typename Left_, typename Right_, typename Bottom_, typename Top_>
		static inline FastMatrix4x4f_CM PerspectiveVK
		(
			const Near_& near_,
			const Far_& far_,
			const Left_& left_,
			const Right_& right_,
			const Bottom_& bottom_,
			const Top_& top_
		)
		{
			// Process isn't particularly too vectorisable without adding a good few undesirable shuffles
			// --- Additionally, this way is generally 15-25% faster than DirectXMath's equivalent in tests
			float right_plus_left_ = static_cast<float>(right_) + static_cast<float>(left_);
			float top_plus_bottom_ = static_cast<float>(top_) + static_cast<float>(bottom_);
			float right_minus_left_reciprocal_ = 1.0f / (static_cast<float>(right_) - static_cast<float>(left_));
			float top_minus_bottom_reciprocal_ = 1.0f / (static_cast<float>(top_) - static_cast<float>(bottom_));
			float near_double_ = static_cast<float>(near_); // Start as near_ copy so we can use the cast float
			float neg_far_minus_near_reciprocal_ = -(1.0f / (static_cast<float>(far_) - near_));
			float far_mult_near_ = static_cast<float>(far_) * near_;
			near_double_ *= 2.0f; // Apply deferred double

			float out_00_ = near_double_ * right_minus_left_reciprocal_; // (2 * near) / (right - left)
			float out_11_ = near_double_ * top_minus_bottom_reciprocal_; // (2 * near) / (top - bottom)
			float out_20_ = right_plus_left_ * right_minus_left_reciprocal_; // (right + left) / (right - left)
			float out_21_ = top_plus_bottom_ * top_minus_bottom_reciprocal_; // (top + bottom) / (top - bottom)
			float out_22_ = static_cast<float>(far_) * neg_far_minus_near_reciprocal_; // far / -(far - near)
			float out_32_ = far_mult_near_ * neg_far_minus_near_reciprocal_; // (far * near) / -(far - near)

			return FastMatrix4x4f_CM
			(
				out_00_, 0.0f,    0.0f,    0.0f,
				0.0f,    out_11_, 0.0f,    0.0f,
				out_20_, out_21_, out_22_, -1.0f,
				0.0f,    0.0f,    out_32_, 0.0f
			);
		}
		template<bool FovIsRads_ = true, typename FovY_, typename Near_, typename Far_, typename AspectRatio_>
		static inline FastMatrix4x4f_CM PerspectiveVK(const FovY_& fov_y_angle_, const Near_& near_, const Far_& far_, const AspectRatio_& aspect_ratio_)
		{
			using fov_y_fp = typename EmuCore::TMPHelpers::first_floating_point<FovY_, float>::type;
			if constexpr (!FovIsRads_)
			{
				return PerspectiveVK<true, fov_y_fp, Near_, Far_, AspectRatio_>
				(
					EmuCore::Pi::DegsToRads(static_cast<fov_y_fp>(fov_y_angle_)),
					near_,
					far_,
					aspect_ratio_
				);
			}
			else
			{
				float left_ = 0.0f, right_ = 0.0f, bottom_ = 0.0f, top_ = 0.0f;
				float scale_ = static_cast<float>(EmuCore::do_tan<fov_y_fp>()(static_cast<fov_y_fp>(fov_y_angle_) * fov_y_fp(0.5f)));
				scale_ *= static_cast<float>(near_);
				EmuMath::Helpers::_underlying_matrix_funcs::_calculate_matrix_perspective_edges_rads<AspectRatio_, float, float, float, float, float, float>
				(
					aspect_ratio_,
					scale_,
					left_,
					right_,
					bottom_,
					top_
				);
				return PerspectiveVK<Near_, Far_, float, float, float, float>(near_, far_, left_, right_, bottom_, top_);
			}
		}

		template<typename Left_, typename Right_, typename Bottom_, typename Top_, typename Near_, typename Far_>
		static inline FastMatrix4x4f_CM OrthographicVK
		(
			const Left_& left_,
			const Right_& right_,
			const Bottom_& bottom_,
			const Top_& top_,
			const Near_& near_,
			const Far_& far_
		)
		{
			// Faster to calculate via scalars since we aren't actually doing too many operations compared to the amount of stores and shuffles we'd need
			float right_minus_left = static_cast<float>(right_) - static_cast<float>(left_);
			float top_minus_bottom = static_cast<float>(top_) - static_cast<float>(bottom_);
			float neg_far_minus_near_reciprocal = -(1.0f / (static_cast<float>(far_) - static_cast<float>(near_)));
			float out_00_ = 2 / right_minus_left;
			float out_11_ = 2 / top_minus_bottom;
			float out_22_ = neg_far_minus_near_reciprocal;
			float out_32_ = near_ * neg_far_minus_near_reciprocal;
			return FastMatrix4x4f_CM
			(
				out_00_, 0.0f,    0.0f,    0.0f,
				0.0f,    out_11_, 0.0f,    0.0f,
				0.0f,    0.0f,    out_22_, 0.0f,
				0.0f,    0.0f,    out_32_, 1.0f
			);
		}
		template<typename Width_, typename Height_, typename Near_, typename Far_>
		static inline FastMatrix4x4f_CM OrthographicVK(const Width_& width_, const Height_& height_, const Near_& near_, const Far_& far_)
		{
			return OrthographicVK<float, Width_, float, Height_, Near_, Far_>(0.0f, width_, 0.0f, height_, near_, far_);
		}
#pragma endregion

		__m128 column0;
		__m128 column1;
		__m128 column2;
		__m128 column3;

	private:
#pragma region ASSERTIONS
		template<std::size_t ColumnIndex_, std::size_t RowIndex_>
		static constexpr inline bool _assert_valid_index()
		{
			if constexpr (ColumnIndex_ < 4)
			{
				if constexpr (RowIndex_ < 4)
				{
					return true;
				}
				else
				{
					static_assert(false, "Provided an invalid Row Index for accessing an EmuMath::FastMatrix4x4f_CM. 0-3 (inclusive) is the valid Row Index range.");
					return false;
				}
			}
			else
			{
				static_assert(false, "Provided an invalid Column Index for accessing an EmuMath::FastMatrix4x4f_CM. 0-3 (inclusive) is the valid Column Index range.");
				return false;
			}
		}

		template<typename To_>
		static constexpr inline bool _assert_valid_cast_to()
		{
			if constexpr (std::is_convertible_v<float, To_>)
			{
				return true;
			}
			else
			{
				static_assert(false, "Provided an invalid type to cast a value from an EmuMath::FastMatrix4x4f_CM to. The provided type must be possible to convert to from float.");
				return false;
			}
		}

		template<typename From_>
		static constexpr inline bool _assert_valid_cast_from()
		{
			if constexpr (std::is_convertible_v<From_, float>)
			{
				return true;
			}
			else
			{
				static_assert(false, "Provided an invalid type to cast to a value within an EmuMath::FastMatrix4x4f_CM. The provided type must be possible to convert to a float.");
				return false;
			}
		}

		template<std::size_t MajorIndex_>
		static constexpr inline bool _assert_valid_major_index()
		{
			if constexpr (MajorIndex_ < 4)
			{
				return true;
			}
			else
			{
				return false;
				static_assert(false, "Provided an invalid Major Index for accessing an EmuMath::FastMatrix4x4f_CM. 0-3 (inclusive) is the valid Major Index range, the same as its Column range.");
			}
		}
#pragma endregion

#pragma region UNDERLYING_HELPERS
		inline __m128 _std_mult_calculate_column(__m128 rhs_column_) const
		{
			// We use a shuffle instead of dumping values and broadcasting as it tends to be better optimised by the compiler
			// --- NOTE: this is slower in debug compared to the broadcasting of dumped values, but faster in release
			__m128 rhs_shuffled_ = EmuMath::SIMD::shuffle<0, 0, 0, 0>(rhs_column_);
			__m128 out_ = _mm_mul_ps(column0, rhs_shuffled_);

			// Repeat above for each individual column index, performing dot product additions with each step
			// --- We use separate add and mul operations instead of fmadd since it appears to be faster in most reasonable use cases
			rhs_shuffled_ = EmuMath::SIMD::shuffle<1, 1, 1, 1>(rhs_column_);
			out_ = _mm_add_ps(out_, _mm_mul_ps(column1, rhs_shuffled_));

			rhs_shuffled_ = EmuMath::SIMD::shuffle<2, 2, 2, 2>(rhs_column_);
			out_ = _mm_add_ps(out_, _mm_mul_ps(column2, rhs_shuffled_));

			rhs_shuffled_ = EmuMath::SIMD::shuffle<3, 3, 3, 3>(rhs_column_);
			return _mm_add_ps(out_, _mm_mul_ps(column3, rhs_shuffled_));
		}
#pragma endregion
	};
}

#pragma region STREAM_OPERATORS
std::ostream& operator<<(std::ostream& stream_, const EmuMath::FastMatrix4x4f_CM& matrix_)
{
	stream_ << matrix_.Store<float, true>();
	return stream_;
}

std::wostream& operator<<(std::wostream& stream_, const EmuMath::FastMatrix4x4f_CM& matrix_)
{
	stream_ << matrix_.Store<float, true>();
	return stream_;
}
#pragma endregion

#endif