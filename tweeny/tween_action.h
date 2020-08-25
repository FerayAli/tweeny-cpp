#pragma once
#include "tween_value.h"

namespace tweeny
{

template<>
struct tween_impl<void> : public tween_base_impl
{
    using updater_t = std::function<state_t(duration_t, tween_impl<void>&)>;
    using creator_t = std::function<updater_t(tween_impl<void>&)>;

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

    std::function<void()> on_begin;
    std::function<void()> on_step;
    std::function<void()> on_end;

	bool is_empty() override
	{
		return (creator_ != nullptr);
	}

	void clear() override
	{
		creator_ = nullptr;
	}
private:
    friend struct tween_private;

    void start() override
    {
		if(creator_ == nullptr)
		{
			return;
		}

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

		auto update_time = (delta.count() * int64_t(speed_multiplier_ * 1000.0f)) / 1000;
		state_ = updater_(duration_t(update_time), *this);
        return state_;
    }

    creator_t creator_;
    updater_t updater_;
};

using tween_action = tween_impl<void>;

}
