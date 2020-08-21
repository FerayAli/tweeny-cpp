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

    template<typename T>
    static T& get_value_by_ref(tween_impl<T>& tween)
    {
        return tween.value_;
    }

    template<typename Tween>
    static state_t update(Tween& tween, duration_t delta)
    {
        return tween.update(delta);
    }
};

} //end of namespace
