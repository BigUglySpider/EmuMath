#include "Tests.hpp"

#include "EmuMath/GeneralMath.h"
#include "EmuMath/Vectors.h"
#include <array>

using namespace EmuCore::TestingHelpers;
using namespace EmuMath;

template<typename T>
using bitset_t = std::bitset<sizeof(T) * CHAR_BIT>;

int main()
{
	constexpr Vector2<std::uint32_t> V2UI32 = { 0xFFFF0000, 0x0000FFFF };
	constexpr Vector2<std::uint32_t> NOT_V2UI32 = ~V2UI32;
	constexpr Vector4<std::uint64_t> V4UI64 = { 0xFFFFFFFFFFFFFFFF, 0x0000FFFF00000000, 0x00000000FFFF0000, 0x0000000000FFFF };

	constexpr float VAL = 2415126.37f;
	constexpr float MINUS_VAL = -VAL;

	constexpr float VAL_FLOOR = EmuCore::TMPHelpers::floor_diff_types<float, float>::ConstexprRound(VAL);
	constexpr float MINUS_VAL_FLOOR = EmuCore::TMPHelpers::floor_diff_types<float, float>::ConstexprRound(MINUS_VAL);

	constexpr float VAL_CEIL = EmuCore::TMPHelpers::ceil_diff_types<float, float>::ConstexprRound(VAL);
	constexpr float MINUS_VAL_CEIL = EmuCore::TMPHelpers::ceil_diff_types<float, float>::ConstexprRound(MINUS_VAL);

	constexpr float VAL_TRUNC = EmuCore::TMPHelpers::trunc_diff_types<float, float>::ConstexprRound(VAL);
	constexpr float MINUS_VAL_TRUNC = EmuCore::TMPHelpers::trunc_diff_types<float, float>::ConstexprRound(MINUS_VAL);

	constexpr Vector4<float> V4f = { 0.31f, -617.369f, 2.3f, 1.0f };
	constexpr Vector4<float> V4f_ceil = EmuMath::Helpers::VectorCeilConstexpr<4, float>(V4f);
	constexpr Vector4<float> V4f_floor = EmuMath::Helpers::VectorFloorConstexpr<4, float>(V4f);
	constexpr Vector4<float> V4f_trunc = EmuMath::Helpers::VectorTruncConstexpr<4, float>(V4f);

	constexpr Vector2<float> v2f = Vector2<float>(V4f);
	constexpr Vector2<float> v2f_ceil = v2f.CeilConstexpr();
	constexpr Vector2<float> v2f_floor = v2f.FloorConstexpr();
	constexpr Vector2<float> v2f_trunc = v2f.TruncConstexpr();

	EmuCore::TMPHelpers::bits_in_type_v<std::array<float, 400>>;

	constexpr Vector2<float> v4f_ywv2_ceil = V4f.AsShuffled<1, 3>().CeilConstexpr();

#pragma region TEST_HARNESS_EXECUTION
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}