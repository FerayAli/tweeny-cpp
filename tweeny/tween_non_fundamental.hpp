#pragma once
#include "tween_non_fundamental.h"

namespace tweeny
{

template<typename Object, typename TargetType>
tween_action
move_from_to(Object& object,
             TargetType begin,
             TargetType end,
             duration_t duration,
             sentinel_t sentinel)
{
    auto initialize_func = [begin = std::move(begin)](Object*, sentinel_t)
    {
        return begin;
    };

    auto updater_func = [](Object* object, TargetType next) mutable
    {
        tween_non_fundamental_export<Object>::set_position(*object, next);
    };

    auto creator = create_tween_updater(&object,
                                        std::move(end),
                                        std::move(sentinel),
                                        std::move(initialize_func),
                                        std::move(updater_func));

    return tween_action(std::move(creator), std::move(duration));
}

template<typename Object, typename TargetType>
tween_action
move_from_to(std::shared_ptr<Object>& object,
             TargetType begin,
             TargetType end,
             duration_t duration)
{
    return move_from_to(*object.get(), begin, end, duration, object);
}

template<typename Object, typename TargetType>
tween_action
move_from_to_local(Object& object,
                   TargetType begin,
                   TargetType end,
                   duration_t duration,
                   sentinel_t sentinel)
{
    auto initialize_func = [begin = std::move(begin)](Object*, sentinel_t)
    {
        return begin;
    };

    auto updater_func = [](Object* object, TargetType next) mutable
    {
        tween_non_fundamental_export<Object>::set_position_local(*object, next);
    };

    auto creator = create_tween_updater(&object,
                                        std::move(end),
                                        std::move(sentinel),
                                        std::move(initialize_func),
                                        std::move(updater_func));

    return tween_action(std::move(creator), std::move(duration));
}

template<typename Object, typename TargetType>
tween_action
move_from_to_local(Object& object,
                   TargetType begin,
                   TargetType end,
                   duration_t duration)
{
    return move_from_to_local(*object.get(), begin, end, duration, object);
}

template<typename Object, typename TargetType>
tween_action
move_to(Object& object,
        TargetType end,
        duration_t duration,
        sentinel_t sentinel)
{
    auto initialize_func = [](Object* object, sentinel_t sentinel)
    {
        if(sentinel.expired())
        {
            return TargetType{};
        }
        return tween_non_fundamental_export<Object>::get_position(*object);
    };

    auto updater_func = [](Object* object, TargetType next) mutable
    {
        tween_non_fundamental_export<Object>::set_position(*object, next);
    };

    auto creator = create_tween_updater(&object,
                                        std::move(end),
                                        std::move(sentinel),
                                        std::move(initialize_func),
                                        std::move(updater_func));

    return tween_action(std::move(creator), std::move(duration));
}

template<typename Object, typename TargetType>
tween_action
move_to(std::shared_ptr<Object>& object,
        TargetType end,
        duration_t duration)
{
    return move_to(*object.get(), end, duration, object);
}

template<typename Object, typename TargetType>
tween_action
move_to_local(Object& object,
             TargetType end,
             duration_t duration,
             sentinel_t sentinel)
{
    auto initialize_func = [](Object* object, sentinel_t sentinel)
    {
        if(sentinel.expired())
        {
            return TargetType{};
        }
        return tween_non_fundamental_export<Object>::get_position_local(*object);
    };

    auto updater_func = [](Object* object, TargetType next) mutable
    {
        tween_non_fundamental_export<Object>::set_position_local(*object, next);
    };

    auto creator = create_tween_updater(&object,
                                        std::move(end),
                                        std::move(sentinel),
                                        std::move(initialize_func),
                                        std::move(updater_func));

    return tween_action(std::move(creator), std::move(duration));
}

template<typename Object, typename TargetType>
tween_action
move_to_local(std::shared_ptr<Object>& object,
              TargetType end,
              duration_t duration)
{
    return move_to_local(*object.get(), end, duration, object);
}

template<typename Object, typename TargetType>
tween_action
move_by(Object& object,
        TargetType amount,
        duration_t duration,
        sentinel_t sentinel)
{
    auto initialize_func = [](Object* object, sentinel_t sentinel)
    {
        if(sentinel.expired())
        {
            return TargetType{};
        }
        return tween_non_fundamental_export<Object>::get_position(*object);
    };

    auto updater_func = [prev = TargetType{}](TargetType* object, TargetType next) mutable
    {
        tween_non_fundamental_export<Object>::set_position(*object, (next - prev));
        prev = next;
    };

    auto creator = create_tween_updater(&object,
                                        std::move(amount),
                                        std::move(sentinel),
                                        std::move(initialize_func),
                                        std::move(updater_func));

    return tween_action(std::move(creator), std::move(duration));
}

template<typename Object, typename TargetType>
tween_action
move_by(std::shared_ptr<Object>& object,
        TargetType amount,
        duration_t duration)
{
    return move_by(*object.get(), amount, duration, object);
}

//template<typename Object, typename TargetType>
//tween_action
//scale_from_to(Object& object,
//             TargetType end,
//             duration_t duration,
//             sentinel_t sentinel);

//template<typename Object, typename TargetType>
//tween_action
//scale_from_to(Object& object,
//             TargetType end,
//             duration_t duration);

//template<typename Object, typename TargetType>
//tween_action
//scale_from_to_local(Object& object,
//                   TargetType end,
//                   duration_t duration,
//                   sentinel_t sentinel);

//template<typename Object, typename TargetType>
//tween_action
//scale_from_to_local(Object& object,
//                   TargetType end,
//                   duration_t duration);

//template<typename Object, typename TargetType>
//tween_action
//scale_to(Object& object,
//             TargetType end,
//             duration_t duration,
//             sentinel_t sentinel);

//template<typename Object, typename TargetType>
//tween_action
//scale_to(Object& object,
//             TargetType end,
//             duration_t duration);

//template<typename Object, typename TargetType>
//tween_action
//scale_to_local(Object& object,
//             TargetType end,
//             duration_t duration,
//             sentinel_t sentinel);

//template<typename Object, typename TargetType>
//tween_action
//scale_to_local(Object& object,
//             TargetType end,
//             duration_t duration);

//template<typename Object, typename TargetType>
//tween_action
//scale_by(Object& object,
//             TargetType end,
//             duration_t duration,
//             sentinel_t sentinel);

//template<typename Object, typename TargetType>
//tween_action
//scale_by(Object& object,
//             TargetType end,
//             duration_t duration);

//template<typename Object, typename TargetType>
//tween_action
//rotate_from_to(Object& object,
//             TargetType end,
//             duration_t duration,
//             sentinel_t sentinel);

//template<typename Object, typename TargetType>
//tween_action
//rotate_from_to(Object& object,
//             TargetType end,
//             duration_t duration);

//template<typename Object, typename TargetType>
//tween_action
//rotate_from_to_local(Object& object,
//                   TargetType end,
//                   duration_t duration,
//                   sentinel_t sentinel);

//template<typename Object, typename TargetType>
//tween_action
//rotate_from_to_local(Object& object,
//                   TargetType end,
//                   duration_t duration);

//template<typename Object, typename TargetType>
//tween_action
//rotate_to(Object& object,
//             TargetType end,
//             duration_t duration,
//             sentinel_t sentinel);

//template<typename Object, typename TargetType>
//tween_action
//rotate_to(Object& object,
//             TargetType end,
//             duration_t duration);

//template<typename Object, typename TargetType>
//tween_action
//rotate_to_local(Object& object,
//             TargetType end,
//             duration_t duration,
//             sentinel_t sentinel);

//template<typename Object, typename TargetType>
//tween_action
//rotate_to_local(Object& object,
//             TargetType end,
//             duration_t duration);

//template<typename Object, typename TargetType>
//tween_action
//rotate_by(Object& object,
//             TargetType end,
//             duration_t duration,
//             sentinel_t sentinel);

//template<typename Object, typename TargetType>
//tween_action
//rotate_by(Object& object,
//             TargetType end,
//             duration_t duration);

//template<typename Object, typename TargetType>
//tween_action
//fade_from_to(Object& object,
//             TargetType end,
//             duration_t duration,
//             sentinel_t sentinel);

//template<typename Object, typename TargetType>
//tween_action
//fade_from_to(Object& object,
//             TargetType end,
//             duration_t duration);

//template<typename Object, typename TargetType>
//tween_action
//fade_to(Object& object,
//             TargetType end,
//             duration_t duration,
//             sentinel_t sentinel);

//template<typename Object, typename TargetType>
//tween_action
//fade_to(Object& object,
//             TargetType end,
//             duration_t duration);

//template<typename Object, typename TargetType>
//tween_action
//fade_by(Object& object,
//             TargetType end,
//             duration_t duration,
//             sentinel_t sentinel);

//template<typename Object, typename TargetType>
//tween_action
//fade_by(Object& object,
//             TargetType end,
//             duration_t duration);

}
