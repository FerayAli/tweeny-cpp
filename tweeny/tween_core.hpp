#pragma once
#include "tween_core.h"
#include <numeric>

namespace tweeny
{

template<typename TargetType>
tween_value<TargetType>
tween_value_from_to(const TargetType& begin,
					const TargetType& end,
					const duration_t& duration,
					const ease_t& ease_func)
{
	auto creator = [begin,
					end,
					duration,
					ease_func]
	(tween_value<TargetType>& self) mutable
	{
		info_t<TargetType> info;
		info.begin = begin;
		info.end = end;
		info.current = begin;
		info.elapsed = duration_t::zero();
		info.duration = duration;
		info.progress = 0.0f;

		if(self.on_begin)
		{
			self.on_begin(std::move(info));
		}

		return create_tween_value_updater(begin,
										  end,
										  duration,
										  ease_func);
	};

	return tween_value<TargetType>(std::move(creator), duration);
}

template<typename TargetType>
tween_action
tween_from_to(TargetType& object,
			  const decltype(std::decay_t<TargetType>(object))& begin,
			  const decltype(std::decay_t<TargetType>(object))& end,
			  const duration_t& duration,
			  const sentinel_t& sentinel,
			  const ease_t& ease_func)
{
	auto creator = [&object,
					begin,
					end,
					sentinel,
					ease_func](tween_action& self)
	{
		if(self.on_begin)
		{
			self.on_begin();
		}

		auto initialize_func = [begin](TargetType*, const sentinel_t&)
		{
			return begin;
		};

		auto updater_func = [](TargetType* object, const TargetType& next)
		{
			(*object) = next;
		};

		return create_tween_updater(&object,
									end,
									sentinel,
									std::move(initialize_func),
									std::move(updater_func),
									ease_func);
	};

	return tween_action(std::move(creator), duration);
}

template<typename TargetType>
tween_action
tween_from_to(const std::shared_ptr<TargetType>& object,
			  const decltype(std::decay_t<TargetType>(*object))& begin,
			  const decltype(std::decay_t<TargetType>(*object))& end,
			  const duration_t& duration,
			  const ease_t& ease_func)
{
    return tween_from_to(*object.get(), begin, end, duration, object, ease_func);
}

template<typename T, typename U>
tween_action
tween_to(T& object,
		 const U& end,
		 const duration_t& duration,
		 const sentinel_t& sentinel,
		 const ease_t& ease_func)
{
	static_assert(std::is_convertible<T, U>::value, "Parameters should be convertable.");

	auto creator = [&object,
					end,
					sentinel,
					ease_func](tween_action& self)
	{
		if(self.on_begin)
		{
			self.on_begin();
		}

		auto initialize_func = [](T* object, sentinel_t sentinel)
		{
			if(sentinel.expired())
			{
				return T{};
			}
			return (*object);
		};

		auto updater_func = [](T* object, T next)
		{
			(*object) = next;
		};

		return create_tween_updater(&object,
									end,
									sentinel,
									std::move(initialize_func),
									std::move(updater_func),
									ease_func);
	};

    return tween_action(std::move(creator), duration);
}

template<typename TargetType>
tween_action
tween_to(const std::shared_ptr<TargetType>& object,
		 const decltype(std::decay_t<TargetType>(*object))& end,
		 const duration_t& duration,
		 const ease_t& ease_func)
{
	return tween_to(*object.get(), end, duration, object, ease_func);
}

template<typename TargetType>
tween_action
tween_by(TargetType& object,
		 const decltype(std::decay_t<TargetType>(object))& amount,
		 const duration_t& duration,
		 const sentinel_t& sentinel,
		 const ease_t& ease_func)
{
	auto creator = [&object,
					amount,
					sentinel,
					ease_func](tween_action& self)
	{
		if(self.on_begin)
		{
			self.on_begin();
		}

		auto initialize_func = [](TargetType*, sentinel_t)
		{
			return TargetType{};
		};

		auto updater_func = [prev = TargetType{}](TargetType* object, TargetType next) mutable
		{
			(*object) += (next - prev);
			prev = next;
		};

		return create_tween_updater(&object,
									amount,
									sentinel,
									std::move(initialize_func),
									std::move(updater_func),
									ease_func);
	};

	return tween_action(std::move(creator), duration);
}

template<typename TargetType>
tween_action
tween_by(const std::shared_ptr<TargetType>& object,
		 decltype(std::decay_t<TargetType>(*object)) amount,
		 const duration_t& duration,
		 const ease_t& ease_func)
{
	return tween_by(*object.get(), amount, duration, object, ease_func);
}

template<typename T1, typename T2, typename... TweenType>
tween_action sequence(const T1& tween1, const T2& tween2, const TweenType&... tween)
{
    std::vector<std::shared_ptr<tween_base_impl>> tween_holder =
    {
		std::make_shared<T1>(tween1),
		std::make_shared<T2>(tween2),
		std::make_shared<TweenType>(tween)...
    };

	return sequence(tween_holder);
}

template<typename TargetType>
tween_action sequence(const std::vector<tween_impl<TargetType>>& tweenies)
{
	std::vector<std::shared_ptr<tween_base_impl>> tween_holder;
	tween_holder.reserve(tweenies.size());
	for(const auto& tween : tweenies)
	{
		tween_holder.emplace_back(std::make_shared<tween_impl<TargetType>>(tween));
	}

	return sequence(tween_holder);
}


template<typename T1, typename T2, typename... TweenType>
tween_action together(T1&& tween1, T2&& tween2, TweenType&&... tween)
{
	std::vector<std::shared_ptr<tween_base_impl>> tween_holder =
	{
		std::make_shared<decltype(std::decay_t<T1>(tween1))>(std::forward<T1>(tween1)),
		std::make_shared<decltype(std::decay_t<T2>(tween2))>(std::forward<T1>(tween2)),
		std::make_shared<decltype(std::decay_t<TweenType>(tween))>(std::forward<TweenType>(tween))...
	};

	return together(tween_holder);
}

template<typename TargetType>
tween_action together(const std::vector<tween_impl<TargetType>>& tweenies)
{
	std::vector<std::shared_ptr<tween_base_impl>> tween_holder;
	tween_holder.reserve(tweenies.size());
	for(const auto& tween : tweenies)
	{
		tween_holder.emplace_back(std::make_shared<tween_impl<TargetType>>(tween));
	}

	return together(tween_holder);
}

template<typename TweenType>
tween_action repeat(TweenType& tween, size_t times)
{
	auto updater = [tween,
					times,
					elapsed = size_t(0),
					finished = false]
		(duration_t delta, tween_action& self) mutable
	{
		if(finished)
		{
			return state_t::finished;
		}

		if(elapsed > 0)
		{
			if(tween_private::is_stop_when_finished_requested(self))
			{
				tween_private::stop_when_finished(tween);
			}
		}

		auto state = tween_private::update(tween, delta);
		if(state == state_t::finished)
		{
			if(elapsed > 0)
			{
				if(tween_private::is_stop_when_finished_requested(self))
				{
					finished = true;
					return state_t::finished;
				}
			}

			if(times == 0)
			{
				tween_private::start(tween);
				elapsed++;
			}
			else
			{
				if(elapsed >= times)
				{
					finished = true;
					return state_t::finished;
				}

				tween_private::start(tween);
				elapsed++;
			}
		}
		return state_t::running;
	};

	auto creator = [updater = std::move(updater)](tween_action& self) mutable
	{
		if(self.on_begin)
		{
			self.on_begin();
		}

		return updater;
	};

	duration_t duration = 0ms;
	if(times > 0)
	{
		duration = times * tween.get_duration();
	}

	return tween_action(std::move(creator), duration);
}

template<typename TweenType>
tween_action repeat(TweenType& tween, const sentinel_t& sentinel, size_t times)
{

}

} //end of namespace tweeny
