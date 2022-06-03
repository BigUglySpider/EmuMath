#ifndef EMU_SIMD_GENERIC_FUNCS_U8X64_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_U8X64_H_INC_ 1

#include "_common_generic_func_helpers.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 set_i8x64
	(
		std::uint8_t e0, std::uint8_t e1, std::uint8_t e2, std::uint8_t e3, std::uint8_t e4, std::uint8_t e5, std::uint8_t e6, std::uint8_t e7,
		std::uint8_t e8, std::uint8_t e9, std::uint8_t e10, std::uint8_t e11, std::uint8_t e12, std::uint8_t e13, std::uint8_t e14, std::uint8_t e15,
		std::uint8_t e16, std::uint8_t e17, std::uint8_t e18, std::uint8_t e19, std::uint8_t e20, std::uint8_t e21, std::uint8_t e22, std::uint8_t e23,
		std::uint8_t e24, std::uint8_t e25, std::uint8_t e26, std::uint8_t e27, std::uint8_t e28, std::uint8_t e29, std::uint8_t e30, std::uint8_t e31,
		std::uint8_t e32, std::uint8_t e33, std::uint8_t e34, std::uint8_t e35, std::uint8_t e36, std::uint8_t e37, std::uint8_t e38, std::uint8_t e39,
		std::uint8_t e40, std::uint8_t e41, std::uint8_t e42, std::uint8_t e43, std::uint8_t e44, std::uint8_t e45, std::uint8_t e46, std::uint8_t e47,
		std::uint8_t e48, std::uint8_t e49, std::uint8_t e50, std::uint8_t e51, std::uint8_t e52, std::uint8_t e53, std::uint8_t e54, std::uint8_t e55,
		std::uint8_t e56, std::uint8_t e57, std::uint8_t e58, std::uint8_t e59, std::uint8_t e60, std::uint8_t e61, std::uint8_t e62, std::uint8_t e63
	)
	{
		return _mm512_set_epi8
		(
			e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31,
			e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e60, e61, e62, e63
		);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 setr_i8x64
	(
		std::uint8_t e0, std::uint8_t e1, std::uint8_t e2, std::uint8_t e3, std::uint8_t e4, std::uint8_t e5, std::uint8_t e6, std::uint8_t e7,
		std::uint8_t e8, std::uint8_t e9, std::uint8_t e10, std::uint8_t e11, std::uint8_t e12, std::uint8_t e13, std::uint8_t e14, std::uint8_t e15,
		std::uint8_t e16, std::uint8_t e17, std::uint8_t e18, std::uint8_t e19, std::uint8_t e20, std::uint8_t e21, std::uint8_t e22, std::uint8_t e23,
		std::uint8_t e24, std::uint8_t e25, std::uint8_t e26, std::uint8_t e27, std::uint8_t e28, std::uint8_t e29, std::uint8_t e30, std::uint8_t e31,
		std::uint8_t e32, std::uint8_t e33, std::uint8_t e34, std::uint8_t e35, std::uint8_t e36, std::uint8_t e37, std::uint8_t e38, std::uint8_t e39,
		std::uint8_t e40, std::uint8_t e41, std::uint8_t e42, std::uint8_t e43, std::uint8_t e44, std::uint8_t e45, std::uint8_t e46, std::uint8_t e47,
		std::uint8_t e48, std::uint8_t e49, std::uint8_t e50, std::uint8_t e51, std::uint8_t e52, std::uint8_t e53, std::uint8_t e54, std::uint8_t e55,
		std::uint8_t e56, std::uint8_t e57, std::uint8_t e58, std::uint8_t e59, std::uint8_t e60, std::uint8_t e61, std::uint8_t e62, std::uint8_t e63
	)
	{
		return _mm512_setr_epi8
		(
			e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31,
			e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e60, e61, e62, e63
		);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 set1_u8x64(std::uint8_t all_)
	{
		return _mm512_set1_epi8(all_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 load_u8x64(const std::uint8_t* p_to_load_)
	{
		return _mm512_load_si512(p_to_load_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 setzero_u8x64()
	{
		return _mm512_setzero_si512();
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_u8x64(std::uint8_t* p_out_, u8x64_arg a_)
	{
		_mm512_store_si512(reinterpret_cast<__m256i*>(p_out_), a_);
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_f32x4_u8x64(f32x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm_castps_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_f32x8_u8x64(f32x8_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_castps_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_f32x16_u8x64(f32x16_arg a_)
	{
		return _mm512_castps_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_f64x2_u8x64(f64x2_arg a_)
	{
		return _mm512_castsi128_si512(_mm_castpd_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_f64x4_u8x64(f64x4_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_castpd_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_f64x8_u8x64(f64x8_arg a_)
	{
		return _mm512_castpd_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_i8x16_u8x64(i8x16_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_i16x8_u8x64(i16x8_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_i32x4_u8x64(i32x4_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_i64x2_u8x64(i64x2_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_i8x32_u8x64(i8x32_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_i16x16_u8x64(i16x16_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_i32x8_u8x64(i32x8_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_i64x4_u8x64(i64x4_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_i8x64_u8x64(i8x64_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_i16x32_u8x64(i16x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_i32x16_u8x64(i32x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_i64x8_u8x64(i64x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_u8x16_u8x64(u8x16_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_u16x8_u8x64(u16x8_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_u32x4_u8x64(u32x4_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_u64x2_u8x64(u64x2_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_u8x32_u8x64(u8x32_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_u16x16_u8x64(u16x16_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_u32x8_u8x64(u32x8_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_u64x4_u8x64(u64x4_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_u8x64_u8x64(u8x64_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_u16x32_u8x64(u16x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_u32x16_u8x64(u32x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_u64x8_u8x64(u64x8_arg a_)
	{
		return a_;
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_f32x4_u8x64(f32x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm_cvtepi32_epi8(_mm_cvtps_epi32(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_f32x8_u8x64(f32x8_arg a_)
	{
		return _mm512_castsi128_si512(_mm256_cvtepi32_epi8(_mm256_cvtps_epi32(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_f32x16_u8x64(f32x16_arg a_)
	{
		return _mm512_castsi128_si512(_mm512_cvtepi32_epi8(_mm512_cvtps_epi32(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_f64x2_u8x64(f64x2_arg a_)
	{
		return _mm512_castsi128_si512(_mm_cvtepi64_epi8(_mm_cvtpd_epi64(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_f64x4_u8x64(f64x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm256_cvtepi64_epi8(_mm256_cvtpd_epi64(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_f64x8_u8x64(f64x8_arg a_)
	{
		return _mm512_castsi128_si512(_mm512_cvtepi64_epi8(_mm512_cvtpd_epi64(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_i8x16_u8x64(i8x16_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_i16x8_u8x64(i16x8_arg a_)
	{
		return _mm512_castsi128_si512(_mm_cvtepi16_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_i32x4_u8x64(i32x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm_cvtepi32_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_i64x2_u8x64(i64x2_arg a_)
	{
		return _mm512_castsi128_si512(_mm_cvtepi64_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_i8x32_u8x64(i8x32_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_i16x16_u8x64(i16x16_arg a_)
	{
		return _mm512_castsi128_si512(_mm256_cvtepi16_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_i32x8_u8x64(i32x8_arg a_)
	{
		return _mm512_castsi128_si512(_mm256_cvtepi32_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_i64x4_u8x64(i64x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm256_cvtepi64_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_i8x64_u8x64(i8x64_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_i16x32_u8x64(i16x32_arg a_)
	{
		return _mm512_castsi256_si512(_mm512_cvtepi16_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_i32x16_u8x64(i32x16_arg a_)
	{
		return _mm512_castsi128_si512(_mm512_cvtepi32_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_i64x8_u8x64(i64x8_arg a_)
	{
		return _mm512_castsi128_si512(_mm512_cvtepi64_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_u8x16_u8x64(u8x16_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_u16x8_u8x64(u16x8_arg a_)
	{
		return _mm512_castsi128_si512(_mm_cvtepi16_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_u32x4_u8x64(u32x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm_cvtepi32_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_u64x2_u8x64(u64x2_arg a_)
	{
		return _mm512_castsi128_si512(_mm_cvtepi64_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_u8x32_u8x64(u8x32_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_u16x16_u8x64(u16x16_arg a_)
	{
		return _mm512_castsi128_si512(_mm256_cvtepi16_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_u32x8_u8x64(u32x8_arg a_)
	{
		return _mm512_castsi128_si512(_mm256_cvtepi32_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_u64x4_u8x64(u64x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm256_cvtepi64_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_u8x64_u8x64(u8x64_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_u16x32_u8x64(u16x32_arg a_)
	{
		return _mm512_castsi256_si512(_mm512_cvtepi16_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_u32x16_u8x64(u32x16_arg a_)
	{
		return _mm512_castsi128_si512(_mm512_cvtepi32_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_u64x8_u8x64(u64x8_arg a_)
	{
		return _mm512_castsi128_si512(_mm512_cvtepi64_epi8(a_));
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 mul_all_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
		EmuSIMD::u8x64 even_bytes = _mm512_mullo_epi16(lhs_, rhs_);
		EmuSIMD::u8x64 odd_bytes = _mm512_mullo_epi16(_mm512_srli_epi16(lhs_, 8), _mm512_srli_epi16(rhs_, 8));
		return _mm512_or_si512(_mm512_slli_epi16(odd_bytes, 8), _mm512_srli_epi16(_mm512_slli_epi16(even_bytes, 8), 8));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 negate_u8x64(EmuSIMD::u8x64_arg to_negate_)
	{
		return _mm512_sub_epi8(_mm512_setzero_si512(), to_negate_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 add_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
		return _mm512_add_epi8(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 sub_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
		return _mm512_sub_epi8(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 mul_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
		return _mm512_mul_epu32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 div_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
		return _mm512_div_epu8(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 addsub_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
		constexpr std::uint8_t byte_mask = static_cast<std::uint8_t>(0xFF);
		const EmuSIMD::u8x64 mask = _mm512_set_epi8
		(
			byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0,
			byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0,
			byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0,
			byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0
		);
		EmuSIMD::u8x64 out = _mm512_add_epi8(lhs_, _mm512_and_si512(mask, rhs_));
		return _mm512_sub_epi8(lhs_, _mm512_andnot_si512(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 subadd_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
		constexpr std::uint8_t byte_mask = static_cast<std::uint8_t>(0xFF);
		const EmuSIMD::u8x64 mask = _mm512_set_epi8
		(
			byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0,
			byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0,
			byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0,
			byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0
		);
		EmuSIMD::u8x64 out = _mm512_sub_epi8(lhs_, _mm512_and_si512(mask, rhs_));
		return _mm512_add_epi8(lhs_, _mm512_andnot_si512(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 fmadd_u8x64(EmuSIMD::u8x64_arg a_, EmuSIMD::u8x64_arg b_, EmuSIMD::u8x64_arg c_)
	{
		return _mm512_add_epi8(mul_all_u8x64(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 fmsub_u8x64(EmuSIMD::u8x64_arg a_, EmuSIMD::u8x64_arg b_, EmuSIMD::u8x64_arg c_)
	{
		return _mm512_sub_epi8(mul_all_u8x64(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 fnmadd_u8x64(EmuSIMD::u8x64_arg a_, EmuSIMD::u8x64_arg b_, EmuSIMD::u8x64_arg c_)
	{
		return _mm512_add_epi8(mul_all_u8x64(negate_u8x64(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 fnmsub_u8x64(EmuSIMD::u8x64_arg a_, EmuSIMD::u8x64_arg b_, EmuSIMD::u8x64_arg c_)
	{
		return _mm512_sub_epi8(mul_all_u8x64(negate_u8x64(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 fmaddsub_u8x64(EmuSIMD::u8x64_arg a_, EmuSIMD::u8x64_arg b_, EmuSIMD::u8x64_arg c_)
	{
		return addsub_u8x64(mul_all_u8x64(negate_u8x64(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 fmsubadd_u8x64(EmuSIMD::u8x64_arg a_, EmuSIMD::u8x64_arg b_, EmuSIMD::u8x64_arg c_)
	{
		return subadd_u8x64(mul_all_u8x64(negate_u8x64(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 floor_u8x64(EmuSIMD::u8x64_arg to_floor_)
	{
		return to_floor_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 ceil_u8x64(EmuSIMD::u8x64_arg to_ceil_)
	{
		return to_ceil_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 trunc_u8x64(EmuSIMD::u8x64_arg to_trunc_)
	{
		return to_trunc_;
	}

	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 round_u8x64(EmuSIMD::u8x64_arg to_round_)
	{
		return to_round_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 mod_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
		return _mm512_rem_epu8(lhs_, rhs_);
	}
#pragma endregion
}

#endif
