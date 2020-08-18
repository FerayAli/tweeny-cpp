#pragma once
#include <memory>
#include <chrono>
using namespace std::chrono_literals;

namespace tweeny
{
using duration_t = std::chrono::nanoseconds;
using sentinel_t = std::weak_ptr<void>;
using tween_id_t = size_t;
enum class state_t
{
    running,
    paused,
    finished
};

enum class direction_t
{
    forward,
    backward
};

template<typename Object>
struct is_shared_ptr : std::false_type {};

template<typename Object>
struct is_shared_ptr<std::shared_ptr<Object>> : std::true_type {};

template<typename Object>
struct tween_non_fundamental_export {};

//Calculate the required speed multiplier in order to finish a running
//tween in given amount of time. This multiplier can the be used as parameter
//to set_speed function.
//float calculate_speed_multiplier()
}
