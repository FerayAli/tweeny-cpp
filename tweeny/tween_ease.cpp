#include "tween_ease.h"
#include "tween_math.h"
#include <math.h>

namespace tweeny
{
using namespace math;

float ease::linear(float x)
{
    return x;
}

float ease::smooth_start2(float x)
{
    return square(x, 2);
}

float ease::smooth_start3(float x)
{
    return square(x, 3);
}

float ease::smooth_stop2(float x)
{
    return flip(square(flip(x), 2));
}

float ease::smooth_stop3(float x)
{
    return flip(square(flip(x), 3));
}

float ease::smooth_step2(float x)
{
    return crossfade(smooth_start2(x), smooth_stop2(x), x);
}

float ease::bell_curve(float x)
{
    return smooth_stop3(x) * smooth_start3(x);
}

float ease::arch(float x)
{
    return scale(flip(x), x);
}

float ease::bounce_bottom(float x)
{
    return std::fabs(x);
}

float ease::bounce_top(float x)
{
    return 1.0f - std::fabs(1.0f - x);
}

float ease::bounce_bottom_top(float x)
{
    return bounce_top(bounce_bottom(x));
}

}
