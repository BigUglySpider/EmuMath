#ifndef EMU_SIMD_GENERIC_FUNCS_F64X2_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_F64X2_H_INC_ 1

#include "_common_generic_func_helpers.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 set_f64x2(double e0, double e1)
	{
		return _mm_set_pd(e0, e1);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 setr_f64x2(double e0, double e1)
	{
		return _mm_setr_pd(e0, e1);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 set1_f64x2(double all_)
	{
		return _mm_set1_pd(all_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 load_f64x2(const double* p_to_load_)
	{
		return _mm_load_pd(p_to_load_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 setzero_f64x2()
	{
		return _mm_setzero_pd();
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 setmasked_f64x2(std::uint8_t bit_mask_)
	{
		constexpr std::int64_t element_mask = static_cast<std::int64_t>(0xFFFFFFFFFFFFFFFF);
		return _mm_castsi128_pd
		(
			_mm_set_epi64x
			(
				(bit_mask_ & 0x01) * element_mask,
				((bit_mask_ & 0x02) >> 1) * element_mask
			)
		);
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_f64x2(double* p_out_, f64x2_arg a_)
	{
		_mm_store_pd(p_out_, a_);
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_f32x4_f64x2(f32x4_arg a_)
	{
		return _mm_castps_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_f32x8_f64x2(f32x8_arg a_)
	{
		return _mm256_castpd256_pd128(_mm256_castps_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_f32x16_f64x2(f32x16_arg a_)
	{
		return _mm512_castpd512_pd128(_mm512_castps_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_f64x2_f64x2(f64x2_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_f64x4_f64x2(f64x4_arg a_)
	{
		return _mm256_castpd256_pd128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_f64x8_f64x2(f64x8_arg a_)
	{
		return _mm512_castpd512_pd128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_i8x16_f64x2(i8x16_arg a_)
	{
		return _mm_castsi128_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_i16x8_f64x2(i16x8_arg a_)
	{
		return _mm_castsi128_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_i32x4_f64x2(i32x4_arg a_)
	{
		return _mm_castsi128_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_i64x2_f64x2(i64x2_arg a_)
	{
		return _mm_castsi128_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_i8x32_f64x2(i8x32_arg a_)
	{
		return _mm256_castpd256_pd128(_mm256_castsi256_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_i16x16_f64x2(i16x16_arg a_)
	{
		return _mm256_castpd256_pd128(_mm256_castsi256_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_i32x8_f64x2(i32x8_arg a_)
	{
		return _mm256_castpd256_pd128(_mm256_castsi256_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_i64x4_f64x2(i64x4_arg a_)
	{
		return _mm256_castpd256_pd128(_mm256_castsi256_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_i8x64_f64x2(i8x64_arg a_)
	{
		return _mm512_castpd512_pd128(_mm512_castsi512_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_i16x32_f64x2(i16x32_arg a_)
	{
		return _mm512_castpd512_pd128(_mm512_castsi512_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_i32x16_f64x2(i32x16_arg a_)
	{
		return _mm512_castpd512_pd128(_mm512_castsi512_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_i64x8_f64x2(i64x8_arg a_)
	{
		return _mm512_castpd512_pd128(_mm512_castsi512_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_u8x16_f64x2(u8x16_arg a_)
	{
		return _mm_castsi128_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_u16x8_f64x2(u16x8_arg a_)
	{
		return _mm_castsi128_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_u32x4_f64x2(u32x4_arg a_)
	{
		return _mm_castsi128_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_u64x2_f64x2(u64x2_arg a_)
	{
		return _mm_castsi128_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_u8x32_f64x2(u8x32_arg a_)
	{
		return _mm256_castpd256_pd128(_mm256_castsi256_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_u16x16_f64x2(u16x16_arg a_)
	{
		return _mm256_castpd256_pd128(_mm256_castsi256_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_u32x8_f64x2(u32x8_arg a_)
	{
		return _mm256_castpd256_pd128(_mm256_castsi256_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_u64x4_f64x2(u64x4_arg a_)
	{
		return _mm256_castpd256_pd128(_mm256_castsi256_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_u8x64_f64x2(u8x64_arg a_)
	{
		return _mm512_castpd512_pd128(_mm512_castsi512_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_u16x32_f64x2(u16x32_arg a_)
	{
		return _mm512_castpd512_pd128(_mm512_castsi512_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_u32x16_f64x2(u32x16_arg a_)
	{
		return _mm512_castpd512_pd128(_mm512_castsi512_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_u64x8_f64x2(u64x8_arg a_)
	{
		return _mm512_castpd512_pd128(_mm512_castsi512_pd(a_));
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_f32x4_f64x2(f32x4_arg a_)
	{
		return _mm_cvtps_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_f32x8_f64x2(f32x8_arg a_)
	{
		return _mm_cvtps_pd(_mm256_castps256_ps128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_f32x16_f64x2(f32x16_arg a_)
	{
		return _mm_cvtps_pd(_mm512_castps512_ps128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_f64x2_f64x2(f64x2_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_f64x4_f64x2(f64x4_arg a_)
	{
		return _mm256_castpd256_pd128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_f64x8_f64x2(f64x8_arg a_)
	{
		return _mm512_castpd512_pd128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_i8x16_f64x2(i8x16_arg a_)
	{
		return _mm_cvtepi64_pd(_mm_cvtepi8_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_i16x8_f64x2(i16x8_arg a_)
	{
		return _mm_cvtepi64_pd(_mm_cvtepi16_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_i32x4_f64x2(i32x4_arg a_)
	{
		return _mm_cvtepi32_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_i64x2_f64x2(i64x2_arg a_)
	{
		return _mm_cvtepi64_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_i8x32_f64x2(i8x32_arg a_)
	{
		return _mm_cvtepi64_pd(_mm_cvtepi8_epi64(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_i16x16_f64x2(i16x16_arg a_)
	{
		return _mm_cvtepi64_pd(_mm_cvtepi16_epi64(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_i32x8_f64x2(i32x8_arg a_)
	{
		return _mm_cvtepi32_pd(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_i64x4_f64x2(i64x4_arg a_)
	{
		return _mm_cvtepi64_pd(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_i8x64_f64x2(i8x64_arg a_)
	{
		return _mm_cvtepi64_pd(_mm_cvtepi8_epi64(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_i16x32_f64x2(i16x32_arg a_)
	{
		return _mm_cvtepi64_pd(_mm_cvtepi16_epi64(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_i32x16_f64x2(i32x16_arg a_)
	{
		return _mm_cvtepi32_pd(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_i64x8_f64x2(i64x8_arg a_)
	{
		return _mm_cvtepi64_pd(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_u8x16_f64x2(u8x16_arg a_)
	{
		return _mm_cvtepi64_pd(_mm_cvtepu8_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_u16x8_f64x2(u16x8_arg a_)
	{
		return _mm_cvtepi64_pd(_mm_cvtepu16_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_u32x4_f64x2(u32x4_arg a_)
	{
		return _mm_cvtepu32_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_u64x2_f64x2(u64x2_arg a_)
	{
		return _mm_cvtepu64_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_u8x32_f64x2(u8x32_arg a_)
	{
		return _mm_cvtepi64_pd(_mm_cvtepu8_epi64(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_u16x16_f64x2(u16x16_arg a_)
	{
		return _mm_cvtepi64_pd(_mm_cvtepu16_epi64(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_u32x8_f64x2(u32x8_arg a_)
	{
		return _mm_cvtepu32_pd(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_u64x4_f64x2(u64x4_arg a_)
	{
		return _mm_cvtepu64_pd(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_u8x64_f64x2(u8x64_arg a_)
	{
		return _mm_cvtepi64_pd(_mm_cvtepu8_epi64(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_u16x32_f64x2(u16x32_arg a_)
	{
		return _mm_cvtepi64_pd(_mm_cvtepu16_epi64(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_u32x16_f64x2(u32x16_arg a_)
	{
		return _mm_cvtepu32_pd(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_u64x8_f64x2(u64x8_arg a_)
	{
		return _mm_cvtepu64_pd(_mm512_castsi512_si128(a_));
	}
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cmpeq_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_)
	{
		return _mm_cmpeq_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cmpneq_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_)
	{
		return _mm_cmpneq_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cmpgt_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_)
	{
		return _mm_cmpgt_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cmplt_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_)
	{
		return _mm_cmplt_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cmpge_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_)
	{
		return _mm_cmpge_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cmple_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_)
	{
		return _mm_cmple_pd(lhs_, rhs_);
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 mul_all_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_)
	{
		return _mm_mul_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 negate_f64x2(EmuSIMD::f64x2_arg to_negate_)
	{
		return _mm_sub_pd(_mm_setzero_pd(), to_negate_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 add_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_)
	{
		return _mm_add_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 sub_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_)
	{
		return _mm_sub_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 mul_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_)
	{
		return _mm_mul_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 div_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_)
	{
		return _mm_div_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 addsub_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_)
	{
		return _mm_addsub_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 fmadd_f64x2(EmuSIMD::f64x2_arg a_, EmuSIMD::f64x2_arg b_, EmuSIMD::f64x2_arg c_)
	{
		return _mm_fmadd_pd(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 fmsub_f64x2(EmuSIMD::f64x2_arg a_, EmuSIMD::f64x2_arg b_, EmuSIMD::f64x2_arg c_)
	{
		return _mm_fmsub_pd(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 fnmadd_f64x2(EmuSIMD::f64x2_arg a_, EmuSIMD::f64x2_arg b_, EmuSIMD::f64x2_arg c_)
	{
		return _mm_fnmadd_pd(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 fnmsub_f64x2(EmuSIMD::f64x2_arg a_, EmuSIMD::f64x2_arg b_, EmuSIMD::f64x2_arg c_)
	{
		return _mm_fnmsub_pd(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 fmaddsub_f64x2(EmuSIMD::f64x2_arg a_, EmuSIMD::f64x2_arg b_, EmuSIMD::f64x2_arg c_)
	{
		return _mm_fmaddsub_pd(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 fmsubadd_f64x2(EmuSIMD::f64x2_arg a_, EmuSIMD::f64x2_arg b_, EmuSIMD::f64x2_arg c_)
	{
		return _mm_fmsubadd_pd(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 floor_f64x2(EmuSIMD::f64x2_arg to_floor_)
	{
		return _mm_floor_pd(to_floor_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 ceil_f64x2(EmuSIMD::f64x2_arg to_ceil_)
	{
		return _mm_ceil_pd(to_ceil_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 trunc_f64x2(EmuSIMD::f64x2_arg to_trunc_)
	{
		return _mm_trunc_pd(to_trunc_);
	}

	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 round_f64x2(EmuSIMD::f64x2_arg to_round_)
	{
		return _mm_round_pd(to_round_, RoundingFlag_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 mod_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_)
	{
		EmuSIMD::f64x2 res = _mm_div_pd(lhs_, rhs_);
		res = _mm_trunc_pd(res);
		return _mm_fnmadd_pd(res, rhs_, lhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 abs_f64x2(EmuSIMD::f64x2_arg in_)
	{
		EmuSIMD::f64x2 negative_mask = cmplt_f64x2(in_, setzero_f64x2());
		EmuSIMD::f64x2 out = _mm_and_pd(negative_mask, mul_all_f64x2(in_, set1_f64x2(-1)));
		return _mm_or_pd(out, _mm_andnot_pd(negative_mask, in_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2_arg sqrt_f64x2(EmuSIMD::f64x2_arg in_)
	{
		return _mm_sqrt_pd(in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 rsqrt_f64x2(EmuSIMD::f64x2_arg in_)
	{
		return div_f64x2(set1_f64x2(1.0), sqrt_f64x2(in_));
	}
#pragma endregion
}

#endif
