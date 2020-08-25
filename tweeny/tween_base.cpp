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
	return 1;
}

void tween_base_impl::update_elapsed(duration_t delta)
{
    elapsed_ += delta;
    elapsed_ = std::max(elapsed_, duration_t::zero());
    elapsed_ = std::min(elapsed_, duration_);
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

void tween_base_impl::stop_when_finished()
{

}

void tween_base_impl::resume()
{}

void tween_base_impl::pause()
{}

void tween_base_impl::clear()
{

}

bool tween_base_impl::is_empty()
{
    return false;
}

duration_t tween_base_impl::get_elapsed() const
{
    return elapsed_;
}

}
