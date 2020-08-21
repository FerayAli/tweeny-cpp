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
struct tween_non_fundamental_export {};

template<typename Object>
struct tween_access{};

namespace math
{
//Make things constexpr
float square(float x, uint32_t n);
float flip(float x);
float mix(float a, float b, float weight, float t);
float crossfade(float a, float b, float t);
float scale(float a, float t);
float reverse_scale(float a, float t);
float arch(float t);
}

}
