#include "tweeny_internal.h"

namespace tweeny
{
namespace detail
{
const std::string GLOBAL_SCOPE = "__internal_scope__";

std::string current_scope_ = GLOBAL_SCOPE;
detail::managers managers_ = {{GLOBAL_SCOPE, std::make_shared<tween_manager>()}};

const std::shared_ptr<tween_manager>& get_active_manager()
{
    return managers_.at(current_scope_);
}

void update(duration_t delta)
{
    for(auto& kvp : managers_)
    {
        kvp.second->update(delta);
    }
}

managers& get_managers()
{
    return managers_;
}

} //end of namespace detail
} //end of namespace tweeny
