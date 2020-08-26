#pragma once
#include "tween_action.h"
#include "tween_private.h"
#include "tween_ease.h"
#include "tween_math.h"

namespace tweeny
{

template<typename Object,
         typename TargetType,
         typename InitializeFunc,
         typename UpdateFunc>
auto create_tween_updater(Object* object,
					 TargetType&& end,
					 const sentinel_t& sentinel,
                     InitializeFunc&& initialize_func,
                     UpdateFunc&& update_func,
					 const ease_t& ease_func = ease::linear)
{
    return [object
			, begin = initialize_func(object, sentinel)
			, end = std::forward<TargetType>(end)
			, sentinel = sentinel
            , update_func = std::forward<UpdateFunc>(update_func)
			, ease_func = ease_func
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

		const auto next = math::lerp(begin, end, self.get_progress(), ease_func);
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
}

template<typename TargetType>
auto create_tween_value_updater(TargetType&& begin,
								TargetType&& end,
								const duration_t& duration,
								const ease_t& ease_func)
{
	auto get_info = [](TargetType&& begin, TargetType&& end, const duration_t& duration)
	{
		info_t<TargetType> info;
		info.begin = std::forward<TargetType>(begin);
		info.end =  std::forward<TargetType>(end);
		info.current = info.begin;
		info.elapsed = duration_t::zero();
		info.duration = duration;
		info.progress = 0.0f;
		return info;
	};

	return [info = get_info(std::forward<TargetType>(begin), std::forward<TargetType>(end), duration)
			, ease_func = ease_func
			, finished = false]
    (duration_t delta, tween_value<TargetType>& self) mutable -> state_t
    {
        if(finished)
        {
            return state_t::finished;
        }

        if(self.get_duration() == duration_t::zero())
        {
			update_func(info.current, info.end);
            finished = true;

            return state_t::finished;
        }

        tween_private::update_elapsed(self, delta);

		info.progress = self.get_progress();
		info.current = math::lerp(info.begin, info.end, info.progress, ease_func);

        if(self.on_step)
        {
			self.on_step(info);
        }

        if(self.get_elapsed() == self.get_duration())
        {
            finished = true;
            if(self.on_end)
            {
				self.on_end(info);
            }
            return state_t::finished;
        }

        return state_t::running;
    };
}

}
