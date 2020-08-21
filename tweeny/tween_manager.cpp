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

void tween_manager::stop_when_finished(tween_id_t id)
{

}

void tween_manager::update(duration_t delta)
{
    for(auto& info : tweenies_)
    {
        tween_private::update(*info.second.tween, delta);
    }
}

}
