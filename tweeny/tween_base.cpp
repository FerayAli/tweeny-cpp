#include "tween_base.h"

namespace tweeny
{

tween_base_impl::tween_base_impl()
{
    static tween_id_t unique_id = 1;
    id_ = unique_id++;
}

float tween_base_impl::get_progress() const
{
    return float(elapsed_.count()) / float(duration_.count());
}

duration_t tween_base_impl::get_duration() const
{
    return duration_;
}

tween_id_t tween_base_impl::get_id() const
{
	return id_;
}

void tween_base_impl::start()
{
    state_ = state_t::running;
	elapsed_ = duration_t::zero();
}

void tween_base_impl::stop()
{
    state_ = state_t::finished;
}

void tween_base_impl::resume()
{
	if(state_ == state_t::running)
	{
		state_ = state_t::paused;
	}
}

void tween_base_impl::pause()
{
	if(state_ == state_t::paused)
	{
		state_ = state_t::running;
	}
}

duration_t tween_base_impl::get_elapsed() const
{
    return elapsed_;
}

}
