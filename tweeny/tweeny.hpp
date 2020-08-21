#pragma once
#include "tweeny.h"
#include "detail/tweeny_internal.h"

namespace tweeny
{
    template<typename T>
    inline tween_id_t start(tween_impl<T> tween)
    {
        return detail::get_active_manager()->start(std::move(tween));
    }

    template<typename T>
    inline void stop(const tween_impl<T>& tween)
    {
        stop(tween.get_id());
    }

}
