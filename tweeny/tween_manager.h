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
	tween_id_t start(tween_impl<T> tween);

	template<typename T>
	void stop(const tween_impl<T>& tween);
    void stop(tween_id_t id);
    void stop_all();

	template<typename T>
	void pause(const tween_impl<T>& tween);
	void pause(const tween_id_t id);
	void pause_all();

	template<typename T>
	void resume(const tween_impl<T>& tween);
	void resume(const tween_id_t id);
	void resume_all();

	template<typename T>
	void stop_when_finished(const tween_impl<T>& tween);
    void stop_when_finished(tween_id_t id);
	void stop_when_finished_all();

	template<typename T>
	void stop_and_finish(const tween_impl<T>& tween, duration_t finish_after = 0ms);
    void stop_and_finish(tween_id_t id, duration_t finish_after = 0ms);
	void stop_and_finish_all();

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

	size_t get_tweenies_count() const;

	void update(duration_t delta);
private:
    struct tween_info
    {
        std::unique_ptr<tween_base_impl> tween;
        uint32_t depth = 0;
    };

    std::unordered_map<tween_id_t, tween_info> tweenies_;
    std::unordered_map<tween_id_t, std::unique_ptr<tween_base_impl>> pending_tweenies_;
};

} //end of namespace tweeny

#include "tween_manager.hpp"
