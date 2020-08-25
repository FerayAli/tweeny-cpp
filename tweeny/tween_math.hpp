#pragma once
#include "tween_math.h"


namespace tweeny
{
namespace math
{

template<typename T>
T lerp(const T& start,
	   const decltype(start)& end,
	   float progress,
	   const ease_t& ease_func)
{
	if(progress <= 0.0f)
	{
		return start;
	}

	if(progress >= 1.0f)
	{
		return end;
	}

	auto completion = ease_func(progress);
	return start * (1.0f - completion) + (end * completion);
}


template<typename InType, typename OutType>
OutType range_map(const InType& in,
				  const decltype(in)& in_start,
				  const decltype(in)& in_end,
				  const OutType& out_start,
				  const decltype(out_start)& out_end,
				  const ease_t& ease_func)
{
	if(in <= in_start)
	{
		return out_start;
	}

	if(in >= in_end)
	{
		return out_end;
	}

	auto progress = in - in_start;
	auto in_factor = static_cast<float>(progress) / static_cast<float>(in_end - in_start);
	OutType result = lerp(out_start, out_end, in_factor, ease_func);
	return result;
}

} //end of namespace math
} //end of namespace tweeny
