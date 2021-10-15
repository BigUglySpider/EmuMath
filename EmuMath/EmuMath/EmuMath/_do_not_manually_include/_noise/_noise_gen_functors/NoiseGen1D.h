#ifndef EMU_MATH_NOISE_GEN_FUNCTOR_1D_H_INC_
#define EMU_MATH_NOISE_GEN_FUNCTOR_1D_H_INC_ 1

#include "_common_noise_gen_functor_includes.h"

namespace EmuMath::Functors
{
	/// <summary>
	/// <para> Noise generation functor for 1-dimensional noise. </para>
	/// <para> Valid EmuMath::NoiseType arguments have been specialised for this functor. Invalid arguments will result in an empty struct. </para>
	/// </summary>
	template<EmuMath::NoiseType NoiseType_>
	struct make_noise_1d
	{
		static_assert(EmuMath::Validity::AssertValidNoiseType<NoiseType_>(), "Invalid NoiseType_ argument provided to EmuMath::Functors::make_noise_1d.");
		constexpr make_noise_1d()
		{
			static_assert(false, "Attempted to construct a make_noise_1d instance for a NoiseType that has not been implemented.");
		}
	};

	/// <summary> Functor to produce 1-dimensional value noise. Produced noise is in the range 0:1. </summary>
	template<>
	struct make_noise_1d<EmuMath::NoiseType::VALUE>
	{
		constexpr make_noise_1d()
		{
		}
		inline float operator()(float point_, float freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			std::int32_t mask_ = permutations_.MaxValue();
			point_ *= freq_;

			std::int32_t i = static_cast<std::int32_t>(floorf(point_)) & mask_;

			return permutations_[i] * (1.0f / mask_);
		}
		template<std::size_t Size_, typename T_>
		inline float operator()(const EmuMath::Vector<Size_, T_>& point_, float freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			return operator()(static_cast<float>(point_.at<0>()), freq_, permutations_);
		}
	};

	/// <summary> Functor to produce 1-dimensional smooth value noise. Produced noise is in the range 0:1. </summary>
	template<>
	struct make_noise_1d<EmuMath::NoiseType::VALUE_SMOOTH>
	{
		EmuCore::do_lerp<float, float, float> lerp_;
		constexpr make_noise_1d() : lerp_()
		{
		}
		inline float operator()(float point_, float freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			std::int32_t mask_ = permutations_.MaxValue();
			point_ *= freq_;

			std::int32_t i0 = static_cast<std::int32_t>(floorf(point_));
			float t_ = EmuMath::Functors::_underlying_noise_gen::SmoothT(point_ - i0);
			i0 &= mask_;
			std::int32_t i1 = (i0 + 1) & mask_;

			float perm_0_ = static_cast<float>(permutations_[i0]);
			float perm_1_ = static_cast<float>(permutations_[i1]);

			return lerp_(perm_0_, perm_1_, t_) * (1.0f / mask_);
		}
		template<std::size_t Size_, typename T_>
		inline float operator()(const EmuMath::Vector<Size_, T_>& point_, float freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			return operator()(static_cast<float>(point_.at<0>()), freq_, permutations_);
		}
	};

	/// <summary> Functor to produce 1-dimensional smooth perlin noise. Produced noise is in the range -0.5:0.5. </summary>
	template<>
	struct make_noise_1d<EmuMath::NoiseType::PERLIN>
	{
		static constexpr std::size_t _num_gradients = 2;
		static constexpr float _gradients[_num_gradients] = { 1.0f, -1.0f };
		static constexpr std::int32_t _gradient_mask = 1;

		EmuCore::do_lerp<float, float, float> lerp_;
		constexpr make_noise_1d() : lerp_()
		{
		}
		inline float operator()(float point_, float freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			std::int32_t mask_ = permutations_.MaxValue();
			point_ *= freq_;
			std::int32_t i0 = static_cast<std::int32_t>(floorf(point_));
			float t0_ = point_ - static_cast<float>(i0);
			float t1_ = t0_ - 1.0f;
			i0 &= mask_;
			std::int32_t i1 = (i0 + 1) & mask_;

			float gradient_0_ = _gradients[permutations_[i0] & _gradient_mask];
			float gradient_1_ = _gradients[permutations_[i1] & _gradient_mask];

			float val_0_ = gradient_0_ * t0_;
			float val_1_ = gradient_1_ * t1_;

			return lerp_(val_0_, val_1_, EmuMath::Functors::_underlying_noise_gen::SmoothT(t0_));
		}
		template<std::size_t Size_, typename T_>
		inline float operator()(const EmuMath::Vector<Size_, T_>& point_, float freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			return operator()(static_cast<float>(point_.at<0>()), freq_, permutations_);
		}
	};
}

#endif