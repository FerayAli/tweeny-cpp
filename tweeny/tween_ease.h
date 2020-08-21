#pragma once
#include "tween_common.h"

namespace tweeny
{
namespace ease
{

float cubic_bezier(float x1, float y1, float x2, float y2);

float linear(float x);

float smooth_start2(float x);
float smooth_start3(float x);

float smooth_stop2(float x);
float smooth_stop3(float x);

float smooth_step2(float x);
float bell_curve(float x);

float arch(float x);

float bounce_bottom(float x);
float bounce_top(float x);
float bounce_bottom_top(float x);

}
}
