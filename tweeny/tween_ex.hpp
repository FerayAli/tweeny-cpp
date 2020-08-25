#pragma once
#include "tween_ex.h"

namespace tweeny
{

template<typename Object, typename TargetType>
tween_action
move_from_to(Object& object,
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

        auto updater_func = [](Object* object, TargetType next) mutable
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
	return move_from_to(*object.get(), begin, end, duration, object, ease_func);
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
				return TargetType{};
			}
			return tween_access<Object>::get_position(*object);
		};

		auto updater_func = [](Object* object, TargetType next) mutable
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

		auto initialize_func = [](Object* object, sentinel_t sentinel)
		{
			if(sentinel.expired())
			{
				return TargetType{};
			}
			return tween_access<Object>::get_position(*object);
		};

		auto updater_func = [prev = TargetType{}](TargetType* object, TargetType next) mutable
		{
			tween_access<Object>::set_position(*object, (next - prev));
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

//template<typename Object, typename TargetType>
//tween_action
//scale_from_to(Object& object,
//             TargetType end,
//             duration_t duration,
//             sentinel_t sentinel);

//template<typename Object, typename TargetType>
//tween_action
//scale_from_to(Object& object,
//             TargetType end,
//             duration_t duration);

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

//template<typename Object, typename TargetType>
//tween_action
//scale_to(Object& object,
//             TargetType end,
//             duration_t duration,
//             sentinel_t sentinel);

//template<typename Object, typename TargetType>
//tween_action
//scale_to(Object& object,
//             TargetType end,
//             duration_t duration);

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

//template<typename Object, typename TargetType>
//tween_action
//scale_by(Object& object,
//             TargetType end,
//             duration_t duration,
//             sentinel_t sentinel);

//template<typename Object, typename TargetType>
//tween_action
//scale_by(Object& object,
//             TargetType end,
//             duration_t duration);

//template<typename Object, typename TargetType>
//tween_action
//rotate_from_to(Object& object,
//             TargetType end,
//             duration_t duration,
//             sentinel_t sentinel);

//template<typename Object, typename TargetType>
//tween_action
//rotate_from_to(Object& object,
//             TargetType end,
//             duration_t duration);

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

//template<typename Object, typename TargetType>
//tween_action
//rotate_to(Object& object,
//             TargetType end,
//             duration_t duration,
//             sentinel_t sentinel);

//template<typename Object, typename TargetType>
//tween_action
//rotate_to(Object& object,
//             TargetType end,
//             duration_t duration);

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

//template<typename Object, typename TargetType>
//tween_action
//rotate_by(Object& object,
//             TargetType end,
//             duration_t duration,
//             sentinel_t sentinel);

//template<typename Object, typename TargetType>
//tween_action
//rotate_by(Object& object,
//             TargetType end,
//             duration_t duration);

//template<typename Object, typename TargetType>
//tween_action
//fade_from_to(Object& object,
//             TargetType end,
//             duration_t duration,
//             sentinel_t sentinel);

//template<typename Object, typename TargetType>
//tween_action
//fade_from_to(Object& object,
//             TargetType end,
//             duration_t duration);

//template<typename Object, typename TargetType>
//tween_action
//fade_to(Object& object,
//             TargetType end,
//             duration_t duration,
//             sentinel_t sentinel);

//template<typename Object, typename TargetType>
//tween_action
//fade_to(Object& object,
//             TargetType end,
//             duration_t duration);

//template<typename Object, typename TargetType>
//tween_action
//fade_by(Object& object,
//             TargetType end,
//             duration_t duration,
//             sentinel_t sentinel);

//template<typename Object, typename TargetType>
//tween_action
//fade_by(Object& object,
//             TargetType end,
//             duration_t duration);

}