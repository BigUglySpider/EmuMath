#ifndef EMU_SIMD_HELPERS_TEMPLATE_BLEND_H_INC_
#define EMU_SIMD_HELPERS_TEMPLATE_BLEND_H_INC_ 1

#include "_underlying_template_helpers/_simd_helpers_underlying_blend.h"
#include "../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuSIMD
{
	template<std::size_t PerElementWidthIfInt_ = 32, class Register_>
	[[nodiscard]] inline Register_ blendv(Register_ a_, Register_ b_, Register_ mask_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_blendv<PerElementWidthIfInt_>(a_, b_, mask_);
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::blendv with an unsupported or unrecognised type as the passed Register_.");
		}
	}

	template<bool...IndexUsesB_, class Register_>
	[[nodiscard]] inline Register_ blend(Register_ a_, Register_ b_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_blend<IndexUsesB_...>(a_, b_);
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::blend with an unsupported or unrecognised type as the passed Register_.");
		}
	}
}

#endif
