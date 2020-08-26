#pragma once
#include "tween_common.h"
#include "tween_updater.h"

namespace tweeny
{

template<typename Object, typename TargetType>
tween_action
move_from_to(Object& object,
			 const TargetType& begin,
			 const TargetType& end,
             const duration_t& duration,
			 const sentinel_t& sentinel,
			 const ease_t& ease_func = ease::linear);

template<typename Object, typename TargetType>
tween_action
move_from_to(const std::shared_ptr<Object>& object,
			 TargetType&& begin,
			 TargetType&& end,
			 const duration_t& duration,
			 const ease_t& ease_func = ease::linear);

//template<typename Object, typename TargetType>
//tween_action
//move_from_to_local(Object& object,
//                   TargetType begin,
//                   TargetType end,
//                   duration_t duration,
//                   sentinel_t sentinel);

//template<typename Object, typename TargetType>
//tween_action
//move_from_to_local(std::shared_ptr<Object>& object,
//                   TargetType begin,
//                   TargetType end,
//                   duration_t duration);

template<typename Object, typename TargetType>
tween_action
move_to(Object& object,
		TargetType&& end,
		const duration_t& duration,
		const sentinel_t& sentinel,
		const ease_t& ease_func = ease::linear);

template<typename Object, typename TargetType>
tween_action
move_to(const std::shared_ptr<Object>& object,
		TargetType&& end,
		const duration_t& duration,
		const ease_t& ease_func = ease::linear);

//template<typename Object, typename TargetType>
//tween_action
//move_to_local(Object& object,
//              TargetType end,
//              duration_t duration,
//              sentinel_t sentinel);

//template<typename Object, typename TargetType>
//tween_action
//move_to_local(std::shared_ptr<Object>& object,
//              TargetType end,
//              duration_t duration);

template<typename Object, typename TargetType>
tween_action
move_by(Object& object,
		TargetType&& amount,
		const duration_t& duration,
		const sentinel_t& sentinel,
		const ease_t& ease_func = ease::linear);

template<typename Object, typename TargetType>
tween_action
move_by(const std::shared_ptr<Object>& object,
		TargetType&& amount,
		const duration_t& duration,
		const ease_t& ease_func = ease::linear);

template<typename Object, typename TargetType>
tween_action
scale_from_to(Object& object,
			  TargetType&& begin,
			  TargetType&& end,
			  const duration_t& duration,
			  const sentinel_t& sentinel,
			  const ease_t& ease_func = ease::linear);

template<typename Object, typename TargetType>
tween_action
scale_from_to(const std::shared_ptr<Object>& object,
			  TargetType&& begin,
			  TargetType&& end,
			  const duration_t& duration,
			  const ease_t& ease_func = ease::linear);

//template<typename Object, typename TargetType>
//typename std::enable_if_t<!is_shared_ptr<Object>::value, tween_action>
//scale_from_to_local(Object& object,
//                    TargetType begin,
//                    TargetType end,
//                    duration_t duration,
//                    sentinel_t sentinel);

//template<typename Object, typename TargetType>
//typename std::enable_if_t<is_shared_ptr<Object>::value, tween_action>
//scale_from_to_local(Object& object,
//                    TargetType begin,
//                    TargetType end,
//                    duration_t duration);

template<typename Object, typename TargetType>
tween_action
scale_to(Object& object,
		 TargetType&& end,
		 const duration_t& duration,
		 const sentinel_t& sentinel,
		 const ease_t& ease_func = ease::linear);

template<typename Object, typename TargetType>
tween_action
scale_to(const std::shared_ptr<Object>& object,
		 TargetType&& end,
		 const duration_t& duration,
		 const ease_t& ease_func = ease::linear);

//template<typename Object, typename TargetType>
//typename std::enable_if_t<!is_shared_ptr<Object>::value, tween_action>
//scale_to_local(Object& object,
//             TargetType end,
//             duration_t duration,
//             sentinel_t sentinel);

//template<typename Object, typename TargetType>
//typename std::enable_if_t<is_shared_ptr<Object>::value, tween_action>
//scale_to_local(Object& object,
//             TargetType end,
//             duration_t duration);

template<typename Object, typename TargetType>
tween_action
scale_by(Object& object,
		 TargetType&& amount,
		 const duration_t& duration,
		 const sentinel_t& sentinel,
		 const ease_t& ease_func = ease::linear);

template<typename Object, typename TargetType>
tween_action
scale_by(const std::shared_ptr<Object>& object,
		 TargetType&& amount,
		 const duration_t& duration,
		 const ease_t& ease_func = ease::linear);

template<typename Object, typename TargetType>
tween_action
rotate_from_to(Object& object,
			   TargetType&& begin,
			   TargetType&& end,
			   const duration_t& duration,
			   const sentinel_t& sentinel,
			   const ease_t& ease_func = ease::linear);

template<typename Object, typename TargetType>
tween_action
rotate_from_to(const std::shared_ptr<Object>& object,
			   TargetType&& begin,
			   TargetType&& end,
			   const duration_t& duration,
			   const ease_t& ease_func = ease::linear);

//template<typename Object, typename TargetType>
//typename std::enable_if_t<!is_shared_ptr<Object>::value, tween_action>
//rotate_from_to_local(Object& object,
//                     TargetType begin,
//                     TargetType end,
//                     duration_t duration,
//                     sentinel_t sentinel);

//template<typename Object, typename TargetType>
//typename std::enable_if_t<is_shared_ptr<Object>::value, tween_action>
//rotate_from_to_local(Object& object,
//                     TargetType begin,
//                     TargetType end,
//                     duration_t duration);

template<typename Object, typename TargetType>
tween_action
rotate_to(Object& object,
		  TargetType&& end,
		  const duration_t& duration,
		  const sentinel_t& sentinel,
		  const ease_t& ease_func = ease::linear);

template<typename Object, typename TargetType>
tween_action
rotate_to(const std::shared_ptr<Object>& object,
		  TargetType&& end,
		  const duration_t& duration,
		  const ease_t& ease_func = ease::linear);

//template<typename Object, typename TargetType>
//typename std::enable_if_t<!is_shared_ptr<Object>::value, tween_action>
//rotate_to_local(Object& object,
//             TargetType end,
//             duration_t duration,
//             sentinel_t sentinel);

//template<typename Object, typename TargetType>
//typename std::enable_if_t<is_shared_ptr<Object>::value, tween_action>
//rotate_to_local(Object& object,
//             TargetType end,
//             duration_t duration);

template<typename Object, typename TargetType>
tween_action
rotate_by(Object& object,
		  TargetType&& amount,
		  const duration_t& duration,
		  const sentinel_t& sentinel,
		  const ease_t& ease_func = ease::linear);

template<typename Object, typename TargetType>
tween_action
rotate_by(const std::shared_ptr<Object>& object,
		  TargetType&& amount,
		  const duration_t& duration,
		  const ease_t& ease_func = ease::linear);

template<typename Object, typename TargetType>
tween_action
fade_from_to(Object& object,
			 TargetType&& begin,
			 TargetType&& end,
			 const duration_t& duration,
			 const sentinel_t& sentinel,
			 const ease_t& ease_func = ease::linear);

template<typename Object, typename TargetType>
tween_action
fade_from_to(const std::shared_ptr<Object>& object,
			 TargetType&& begin,
			 TargetType&& end,
			 const duration_t& duration,
			 const ease_t& ease_func = ease::linear);

template<typename Object, typename TargetType>
tween_action
fade_to(Object& object,
		TargetType&& end,
		const duration_t& duration,
		const sentinel_t& sentinel,
		const ease_t& ease_func = ease::linear);

template<typename Object, typename TargetType>
tween_action
fade_to(const std::shared_ptr<Object>& object,
		TargetType&& end,
		const duration_t& duration,
		const ease_t& ease_func = ease::linear);

template<typename Object, typename TargetType>
tween_action
fade_by(Object& object,
		TargetType&& amount,
		const duration_t& duration,
		const sentinel_t& sentinel,
		const ease_t& ease_func = ease::linear);

template<typename Object, typename TargetType>
tween_action
fade_by(const std::shared_ptr<Object>& object,
		TargetType&& amount,
		const duration_t& duration,
		const ease_t& ease_func = ease::linear);

template<typename Object, typename TargetType>
tween_action
shake(Object& object,
	  TargetType initial_force,
	  const sentinel_t& sentinel,
	  const duration_t& duration = 1s,
	  uint32_t shake_count = 6);

template<typename Object, typename TargetType>
tween_action
shake(const std::shared_ptr<Object>& object,
	  TargetType initial_force,
	  const duration_t& duration = 1s,
	  uint32_t shake_count = 6);

} //end of namespace

#include "tween_ex.hpp"

