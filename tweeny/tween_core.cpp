#include "tween_core.h"

namespace tweeny
{

tween_action sequence(const std::vector<std::shared_ptr<tween_base_impl>>& tweenies)
{
	if(tweenies.empty())
	{
		return tween_action();
	}

	duration_t duration = 0ms;
	for(auto& tween : tweenies)
	{
		duration += tween->get_duration();
	}

	auto updater = [tweenies
					, current_tween_idx = size_t(0)
					, prev_elapsed = duration_t::zero()
					, start_required = true
					, finished = false]
		(duration_t delta, tween_action& self) mutable
	{
		if(finished)
		{
			return state_t::finished;
		}

		if(start_required)
		{
			tween_private::start(*tweenies.at(current_tween_idx));
			prev_elapsed = duration_t::zero();
			start_required = false;
		}

		auto& current_tween = tweenies.at(current_tween_idx);
		auto state = tween_private::update(*current_tween, delta);

		auto elapsed_diff = current_tween->get_elapsed() - prev_elapsed;
		prev_elapsed = current_tween->get_elapsed();

		tween_private::update_elapsed(self, elapsed_diff);
		if(self.on_step)
		{
			self.on_step();
		}

		if(state == state_t::finished)
		{
			current_tween_idx++;
			if(current_tween_idx == tweenies.size())
			{
				finished = true;
				if(self.on_end)
				{
					self.on_end();
				}
				return state_t::finished;
			}
			start_required = true;
		}
		return state_t::running;
	};

	auto creator = [updater = std::move(updater)](tween_action& self)
	{
		if(self.on_begin)
		{
			self.on_begin();
		}
		return updater;
	};

	return tween_action(std::move(creator), duration);
}

tween_action together(const std::vector<std::shared_ptr<tween_base_impl>>& tweenies)
{
	if(tweenies.empty())
	{
		return tween_action();
	}

	duration_t duration = 0ms;
	for(const auto& tween : tweenies)
	{
		duration = std::max(tween->get_duration(), duration);
	}

	auto updater = [tweenies,
					start_required = true,
					finished = false](duration_t delta, tween_action& self) mutable
	{
		if(finished)
		{
			return state_t::finished;
		}

		if(start_required)
		{
			for(auto& tween : tweenies)
			{
				tween_private::start(*tween);
			}
			start_required = false;
		}

		if(tween_private::is_stop_when_finished_requested(self))
		{
			for(auto& tween : tweenies)
			{
				tween_private::stop_when_finished(*tween);
			}
		}

		finished = true;
		for(auto& tween : tweenies)
		{
			const auto state = tween_private::update(*tween, delta);
			finished &= (state == state_t::finished);
		}

		tween_private::update_elapsed(self, delta);
		if(self.on_step)
		{
			self.on_step();
		}

		if(finished)
		{
			if(self.on_end)
			{
				self.on_end();
			}
			return state_t::finished;
		}

		return state_t::running;
	};

	auto creator = [updater = std::move(updater)](tween_action& self)
	{
		if(self.on_begin)
		{
			self.on_begin();
		}

		return updater;
	};

	return tween_action(std::move(creator), duration);
}

tween_action delay(const duration_t& duration)
{
	auto updater = [finished = false](duration_t delta, tween_action& self) mutable
	{
		if(finished)
		{
			return state_t::finished;
		}

		tween_private::update_elapsed(self, delta);
		if(self.on_step)
		{
			self.on_step();
		}

		if(self.get_elapsed() == self.get_duration())
		{
			finished = true;
			if(self.on_end)
			{
				self.on_end();
			}
			return state_t::finished;
		}

		return state_t::running;
	};

	auto creator = [updater = std::move(updater)](tween_action& self)
	{
		if(self.on_begin)
		{
			self.on_begin();
		}

		return updater;
	};

	return tween_action(std::move(creator), duration);
}

tween_action delay(const duration_t& duration, const sentinel_t& sentinel)
{
	auto updater = [sentinel, finished = false](duration_t delta, tween_action& self) mutable
	{
		if(finished)
		{
			return state_t::finished;
		}

		if(sentinel.expired())
		{
			finished = true;
			return state_t::finished;
		}

		tween_private::update_elapsed(self, delta);
		if(self.on_step)
		{
			self.on_step();
		}

		if(self.get_elapsed() == self.get_duration())
		{
			finished = true;
			if(self.on_end)
			{
				self.on_end();
			}
			return state_t::finished;
		}

		return state_t::running;
	};

	auto creator = [updater = std::move(updater)](tween_action& self)
	{
		if(self.on_begin)
		{
			self.on_begin();
		}

		return updater;
	};

	return tween_action(std::move(creator), duration);
}

}
