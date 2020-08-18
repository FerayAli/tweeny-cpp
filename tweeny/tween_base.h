#pragma once
#include "tween_common.h"
#include <functional>

namespace tweeny
{

struct tween_base_impl
{
    friend struct tween_private;

    virtual ~tween_base_impl() = default;

    tween_base_impl() = default;
    tween_base_impl(const tween_base_impl&) = default;
    tween_base_impl(tween_base_impl&&) = default;

    tween_base_impl& operator=(const tween_base_impl&) = default;
    tween_base_impl& operator=(tween_base_impl&&) = default;

    float get_progress() const;
    duration_t get_elapsed() const;
    duration_t get_duration() const;

    direction_t get_direction() const
    {
        return direction_;
    }

    tween_id_t get_id() const;

    bool is_empty();
    void clear();
protected:
    virtual state_t update(duration_t delta) = 0;

    void set_direction(direction_t dir)
    {
        direction_ = dir;
        if(dir == direction_t::forward)
        {
            elapsed_ = duration_t::zero();
        }
        else if(dir == direction_t::backward)
        {
            elapsed_ = duration_;
        }
    }

    void update_elapsed(duration_t delta)
    {
        elapsed_ += delta;
        elapsed_ = std::max(elapsed_, duration_t::zero());
        elapsed_ = std::min(elapsed_, duration_);
    }

    virtual void start()
    {
        state_ = state_t::running;
    }

    void stop()
    {
        state_ = state_t::finished;
    }

    void stop_when_finished()
    {

    }

    void resume(){}
    void pause(){}

    tween_id_t id_;
    state_t state_ = state_t::finished;

    bool stop_when_finished_ = false;
    direction_t direction_ = direction_t::forward;

    duration_t elapsed_ = duration_t::zero();
    duration_t duration_ = duration_t::zero();
};

}
