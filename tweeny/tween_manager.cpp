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

void tween_manager::pause(const tween_id_t id)
{
	auto iter = tweenies_.find(id);
	if(iter != std::end(tweenies_))
	{
		tween_private::pause(*iter->second.tween);
	}
}

void tween_manager::pause_all()
{
	for(auto& info : tweenies_)
	{
		tween_private::pause(*info.second.tween);
	}
}

void tween_manager::resume(const tween_id_t tween)
{
	auto iter = tweenies_.find(tween);
	if(iter != std::end(tweenies_))
	{
		tween_private::resume(*iter->second.tween);
	}
}

void tween_manager::resume_all()
{
	for(auto& info : tweenies_)
	{
		tween_private::resume(*info.second.tween);
	}
}

void tween_manager::stop_when_finished(tween_id_t id)
{
	auto iter = tweenies_.find(id);
	if(iter != std::end(tweenies_))
	{
		tween_private::stop_when_finished(*iter->second.tween);
	}
}

void tween_manager::stop_when_finished_all()
{
	for(auto& info : tweenies_)
	{
		tween_private::stop_when_finished(*info.second.tween);
	}
}

void tween_manager::stop_and_finish(tween_id_t id, duration_t finish_after)
{
	//TODO
//	auto iter = tweenies_.find(tween);
//	if(iter != std::end(tweenies_))
//	{
//		tween_private::stop(*iter->second.tween);
//	}
}

void tween_manager::stop_and_finish_all()
{
	//TODO
}

bool tween_manager::is_stopping(tween_id_t id)
{
	auto iter = tweenies_.find(id);
	if(iter != std::end(tweenies_))
	{
		return tween_private::is_stop_when_finished_requested(*iter->second.tween);
	}
	return false;
}

bool tween_manager::is_running(tween_id_t id)
{
	auto iter = tweenies_.find(id);
	if(iter != std::end(tweenies_))
	{
		return tween_private::is_running(*iter->second.tween);
	}
	return false;
}

bool tween_manager::is_paused(tween_id_t id)
{
	auto iter = tweenies_.find(id);
	if(iter != std::end(tweenies_))
	{
		return tween_private::is_paused(*iter->second.tween);
	}
	return false;
}

void tween_manager::set_speed_multiplier(tween_id_t id, float speed_multiplier)
{
	auto iter = tweenies_.find(id);
	if(iter != std::end(tweenies_))
	{
		tween_private::set_speed_multiplier(*iter->second.tween, speed_multiplier);
	}
}

float tween_manager::get_speed_multiplier(tween_id_t id)
{
	auto iter = tweenies_.find(id);
	if(iter != std::end(tweenies_))
	{
		return tween_private::get_speed_multiplier(*iter->second.tween);
	}
	return 1.0f;
}

size_t tween_manager::get_tweenies_count() const
{
	return tweenies_.size();
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


}
