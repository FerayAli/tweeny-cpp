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
		tween.stop_when_finished_ = true;
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
		tween.elapsed_ += delta;
		tween.elapsed_ = std::max(tween.elapsed_, duration_t::zero());
		tween.elapsed_ = std::min(tween.elapsed_, tween.duration_);
    }

	template<typename Tween>
	static void set_speed_multiplier(Tween& tween, float speed_multiplier)
	{
		tween.speed_multiplier_ = speed_multiplier;
	}

	template<typename Tween>
	static float get_speed_multiplier(const Tween& tween)
	{
		return tween.speed_multiplier_;
	}

	template<typename Tween>
	static bool is_stop_when_finished_requested(const Tween& tween)
	{
		return tween.stop_when_finished_;
	}

	template<typename Tween>
	static bool is_running(const Tween& tween)
	{
		return tween.state_ == state_t::running;
	}

	template<typename Tween>
	static bool is_paused(const Tween& tween)
	{
		return tween.state_ == state_t::paused;
	}

	template<typename Tween>
	static state_t update(Tween& tween, duration_t delta)
	{
		return tween.update(delta);
	}

};

} //end of namespace
