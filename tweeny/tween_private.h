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

    template<typename T>
    static void stop_when_finished(tween_impl<T>& tween)
    {
        tween.stop_when_finished();
    }

    template<typename T>
    static void resume(tween_impl<T>& tween)
    {
        tween.resume();
    }

    template<typename T>
    static void pause(tween_impl<T>& tween)
    {
        tween.pause();
    }

    template<typename T>
    static void set_direction(tween_impl<T>& tween, direction_t dir)
    {
        tween.set_direction(dir);
    }

    template<typename T>
    static void update_elapsed(tween_impl<T>& tween, duration_t delta)
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
