#include "tween_base.h"

namespace tweeny
{

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
