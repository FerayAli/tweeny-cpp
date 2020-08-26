#include "tweeny.h"
#include "detail/tweeny_internal.h"

namespace tweeny
{

void stop(tween_id_t id)
{
	detail::get_active_manager()->stop(id);
}

void pause(const tween_id_t id)
{
	detail::get_active_manager()->pause(id);
}

void resume(const tween_id_t id)
{
	detail::get_active_manager()->resume(id);
}

void stop_when_finished(tween_id_t id)
{
	detail::get_active_manager()->stop_when_finished(id);
}

void stop_and_finish(tween_id_t id, duration_t finish_after)
{
	detail::get_active_manager()->stop_and_finish(id, finish_after);
}

bool is_stopping(tween_id_t id)
{
	return detail::get_active_manager()->is_stopping(id);
}

bool is_running(tween_id_t id)
{
	return detail::get_active_manager()->is_running(id);
}

bool is_paused(tween_id_t id)
{
	return detail::get_active_manager()->is_paused(id);
}

void set_speed_multiplier(tween_id_t id, float speed_multiplier)
{
	detail::get_active_manager()->set_speed_multiplier(id, speed_multiplier);
}

float get_speed_multiplier(tween_id_t id)
{
	return detail::get_active_manager()->get_speed_multiplier(id);
}

}
