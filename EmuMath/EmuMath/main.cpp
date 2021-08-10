#include "Tests.hpp"

#include "EmuMath/GeneralMath.h"
#include "EmuMath/NoOverflowT.h"
#include "EmuMath/Vectors.h"
#include "EmuMath/FastVector.h"
#include "EmuMath/Matrices.h"
#include <array>

using namespace EmuCore::TestingHelpers;
using namespace EmuMath;

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

int main()
{
	const float bobs[4] = { 1.0f, 2.0f, 3.0f, 4.0f };
	FastVector<4, float> yo(2.0f, 1.0f, 5.0f, -777.69f);
	FastVector<4, float> no(5.0f, 1.0f, 6.0f, 2.0f);
	yo.vectorData = _mm_load_ps(bobs);
	const float* pData = yo.vectorData.m128_f32;
	std::cout << "Data: { " << pData[0] << ", " << pData[1] << ", " << pData[2] << ", " << pData[3] << " }\n";
	yo = yo.Shuffle<2, 1, 0, 3>();
	std::cout << "Data: { " << pData[0] << ", " << pData[1] << ", " << pData[2] << ", " << pData[3] << " }\n";
	float dot = yo.DotProduct(no);
	std::cout << yo << " DOT " << no << " = " << dot << "\n\n";

	FastVector<4, float> max0(123.4f, 123.3f, 3.0f, -123.5f);
	FastVector<4, float> max1(4.6f, 22.5f, 3.5f, -22.5f);
	FastVector<4, float> max2(2.3f, -77.1f, 666.666f, 2.2f);
	FastVector<4, float> max3(12.0f, 34.0f, 56.0f, 78.0f);
	std::cout << max0 << " | Min: " << max0.Min() << " |  Max: " << max0.Max() << " | Average: " << max0.Mean() << "\n";
	std::cout << max1 << " | Min: " << max1.Min() << " |  Max: " << max1.Max() << " | Average: " << max1.Mean() << "\n";
	std::cout << max2 << " | Min: " << max2.Min() << " |  Max: " << max2.Max() << " | Average: " << max2.Mean() << "\n";
	std::cout << max3 << " | Min: " << max3.Min() << " |  Max: " << max3.Max() << " | Average: " << max3.Mean() << "\n";

	__m128 test128 = _mm_setr_ps(1.0f, 2.0f, 3.0f, 4.0f);
	test128 = EmuMath::SIMD::horizontal_vector_sum(test128);
	std::cout << "[0] = " << EmuMath::SIMD::get_m128_index(test128, 0) << "\n";
	std::cout << "[1] = " << EmuMath::SIMD::get_m128_index(test128, 1) << "\n";
	std::cout << "[2] = " << EmuMath::SIMD::get_m128_index(test128, 2) << "\n";
	std::cout << "[3] = " << EmuMath::SIMD::get_m128_index(test128, 3) << "\n";

	EmuMath::FastVector<4, float> a(1.0f, 1.0f, 1.0f, 1.0f);
	EmuMath::FastVector<4, float> b(1.0f, 2.0f, 1.0f, 1.0f);
	std::cout << a << " == " << b << ": " << (EmuMath::SIMD::all_not_equal<false, true, false, false>(a.vectorData, b.vectorData) ? "true" : "false") << "\n";

	constexpr std::uint32_t c = 0b0011;
	constexpr std::uint32_t d = 0b11111111111111110111111111111111;
	constexpr std::uint32_t e = 0;
	std::cout
		<< "c bits: " << EmuCore::ArithmeticHelpers::num_active_bits(c) << "\t(" << std::bitset<32>(c) << ")\n"
		<< "d bits: " << EmuCore::ArithmeticHelpers::num_active_bits(d) << "\t(" << std::bitset<32>(d) << ")\n"
		<< "e bits: " << EmuCore::ArithmeticHelpers::num_active_bits(e) << "\t(" << std::bitset<32>(e) << ")\n";
	
	
	EmuMath::MatrixCM<4, 4, float> blooble(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	constexpr EmuMath::MatrixCM<25, 25, float> mat_25x25_identity = EmuMath::MatrixCM<25, 25, float>::Identity();
	std::cout << mat_25x25_identity << "\n";

	//blooble.columns[1] *= 10.0f;
	std::cout << "Base:\n" << blooble << std::endl;
	std::cout << "Tranpose:\n" << blooble.Transpose() << std::endl;
	std::cout << "Added to self:\n" << (blooble + blooble) << std::endl;
	std::cout << "Subtracted from self 3 times:\n" << (blooble - blooble - blooble - blooble) << std::endl;
	std::cout << "Negated:\n" << -blooble << std::endl;
	//std::cout << "Negated row 1:\n" << (-blooble).GetRow<1>() << std::endl;
	//std::cout << "Column 3:\n" << blooble.GetColumn<3>() << std::endl;
	std::cout << "Multiplied by 0.5f:\n" << (blooble * 0.5f) << std::endl;
	std::cout << "Trace: " << blooble.Trace() << std::endl;
	std::cout << "\n\n" << blooble << "\nMULT\n" << (blooble * 2.5f) << "\nEQUALS:\n" << (blooble * (blooble * 2.5f)) << std::endl;

	std::cout << "BLOOBLE ROWS EXTRACTED INDIVIDUALLY:\n" << EmuMath::Helpers::MatrixCopyAsRows(blooble) << "\n";
	std::cout << "BLOOBLE COLUMNS EXTRACTED INDIVIDUALLY:\n" << EmuMath::Helpers::MatrixCopyAsColumns(blooble) << "\n";

	std::cout << "Identity:\n" << blooble.Identity() << std::endl;


	std::cout << "Submatrix(0-1, 0-1):\n" << EmuMath::Helpers::MatrixSubMatrix<0, 1, 0, 1>(blooble) << std::endl;
	std::cout << "Submatrix(0-1, 1-3):\n" << EmuMath::Helpers::MatrixSubMatrix<0, 1, 1, 3>(blooble) << std::endl;

	system("pause");

#pragma region TEST_HARNESS_EXECUTION
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}