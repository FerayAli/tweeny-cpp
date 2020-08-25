#pragma once
#include "tween_manager.h"
#include "tween_scope.h"

namespace tweeny
{
    template<typename T>
    tween_id_t start(tween_impl<T> tween);

    template<typename T>
    void stop(const tween_impl<T>& tween);
    void stop(tween_id_t id);

	template<typename T>
	void pause(const tween_impl<T>& tween);
	void pause(const tween_id_t id);

	template<typename T>
	void resume(const tween_impl<T>& tween);
	void resume(const tween_id_t id);

	template<typename T>
	void stop_when_finished(const tween_impl<T>& tween);
	void stop_when_finished(tween_id_t id);

	template<typename T>
	void stop_and_finish(const tween_impl<T>& tween, duration_t finish_after = 0ms);
	void stop_and_finish(tween_id_t id, duration_t finish_after = 0ms);

	template<typename T>
	bool is_stopping(const tween_impl<T>& tween);
	bool is_stopping(tween_id_t id);

	template<typename T>
	bool is_running(const tween_impl<T>& tween);
	bool is_running(tween_id_t id);

	template<typename T>
	bool is_paused(const tween_impl<T>& tween);
	bool is_paused(tween_id_t id);

	template<typename T>
	void set_speed_multiplier(const tween_impl<T>& tween, float speed_multiplier = 1.0f);
	void set_speed_multiplier(tween_id_t id, float speed_multiplier = 1.0f);

	template<typename T>
	float get_speed_multiplier(const tween_impl<T>& tween);
	float get_speed_multiplier(tween_id_t id);

//########################################################################################

//	scope& push_scope(const std::string& scope_id);
//	void pop_scope(const std::string& scope_id);

//	scope& get_scope(const std::string& scope_id);
//	void clear_scopes();

//	tween_manager& get_scope_manager(const std::string& scope_id);

//	void stop_tweenies_in_scope(const std::string& scope_id);
//	void pause_tweenies_in_scope(const std::string& scope_id);
//	void resume_tweenies_in_scope(const std::string& scope_id);
}

#include "tweeny.hpp"
