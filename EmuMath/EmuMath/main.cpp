#include "EmuMath/Vector.h"
#include "EmuMath/FastVector.h"
#include "EmuMath/Matrix.h"
#include "EmuMath/NoOverflowT.h"
#include "EmuCore/TMPHelpers/Tuples.h"
#include <array>
#include <bitset>
#include <iomanip>

#include "Tests.hpp"
using namespace EmuCore::TestingHelpers;

template<typename T_>
using simple_bitset = std::bitset<sizeof(T_) * CHAR_BIT>;

template<typename T_, std::size_t Size_>
inline std::ostream& operator<<(std::ostream& stream_, const std::array<T_, Size_>& arr_)
{
	std::ostringstream str;
	str << "{ ";
	str << arr_[0];
	for (std::size_t i = 1; i < Size_; ++i)
	{
		str << ", " << arr_[i];
	}
	str << " }";
	stream_ << str.str();
	return stream_;
}

template<typename T_, int Max_ = std::numeric_limits<int>::max()>
struct SettyBoi
{
	SettyBoi() : SettyBoi(static_cast<unsigned int>(time(0)))
	{
	}
	SettyBoi(unsigned int seed_)
	{
		srand(seed_);
	}

	T_ operator()() const
	{
		return T_(rand() % Max_);
	}
	T_ operator()(const std::size_t x_, const std::size_t y_) const
	{
		return T_(rand() % (x_ + y_ + 1));
	}
};

bool boolfunc(bool bool_)
{
	return bool(bool_);
}

template<std::size_t X_, std::size_t Y_, typename Type_, bool ColumnMajor_>
void TestFunc(const EmuMath::Matrix<X_, Y_, Type_, ColumnMajor_>& matrix_)
{
	std::cout << matrix_ << "\n";
}
template<std::size_t X_, std::size_t Y_, typename Type_, bool ColumnMajor_>
void TestFunc(EmuMath::Matrix<X_, Y_, Type_, ColumnMajor_>&& matrix_)
{
	TestFunc(std::forward<EmuMath::Matrix<X_, Y_, Type_, ColumnMajor_>>(matrix_));
}
template<std::size_t FirstX_, std::size_t FirstY_, typename FirstType_, bool FirstColumnMajor_, std::size_t...X_, std::size_t...Y_, typename...Types_, bool...ColumnMajors_>
void TestFunc(const EmuMath::Matrix<FirstX_, FirstY_, FirstType_, FirstColumnMajor_>& first_, const EmuMath::Matrix<X_, Y_, Types_, ColumnMajors_>&...matrices_)
{
	TestFunc(first_);
	TestFunc(matrices_...);
}

