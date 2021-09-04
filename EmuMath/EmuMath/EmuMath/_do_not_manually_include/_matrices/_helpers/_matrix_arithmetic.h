#ifndef EMU_MATH_MATRIX_HELPERS_ARITHMETIC_H_INC_
#define EMU_MATH_MATRIX_HELPERS_ARITHMETIC_H_INC_ 1

#include "_common_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_,
		Func_ func_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_lhs_rhs_operation
			<
				EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
				LhsMatrix_,
				Rhs_,
				Func_&
			>(lhs_, rhs_, func_);
		}
		else
		{
			static_assert(false, "Attempting to perform an operation on an EmuMath matrix which takes a rhs_ argument, but the lhs_ argument was not an EmuMath matrix.");
		}
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		Func_ func_ = Func_();
		return MatrixLhsRhsOperation<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_, LhsMatrix_, Rhs_, Func_&>(lhs_, rhs_, func_);
	}
	template<typename out_contained_type, bool OutColumnMajor_ , class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_,
		Func_ func_
	)
	{
		return MatrixLhsRhsOperation<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_, LhsMatrix_, Rhs_, Func_&>(lhs_, rhs_, func_);
	}
	template<typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixLhsRhsOperation<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_, LhsMatrix_, Rhs_, Func_>(lhs_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_,
		Func_ func_
	)
	{
		return MatrixLhsRhsOperation<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, rhs_, Func_&>(lhs_, rhs_, func_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixLhsRhsOperation<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, rhs_, Func_>(lhs_, rhs_);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_,
		Func_ func_
	)
	{
		return MatrixLhsRhsOperation<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_, Func_&>
		(
			lhs_,
			rhs_,
			func_
		);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixLhsRhsOperation<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_, Func_>
		(
			lhs_,
			rhs_
		);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_,
		Func_ func_
	)
	{
		return MatrixLhsRhsOperation<OutNumColumns_, OutNumColumns_, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_, Func_&>(lhs_, rhs_, func_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixLhsRhsOperation<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_, Func_>(lhs_, rhs_);
	}
	template<typename out_contained_type, class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_,
		Func_ func_
	)
	{
		return MatrixLhsRhsOperation<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_, Func_&>
		(
			lhs_,
			rhs_,
			func_
		);
	}
	template<typename out_contained_type, class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixLhsRhsOperation<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_, Func_>
		(
			lhs_,
			rhs_
		);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_,
		Func_ func_
	)
	{
		return MatrixLhsRhsOperation<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_, Func_&>
		(
			lhs_,
			rhs_,
			func_
		);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixLhsRhsOperation<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_, Func_>
		(
			lhs_,
			rhs_
		);
	}
	template<class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_,
		Func_ func_
	)
	{
		return MatrixLhsRhsOperation<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_, Func_&>
		(
			lhs_,
			rhs_,
			func_
		);
	}
	template<class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixLhsRhsOperation<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_, Func_>
		(
			lhs_,
			rhs_
		);
	}

	/// <summary>
	/// <para> Performs an addition operation on the passed lhs_ matrix using the passed rhs_. </para>
	/// <para> If the passed rhs_ is a matrix, respective indices in each matrix will be added. Otherwise, each index in the lhs_ matrix will have Rhs_ added to it. </para>
	/// <para> Additions are performed using EmuCore::do_add&lt;LhsMatrix_::value_type, Rhs_ (or Rhs_::value_type if it is a matrix)&gt;. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained within the result matrix.</typeparam>
	/// <typeparam name="LhsMatrix_">Type of matrix appearing on the left-hand side of addition.</typeparam>
	/// <typeparam name="Rhs_">Type of matrix or scalar appearing on the right-hand side of addition.</typeparam>
	/// <param name="lhs_">EmuMath matrix appearing on the left-hand side of addition.</param>
	/// <param name="rhs_">EmuMath matrix or scalar appearing on the right-hand side of addition.</param>
	/// <returns>Matrix containing the results of adding rhs_ to the lhs_ matrix.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixAdd(const LhsMatrix_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			if constexpr (EmuMath::TMP::is_emu_matrix_v<Rhs_>)
			{
				using adder_type = EmuCore::do_add<typename LhsMatrix_::value_type, typename Rhs_::value_type>;
				return _underlying_matrix_funcs::_matrix_lhs_rhs_operation
				<
					EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
					LhsMatrix_,
					Rhs_,
					adder_type
				>(lhs_, rhs_);
			}
			else
			{
				using adder_type = EmuCore::do_add<typename LhsMatrix_::value_type, Rhs_>;
				return _underlying_matrix_funcs::_matrix_lhs_rhs_operation
				<
					EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
					LhsMatrix_,
					Rhs_,
					adder_type
				>(lhs_, rhs_);
			}
		}
		else
		{
			static_assert(false, "Attempted to perform matrix addition, but provided a non-EmuMath-matrix lhs_ argument.");
		}
	}
	template<typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixAdd(const LhsMatrix_& lhs_, const Rhs_& rhs_)
	{
		return MatrixAdd<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixAdd(const LhsMatrix_& lhs_, const Rhs_& rhs_)
	{
		return MatrixAdd<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixAdd
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixAdd<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major> MatrixAdd(const LhsMatrix_& lhs_, const Rhs_& rhs_)
	{
		return MatrixAdd<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<typename out_contained_type, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major> MatrixAdd
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixAdd<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixAdd
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixAdd<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixAdd
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixAdd<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}

	/// <summary>
	/// <para> Performs an subtraction operation on the passed lhs_ matrix using the passed rhs_. </para>
	/// <para>
	///		If the passed rhs_ is a matrix, respective indices in each matrix will be subtracted. 
	/// Otherwise, each index in the lhs_ matrix will have Rhs_ subtracted from it.
	/// </para>
	/// <para> Subtractions are performed using EmuCore::do_subtract&lt;LhsMatrix_::value_type, Rhs_ (or Rhs_::value_type if it is a matrix)&gt;. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained within the result matrix.</typeparam>
	/// <typeparam name="LhsMatrix_">Type of matrix appearing on the left-hand side of subtraction.</typeparam>
	/// <typeparam name="Rhs_">Type of matrix or scalar appearing on the right-hand side of subtraction.</typeparam>
	/// <param name="lhs_">EmuMath matrix appearing on the left-hand side of subtraction.</param>
	/// <param name="rhs_">EmuMath matrix or scalar appearing on the right-hand side of subtraction.</param>
	/// <returns>Matrix containing the results of subtracting rhs_ from the lhs_ matrix.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixSubtract(const LhsMatrix_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			if constexpr (EmuMath::TMP::is_emu_matrix_v<Rhs_>)
			{
				using subtractor_type = EmuCore::do_subtract<typename LhsMatrix_::value_type, typename Rhs_::value_type>;
				return _underlying_matrix_funcs::_matrix_lhs_rhs_operation
				<
					EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
					LhsMatrix_,
					Rhs_,
					subtractor_type
				>(lhs_, rhs_);
			}
			else
			{
				using subtractor_type = EmuCore::do_subtract<typename LhsMatrix_::value_type, Rhs_>;
				return _underlying_matrix_funcs::_matrix_lhs_rhs_operation
				<
					EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
					LhsMatrix_,
					Rhs_,
					subtractor_type
				>(lhs_, rhs_);
			}
		}
		else
		{
			static_assert(false, "Attempted to perform matrix subtraction, but provided a non-EmuMath-matrix lhs_ argument.");
		}
	}
	template<typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixSubtract(const LhsMatrix_& lhs_, const Rhs_& rhs_)
	{
		return MatrixSubtract<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixSubtract(const LhsMatrix_& lhs_, const Rhs_& rhs_)
	{
		return MatrixSubtract<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixSubtract
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixSubtract<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major> MatrixSubtract(const LhsMatrix_& lhs_, const Rhs_& rhs_)
	{
		return MatrixSubtract<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<typename out_contained_type, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major> MatrixSubtract
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixSubtract<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixSubtract
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixSubtract<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixSubtract
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixSubtract<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}

	/// <summary>
	/// <para> Performs a basic multiplication operation on lhs_ using the passed rhs_. </para>
	/// <para>
	///		If the passed rhs_ is a matrix, respective indices in each matrix will be multiplied. 
	///		Otherwise, each index in the lhs_ matrix will be multiplied by rhs_.
	/// </para>
	/// <para> Multiplications are performed using EmuCore::do_multiply&lt;LhsMatrix_::value_type, Rhs_ (or Rhs_::value_type if it is a matrix)&gt;. </para>
	/// <para> NOTE: This is NOT a standard matrix multiplication operation. For such behaviour, use MatrixMultiply instead. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained within the result matrix.</typeparam>
	/// <typeparam name="LhsMatrix_">Type of matrix appearing on the left-hand side of multiplication.</typeparam>
	/// <typeparam name="Rhs_">Type of matrix or scalar appearing on the right-hand side of multiplication.</typeparam>
	/// <param name="lhs_">EmuMath matrix appearing on the left-hand side of multiplication.</param>
	/// <param name="rhs_">EmuMath matrix or scalar appearing on the right-hand side of multiplication.</param>
	/// <returns>Matrix containing the results of performing a basic multiplication on the lhs_ matrix by the provided rhs_.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixMultiplyBasic(const LhsMatrix_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			if constexpr (EmuMath::TMP::is_emu_matrix_v<Rhs_>)
			{
				using multiplier_type = EmuCore::do_multiply<typename LhsMatrix_::value_type, typename Rhs_::value_type>;
				return _underlying_matrix_funcs::_matrix_lhs_rhs_operation
				<
					EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
					LhsMatrix_,
					Rhs_,
					multiplier_type
				>(lhs_, rhs_);
			}
			else
			{
				using multiplier_type = EmuCore::do_multiply<typename LhsMatrix_::value_type, Rhs_>;
				return _underlying_matrix_funcs::_matrix_lhs_rhs_operation
				<
					EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
					LhsMatrix_,
					Rhs_,
					multiplier_type
				>(lhs_, rhs_);
			}
		}
		else
		{
			static_assert(false, "Attempted to perform basic matrix multiplication, but provided a non-EmuMath-matrix lhs_ argument.");
		}
	}
	template<typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixMultiplyBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixMultiplyBasic<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixMultiplyBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixMultiplyBasic<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixMultiplyBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixMultiplyBasic<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major> MatrixMultiplyBasic(const LhsMatrix_& lhs_, const Rhs_& rhs_)
	{
		return MatrixMultiplyBasic<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<typename out_contained_type, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major> MatrixMultiplyBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixMultiplyBasic<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixMultiplyBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixMultiplyBasic<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixMultiplyBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixMultiplyBasic<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}

	/// <summary>
	/// <para> Performs a basic division operation on lhs_ using the passed rhs_. </para>
	/// <para>
	///		If the passed rhs_ is a matrix, respective indices in each matrix will be divided. 
	///		Otherwise, each index in the lhs_ matrix will be divided by rhs_.
	/// </para>
	/// <para> Divisions are performed using EmuCore::do_divide&lt;LhsMatrix_::value_type, Rhs_ (or Rhs_::value_type if it is a matrix)&gt;. </para>
	/// <para> NOTE: This is NOT a standard matrix division operation. Such behaviour is mathematically undefined. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained within the result matrix.</typeparam>
	/// <typeparam name="LhsMatrix_">Type of matrix appearing on the left-hand side of division.</typeparam>
	/// <typeparam name="Rhs_">Type of matrix or scalar appearing on the right-hand side of division.</typeparam>
	/// <param name="lhs_">EmuMath matrix appearing on the left-hand side of division.</param>
	/// <param name="rhs_">EmuMath matrix or scalar appearing on the right-hand side of division.</param>
	/// <returns>Matrix containing the results of performing a basic division on the lhs_ matrix by the provided rhs_.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixDivideBasic(const LhsMatrix_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			if constexpr (EmuMath::TMP::is_emu_matrix_v<Rhs_>)
			{
				using divider_type = EmuCore::do_divide<typename LhsMatrix_::value_type, typename Rhs_::value_type>;
				return _underlying_matrix_funcs::_matrix_lhs_rhs_operation
				<
					EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
					LhsMatrix_,
					Rhs_,
					divider_type
				>(lhs_, rhs_);
			}
			else
			{
				using divider_type = EmuCore::do_divide<typename LhsMatrix_::value_type, Rhs_>;
				return _underlying_matrix_funcs::_matrix_lhs_rhs_operation
				<
					EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
					LhsMatrix_,
					Rhs_,
					divider_type
				>(lhs_, rhs_);
			}
		}
		else
		{
			static_assert(false, "Attempted to perform basic matrix division, but provided a non-EmuMath-matrix lhs_ argument.");
		}
	}
	template<typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixDivideBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixDivideBasic<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixDivideBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixDivideBasic<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixDivideBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixDivideBasic<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major> MatrixDivideBasic(const LhsMatrix_& lhs_, const Rhs_& rhs_)
	{
		return MatrixDivideBasic<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<typename out_contained_type, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major> MatrixDivideBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixDivideBasic<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixDivideBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixDivideBasic<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixDivideBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixDivideBasic<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}

	/// <summary>
	/// <para> Performs a multiplication operation on lhs_ using the passed rhs_. </para>
	/// <para>
	///		If the passed rhs_ is a matrix, the resulting matrix will be that of a standard matrix multiplication.
	///		Otherwise, each index in the lhs_ matrix will be multiplied by rhs_.
	/// </para>
	/// <para> If rhs_ is a scalar, multiplications are performed using EmuCore::do_multiply&lt;LhsMatrix_::value_type, Rhs_ (or Rhs_::value_type if it is a matrix)&gt;. </para>
	/// <para> NOTE: This is a standard matrix multiplication operation. To instead multiply respective matrix indices, use MatrixMultiplyBasic. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained within the result matrix.</typeparam>
	/// <typeparam name="LhsMatrix_">Type of matrix appearing on the left-hand side of multiplication.</typeparam>
	/// <typeparam name="Rhs_">Type of matrix or scalar appearing on the right-hand side of multiplication.</typeparam>
	/// <param name="lhs_">EmuMath matrix appearing on the left-hand side of multiplication.</param>
	/// <param name="rhs_">EmuMath matrix or scalar appearing on the right-hand side of multiplication.</param>
	/// <returns>Matrix containing the results of performing multiplication on the lhs_ matrix by the provided rhs_.</returns>
	template<typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline typename EmuMath::TMP::emu_matrix_multiplication_result<out_contained_type, OutColumnMajor_, LhsMatrix_, Rhs_>::type MatrixMultiply
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			if constexpr(!std::is_same_v<typename EmuMath::TMP::emu_matrix_multiplication_result<out_contained_type, OutColumnMajor_, LhsMatrix_, Rhs_>::type, void>)
			{
				return _underlying_matrix_funcs::_matrix_std_multiply
				<
					typename EmuMath::TMP::emu_matrix_multiplication_result<out_contained_type, OutColumnMajor_, LhsMatrix_, Rhs_>::type,
					LhsMatrix_,
					Rhs_
				>(lhs_, rhs_);
			}
			else
			{
				static_assert(false, "Attempted to multiply two EmuMath matrices which can not be multiplied together. When multiplying matrices, the left-hand matrix must have the same number of columns as the right-hand matrix's number of rows.");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform matrix multiplication with a lhs_ argument that is not an EmuMath matrix.");
		}
	}
	template<typename out_contained_type, class LhsMatrix_, class Rhs_>
	constexpr inline typename EmuMath::TMP::emu_matrix_multiplication_result<out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>::type MatrixMultiply
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixMultiply<out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline typename EmuMath::TMP::emu_matrix_multiplication_result<typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>::type MatrixMultiply
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixMultiply<typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<class LhsMatrix_, class Rhs_>
	constexpr inline typename EmuMath::TMP::emu_matrix_multiplication_result<typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>::type MatrixMultiply
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixMultiply<typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
}

#endif
