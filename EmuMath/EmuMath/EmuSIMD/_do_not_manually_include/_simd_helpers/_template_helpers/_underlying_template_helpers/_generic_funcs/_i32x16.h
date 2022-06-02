#ifndef EMU_SIMD_GENERIC_FUNCS_I32X16_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_I32X16_H_INC_ 1

#include "_common_generic_func_helpers.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 set_i32x16
	(
		std::int32_t e0, std::int32_t e1, std::int32_t e2, std::int32_t e3, std::int32_t e4, std::int32_t e5, std::int32_t e6, std::int32_t e7,
		std::int32_t e8, std::int32_t e9, std::int32_t e10, std::int32_t e11, std::int32_t e12, std::int32_t e13, std::int32_t e14, std::int32_t e15
	)
	{
		return _mm512_set_epi32(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 setr_i32x16
	(
		std::int32_t e0, std::int32_t e1, std::int32_t e2, std::int32_t e3, std::int32_t e4, std::int32_t e5, std::int32_t e6, std::int32_t e7,
		std::int32_t e8, std::int32_t e9, std::int32_t e10, std::int32_t e11, std::int32_t e12, std::int32_t e13, std::int32_t e14, std::int32_t e15
	)
	{
		return _mm512_setr_epi32(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 set1_i32x16(std::int32_t all_)
	{
		return _mm512_set1_epi32(all_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 load_i32x16(const std::int32_t* p_to_load_)
	{
		return _mm512_load_si512(p_to_load_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 setzero_i32x16()
	{
		return _mm512_setzero_si512();
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_i32x16(std::int32_t* p_out_, i32x16_arg a_)
	{
		_mm512_store_si512(reinterpret_cast<__m256i*>(p_out_), a_);
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_f32x4_i32x16(f32x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm_castps_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_f32x8_i32x16(f32x8_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_castps_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_f32x16_i32x16(f32x16_arg a_)
	{
		return _mm512_castps_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_f64x2_i32x16(f64x2_arg a_)
	{
		return _mm512_castsi128_si512(_mm_castpd_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_f64x4_i32x16(f64x4_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_castpd_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_f64x8_i32x16(f64x8_arg a_)
	{
		return _mm512_castpd_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_i8x16_i32x16(i8x16_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_i16x8_i32x16(i16x8_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_i32x4_i32x16(i32x4_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_i64x2_i32x16(i64x2_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_i8x32_i32x16(i8x32_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_i16x16_i32x16(i16x16_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_i32x8_i32x16(i32x8_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_i64x4_i32x16(i64x4_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_i8x64_i32x16(i8x64_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_i16x32_i32x16(i16x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_i32x16_i32x16(i32x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_i64x8_i32x16(i64x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_u8x16_i32x16(u8x16_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_u16x8_i32x16(u16x8_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_u32x4_i32x16(u32x4_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_u64x2_i32x16(u64x2_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_u8x32_i32x16(u8x32_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_u16x16_i32x16(u16x16_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_u32x8_i32x16(u32x8_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_u64x4_i32x16(u64x4_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_u8x64_i32x16(u8x64_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_u16x32_i32x16(u16x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_u32x16_i32x16(u32x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_u64x8_i32x16(u64x8_arg a_)
	{
		return a_;
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_f32x4_i32x16(f32x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm_cvtps_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_f32x8_i32x16(f32x8_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_cvtps_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_f32x16_i32x16(f32x16_arg a_)
	{
		return _mm512_cvtps_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_f64x2_i32x16(f64x2_arg a_)
	{
		return _mm512_castsi128_si512(_mm_cvtpd_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_f64x4_i32x16(f64x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm256_cvtpd_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_f64x8_i32x16(f64x8_arg a_)
	{
		return _mm512_castsi256_si512(_mm512_cvtpd_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_i8x16_i32x16(i8x16_arg a_)
	{
		return _mm512_cvtepi8_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_i16x8_i32x16(i16x8_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_cvtepi16_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_i32x4_i32x16(i32x4_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_i64x2_i32x16(i64x2_arg a_)
	{
		return _mm512_castsi128_si512(_mm_cvtepi64_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_i8x32_i32x16(i8x32_arg a_)
	{
		return _mm512_cvtepi8_epi32(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_i16x16_i32x16(i16x16_arg a_)
	{
		return _mm512_cvtepi16_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_i32x8_i32x16(i32x8_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_i64x4_i32x16(i64x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm256_cvtepi64_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_i8x64_i32x16(i8x64_arg a_)
	{
		return _mm512_cvtepi8_epi32(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_i16x32_i32x16(i16x32_arg a_)
	{
		return _mm512_cvtepi16_epi32(_mm512_castsi512_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_i32x16_i32x16(i32x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_i64x8_i32x16(i64x8_arg a_)
	{
		return _mm512_castsi256_si512(_mm512_cvtepi64_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_u8x16_i32x16(i8x16_arg a_)
	{
		return _mm512_cvtepu8_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_u16x8_i32x16(i16x8_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_cvtepu16_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_u32x4_i32x16(i32x4_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_u64x2_i32x16(i64x2_arg a_)
	{
		return _mm512_castsi128_si512(_mm_cvtepi64_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_u8x32_i32x16(i8x32_arg a_)
	{
		return _mm512_cvtepu8_epi32(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_u16x16_i32x16(i16x16_arg a_)
	{
		return _mm512_cvtepu16_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_u32x8_i32x16(i32x8_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_u64x4_i32x16(i64x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm256_cvtepi64_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_u8x64_i32x16(i8x64_arg a_)
	{
		return _mm512_cvtepu8_epi32(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_u16x32_i32x16(i16x32_arg a_)
	{
		return _mm512_cvtepu16_epi32(_mm512_castsi512_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_u32x16_i32x16(i32x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_u64x8_i32x16(i64x8_arg a_)
	{
		return _mm512_castsi256_si512(_mm512_cvtepi64_epi32(a_));
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 mul_all_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_)
	{
		return _mm512_mullo_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 negate_i32x16(EmuSIMD::i32x16_arg to_negate_)
	{
		return _mm512_sub_epi32(_mm512_setzero_si512(), to_negate_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 add_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_)
	{
		return _mm512_add_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 sub_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_)
	{
		return _mm512_sub_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 mul_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_)
	{
		return _mm512_mul_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 div_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_)
	{
		return _mm512_div_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 addsub_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_)
	{
		constexpr std::int32_t bytes_mask = static_cast<std::int32_t>(0xFFFFFFFF);
		const EmuSIMD::i32x16 mask = _mm512_set_epi32(bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::i32x16 out = _mm512_add_epi32(lhs_, _mm512_and_si512(mask, rhs_));
		return _mm512_sub_epi32(lhs_, _mm512_andnot_si512(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 subadd_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_)
	{
		constexpr std::int32_t bytes_mask = static_cast<std::int32_t>(0xFFFFFFFF);
		const EmuSIMD::i32x16 mask = _mm512_set_epi32(bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::i32x16 out = _mm512_sub_epi32(lhs_, _mm512_and_si512(mask, rhs_));
		return _mm512_add_epi32(lhs_, _mm512_andnot_si512(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 fmadd_i32x16(EmuSIMD::i32x16_arg a_, EmuSIMD::i32x16_arg b_, EmuSIMD::i32x16_arg c_)
	{
		return _mm512_add_epi32(mul_all_i32x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 fmsub_i32x16(EmuSIMD::i32x16_arg a_, EmuSIMD::i32x16_arg b_, EmuSIMD::i32x16_arg c_)
	{
		return _mm512_sub_epi32(mul_all_i32x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 fnmadd_i32x16(EmuSIMD::i32x16_arg a_, EmuSIMD::i32x16_arg b_, EmuSIMD::i32x16_arg c_)
	{
		return _mm512_add_epi32(mul_all_i32x16(negate_i32x16(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 fnmsub_i32x16(EmuSIMD::i32x16_arg a_, EmuSIMD::i32x16_arg b_, EmuSIMD::i32x16_arg c_)
	{
		return _mm512_sub_epi32(mul_all_i32x16(negate_i32x16(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 fmaddsub_i32x16(EmuSIMD::i32x16_arg a_, EmuSIMD::i32x16_arg b_, EmuSIMD::i32x16_arg c_)
	{
		return addsub_i32x16(mul_all_i32x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 fmsubadd_i32x16(EmuSIMD::i32x16_arg a_, EmuSIMD::i32x16_arg b_, EmuSIMD::i32x16_arg c_)
	{
		return subadd_i32x16(mul_all_i32x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 floor_i32x16(EmuSIMD::i32x16_arg to_floor_)
	{
		return to_floor_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 ceil_i32x16(EmuSIMD::i32x16_arg to_ceil_)
	{
		return to_ceil_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 trunc_i32x16(EmuSIMD::i32x16_arg to_trunc_)
	{
		return to_trunc_;
	}

	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 round_i32x16(EmuSIMD::i32x16_arg to_round_)
	{
		return to_round_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 mod_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_)
	{
		return _mm512_rem_epi32(lhs_, rhs_);
	}
#pragma endregion
}

#endif