int main()
{
	srand(static_cast<unsigned int>(time(0)));

	EmuMath::Vector<4, double> _1(4.0f, 5.0f, 6.0f, 37.0f);

	EmuMath::Matrix<4, 4, float, true> matrix_
	(
		EmuMath::Vector4<float>(0.0f, 1.0f, 2.0f, 3.0f),
		std::move(_1),
		EmuMath::Vector4<std::uint8_t>(8.0f, 9.0f, 10.0f, 11.0f),
		EmuMath::Vector4<std::uint64_t>(12.0f, 13.0f, 14.0f, 15.0f)
	);


	std::cout << matrix_ << "\n";
	std::cout << "[2]: " << matrix_[2] << "\n";
	std::cout << "[7]: " << matrix_[7] << "\n";
	std::cout << "[13]: " << matrix_[13] << "\n";
	std::cout << "[15]: " << matrix_[15] << "\n";
	std::cout << "Column 3: " << matrix_.GetColumn<3>() << "\n";
	std::cout << "Row 2: " << matrix_.GetRow<2>() << "\n";
	
	std::cout << matrix_ << "\n";

	using test_type = EmuCore::TMPHelpers::tuple_n<10, float>::type;

	constexpr auto vec_ = (EmuMath::Vector<10, float>(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f));;
	constexpr test_type tuple_ = EmuMath::Helpers::VectorAsTuple(vec_);
	std::cout << std::get<0>(tuple_) << "\n";

	constexpr auto column_ = EmuMath::Helpers::VectorToColumnMatrix<true>(vec_);
	constexpr auto row_ = EmuMath::Helpers::VectorToRowMatrix<true>(vec_);
	std::cout << column_ << "\n";
	std::cout << row_ << "\n";

	auto out_a_ = EmuMath::Helpers::MatrixGetTheoretical<2, 2>(matrix_);
	auto out_b_ = EmuMath::Helpers::MatrixGetTheoretical<2, 5>(matrix_);
	auto out_c_ = EmuMath::Helpers::MatrixGetTheoretical<13>(matrix_);
	auto out_d_ = EmuMath::Helpers::MatrixGetTheoretical<16>(matrix_);

	constexpr EmuMath::Matrix<4, 4, float, true> mat_a_
	(
		EmuMath::Vector4<float>(1.0f, 2.0f, 3.0f, 4.0f),
		EmuMath::Vector4<float>(5.0f, 6.0f, 7.0f, 8.0f),
		EmuMath::Vector4<float>(9.0f, 10.0f, 11.0f, 12.0f),
		EmuMath::Vector4<float>(13.0f, 14.0f, 15.0f, 16.0f)
	);
	constexpr EmuMath::Matrix<4, 4, float, true> mat_b_
	(
		EmuMath::Vector4<float>(1.0f + 16.0f, 2.0f + 16.0f, 3.0f + 16.0f, 4.0f + 16.0f),
		EmuMath::Vector4<float>(5.0f + 16.0f, 6.0f + 16.0f, 7.0f + 16.0f, 8.0f + 16.0f),
		EmuMath::Vector4<float>(9.0f + 16.0f, 10.0f + 16.0f, 11.0f + 16.0f, 12.0f + 16.0f),
		EmuMath::Vector4<float>(13.0f + 16.0f, 14.0f + 16.0f, 15.0f + 16.0f, 16.0f + 16.0f)
	);
	constexpr auto mat_res_ = EmuMath::Helpers::MatrixDivideBasic<long double>(mat_a_, mat_b_);
	constexpr auto mat_res_scalar_ = EmuMath::Helpers::MatrixDivideBasic(mat_a_, 25.0f);

	std::cout << mat_res_scalar_ << "\n";

	constexpr auto mat_mult = EmuMath::Helpers::MatrixMultiply<float, true>(mat_a_, mat_b_);

	std::cout << "\n\n";
	std::cout << mat_a_ << "\nMULT\n" << mat_b_ << "\n:\n" << mat_mult << "\n";

	constexpr auto mat_c_ = EmuMath::Matrix<5, 2, float, true>
	(
		EmuMath::Vector<2, float>(2.0f, 4.0f),
		EmuMath::Vector<2, float>(6.0f, 8.0f),
		EmuMath::Vector<2, float>(10.0f, 12.0f),
		EmuMath::Vector<2, float>(14.0f, 16.0f),
		EmuMath::Vector<2, float>(18.0f, 20.0f)
	);
	constexpr auto mat_d_ = EmuMath::Matrix<3, 5, double, false>
	(
		EmuMath::Vector<2, double>(13.0, 16.0),
		EmuMath::Vector<2, double>(2.5, 0.5),
		EmuMath::Vector<2, double>(1.0, 0.25),
		EmuMath::Vector<2, double>(1.0, 0.1),
		EmuMath::Vector<2, double>(2.0, 6)
	);
	constexpr auto mat_mult_cd_ = EmuMath::Helpers::MatrixMultiply<double, true>(mat_c_, mat_d_);

	EmuMath::TMP::emu_matrix_multiplication_result_t<float, true, EmuMath::Matrix<5, 2, float, true>, EmuMath::Matrix<2, 5, double, false>> dummy_;

	std::cout << "\n\n";
	std::cout << mat_c_ << "\nMULT\n" << mat_d_ << "\n:\n" << mat_mult_cd_ << "\n";

	//constexpr auto mat_mult_dc_ = EmuMath::Helpers::MatrixMultiply<double, true>(mat_d_, mat_c_);
	//std::cout << "\n\n";
	//std::cout << mat_d_ << "\nMULT\n" << mat_c_ << "\n:\n" << mat_mult_dc_ << "\n";

	constexpr auto mat_mult_c05_ = EmuMath::Helpers::MatrixMultiply<double, false>(mat_c_, 0.5);
	std::cout << "\n\n";
	std::cout << mat_c_ << "\nMULT\n" << 0.5 << "\n:\n" << mat_mult_c05_ << "\n";

	constexpr auto mat_e_ = EmuMath::Matrix<4, 3, float>
	(
		EmuMath::Vector<3, float>(1.0f, 5.0f, 9.0f),
		EmuMath::Vector<3, float>(2.0f, 6.0f, 10.0f),
		EmuMath::Vector<3, float>(3.0f, 7.0f, 11.0f),
		EmuMath::Vector<3, float>(4.0f, 8.0f, 12.0f)
	);
	constexpr auto mat_f_ = EmuMath::Helpers::VectorToColumnMatrix(EmuMath::Vector<4, double>(10.0, 20.0, 30.0, 40.0));
	
	constexpr auto mat_mult_ef_ = EmuMath::Helpers::MatrixMultiply<double, true>(mat_e_, mat_f_);
	std::cout << "\n\n";
	std::cout << mat_e_ << "\nMULT\n" << mat_f_ << "\n:\n" << mat_mult_ef_ << "\n";

	EmuMath::Matrix<4, 4, float> wee
	(
		EmuMath::Vector<3, float>(1.0f, 5.0f, 9.0f),
		EmuMath::Vector<3, float>(2.0f, 6.0f, 10.0f),
		EmuMath::Vector<3, float>(3.0f, 7.0f, 11.0f),
		EmuMath::Vector<3, float>(4.0f, 8.0f, 12.0f)
	);
	wee = EmuMath::Helpers::MatrixMultiply(wee, 1.0f / (rand() + 1.0f));
	std::cout << wee << "\n";
	constexpr auto wee_identity = EmuMath::Helpers::MatrixIdentity(wee);
	std::cout << "Identity:\n" << wee_identity << "\n";

	constexpr std::size_t Size_ = 1;
	std::cout << Size_ << "x" << Size_ << " Identity:\n" << EmuMath::Helpers::MatrixIdentity<Size_, Size_, float, true>();

	constexpr auto size_identity_ = EmuMath::Helpers::MatrixIdentity<Size_, Size_, float, true>();

#pragma region TEST_HARNESS_EXECUTION
	system("pause");
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}
