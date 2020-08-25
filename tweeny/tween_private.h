#pragma once
#include "tween_action.h"

namespace tweeny
{

struct tween_private
{
    template<typename Tween>
    static void start(Tween& tween)
    {
        tween.start();
    }

    template<typename Tween>
    static void stop(Tween& tween)
    {
        tween.stop();
    }

    template<typename Tween>
    static void stop_when_finished(Tween& tween)
    {
        tween.stop_when_finished();
    }

    template<typename Tween>
    static void resume(Tween& tween)
    {
        tween.resume();
    }

    template<typename Tween>
    static void pause(Tween& tween)
    {
        tween.pause();
    }

    template<typename Tween>
    static void update_elapsed(Tween& tween, duration_t delta)
    {
        tween.update_elapsed(delta);
    }

    template<typename Tween>
    static state_t update(Tween& tween, duration_t delta)
    {
        return tween.update(delta);
    }

	template<typename Tween>
	static bool is_stop_when_finished_requested(Tween& tween)
	{
		return tween.stop_when_finished_;
	}
};

} //end of namespace
