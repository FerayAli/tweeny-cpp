#include "tweeny.h"
#include "detail/tweeny_internal.h"

namespace tweeny
{

void open_scope(const std::string& scope_name)
{
    detail::set_current_scope_name(scope_name);
    detail::get_managers()[detail::get_current_scope_name()] = std::make_shared<tween_manager>();
}

void stop_tweenies_in_scope(const std::string& scope_name)
{
    auto& managers = detail::get_managers();
    auto iter = managers.find(scope_name);
    if(iter != managers.end())
    {
        iter->second->stop_all();
    }
}

void close_scope()
{
    if(detail::get_current_scope_name() == "__internal_scope__")
    {
        return;
    }

    auto& managers = detail::get_managers();
    auto iter = managers.find(detail::get_current_scope_name());
    if(iter != managers.end() && (iter->second->get_tweenies_count() == 0))
    {
        managers.erase(iter);
    }

    detail::set_current_scope_name("__internal_scope__");
}

void stop(tween_id_t id)
{
    detail::get_active_manager()->stop(id);
}


}
