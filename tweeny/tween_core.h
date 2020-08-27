#pragma once
#include "tween_common.h"
#include "tween_updater.h"
#include "tween_private.h"
#include "tween_ease.h"
#include <vector>

namespace tweeny
{

template<typename TargetType>
tween_value<TargetType>
tween_value_from_to(const TargetType& begin,
					const TargetType& end,
					const duration_t& duration,
					const ease_t& ease_func = ease::linear);

template<typename TargetType>
tween_action
tween_from_to(TargetType& object,
			  const decltype(std::decay_t<TargetType>(object))& begin,
			  const decltype(std::decay_t<TargetType>(object))& end,
			  const duration_t& duration,
			  const sentinel_t& sentinel,
			  const ease_t& ease_func = ease::linear);

template<typename TargetType>
tween_action
tween_from_to(const std::shared_ptr<TargetType>& object,
			  const decltype(std::decay_t<TargetType>(*object))& begin,
			  const decltype(std::decay_t<TargetType>(*object))& end,
			  const duration_t& duration,
			  const ease_t& ease_func = ease::linear);


template<typename T, typename U>
tween_action
tween_to(T& object,
		 const U& end,
		 const duration_t& duration,
		 const sentinel_t& sentinel,
		 const ease_t& ease_func = ease::linear);

template<typename TargetType>
tween_action
tween_to(const std::shared_ptr<TargetType>& object,
		 const decltype(std::decay_t<TargetType>(*object))& end,
		 const duration_t& duration,
		 const ease_t& ease_func = ease::linear);


template<typename TargetType>
tween_action
tween_by(TargetType& object,
		 const decltype(std::decay_t<TargetType>(object))& amount,
		 const duration_t duration,
		 const sentinel_t sentinel,
		 const ease_t& ease_func = ease::linear);

template<typename TargetType>
tween_action
tween_by(const std::shared_ptr<TargetType>& object,
		 const decltype(std::decay_t<TargetType>(*object))& amount,
		 const duration_t& duration,
		 const ease_t& ease_func = ease::linear);


template<typename TargetType>
tween_action sequence(const std::vector<tween_impl<TargetType>>& tweenies);

tween_action sequence(const std::vector<std::shared_ptr<tween_base_impl>>& tweenies);

template<typename T1, typename T2, typename... TweenType>
tween_action sequence(const T1& tween1, const T2& tween2, const TweenType&... tween);


template<typename TargetType>
tween_action together(const std::vector<tween_impl<TargetType>>& tweenies);

tween_action together(const std::vector<std::shared_ptr<tween_base_impl>>& tweenies);

template<typename T1, typename T2, typename... TweenType>
tween_action together(T1&& tween1, T2&& tween2, TweenType&&... tween);


tween_action delay(const duration_t& duration, const sentinel_t& sentinel);

tween_action delay(const duration_t& duration);

template<typename TweenType>
tween_action repeat(TweenType& tween, size_t times = 0);

template<typename TweenType>
tween_action repeat(TweenType& tween, const sentinel_t& sentinel, size_t times = 0);

} //end of namespace tweeny

#include "tween_core.hpp"
