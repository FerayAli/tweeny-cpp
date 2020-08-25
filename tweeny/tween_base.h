#pragma once
#include "tween_common.h"
#include <functional>
#include <algorithm>

namespace tweeny
{

struct tween_base_impl
{
    friend struct tween_private;

    virtual ~tween_base_impl() = default;

    tween_base_impl();
    tween_base_impl(const tween_base_impl&) = default;
    tween_base_impl(tween_base_impl&&) = default;

    tween_base_impl& operator=(const tween_base_impl&) = default;
    tween_base_impl& operator=(tween_base_impl&&) = default;

    float get_progress() const;
    duration_t get_elapsed() const;
    duration_t get_duration() const;

	tween_id_t get_id() const;

	virtual bool is_empty() = 0;
	virtual void clear() = 0;
protected:
    virtual state_t update(duration_t delta) = 0;
	virtual void start();

    void stop();
	void resume();
	void pause();

	tween_id_t id_ = 1;
    state_t state_ = state_t::finished;

    duration_t elapsed_ = duration_t::zero();
    duration_t duration_ = duration_t::zero();

	bool stop_when_finished_ = false;

	float speed_multiplier_ = 1.0f;
};

}
