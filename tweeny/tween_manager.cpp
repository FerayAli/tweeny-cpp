#include "tween_manager.h"

namespace tweeny
{

void tween_manager::stop(tween_id_t id)
{
    auto iter = tweenies_.find(id);
    if(iter != std::end(tweenies_))
    {
        tween_private::stop(*iter->second.tween);
    }
}

void tween_manager::stop_all()
{
    for(auto& info : tweenies_)
    {
        tween_private::stop(*info.second.tween);
    }
}

void tween_manager::stop_when_finished(tween_id_t id)
{

}

void tween_manager::update(duration_t delta)
{
    for(auto iter = tweenies_.begin(); iter != tweenies_.end();)
    {
        iter->second.depth++;

        auto state = tween_private::update(*iter->second.tween, delta);
        if(state == state_t::finished)
        {
            iter->second.depth--;
            iter = tweenies_.erase(iter);
        }
        else
        {
            iter->second.depth--;
            ++iter;
        }
    }
}

size_t tween_manager::get_tweenies_count() const
{
    return tweenies_.size();
}

}
