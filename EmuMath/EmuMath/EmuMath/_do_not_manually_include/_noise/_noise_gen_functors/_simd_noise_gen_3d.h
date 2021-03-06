#ifndef EMU_MATH_FAST_NOISE_GEN_FUNCTOR_3D_H_INC_
#define EMU_MATH_FAST_NOISE_GEN_FUNCTOR_3D_H_INC_ 1

#include "_common_fast_noise_gen_functors_includes.h"
#include "../../../../EmuSIMD/SIMDHelpers.h"
#include "../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuMath::Validity
{
	template<class Reg_>
	[[nodiscard]] static constexpr inline bool _assert_fast_noise_3d_valid_register()
	{
		if constexpr (std::is_same_v<__m128, Reg_>)
		{
			return true;
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Reg_>(), "Provided an unsupported register for fast_noise_3d. There is only support for the following floating-point SIMD registers: __m128.");
			return false;
		}
	}
}

namespace EmuMath::Functors
{
	template<EmuMath::NoiseType NoiseType_, class Register_ = __m128>
	struct make_fast_noise_3d
	{
		static_assert(EmuMath::Validity::assert_valid_noise_type<NoiseType_>(), "Invalid NoiseType_ argument provided to EmuMath::Functors::make_fast_noise_3d.");
		static_assert(EmuMath::Validity::_assert_fast_noise_3d_valid_register<Register_>(), "Invalid Register_ type argument provided to EmuMath::Functors::make_fast_noise_3d.");
		constexpr make_fast_noise_3d()
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to construct a make_fast_noise_3d instance for a NoiseType that has not been implemented.");
		}
	};

	template<>
	struct make_fast_noise_3d<EmuMath::NoiseType::VALUE, __m128>
	{
		inline make_fast_noise_3d()
		{
		}

		[[nodiscard]] inline __m128 operator()
		(
			__m128 points_x_,
			__m128 points_y_,
			__m128 points_z_,
			__m128 freq_,
			__m128i permutations_mask_128_,
			const EmuMath::NoisePermutations& permutations_
		)
		{
			points_x_ = EmuSIMD::floor(EmuSIMD::mul_all(points_x_, freq_));
			points_y_ = EmuSIMD::floor(EmuSIMD::mul_all(points_y_, freq_));
			points_z_ = EmuSIMD::floor(EmuSIMD::mul_all(points_z_, freq_));

			__m128i ix_128i_ = EmuSIMD::bitwise_and(_mm_cvtps_epi32(points_x_), permutations_mask_128_);
			__m128i iy_128i_ = EmuSIMD::bitwise_and(_mm_cvtps_epi32(points_y_), permutations_mask_128_);
			__m128i iz_128i_ = EmuSIMD::bitwise_and(_mm_cvtps_epi32(points_z_), permutations_mask_128_);

			int ix_[4];
			int iy_[4];
			int iz_[4];
			EmuSIMD::store(iz_128i_, iz_);
			EmuSIMD::store(iy_128i_, iy_);
			EmuSIMD::store(ix_128i_, ix_);

			float perms_[4];
			std::size_t mask_ = static_cast<std::size_t>(permutations_.HighestStoredValue());
			for (std::size_t i = 0; i < 4; ++i)
			{
				std::size_t perm_x_ = static_cast<std::size_t>(permutations_[ix_[i]]);
				std::size_t perm_xyz_ = (static_cast<std::size_t>(permutations_[(perm_x_ + iy_[i]) & mask_]) + iz_[i]) & mask_;
				perms_[i] = static_cast<float>(permutations_[perm_xyz_]);
			}

			return EmuSIMD::div(EmuSIMD::load<__m128>(perms_), _mm_cvtepi32_ps(permutations_mask_128_));
		}
	};

	template<>
	struct make_fast_noise_3d<EmuMath::NoiseType::VALUE_SMOOTH, __m128>
	{
		inline make_fast_noise_3d() : smooth_t()
		{
		}

		[[nodiscard]] inline __m128 operator()
		(
			__m128 points_x_,
			__m128 points_y_,
			__m128 points_z_,
			__m128 freq_,
			__m128i permutations_mask_128_,
			const EmuMath::NoisePermutations& permutations_
		)
		{
			points_x_ = EmuSIMD::mul_all(points_x_, freq_);
			points_y_ = EmuSIMD::mul_all(points_y_, freq_);
			points_z_ = EmuSIMD::mul_all(points_z_, freq_);

			// Weightings and start of indices
			__m128 tx_ = EmuSIMD::floor(points_x_);
			__m128i ix_0_128i_ = _mm_cvtps_epi32(tx_);
			tx_ = smooth_t(EmuSIMD::sub(points_x_, tx_));

			__m128 ty_ = EmuSIMD::floor(points_y_);
			__m128i iy_0_128i_ = _mm_cvtps_epi32(ty_);
			ty_ = smooth_t(EmuSIMD::sub(points_y_, ty_));

			__m128 tz_ = EmuSIMD::floor(points_z_);
			__m128i iz_0_128i_ = _mm_cvtps_epi32(tz_);
			tz_ = smooth_t(EmuSIMD::sub(points_z_, tz_));

			// Mask indices and get alternatives to lerp
			ix_0_128i_ = EmuSIMD::bitwise_and(ix_0_128i_, permutations_mask_128_);
			iy_0_128i_ = EmuSIMD::bitwise_and(iy_0_128i_, permutations_mask_128_);
			iz_0_128i_ = EmuSIMD::bitwise_and(iz_0_128i_, permutations_mask_128_);
			__m128i one_128i_ = EmuSIMD::set1<__m128i, 32>(1);
			__m128i iz_1_128i_ = EmuSIMD::bitwise_and(EmuSIMD::add<32>(iz_0_128i_, one_128i_), permutations_mask_128_);
			__m128i iy_1_128i_ = EmuSIMD::bitwise_and(EmuSIMD::add<32>(iy_0_128i_, one_128i_), permutations_mask_128_);
			__m128i ix_1_128i_ = EmuSIMD::bitwise_and(EmuSIMD::add<32>(ix_0_128i_, one_128i_), permutations_mask_128_);

			// Store 0 indices
			int ix_0_[4];
			int iy_0_[4];
			int iz_0_[4];
			EmuSIMD::store(ix_0_128i_, ix_0_);
			EmuSIMD::store(iy_0_128i_, iy_0_);
			EmuSIMD::store(iz_0_128i_, iz_0_);

			// Store 1 indices
			int ix_1_[4];
			int iy_1_[4];
			int iz_1_[4];
			EmuSIMD::store(ix_1_128i_, ix_1_);
			EmuSIMD::store(iy_1_128i_, iy_1_);
			EmuSIMD::store(iz_1_128i_, iz_1_);

			float perms_000_[4];
			float perms_001_[4];
			float perms_010_[4];
			float perms_011_[4];
			float perms_100_[4];
			float perms_101_[4];
			float perms_110_[4];
			float perms_111_[4];
			std::size_t mask_ = permutations_.HighestStoredValue();

			for (std::size_t i = 0; i < 4; ++i)
			{
				// Forced store as size_t so we can handle width changes if EmuMath::NoisePermutationValue is not size_t width
				std::size_t perm_0_ = static_cast<std::size_t>(permutations_[ix_0_[i]]);
				std::size_t perm_1_ = static_cast<std::size_t>(permutations_[ix_1_[i]]);

				std::size_t perm_00_ = static_cast<std::size_t>(permutations_[(perm_0_ + iy_0_[i]) & mask_]);
				std::size_t perm_01_ = static_cast<std::size_t>(permutations_[(perm_0_ + iy_1_[i]) & mask_]);
				std::size_t perm_10_ = static_cast<std::size_t>(permutations_[(perm_1_ + iy_0_[i]) & mask_]);
				std::size_t perm_11_ = static_cast<std::size_t>(permutations_[(perm_1_ + iy_1_[i]) & mask_]);

				perms_000_[i] = static_cast<float>(permutations_[(perm_00_ + iz_0_[i]) & mask_]);
				perms_001_[i] = static_cast<float>(permutations_[(perm_00_ + iz_1_[i]) & mask_]);
				perms_010_[i] = static_cast<float>(permutations_[(perm_01_ + iz_0_[i]) & mask_]);
				perms_011_[i] = static_cast<float>(permutations_[(perm_01_ + iz_1_[i]) & mask_]);
				perms_100_[i] = static_cast<float>(permutations_[(perm_10_ + iz_0_[i]) & mask_]);
				perms_101_[i] = static_cast<float>(permutations_[(perm_10_ + iz_1_[i]) & mask_]);
				perms_110_[i] = static_cast<float>(permutations_[(perm_11_ + iz_0_[i]) & mask_]);
				perms_111_[i] = static_cast<float>(permutations_[(perm_11_ + iz_1_[i]) & mask_]);
			}

			// X-lerps
			__m128 lerp_0_ = EmuSIMD::fused_lerp(EmuSIMD::load<__m128>(perms_000_), EmuSIMD::load<__m128>(perms_100_), tx_);
			__m128 lerp_1_ = EmuSIMD::fused_lerp(EmuSIMD::load<__m128>(perms_010_), EmuSIMD::load<__m128>(perms_110_), tx_);
			__m128 lerp_2_ = EmuSIMD::fused_lerp(EmuSIMD::load<__m128>(perms_001_), EmuSIMD::load<__m128>(perms_101_), tx_);
			__m128 lerp_3_ = EmuSIMD::fused_lerp(EmuSIMD::load<__m128>(perms_011_), EmuSIMD::load<__m128>(perms_111_), tx_);

			// Y-lerps
			lerp_0_ = EmuSIMD::fused_lerp(lerp_0_, lerp_1_, ty_);
			lerp_2_ = EmuSIMD::fused_lerp(lerp_2_, lerp_3_, ty_);

			// Final Z-lerp and normalise
			return EmuSIMD::div(EmuSIMD::fused_lerp(lerp_0_, lerp_2_, tz_), _mm_cvtepi32_ps(permutations_mask_128_));
		}

		EmuMath::Functors::_underlying_noise_gen::_fast_smooth_t<__m128> smooth_t;
	};

	template<>
	struct make_fast_noise_3d<EmuMath::NoiseType::PERLIN, __m128>
	{
	public:
		using gradients = EmuMath::Functors::_underlying_noise_gen::perlin_gradients<3, __m128>;

		/// <summary> Gradients for calculation. W index contains a duplicate of the Z index. </summary>
		const typename gradients::register_array _gradients_128;
		static constexpr std::size_t _duplicate_gradient_index = 2;

		make_fast_noise_3d() :
			smooth_t(),
			ix_0(),
			ix_1(),
			iy_0(),
			iy_1(),
			iz_0(),
			iz_1(),
			_gradients_128(gradients::init_registers<_duplicate_gradient_index>())
		{
		}

		[[nodiscard]] inline __m128 operator()
		(
			__m128 points_x_,
			__m128 points_y_,
			__m128 points_z_,
			__m128 freq_,
			__m128i permutations_mask_128_,
			const EmuMath::NoisePermutations& permutations_
		)
		{
			points_x_ = EmuSIMD::mul_all(points_x_, freq_);
			points_y_ = EmuSIMD::mul_all(points_y_, freq_);
			points_z_ = EmuSIMD::mul_all(points_z_, freq_);

			// temp_0: floor(x)...
			__m128 temp_0_128_ = EmuSIMD::floor(points_x_);
			__m128 tx_0_128_ = EmuSIMD::sub(points_x_, temp_0_128_);
			__m128i ix_0_128_ = _mm_cvtps_epi32(temp_0_128_);

			// temp_0: floor(y)...
			temp_0_128_ = EmuSIMD::floor(points_y_);
			__m128 ty_0_128_ = EmuSIMD::sub(points_y_, temp_0_128_);
			__m128i iy_0_128_ = _mm_cvtps_epi32(temp_0_128_);

			// temp_0: floor(z)...
			temp_0_128_ = EmuSIMD::floor(points_z_);
			__m128 tz_0_128_ = EmuSIMD::sub(points_z_, temp_0_128_);
			__m128i iz_0_128_ = _mm_cvtps_epi32(temp_0_128_);

			// Get secondary lerp weightings
			// --- temp_0: { 1, 1, 1, 1 }
			temp_0_128_ = _mm_set1_ps(1.0f);
			__m128 tx_1_128_ = EmuSIMD::sub(tx_0_128_, temp_0_128_);
			__m128 ty_1_128_ = EmuSIMD::sub(ty_0_128_, temp_0_128_);
			__m128 tz_1_128_ = EmuSIMD::sub(tz_0_128_, temp_0_128_);

			// Mask and find secondaries to permutation indices
			ix_0_128_ = EmuSIMD::bitwise_and(permutations_mask_128_, ix_0_128_);
			iy_0_128_ = EmuSIMD::bitwise_and(permutations_mask_128_, iy_0_128_);
			iz_0_128_ = EmuSIMD::bitwise_and(permutations_mask_128_, iz_0_128_);
			__m128i one_128i_ = _mm_cvtps_epi32(temp_0_128_);
			__m128i ix_1_128_ = EmuSIMD::bitwise_and(permutations_mask_128_, EmuSIMD::add<32>(ix_0_128_, one_128i_));
			__m128i iy_1_128_ = EmuSIMD::bitwise_and(permutations_mask_128_, EmuSIMD::add<32>(iy_0_128_, one_128i_));
			__m128i iz_1_128_ = EmuSIMD::bitwise_and(permutations_mask_128_, EmuSIMD::add<32>(iz_0_128_, one_128i_));

			// Store last calculated values first for best chance at a cache hit
			EmuSIMD::store(iz_1_128_, iz_1.data());
			EmuSIMD::store(iz_0_128_, iz_0.data());

			EmuSIMD::store(iy_1_128_, iy_1.data());
			EmuSIMD::store(iy_0_128_, iy_0.data());

			EmuSIMD::store(ix_1_128_, ix_1.data());
			EmuSIMD::store(ix_0_128_, ix_0.data());

			// Find the gradients we'll be making use of in interpolations
			// --- No benefit from manually inlining this part within the function in release, so best to just keep this function cleaner
			__m128 vals_000_, vals_001_, vals_010_, vals_011_, vals_100_, vals_101_, vals_110_, vals_111_;
			_calculate_values_to_lerp
			(
				permutations_,
				tx_0_128_,
				ty_0_128_,
				tz_0_128_,
				tx_1_128_,
				ty_1_128_,
				tz_1_128_,
				vals_000_,
				vals_001_,
				vals_010_,
				vals_011_,
				vals_100_,
				vals_101_,
				vals_110_,
				vals_111_
			);
			
			// Apply smooth (or fade) function to our weightings
			tx_0_128_ = smooth_t(tx_0_128_);
			ty_0_128_ = smooth_t(ty_0_128_);
			tz_0_128_ = smooth_t(tz_0_128_);

			// Primary lerps
			// --- Use fused lerps to skip 7 floating-point rounding operations
			__m128 lerp_0_ = EmuSIMD::fused_lerp(vals_000_, vals_100_, tx_0_128_);
			__m128 lerp_1_ = EmuSIMD::fused_lerp(vals_010_, vals_110_, tx_0_128_);
			__m128 lerp_2_ = EmuSIMD::fused_lerp(vals_001_, vals_101_, tx_0_128_);
			__m128 lerp_3_ = EmuSIMD::fused_lerp(vals_011_, vals_111_, tx_0_128_);

			// Secondary lerps
			lerp_0_ = EmuSIMD::fused_lerp(lerp_0_, lerp_1_, ty_0_128_);
			lerp_2_ = EmuSIMD::fused_lerp(lerp_2_, lerp_3_, ty_0_128_);

			// Final tertiary lerp
			return EmuSIMD::fused_lerp(lerp_0_, lerp_2_, tz_0_128_);
		}

	private:
		inline void _calculate_values_to_lerp
		(
			const EmuMath::NoisePermutations& permutations_,
			__m128 tx_0_,
			__m128 ty_0_,
			__m128 tz_0_,
			__m128 tx_1_,
			__m128 ty_1_,
			__m128 tz_1_,
			__m128& vals_000_,
			__m128& vals_001_,
			__m128& vals_010_,
			__m128& vals_011_,
			__m128& vals_100_,
			__m128& vals_101_,
			__m128& vals_110_,
			__m128& vals_111_
		)
		{
			// Find our permutation values; all will be initialised in the upcoming loop
			std::size_t perm_000_[4];
			std::size_t perm_001_[4];
			std::size_t perm_010_[4];
			std::size_t perm_011_[4];
			std::size_t perm_100_[4];
			std::size_t perm_101_[4];
			std::size_t perm_110_[4];
			std::size_t perm_111_[4];
			std::size_t perm_0_, perm_1_, perm_00_, perm_01_, perm_10_, perm_11_;
			std::size_t mask_ = static_cast<std::size_t>(permutations_.HighestStoredValue());

			// One permutation per value per item; since we're working with 4 outputs, this means we need to loop 4 times
			for (std::size_t i = 0; i < 4; ++i)
			{
				perm_0_ = static_cast<std::size_t>(permutations_[ix_0[i]]);
				perm_1_ = static_cast<std::size_t>(permutations_[ix_1[i]]);

				perm_00_ = static_cast<std::size_t>(permutations_[(perm_0_ + iy_0[i]) & mask_]);
				perm_01_ = static_cast<std::size_t>(permutations_[(perm_0_ + iy_1[i]) & mask_]);
				perm_10_ = static_cast<std::size_t>(permutations_[(perm_1_ + iy_0[i]) & mask_]);
				perm_11_ = static_cast<std::size_t>(permutations_[(perm_1_ + iy_1[i]) & mask_]);

				perm_000_[i] = static_cast<std::size_t>(permutations_[(perm_00_ + iz_0[i]) & mask_]) & gradients::mask;
				perm_001_[i] = static_cast<std::size_t>(permutations_[(perm_00_ + iz_1[i]) & mask_]) & gradients::mask;
				perm_010_[i] = static_cast<std::size_t>(permutations_[(perm_01_ + iz_0[i]) & mask_]) & gradients::mask;
				perm_011_[i] = static_cast<std::size_t>(permutations_[(perm_01_ + iz_1[i]) & mask_]) & gradients::mask;
				perm_100_[i] = static_cast<std::size_t>(permutations_[(perm_10_ + iz_0[i]) & mask_]) & gradients::mask;
				perm_101_[i] = static_cast<std::size_t>(permutations_[(perm_10_ + iz_1[i]) & mask_]) & gradients::mask;
				perm_110_[i] = static_cast<std::size_t>(permutations_[(perm_11_ + iz_0[i]) & mask_]) & gradients::mask;
				perm_111_[i] = static_cast<std::size_t>(permutations_[(perm_11_ + iz_1[i]) & mask_]) & gradients::mask;
			}

			// Use discovered permutations to form gradient dot products for our output values
			// 000
			__m128 gradient_0_ = _gradients_128[perm_000_[0]];
			__m128 gradient_1_ = _gradients_128[perm_000_[1]];
			__m128 gradient_2_ = _gradients_128[perm_000_[2]];
			__m128 gradient_3_ = _gradients_128[perm_000_[3]];
			
			// X - Pre-store the Y components in the indices [1] and [3] from each temp shuffle
			__m128 temp_0_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_0_, gradient_1_);
			__m128 temp_1_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_2_, gradient_3_);
			__m128 row_ = EmuSIMD::shuffle<0, 2, 0, 2>(temp_0_, temp_1_);
			vals_000_ = _mm_mul_ps(row_, tx_0_);
			
			// Y - Already prestored Y in previous two shuffles, so we can form row straight away
			row_ = EmuSIMD::shuffle<1, 3, 1, 3>(temp_0_, temp_1_);
			vals_000_ = _mm_add_ps(vals_000_, _mm_mul_ps(row_, ty_0_));
			
			// Z - One more batch of shuffles to extract the Z-coordinates of the gradients
			// --- We can, however, take advantage of the duplicate Z in the W-element to use blends and a "shuffle" (optimised by templates)
			temp_0_ = EmuSIMD::blend<0, 0, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::blend<0, 0, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<2, 3, 2, 3>(temp_0_, temp_1_);
			vals_000_ = _mm_add_ps(vals_000_, _mm_mul_ps(row_, tz_0_));
			
			// ABOVE COMMENTS APPLY TO SUBSEQUENT OUTPUTS
			// 001
			gradient_0_ = _gradients_128[perm_001_[0]];
			gradient_1_ = _gradients_128[perm_001_[1]];
			gradient_2_ = _gradients_128[perm_001_[2]];
			gradient_3_ = _gradients_128[perm_001_[3]];
			
			// X
			temp_0_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<0, 2, 0, 2>(temp_0_, temp_1_);
			vals_001_ = _mm_mul_ps(row_, tx_0_);
			
			// Y
			row_ = EmuSIMD::shuffle<1, 3, 1, 3>(temp_0_, temp_1_);
			vals_001_ = _mm_add_ps(vals_001_, _mm_mul_ps(row_, ty_0_));
			
			// Z
			temp_0_ = EmuSIMD::blend<0, 0, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::blend<0, 0, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<2, 3, 2, 3>(temp_0_, temp_1_);
			vals_001_ = _mm_add_ps(vals_001_, _mm_mul_ps(row_, tz_1_));
			
			// 010
			gradient_0_ = _gradients_128[perm_010_[0]];
			gradient_1_ = _gradients_128[perm_010_[1]];
			gradient_2_ = _gradients_128[perm_010_[2]];
			gradient_3_ = _gradients_128[perm_010_[3]];
			
			// X
			temp_0_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<0, 2, 0, 2>(temp_0_, temp_1_);
			vals_010_ = _mm_mul_ps(row_, tx_0_);
			
			// Y
			row_ = EmuSIMD::shuffle<1, 3, 1, 3>(temp_0_, temp_1_);
			vals_010_ = _mm_add_ps(vals_010_, _mm_mul_ps(row_, ty_1_));
			
			// Z
			temp_0_ = EmuSIMD::blend<0, 0, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::blend<0, 0, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<2, 3, 2, 3>(temp_0_, temp_1_);
			vals_010_ = _mm_add_ps(vals_010_, _mm_mul_ps(row_, tz_0_));
			
			// 011
			gradient_0_ = _gradients_128[perm_011_[0]];
			gradient_1_ = _gradients_128[perm_011_[1]];
			gradient_2_ = _gradients_128[perm_011_[2]];
			gradient_3_ = _gradients_128[perm_011_[3]];
			
			// X
			temp_0_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<0, 2, 0, 2>(temp_0_, temp_1_);
			vals_011_ = _mm_mul_ps(row_, tx_0_);
			
			// Y
			row_ = EmuSIMD::shuffle<1, 3, 1, 3>(temp_0_, temp_1_);
			vals_011_ = _mm_add_ps(vals_011_, _mm_mul_ps(row_, ty_1_));
			
			// Z
			temp_0_ = EmuSIMD::blend<0, 0, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::blend<0, 0, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<2, 3, 2, 3>(temp_0_, temp_1_);
			vals_011_ = _mm_add_ps(vals_011_, _mm_mul_ps(row_, tz_1_));
			
			// 100
			gradient_0_ = _gradients_128[perm_100_[0]];
			gradient_1_ = _gradients_128[perm_100_[1]];
			gradient_2_ = _gradients_128[perm_100_[2]];
			gradient_3_ = _gradients_128[perm_100_[3]];
			
			// X
			temp_0_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<0, 2, 0, 2>(temp_0_, temp_1_);
			vals_100_ = _mm_mul_ps(row_, tx_1_);
			
			// Y
			row_ = EmuSIMD::shuffle<1, 3, 1, 3>(temp_0_, temp_1_);
			vals_100_ = _mm_add_ps(vals_100_, _mm_mul_ps(row_, ty_0_));
			
			// Z
			temp_0_ = EmuSIMD::blend<0, 0, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::blend<0, 0, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<2, 3, 2, 3>(temp_0_, temp_1_);
			vals_100_ = _mm_add_ps(vals_100_, _mm_mul_ps(row_, tz_0_));
			
			// 101
			gradient_0_ = _gradients_128[perm_101_[0]];
			gradient_1_ = _gradients_128[perm_101_[1]];
			gradient_2_ = _gradients_128[perm_101_[2]];
			gradient_3_ = _gradients_128[perm_101_[3]];
			
			// X
			temp_0_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<0, 2, 0, 2>(temp_0_, temp_1_);
			vals_101_ = _mm_mul_ps(row_, tx_1_);
			
			// Y
			row_ = EmuSIMD::shuffle<1, 3, 1, 3>(temp_0_, temp_1_);
			vals_101_ = _mm_add_ps(vals_101_, _mm_mul_ps(row_, ty_0_));
			
			// Z
			temp_0_ = EmuSIMD::blend<0, 0, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::blend<0, 0, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<2, 3, 2, 3>(temp_0_, temp_1_);
			vals_101_ = _mm_add_ps(vals_101_, _mm_mul_ps(row_, tz_1_));
			
			// 110
			gradient_0_ = _gradients_128[perm_110_[0]];
			gradient_1_ = _gradients_128[perm_110_[1]];
			gradient_2_ = _gradients_128[perm_110_[2]];
			gradient_3_ = _gradients_128[perm_110_[3]];
			
			// X
			temp_0_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<0, 2, 0, 2>(temp_0_, temp_1_);
			vals_110_ = _mm_mul_ps(row_, tx_1_);
			
			// Y
			row_ = EmuSIMD::shuffle<1, 3, 1, 3>(temp_0_, temp_1_);
			vals_110_ = _mm_add_ps(vals_110_, _mm_mul_ps(row_, ty_1_));
			
			// Z
			temp_0_ = EmuSIMD::blend<0, 0, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::blend<0, 0, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<2, 3, 2, 3>(temp_0_, temp_1_);
			vals_110_ = _mm_add_ps(vals_110_, _mm_mul_ps(row_, tz_0_));
			
			// 111
			gradient_0_ = _gradients_128[perm_111_[0]];
			gradient_1_ = _gradients_128[perm_111_[1]];
			gradient_2_ = _gradients_128[perm_111_[2]];
			gradient_3_ = _gradients_128[perm_111_[3]];
			
			// X
			temp_0_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<0, 2, 0, 2>(temp_0_, temp_1_);
			vals_111_ = _mm_mul_ps(row_, tx_1_);
			
			// Y
			row_ = EmuSIMD::shuffle<1, 3, 1, 3>(temp_0_, temp_1_);
			vals_111_ = _mm_add_ps(vals_111_, _mm_mul_ps(row_, ty_1_));
			
			// Z
			temp_0_ = EmuSIMD::blend<0, 0, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::blend<0, 0, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<2, 3, 2, 3>(temp_0_, temp_1_);
			vals_111_ = _mm_add_ps(vals_111_, _mm_mul_ps(row_, tz_1_));
		}


		std::array<int, 4> ix_0;
		std::array<int, 4> ix_1;
		std::array<int, 4> iy_0;
		std::array<int, 4> iy_1;
		std::array<int, 4> iz_0;
		std::array<int, 4> iz_1;
		EmuMath::Functors::_underlying_noise_gen::_fast_smooth_t<__m128> smooth_t;
	};
}

#endif
