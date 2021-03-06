#pragma once
#include "tween_ex.h"
#include "tween_core.h"
#include "tween_math.h"
#include <vector>

namespace tweeny
{

template<typename Object, typename TargetType>
tween_action
move_from_to(Object& object,
			 const TargetType& begin,
			 const TargetType& end,
             const duration_t& duration,
			 const sentinel_t& sentinel,
			 const ease_t& ease_func)
{
    auto creator = [&object
					, begin = begin
					, end = end
					, sentinel = sentinel
					, ease_func = ease_func]
    (tween_action& self)
    {
        if(self.on_begin)
        {
            self.on_begin();
        }

        auto initialize_func = [begin](Object*, sentinel_t)
        {
            return begin;
        };

		auto updater_func = [](Object* object, const decltype(std::decay_t<TargetType>(end))& next) mutable
        {
			tween_access<Object>::set_position(*object, next);
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

template<typename Object, typename TargetType>
tween_action
move_from_to(const std::shared_ptr<Object>& object,
			 TargetType&& begin,
			 TargetType&& end,
			 const duration_t& duration,
			 const ease_t& ease_func)
{
	return move_from_to(*object.get(),
						std::forward<TargetType>(begin),
						std::forward<TargetType>(end),
						duration,
						object,
						ease_func);
}

//template<typename Object, typename TargetType>
//tween_action
//move_from_to_local(Object& object,
//                   TargetType begin,
//                   TargetType end,
//                   duration_t duration,
//                   sentinel_t sentinel)
//{
//    auto initialize_func = [begin](Object*, sentinel_t)
//    {
//        return begin;
//    };

//    auto updater_func = [](Object* object, TargetType next) mutable
//    {
//		tween_access<Object>::set_position_local(*object, next);
//    };

////    auto creator = create_tween_updater(&object,
////                                        std::move(end),
////                                        std::move(sentinel),
////                                        std::move(initialize_func),
////                                        std::move(updater_func));

////    return tween_action(std::move(creator), std::move(duration));
//    return tween_action();
//}

//template<typename Object, typename TargetType>
//tween_action
//move_from_to_local(Object& object,
//                   TargetType begin,
//                   TargetType end,
//                   duration_t duration)
//{
//    return move_from_to_local(*object.get(), begin, end, duration, object);
//}

template<typename Object, typename TargetType>
tween_action
move_to(Object& object,
		TargetType&& end,
		const duration_t& duration,
		const sentinel_t& sentinel,
		const ease_t& ease_func)
{
	auto creator = [&object
					, end = std::forward<TargetType>(end)
					, sentinel = sentinel
					, ease_func = ease_func]
		(tween_action& self)
	{
		if(self.on_begin)
		{
			self.on_begin();
		}

		auto initialize_func = [](Object* object, sentinel_t sentinel)
		{
			if(sentinel.expired())
			{
				return decltype(std::decay_t<TargetType>(end)){};
			}
			return tween_access<Object>::get_position(*object);
		};

		auto updater_func = [](Object* object, const decltype(std::decay_t<TargetType>(end))& next) mutable
		{
			tween_access<Object>::set_position(*object, next);
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

template<typename Object, typename TargetType>
tween_action
move_to(const std::shared_ptr<Object>& object,
		TargetType&& end,
		const duration_t& duration,
		const ease_t& ease_func)
{
	return move_to(*object.get(), std::forward<TargetType>(end), duration, object, ease_func);
}

//template<typename Object, typename TargetType>
//tween_action
//move_to_local(Object& object,
//             TargetType end,
//             duration_t duration,
//             sentinel_t sentinel)
//{
//    auto initialize_func = [](Object* object, sentinel_t sentinel)
//    {
//        if(sentinel.expired())
//        {
//            return TargetType{};
//        }
//		return tween_access<Object>::get_position_local(*object);
//    };

//    auto updater_func = [](Object* object, TargetType next) mutable
//    {
//		tween_access<Object>::set_position_local(*object, next);
//    };

////    auto creator = create_tween_updater(&object,
////                                        std::move(end),
////                                        std::move(sentinel),
////                                        std::move(initialize_func),
////                                        std::move(updater_func));

////    return tween_action(std::move(creator), std::move(duration));
//    return tween_action();
//}

//template<typename Object, typename TargetType>
//tween_action
//move_to_local(std::shared_ptr<Object>& object,
//              TargetType end,
//              duration_t duration)
//{
//    return move_to_local(*object.get(), end, duration, object);
//}

template<typename Object, typename TargetType>
tween_action
move_by(Object& object,
		TargetType&& amount,
		const duration_t& duration,
		const sentinel_t& sentinel,
		const ease_t& ease_func)
{
	auto creator = [&object
					, amount = std::forward<TargetType>(amount)
					, sentinel = sentinel
					, ease_func = ease_func]
		(tween_action& self)
	{
		if(self.on_begin)
		{
			self.on_begin();
		}

		auto initialize_func = [](Object*, sentinel_t)
		{
			return decltype(std::decay_t<TargetType>(amount)){};
		};

		auto updater_func = [prev = decltype(std::decay_t<TargetType>(amount)){}]
			(Object* object, const decltype(std::decay_t<TargetType>(amount))& next) mutable
		{
			const auto current = tween_access<Object>::get_position(*object);
			tween_access<Object>::set_position(*object, current + (next - prev));

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

template<typename Object, typename TargetType>
tween_action
move_by(const std::shared_ptr<Object>& object,
		TargetType&& amount,
		const duration_t& duration,
		const ease_t& ease_func)
{
	return move_by(*object.get(), std::forward<TargetType>(amount), duration, object, ease_func);
}

template<typename Object, typename TargetType>
tween_action
scale_from_to(Object& object,
			  TargetType&& begin,
			  TargetType&& end,
			  const duration_t& duration,
			  const sentinel_t& sentinel,
			  const ease_t& ease_func)
{
	auto creator = [&object
					, begin = std::forward<TargetType>(begin)
					, end = std::forward<TargetType>(end)
					, sentinel = sentinel
					, ease_func = ease_func]
		(tween_action& self)
	{
		if(self.on_begin)
		{
			self.on_begin();
		}

		auto initialize_func = [begin](Object*, sentinel_t)
		{
			return begin;
		};

		auto updater_func = [](Object* object, const decltype(std::decay_t<TargetType>(end))& next) mutable
		{
			tween_access<Object>::set_scale(*object, next);
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

template<typename Object, typename TargetType>
tween_action
scale_from_to(const std::shared_ptr<Object>& object,
			  TargetType&& begin,
			  TargetType&& end,
			  const duration_t& duration,
			  const ease_t& ease_func)
{
	return scale_from_to(*object.get(),
						 std::forward<TargetType>(begin),
						 std::forward<TargetType>(end),
						 duration,
						 object,
						 ease_func);
}

//template<typename Object, typename TargetType>
//tween_action
//scale_from_to_local(Object& object,
//                   TargetType end,
//                   duration_t duration,
//                   sentinel_t sentinel);

//template<typename Object, typename TargetType>
//tween_action
//scale_from_to_local(Object& object,
//                   TargetType end,
//                   duration_t duration);

template<typename Object, typename TargetType>
tween_action
scale_to(Object& object,
		 TargetType&& end,
		 const duration_t& duration,
		 const sentinel_t& sentinel,
		 const ease_t& ease_func)
{
	auto creator = [&object
					, end = std::forward<TargetType>(end)
					, sentinel = sentinel
					, ease_func = ease_func]
		(tween_action& self)
	{
		if(self.on_begin)
		{
			self.on_begin();
		}

		auto initialize_func = [](Object* object, sentinel_t sentinel)
		{
			if(sentinel.expired())
			{
				return decltype(std::decay_t<TargetType>(end)){};
			}
			return tween_access<Object>::get_scale(*object);
		};

		auto updater_func = [](Object* object, const decltype(std::decay_t<TargetType>(end))& next) mutable
		{
			tween_access<Object>::set_scale(*object, next);
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

template<typename Object, typename TargetType>
tween_action
scale_to(const std::shared_ptr<Object>& object,
		 TargetType&& end,
		 const duration_t& duration,
		 const ease_t& ease_func)
{
	return scale_to(*object.get(), std::forward<TargetType>(end), duration, object, ease_func);
}

//template<typename Object, typename TargetType>
//tween_action
//scale_to_local(Object& object,
//             TargetType end,
//             duration_t duration,
//             sentinel_t sentinel);

//template<typename Object, typename TargetType>
//tween_action
//scale_to_local(Object& object,
//             TargetType end,
//             duration_t duration);

template<typename Object, typename TargetType>
tween_action
scale_by(Object& object,
		 TargetType&& amount,
		 const duration_t& duration,
		 const sentinel_t& sentinel,
		 const ease_t& ease_func)
{
	auto creator = [&object
					, amount = std::forward<TargetType>(amount)
					, sentinel = sentinel
					, ease_func = ease_func]
		(tween_action& self)
	{
		if(self.on_begin)
		{
			self.on_begin();
		}

		auto initialize_func = [](Object*, sentinel_t)
		{
			return decltype(std::decay_t<TargetType>(amount)){};
		};

		auto updater_func = [prev = TargetType{}]
			(Object* object, const decltype(std::decay_t<TargetType>(amount))& next) mutable
		{
			const auto current = tween_access<Object>::get_scale(*object);
			tween_access<Object>::set_scale(*object, current + (next - prev));

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

template<typename Object, typename TargetType>
tween_action
scale_by(Object& object,
		 TargetType&& end,
		 const duration_t& duration,
		 const ease_t& ease_func)
{
	return scale_by(*object.get(), std::forward<TargetType>(end), duration, object, ease_func);
}

template<typename Object, typename TargetType>
tween_action
rotate_from_to(Object& object,
			   TargetType&& begin,
			   TargetType&& end,
			   const duration_t& duration,
			   const sentinel_t& sentinel,
			   const ease_t& ease_func)
{
	auto creator = [&object
					, begin = std::forward<TargetType>(begin)
					, end = std::forward<TargetType>(end)
					, sentinel = sentinel
					, ease_func = ease_func]
		(tween_action& self)
	{
		if(self.on_begin)
		{
			self.on_begin();
		}

		auto initialize_func = [begin](Object*, sentinel_t)
		{
			return begin;
		};

		auto updater_func = [](Object* object, const decltype(std::decay_t<TargetType>(end))& next) mutable
		{
			tween_access<Object>::set_rotation(*object, next);
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

template<typename Object, typename TargetType>
tween_action
rotate_from_to(const std::shared_ptr<Object>& object,
			   TargetType&& begin,
			   TargetType&& end,
			   const duration_t& duration,
			   const ease_t& ease_func)
{
	return rotate_from_to(*object.get(),
						  std::forward<TargetType>(begin),
						  std::forward<TargetType>(end),
						  duration,
						  object,
						  ease_func);
}

//template<typename Object, typename TargetType>
//tween_action
//rotate_from_to_local(Object& object,
//                   TargetType end,
//                   duration_t duration,
//                   sentinel_t sentinel);

//template<typename Object, typename TargetType>
//tween_action
//rotate_from_to_local(Object& object,
//                   TargetType end,
//                   duration_t duration);

template<typename Object, typename TargetType>
tween_action
rotate_to(Object& object,
		  TargetType&& end,
		  const duration_t& duration,
		  const sentinel_t& sentinel,
		  const ease_t& ease_func)
{
	auto creator = [&object
					, end = std::forward<TargetType>(end)
					, sentinel = sentinel
					, ease_func = ease_func]
		(tween_action& self)
	{
		if(self.on_begin)
		{
			self.on_begin();
		}

		auto initialize_func = [](Object* object, sentinel_t sentinel)
		{
			if(sentinel.expired())
			{
				return decltype(std::decay_t<TargetType>(end)){};
			}
			return tween_access<Object>::get_rotation(*object);
		};

		auto updater_func = [](Object* object, const decltype(std::decay_t<TargetType>(end))& next) mutable
		{
			tween_access<Object>::set_rotation(*object, next);
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

template<typename Object, typename TargetType>
tween_action
rotate_to(const std::shared_ptr<Object>& object,
		  TargetType&& end,
		  const duration_t& duration,
		  const ease_t& ease_func)
{
	return rotate_to(*object.get(), std::forward<TargetType>(end), duration, ease_func);
}

//template<typename Object, typename TargetType>
//tween_action
//rotate_to_local(Object& object,
//             TargetType end,
//             duration_t duration,
//             sentinel_t sentinel);

//template<typename Object, typename TargetType>
//tween_action
//rotate_to_local(Object& object,
//             TargetType end,
//             duration_t duration);

template<typename Object, typename TargetType>
tween_action
rotate_by(Object& object,
		  TargetType&& amount,
		  const duration_t& duration,
		  const sentinel_t& sentinel,
		  const ease_t& ease_func)
{
	auto creator = [&object
					, amount = std::forward<TargetType>(amount)
					, sentinel = sentinel
					, ease_func = ease_func]
		(tween_action& self)
	{
		if(self.on_begin)
		{
			self.on_begin();
		}

		auto initialize_func = [](Object*, sentinel_t)
		{
			return decltype(std::decay_t<TargetType>(amount)){};
		};

		auto updater_func = [prev = TargetType{}]
			(Object* object, const decltype(std::decay_t<TargetType>(amount))& next) mutable
		{
			const auto current = tween_access<Object>::get_rotation(*object);
			tween_access<Object>::set_rotation(*object, current + (next - prev));

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

template<typename Object, typename TargetType>
tween_action
rotate_by(const std::shared_ptr<Object>& object,
		  TargetType&& amount,
		  const duration_t& duration,
		  const ease_t& ease_func)
{
	return rotate_by(*object.get(), std::forward<TargetType>(amount), duration, object, ease_func);
}

template<typename Object, typename TargetType>
tween_action
fade_from_to(Object& object,
			 TargetType&& begin,
			 TargetType&& end,
			 const duration_t& duration,
			 const sentinel_t& sentinel,
			 const ease_t& ease_func)
{
	auto creator = [&object
					, begin = std::forward<TargetType>(begin)
					, end = std::forward<TargetType>(end)
					, sentinel = sentinel
					, ease_func = ease_func]
		(tween_action& self)
	{
		if(self.on_begin)
		{
			self.on_begin();
		}

		auto initialize_func = [begin](Object*, sentinel_t)
		{
			return begin;
		};

		auto updater_func = [](Object* object, const decltype(std::decay_t<TargetType>(end))& next) mutable
		{
			tween_access<Object>::set_opacity(*object, next);
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

template<typename Object, typename TargetType>
tween_action
fade_from_to(const std::shared_ptr<Object>& object,
			 TargetType&& begin,
			 TargetType&& end,
			 const duration_t& duration,
			 const ease_t& ease_func)
{
	return fade_from_to(*object.get(),
						std::forward<TargetType>(begin),
						std::forward<TargetType>(end),
						duration,
						object,
						ease_func);
}

template<typename Object, typename TargetType>
tween_action
fade_to(Object& object,
		TargetType&& end,
		const duration_t& duration,
		const sentinel_t& sentinel,
		const ease_t& ease_func)
{
	auto creator = [&object
					, end = std::forward<TargetType>(end)
					, sentinel = sentinel
					, ease_func = ease_func]
		(tween_action& self)
	{
		if(self.on_begin)
		{
			self.on_begin();
		}

		auto initialize_func = [](Object* object, sentinel_t sentinel)
		{
			if(sentinel.expired())
			{
				return decltype(std::decay_t<TargetType>(end)){};
			}
			return tween_access<Object>::get_opacity(*object);
		};

		auto updater_func = [](Object* object, const decltype(std::decay_t<TargetType>(end))& next) mutable
		{
			tween_access<Object>::set_opacity(*object, next);
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

template<typename Object, typename TargetType>
tween_action
fade_to(const std::shared_ptr<Object>& object,
		TargetType&& end,
		const duration_t& duration,
		const ease_t& ease_func)
{
	return fade_to(*object.get(), std::forward<TargetType>(end), duration, object, ease_func);
}

template<typename Object, typename TargetType>
tween_action
fade_by(Object& object,
		TargetType&& amount,
		const duration_t& duration,
		const sentinel_t& sentinel,
		const ease_t& ease_func)
{
	auto creator = [&object
					, amount = std::forward<TargetType>(amount)
					, sentinel = sentinel
					, ease_func = ease_func]
		(tween_action& self)
	{
		if(self.on_begin)
		{
			self.on_begin();
		}

		auto initialize_func = [](Object*, sentinel_t)
		{
			return decltype(std::decay_t<TargetType>(amount)){};
		};

		auto updater_func = [prev = TargetType{}]
			(Object* object, const decltype(std::decay_t<TargetType>(amount))& next) mutable
		{
			const auto current = tween_access<Object>::get_opacity(*object);
			tween_access<Object>::set_opacity(*object, current + (next - prev));

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

template<typename Object, typename TargetType>
tween_action
fade_by(const std::shared_ptr<Object>& object,
		TargetType&& amount,
		const duration_t& duration,
		const ease_t& ease_func)
{
	return fade_by(*object.get(), std::forward<TargetType>(amount), duration, object, ease_func);
}

template<typename Object, typename TargetType>
tween_action
shake(Object& object,
	  TargetType initial_force,
	  const sentinel_t& sentinel,
	  const duration_t& duration,
	  uint32_t shake_count)
{
	shake_count = math::clamp(shake_count, 1u, 25u);
	const auto total_action_count = shake_count * 4;
	const auto action_duration = duration / total_action_count;

	std::vector<tween_action> tweenies;
	tweenies.reserve(total_action_count);
	for(size_t i = 0; i < shake_count; i++)
	{
		tweenies.emplace_back(move_by(object, initial_force, action_duration, sentinel));
		tweenies.emplace_back(move_by(object, -initial_force, action_duration, sentinel));
		tweenies.emplace_back(move_by(object, -initial_force, action_duration, sentinel));
		tweenies.emplace_back(move_by(object, initial_force, action_duration, sentinel));
		initial_force = initial_force * 0.75f;
	}

	return sequence(tweenies);
}

template<typename Object, typename TargetType>
tween_action
shake(const std::shared_ptr<Object>& object,
	  TargetType initial_force,
	  const duration_t& duration,
	  uint32_t shake_count)
{
	return shake(*object.get(), std::move(initial_force), object, duration, shake_count);
}

} //end of namespace tweeny
