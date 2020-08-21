#pragma once
#include "tween_action.h"
#include "tween_private.h"
#include "tween_ease.h"

namespace tweeny
{

template<typename Object,
         typename TargetType,
         typename InitializeFunc,
         typename UpdateFunc>
auto create_tween_updater(Object* object,
                     TargetType end,
                     sentinel_t sentinel,
                     InitializeFunc&& initialize_func,
                     UpdateFunc&& update_func,
                     ease_t ease_func = ease::linear)
{
    auto updater = [object
            , begin = initialize_func(object, sentinel)
            , end = std::move(end)
            , sentinel = std::move(sentinel)
            , update_func = std::forward<UpdateFunc>(update_func)
            , ease_func = std::move(ease_func)
            , finished = false]
    (duration_t delta, tween_action& self) mutable -> state_t
    {
        if(finished)
        {
            return state_t::finished;
        }

        if(sentinel.expired())
        {
            finished = true;
            return state_t::finished;
        }

        if(self.get_duration() == duration_t::zero())
        {
            update_func(object, end);
            finished = true;

            return state_t::finished;
        }

        tween_private::update_elapsed(self, delta);

        const float progress = ease_func(self.get_progress());
        const TargetType next = begin + ((end - begin) * progress);
        update_func(object, next);

        if(self.on_step)
        {
            self.on_step();
        }

        if(self.get_elapsed() == self.get_duration())
        {
            finished = true;
            if(self.on_end)
            {
                self.on_end();
            }
            return state_t::finished;
        }

        return state_t::running;
    };

    auto creator = [updater = std::move(updater)]
            (tween_action& self)
    {
        if(self.on_begin)
        {
            self.on_begin();
        }
        return updater;
    };

    return creator;
}

template<typename TargetType,
         typename InitializeFunc,
         typename UpdateFunc>
auto create_tween_value_creator(TargetType end,
                                duration_t duration,
                                InitializeFunc&& initialize_func,
                                UpdateFunc&& update_func)
{
    auto updater = [begin = initialize_func()
            , end
            , update_func = std::move(update_func)
            , finished = false]
    (duration_t delta, tween_value<TargetType>& self) mutable -> state_t
    {
        if(finished)
        {
            return state_t::finished;
        }

        if(self.get_duration() == duration_t::zero())
        {
            auto& value = tween_private::get_value_by_ref(self);
            update_func(&value, end);
            finished = true;

            return state_t::finished;
        }

        tween_private::update_elapsed(self, delta);

        const float progress = self.get_progress();
        const TargetType next = begin + ((end - begin) * progress);
        auto& value = tween_private::get_value_by_ref(self);
        update_func(&value, next);

        if(self.on_step)
        {
            self.on_step(value);
        }

        if(self.get_elapsed() == self.get_duration())
        {
            finished = true;
            if(self.on_end)
            {
                self.on_end(value);
            }
            return state_t::finished;
        }

        return state_t::running;
    };

    auto creator = [updater = std::move(updater)
                    , begin = initialize_func()
                    , end]
            (tween_impl<TargetType>& self)
    {
        if(self.on_begin)
        {
            self.on_begin(begin);
        }
        return std::make_tuple(updater, begin);
    };

    return creator;
}

}
