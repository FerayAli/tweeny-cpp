#pragma once
#include "tween_common.h"
#include "tween_ease.h"
#include <algorithm>

namespace tweeny
{
namespace math
{

//---------------------------------------------------------------------------------------
/// Return a value between 'start' and 'end', based on progress(0.0f - 1.0f)
//---------------------------------------------------------------------------------------
template<typename T>
T lerp(const T& start,
	   const decltype(start)& end,
	   float progress,
	   const ease_t& ease_func = ease::linear);

//---------------------------------------------------------------------------------------
/// Return a value between 'out_start' and 'out_end',
/// based on percent of 'in' between 'in_start' and 'in_end'.
//---------------------------------------------------------------------------------------
template<typename InType, typename OutType>
OutType range_map(const InType& in,
				  const decltype(in)& in_start,
				  const decltype(in)& in_end,
				  const OutType& out_start,
				  const decltype(out_start)& out_end,
				  const ease_t& ease_func = ease::linear);

//Make things constexpr
float square(float x, int n);
float flip(float x);
float mix(float a, float b, float weight, float t);
float crossfade(float a, float b, float t);
float scale(float a, float t);
float reverse_scale(float a, float t);
float arch(float t);

} //end of namespace math
} //end of namespace tweeny
