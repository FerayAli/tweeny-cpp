#pragma once
#include <string>

namespace tweeny
{

struct scope
{
	enum class pause_mode_t
	{
		inherit,
		process,
		stop
	};

	std::string id;
	pause_mode_t pause_mode = pause_mode_t::inherit;
};

} //end of namespace tweeny
