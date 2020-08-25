#pragma once
#include "tween_base.h"

namespace tweeny
{

template<typename TargetType>
struct info_t
{
	TargetType begin = {};
	TargetType end = {};
	TargetType current = {};

	duration_t elapsed = duration_t::zero();
	duration_t duration = duration_t::zero();

	float progress = 0.0f;
};

template<typename T>
struct tween_impl : public tween_base_impl
{
    using updater_t = std::function<state_t(duration_t, tween_impl<T>&)>;
    using creator_t = std::function<std::tuple<updater_t, T>(tween_impl<T>&)>;

    ~tween_impl() = default;
    tween_impl() = default;
    tween_impl(creator_t&& creator, duration_t duration)
    {
        creator_ = std::move(creator);
        duration_ = duration;
    }

    tween_impl(const tween_impl&) = default;
    tween_impl(tween_impl&&) = default;

    tween_impl& operator=(const tween_impl&) = default;
    tween_impl& operator=(tween_impl&&) = default;

	std::function<void(const info_t<T>&)> on_begin;
	std::function<void(const info_t<T>&)> on_step;
	std::function<void(const info_t<T>&)> on_end;
private:
    friend struct tween_private;

    void start() override
    {
        tween_base_impl::start();
		updater_ = creator_(*this);
    }

    state_t update(duration_t delta) override
    {
        if(state_ == state_t::finished ||
           state_ == state_t::paused)
        {
            return state_;
        }

        state_ = updater_(delta, *this);
        return state_;
    }

    creator_t creator_;
    updater_t updater_;
};

template<typename T>
using tween_value = tween_impl<T>;

}
