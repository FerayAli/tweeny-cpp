#include <iostream>
#include <tweeny/tween_action.h>
#include <tweeny/tween_private.h>
#include <tweeny/tween_fundamental.h>
#include <vector>

void rotateClockwise90(std::vector<std::string>& a)
{
    auto N = a.size();
    for (int i = 0; i < N / 2; i++)
    {
        for (int j = i; j < N - i - 1; j++)
        {
            int temp = a[i][j];
            a[i][j] = a[N - 1 - j][i];
            a[N - 1 - j][i] = a[N - 1 - i][N - 1 - j];
            a[N - 1 - i][N - 1 - j] = a[j][N - 1 - i];
            a[j][N - 1 - i] = temp;
        }
    }
}

int main()
{
    const auto SIZE = 100;
    std::vector<int> function_data(SIZE, 0);

    auto data = std::make_shared<int>(0);
    tweeny::tween_action a = tweeny::tween_from_to(data,
                                                   0,
                                                   SIZE,
                                                   std::chrono::milliseconds(SIZE),
                                                   tweeny::ease::bounce_bottom_top);
    tweeny::tween_private::start(a);

    for(auto& fd : function_data)
    {
        fd = *data;
        tweeny::tween_private::update(a, 1ms);
    }

    std::vector<std::string> output;
    for(const auto fd : function_data)
    {
        auto o = std::string(fd, '*');
        for(int i = fd; i < SIZE; i++)
        {
            o.push_back(' ');
        }
        output.emplace_back(o);
    }

    rotateClockwise90(output);
    rotateClockwise90(output);
    rotateClockwise90(output);

    for(const auto& line : output)
    {
        for(auto c : line)
        {
            std::cout << c;
        }
        std::cout << std::endl;
    }

	return 0;
}
