#pragma once
#include <memory>
#include <chrono>
#include <functional>

using namespace std::chrono_literals;

namespace tweeny
{

using duration_t = std::chrono::nanoseconds;
using sentinel_t = std::weak_ptr<void>;
using tween_id_t = size_t;
using ease_t = std::function<float(float)>;

enum class state_t
{
    running,
    paused,
    finished
};

template<typename Object>
struct tween_access{};

}
