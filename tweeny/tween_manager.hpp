#pragma once
#include "tween_manager.h"

namespace tweeny
{

template<typename T>
tween_id_t tween_manager::start(tween_impl<T> tween)
{
	tween_info& info = tweenies_[tween.get_id()];

	info.tween = std::make_unique<tween_impl<T>>(std::move(tween));

	tween_private::start(*info.tween);

	auto i = info.tween->get_id();
	return i;
}

template<typename T>
void tween_manager::stop(const tween_impl<T>& tween)
{
	stop(tween.get_id());
}

template<typename T>
void tween_manager::pause(const tween_impl<T>& tween)
{
	return pause(tween.get_id());
}

template<typename T>
void tween_manager::resume(const tween_impl<T>& tween)
{
	return resume(tween.get_id());
}

template<typename T>
void tween_manager::stop_when_finished(const tween_impl<T>& tween)
{
	stop_when_finished(tween.get_id());
}

template<typename T>
void tween_manager::stop_and_finish(const tween_impl<T>& tween, duration_t finish_after)
{
	stop_when_finished(tween.get_id(), finish_after);
}

template<typename T>
bool tween_manager::is_stopping(const tween_impl<T>& tween)
{
	return is_stopping(tween.get_id());
}

template<typename T>
bool tween_manager::is_running(const tween_impl<T>& tween)
{
	return is_running(tween.get_id());
}

template<typename T>
bool tween_manager::is_paused(const tween_impl<T>& tween)
{
	return is_paused(tween.get_id());
}

template<typename T>
void tween_manager::set_speed_multiplier(const tween_impl<T>& tween, float speed_multiplier)
{
	set_speed_multiplier(tween.get_id(), speed_multiplier);
}

template<typename T>
float tween_manager::get_speed_multiplier(const tween_impl<T>& tween)
{
	return get_speed_multiplier(tween.get_id());
}

}
