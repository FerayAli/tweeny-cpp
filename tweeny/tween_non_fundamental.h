#pragma once
#include "tween_common.h"
#include "tween_updater.h"

namespace tweeny
{

template<typename Object, typename TargetType>
typename std::enable_if_t<!is_shared_ptr<Object>::value, tween_action>
move_from_to(Object& object,
             TargetType begin,
             TargetType end,
             duration_t duration,
             sentinel_t sentinel);

template<typename Object, typename TargetType>
typename std::enable_if_t<is_shared_ptr<Object>::value, tween_action>
move_from_to(Object& object,
             TargetType begin,
             TargetType end,
             duration_t duration);

template<typename Object, typename TargetType>
typename std::enable_if_t<!is_shared_ptr<Object>::value, tween_action>
move_from_to_local(Object& object,
                   TargetType begin,
                   TargetType end,
                   duration_t duration,
                   sentinel_t sentinel);

template<typename Object, typename TargetType>
typename std::enable_if_t<is_shared_ptr<Object>::value, tween_action>
move_from_to_local(Object& object,
                   TargetType begin,
                   TargetType end,
                   duration_t duration);

template<typename Object, typename TargetType>
typename std::enable_if_t<!is_shared_ptr<Object>::value, tween_action>
move_to(Object& object,
             TargetType end,
             duration_t duration,
             sentinel_t sentinel);

template<typename Object, typename TargetType>
typename std::enable_if_t<is_shared_ptr<Object>::value, tween_action>
move_to(Object& object,
             TargetType end,
             duration_t duration);

template<typename Object, typename TargetType>
typename std::enable_if_t<!is_shared_ptr<Object>::value, tween_action>
move_to_local(Object& object,
             TargetType end,
             duration_t duration,
             sentinel_t sentinel);

template<typename Object, typename TargetType>
typename std::enable_if_t<is_shared_ptr<Object>::value, tween_action>
move_to_local(Object& object,
             TargetType end,
             duration_t duration);

template<typename Object, typename TargetType>
typename std::enable_if_t<!is_shared_ptr<Object>::value, tween_action>
move_by(Object& object,
        TargetType amount,
        duration_t duration,
        sentinel_t sentinel);

template<typename Object, typename TargetType>
typename std::enable_if_t<is_shared_ptr<Object>::value, tween_action>
move_by(Object& object,
        TargetType amount,
        duration_t duration);

//template<typename Object, typename TargetType>
//typename std::enable_if_t<!is_shared_ptr<Object>::value, tween_action>
//scale_from_to(Object& object,
//              TargetType begin,
//              TargetType end,
//              duration_t duration,
//              sentinel_t sentinel);

//template<typename Object, typename TargetType>
//typename std::enable_if_t<is_shared_ptr<Object>::value, tween_action>
//scale_from_to(Object& object,
//              TargetType begin,
//              TargetType end,
//              duration_t duration);

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

//template<typename Object, typename TargetType>
//typename std::enable_if_t<!is_shared_ptr<Object>::value, tween_action>
//scale_to(Object& object,
//             TargetType end,
//             duration_t duration,
//             sentinel_t sentinel);

//template<typename Object, typename TargetType>
//typename std::enable_if_t<is_shared_ptr<Object>::value, tween_action>
//scale_to(Object& object,
//             TargetType end,
//             duration_t duration);

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

//template<typename Object, typename TargetType>
//typename std::enable_if_t<!is_shared_ptr<Object>::value, tween_action>
//scale_by(Object& object,
//             TargetType end,
//             duration_t duration,
//             sentinel_t sentinel);

//template<typename Object, typename TargetType>
//typename std::enable_if_t<is_shared_ptr<Object>::value, tween_action>
//scale_by(Object& object,
//             TargetType end,
//             duration_t duration);

//template<typename Object, typename TargetType>
//typename std::enable_if_t<!is_shared_ptr<Object>::value, tween_action>
//rotate_from_to(Object& object,
//               TargetType begin,
//               TargetType end,
//               duration_t duration,
//               sentinel_t sentinel);

//template<typename Object, typename TargetType>
//typename std::enable_if_t<is_shared_ptr<Object>::value, tween_action>
//rotate_from_to(Object& object,
//               TargetType begin,
//               TargetType end,
//               duration_t duration);

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

//template<typename Object, typename TargetType>
//typename std::enable_if_t<!is_shared_ptr<Object>::value, tween_action>
//rotate_to(Object& object,
//             TargetType end,
//             duration_t duration,
//             sentinel_t sentinel);

//template<typename Object, typename TargetType>
//typename std::enable_if_t<is_shared_ptr<Object>::value, tween_action>
//rotate_to(Object& object,
//             TargetType end,
//             duration_t duration);

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

//template<typename Object, typename TargetType>
//typename std::enable_if_t<!is_shared_ptr<Object>::value, tween_action>
//rotate_by(Object& object,
//             TargetType end,
//             duration_t duration,
//             sentinel_t sentinel);

//template<typename Object, typename TargetType>
//typename std::enable_if_t<is_shared_ptr<Object>::value, tween_action>
//rotate_by(Object& object,
//             TargetType end,
//             duration_t duration);

//template<typename Object, typename TargetType>
//typename std::enable_if_t<!is_shared_ptr<Object>::value, tween_action>
//fade_from_to(Object& object,
//             TargetType begin,
//             TargetType end,
//             duration_t duration,
//             sentinel_t sentinel);

//template<typename Object, typename TargetType>
//typename std::enable_if_t<is_shared_ptr<Object>::value, tween_action>
//fade_from_to(Object& object,
//             TargetType begin,
//             TargetType end,
//             duration_t duration);

//template<typename Object, typename TargetType>
//typename std::enable_if_t<!is_shared_ptr<Object>::value, tween_action>
//fade_to(Object& object,
//             TargetType end,
//             duration_t duration,
//             sentinel_t sentinel);

//template<typename Object, typename TargetType>
//typename std::enable_if_t<is_shared_ptr<Object>::value, tween_action>
//fade_to(Object& object,
//             TargetType end,
//             duration_t duration);

//template<typename Object, typename TargetType>
//typename std::enable_if_t<!is_shared_ptr<Object>::value, tween_action>
//fade_by(Object& object,
//             TargetType end,
//             duration_t duration,
//             sentinel_t sentinel);

//template<typename Object, typename TargetType>
//typename std::enable_if_t<is_shared_ptr<Object>::value, tween_action>
//fade_by(Object& object,
//             TargetType end,
//             duration_t duration);

//TODO
//zoom_in
//zoom_out
//fade_in
//fade_out
//blink
//shake(direction_angle)
//pulse

} //end of namespace

#include "tween_non_fundamental.hpp"

