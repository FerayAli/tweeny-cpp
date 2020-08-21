#pragma once
#include "tween_common.h"
#include "tween_updater.h"
#include "tween_private.h"
#include "tween_ease.h"
#include <vector>

//NAME - tween_core
namespace tweeny
{

template<typename TargetType>
tween_value<TargetType>
tween_value_from_to(TargetType begin,
                    TargetType end,
                    duration_t duration);

template<typename TargetType>
tween_action
tween_from_to(TargetType& object,
              decltype(std::decay_t<TargetType>(object)) begin,
              decltype(std::decay_t<TargetType>(object)) end,
              duration_t duration,
              sentinel_t sentinel,
              ease_t ease_func = ease::linear);

template<typename TargetType>
tween_action
tween_from_to(std::shared_ptr<TargetType>& object,
              decltype(std::decay_t<TargetType>(*object)) begin,
              decltype(std::decay_t<TargetType>(*object)) end,
              duration_t duration,
              ease_t ease_func = ease::linear);

template<typename TargetType>
tween_action
tween_to(TargetType& object,
         decltype(std::decay_t<TargetType>(object)) end,
         duration_t duration,
         sentinel_t sentinel);

template<typename TargetType>
tween_action
tween_to(std::shared_ptr<TargetType>& object,
         TargetType end,
         duration_t duration);

template<typename TargetType>
tween_action
tween_by(TargetType& object,
         decltype(std::decay_t<TargetType>(object)) amount,
         duration_t duration,
         sentinel_t sentinel);

template<typename TargetType>
tween_action
tween_by(std::shared_ptr<TargetType>& object,
         decltype(std::decay_t<TargetType>(object)) amount,
         duration_t duration);

template<typename T1, typename T2, typename... TweenType>
tween_action sequence(T1&& tween1, T2&& tween2, TweenType&&... tween);

template<typename T>
tween_action sequence(const std::vector<tween_impl<T>>& tweenies);

//template<typename... TweenType>
//tween_action together(TweenType&&... tween);

//tween_action together(const std::vector<tween_action>& tweenies);

//tween_action delay(duration_t duration);

//tween_action delay(duration_t duration, sentinel_t sentinel);

//template<typename TweenType>
//tween_action repeat(TweenType& tween, size_t times);

} //end of namespace tweeny

#include "tween_fundamental.hpp"
