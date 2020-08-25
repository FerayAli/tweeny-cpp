#pragma once
//#include <tweeny/tweeny.h>
//#include <iostream>
//using namespace tweeny;

//template<typename Tween, typename T>
//void RunAndTest(const Tween& action,
//				const T& expected,
//				duration_t runFor = 1s)
//{
//	tweeny::start(action);

//	duration_t start = 0ms;
//	while(start < runFor)
//	{
//		tweeny::detail::update(16ms);
//		start += 16ms;
//	}

//	static uint64_t testCounter = 0;
//	std::cout << "Test " << ++testCounter << ((current == expected) ? " OK" : " FAIL");
//}

//void test_core()
//{
//	auto SENTINEL = std::make_shared<int>();
//	uint8_t value = 111;
//	auto action = tween_from_to(value, 222, 1s, SENTINEL);
//	RunAndTest(action, 222);
//}

