#pragma once
#include <tweeny/tweeny.h>
#include <iostream>
using namespace tweeny;

static uint64_t testCounter = 0;

template<typename Tween, typename T1, typename T2>
void RunAndTest(const Tween& action,
				T1& current,
				const T2& expected,
				duration_t runFor = 1s)
{
	tweeny::start(action);

	duration_t start = 0ms;
	while(start < runFor)
	{
		tweeny::detail::update(16ms);
		start += 16ms;
	}

	std::cout << "Test " << ++testCounter << ((current == expected) ? ": OK" : ": FAIL") << std::endl;
	std::cout << "Current: " << current << std::endl;
	std::cout << "Expected: " << expected << std::endl;
	std::cout << "------------------------" << std::endl;
}

void test_core()
{
	auto SENTINEL = std::make_shared<int>();

	{
		uint8_t value = 111;
		auto action = tween_to(value, 222, 1s, SENTINEL);
		RunAndTest(action, value, 222);
	}

	{
		uint8_t value = 0;
		const auto expected = 255;
		auto action = tween_to(value, expected, 1s, SENTINEL);
		RunAndTest(action, value, expected);
	}

	{
		uint64_t value = 111;
		const auto expected = std::numeric_limits<uint64_t>::max();
		auto action = tween_to(value, expected, 1s, SENTINEL);
		RunAndTest(action, value, expected);
	}

	{
		int value = 99999;
		const auto expected = -99999;
		auto action = tween_to(value, expected, 1s, SENTINEL);
		RunAndTest(action, value, expected);
	}

	std::cout << "Tests are finished!" << std::endl;
}

