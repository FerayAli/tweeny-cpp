#pragma once
#include "tween_fundamental.h"
#include <numeric>

namespace tweeny
{

template<typename TargetType>
tween_value<TargetType>
tween_value_from_to(TargetType begin,
                    TargetType end,
                    duration_t duration)
{
    auto initialize_func = [begin]() -> TargetType
    {
        return begin;
    };

    auto updater_func = [](TargetType* object, TargetType next)
    {
        (*object) = next;
    };

    auto creator = create_tween_value_creator(end,
                                              duration,
                                              std::move(initialize_func),
                                              std::move(updater_func));

    return tween_value<TargetType>(std::move(creator), duration);
}

template<typename TargetType>
tween_action
tween_from_to(TargetType& object,
              decltype(std::decay_t<TargetType>(object)) begin,
              decltype(std::decay_t<TargetType>(object)) end,
              duration_t duration,
              sentinel_t sentinel)
{
    auto initialize_func = [begin](TargetType* object, sentinel_t sentinel)
    {
        if(sentinel.expired())
        {
            return TargetType{};
        }
        return begin;
    };

    auto updater_func = [](TargetType* object, TargetType next)
    {
        (*object) = next;
    };

    auto update_impl = create_tween_creator(&object,
                                                   end,
                                                   duration,
                                                   sentinel,
                                                   initialize_func,
                                                   updater_func);

    return tween_action(std::move(update_impl), duration);
}

template<typename TargetType>
typename std::enable_if_t<is_shared_ptr<TargetType>::value, tween_action>
tween_from_to(TargetType& object,
              decltype(std::decay_t<TargetType>(object)) begin,
              decltype(std::decay_t<TargetType>(object)) end,
              duration_t duration)
{
    return tween_from_to(*object.get(), begin, end, duration, object);
}

template<typename TargetType>
//typename std::enable_if_t<!is_shared_ptr<TargetType>::value, tween_action>
tween_action
tween_to(TargetType& object,
         decltype(std::decay_t<TargetType>(object)) end,
         duration_t duration,
         sentinel_t sentinel)
{
    auto initialize_func = [](TargetType* object, sentinel_t sentinel)
    {
        if(sentinel.expired())
        {
            return TargetType{};
        }
        return (*object);
    };

    auto updater_func = [](TargetType* object, TargetType next)
    {
        (*object) = next;
    };

    auto update_impl = create_tween_creator(&object,
                                                   end,
                                                   duration,
                                                   sentinel,
                                                   initialize_func,
                                                   updater_func);

    return tween_action(std::move(update_impl), duration);
}

template<typename TargetType>
//typename std::enable_if_t<is_shared_ptr<TargetType>::value, tween_action>
tween_action
tween_to(std::shared_ptr<TargetType>& object,
         TargetType end,
         duration_t duration)
{
    return tween_to(*object.get(), end, duration, object);
}

template<typename TargetType>
typename std::enable_if_t<!is_shared_ptr<TargetType>::value, tween_action>
tween_by(TargetType& object,
         decltype(std::decay_t<TargetType>(object)) amount,
         duration_t duration,
         sentinel_t sentinel)
{
    auto initialize_func = [](TargetType*, sentinel_t)
    {
        return TargetType{};
    };

    auto updater_func = [prev = TargetType{}](TargetType* object, TargetType next) mutable
    {
        (*object) += (next - prev);
        prev = next;
    };

    auto update_impl = create_tween_creator(&object,
                                                   amount,
                                                   duration,
                                                   sentinel,
                                                   initialize_func,
                                                   updater_func);

    return tween_action(std::move(update_impl), duration);
}

template<typename TargetType>
typename std::enable_if_t<is_shared_ptr<TargetType>::value, tween_action>
tween_by(TargetType& object,
         decltype(std::decay_t<TargetType>(object)) amount,
         duration_t duration)
{
    return tween_by(*object.get(), amount, duration, object);
}

template<typename T1, typename T2, typename... TweenType>
tween_action sequence(T1&& tween1, T2&& tween2, TweenType&&... tween)
{
    std::vector<std::shared_ptr<tween_base_impl>> tween_holder =
    {
        std::make_shared<decltype(std::decay_t<T1>(tween1))>,
        std::make_shared<decltype(std::decay_t<T2>(tween2))>,
        std::make_shared<decltype(std::decay_t<TweenType>(tween))>
            (std::forward<TweenType>(tween))...
    };

    duration_t duration = 0ms;
    for(auto& tween : tween_holder)
    {
        duration += tween->get_duration();
    }

    auto updater = [tween_holder = std::move(tween_holder)
                    , current_tween_idx = size_t(0)
                    , prev_elapsed = duration_t::zero()
                    , start_required = true
                    , finished = false]
            (duration_t delta, tween_action& self) mutable
    {
        if(finished)
        {
            return state_t::finished;
        }

        if(start_required)
        {
            tween_private::start(*tween_holder.at(current_tween_idx));
            prev_elapsed = duration_t::zero();
            start_required = false;
        }

        auto& current_tween = tween_holder.at(current_tween_idx);
        auto state = tween_private::update(*current_tween, delta);

        auto elapsed_diff = current_tween->get_elapsed() - prev_elapsed;
        prev_elapsed = current_tween->get_elapsed();

        tween_private::update_elapsed(self, elapsed_diff);

        if(state == state_t::finished)
        {
            current_tween_idx++;
            if(current_tween_idx == tween_holder.size())
            {
                finished = true;
                return state_t::finished;
            }
            start_required = true;
        }
        return state_t::running;
    };

    auto creator = [updater = std::move(updater)](tween_action& self)
    {
        if(self.on_begin)
        {
            self.on_begin();
        }
        return updater;
    };

    return tween_action(std::move(creator), duration);
}

//tween_action sequence(const std::vector<tween_action>& tweenies)
//{
//    std::cout << "sequence vector" << std::endl;
//    return tween_action();
//}

template<typename... TweenType>
tween_action together(TweenType&&... tween)
{
    return tween_action();
}

tween_action together(const std::vector<tween_action>& tweenies)
{
    return tween_action();
}

tween_action delay(duration_t duration)
{
    auto updater = [finished = false](duration_t delta, tween_action& self) mutable
    {
        if(finished)
        {
            return state_t::finished;
        }

        tween_private::update_elapsed(self, delta);
        if(self.get_elapsed() == self.get_duration())
        {
            finished = true;
            return state_t::finished;
        }

        return state_t::running;
    };

    auto creator = [updater = std::move(updater)](tween_action& self)
    {
        if(self.on_begin)
        {
            self.on_begin();
        }
        return updater;
    };

    return tween_action(std::move(creator), duration);
}

tween_action delay(duration_t duration, sentinel_t sentinel)
{
    return tween_action();
}

template<typename TweenType>
tween_action repeat(TweenType& tween, size_t times)
{
    auto updater = [tween, elapsed_times = size_t(0)]
            (duration_t delta, tween_action&) mutable
    {
//TODO
//        auto state = tween.update(delta);
        return state_t::running;
    };

    return tween_action(std::move(updater), tween.get_duration());
}

template<typename TweenType>
TweenType reverse(const TweenType& tween)
{
    TweenType reversed_tween = tween;
    if(reversed_tween.get_direction() == direction_t::forward)
    {
        tween_private::set_direction(reversed_tween, direction_t::backward);
    }
    else
    {
        tween_private::set_direction(reversed_tween, direction_t::forward);
    }
    return reversed_tween;
}

} //end of namespace tweeny
