#pragma once
#include "tween_action.h"
#include "tween_private.h"
#include "tween_core.h"
#include "tween_ex.h"
#include <unordered_map>

namespace tweeny
{

struct tween_manager
{
    template<typename T>
    tween_id_t start(tween_impl<T> tween)
    {
        tween_info& info = tweenies_[tween.get_id()];

        info.tween = std::make_unique<tween_impl<T>>(std::move(tween));

        tween_private::start(*info.tween);

        auto i = info.tween->get_id();
        return i;
    }

    template<typename T>
    void stop(const tween_impl<T>& tween)
    {
        stop(tween.get_id());
    }
    void stop(tween_id_t id);
    void stop_all();

    template<typename T>
    void stop_when_finished(const tween_impl<T>& tween)
    {
        stop_when_finished(tween.get_id());
    }

    void stop_when_finished(tween_id_t id);

    template<typename T>
    void stop_and_finish(const tween_impl<T>& tween, duration_t finish_after = 0ms)
    {
        stop_when_finished(tween.get_id(), finish_after);
    }

    void stop_and_finish(tween_id_t id, duration_t finish_after = 0ms);

    void update(duration_t delta);





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
    size_t get_tweenies_count() const;
private:
    struct tween_info
    {
        std::unique_ptr<tween_base_impl> tween;
        uint32_t depth = 0;
    };

    std::unordered_map<tween_id_t, tween_info> tweenies_;
    std::unordered_map<tween_id_t, std::unique_ptr<tween_base_impl>> pending_tweenies_;
};

}
