#pragma once
#include "tweeny.h"
#include "detail/tweeny_internal.h"

namespace tweeny
{
    template<typename T>
    inline tween_id_t start(tween_impl<T> tween)
    {
        return detail::get_active_manager()->start(std::move(tween));
    }

    template<typename T>
    inline void stop(const tween_impl<T>& tween)
    {
        stop(tween.get_id());
    }

	template<typename T>
	void pause(const tween_impl<T>& tween)
	{
		pause(tween.get_id());
	}

	template<typename T>
	void resume(const tween_impl<T>& tween)
	{
		resume(tween.get_id());
	}

	template<typename T>
	void stop_when_finished(const tween_impl<T>& tween)
	{
		stop_when_finished(tween.get_id());
	}

	template<typename T>
	void stop_and_finish(const tween_impl<T>& tween, duration_t finish_after)
	{
		stop_and_finish(tween.get_id(), finish_after);
	}

	template<typename T>
	bool is_stopping(const tween_impl<T>& tween)
	{
		return is_stopping(tween.get_id());
	}

	template<typename T>
	bool is_running(const tween_impl<T>& tween)
	{
		return is_running(tween.get_id());
	}

	template<typename T>
	bool is_paused(const tween_impl<T>& tween)
	{
		return is_paused(tween.get_id());
	}

	template<typename T>
	void set_speed_multiplier(const tween_impl<T>& tween, float speed_multiplier)
	{
		set_speed_multiplier(tween.get_id(), speed_multiplier);
	}

	template<typename T>
	float get_speed_multiplier(const tween_impl<T>& tween)
	{
		return get_speed_multiplier(tween.get_id());
	}
}
