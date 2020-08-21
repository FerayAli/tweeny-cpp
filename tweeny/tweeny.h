#pragma once
#include "tween_manager.h"
#include "detail/tweeny_internal.h"

namespace tweeny
{
    // scope_structure
    // name
    // pause_mode - inherit, process, stop

//    void push_scope();
//    void pop_scope();
//    void clear_scope();

//    get_manager("game")
//    tweeny::start(tween);
//    tweeny::get_manager("game").start(tween);
//    tweeny::start(tween);





    void stop_tweenies_in_scope(const std::string& scope_name);

    template<typename T>
    tween_id_t start(tween_impl<T> tween);

    template<typename T>
    void stop(const tween_impl<T>& tween);

    void stop(tween_id_t id);
}

#include "tweeny.hpp"
