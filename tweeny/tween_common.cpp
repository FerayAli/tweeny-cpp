#include "tween_common.h"

namespace tweeny
{

sentinel_t global_sentinel()
{
	static auto sentinel = std::make_shared<int>();
	return sentinel;
}


}
