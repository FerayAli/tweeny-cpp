#pragma once
#include "tween_action.h"
#include "tween_private.h"
#include "tween_fundamental.h"
#include "tween_non_fundamental.h"
#include <unordered_map>

namespace tweeny
{

struct tween_manager
{
    template<typename T>
    tween_id_t start(tween_impl<T> tween)
    {
        tween_info& info = tweenies_[1];
        info.tween = std::make_unique<tween_impl<T>>(tween);

        tween_private::start(*info.tween);

        return 1;
    }

    template<typename T>
    void stop(const tween_impl<T>& tween)
    {

    }

    void stop(tween_id_t id){}

    template<typename T>
    void stop_when_finished(const tween_impl<T>& tween){}

    void stop_when_finished(tween_id_t id){}

    template<typename T>
    void stop_and_finish(const tween_impl<T>& tween, duration_t finish_after = 0ms);

    void stop_and_finish(tween_id_t id, duration_t finish_after = 0ms);

    void update(duration_t delta)
    {
        for(auto& info : tweenies_)
        {
            tween_private::update(*info.second.tween, delta);
        }
    }





    //stop_and_finish
    //resume
    //pause
    //set_speed
    //set_remaining_duration
    //get_speed
    //is_stopping
    //is_running
    //is_paused
    //update

private:
    struct tween_info
    {
        std::unique_ptr<tween_base_impl> tween;
        uint32_t depth = 0;
    };

    std::unordered_map<tween_id_t, tween_info> tweenies_;
};

}
