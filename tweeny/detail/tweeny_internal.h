#pragma once
#include "../tween_manager.h"

namespace tweeny
{

namespace detail
{
    using managers = std::unordered_map<std::string, std::shared_ptr<tween_manager>>;
    managers& get_managers();
    const std::shared_ptr<tween_manager>& get_active_manager();
    void set_current_scope_name(const std::string& scope_name);
    const std::string& get_current_scope_name();
    void update(duration_t delta);
}

}
