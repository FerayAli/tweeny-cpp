#include <iostream>
#include <tweeny/tweeny.h>
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

struct Sprite
{

    void set_pos(float x)
    {
        posX = x;
    }

    float get_pos()
    {
        return posX;
    }
private:
    float posX;
};

namespace tweeny
{
template<>
struct tween_non_fundamental_export<Sprite>
{
    static void set_position(Sprite& sprite, float x)
    {
        sprite.set_pos(x);
    }

    static float get_position(Sprite& sprite)
    {
        return sprite.get_pos();
    }
};

}

float lerp(float begin, float end, float progress)
{
    return begin + ((end - begin) * progress);
}

int main()
{
    std::cout << lerp(50, 100, 0.0f) << std::endl;

//    tweeny::tween_value<float> t = tweeny::tween_value_from_to(0.0f, 100.0f, 1s);

//    tweeny::tween_value_from_to(1000, 0, tweeny::unit_speed(100, 1s));
//    t.on_step = [](info_t<float> data)
//    {
//        if(data.current == 500)
//        {
//            tweeny::set_unit_speed(data.self_id, tweeny::unit_speed(50, 1s))
//        }

//        if(data.current == 100)
//        {
//            tweeny::set_unit_speed(data.self_id, tweeny::unit_speed(10, 1s))
//        }

//        data.begin;
//        data.end;
//        data.progress;
//        data.elapsed;
//        data.duration;

//        data.unit_speed.unit
//        data.unit_speed.speed
//    };


//    //Units per time
//    tweeny::unit_speed(1, 1s);
////    tweeny::units_per_time(1, 500ms);

//    tweeny::tween_value_from_to(0, 1000, tweeny::unit_speed(100));
////  tweeny::set_speed(t, tweeny::unit_speed(50, 1s));
////  tweeny::set_speed_multiplier(t, 2.0f);


    auto sprite = std::make_shared<Sprite>();
    auto tween_sprite = tweeny::move_to(sprite, 10.0f, 10ms);
    auto seq = tweeny::sequence(tween_sprite, tween_sprite);
    tweeny::start(seq);

    for(int i = 0; i < 20; i++)
    {
        tweeny::detail::update(1ms);
        std::cout << sprite->get_pos() << std::endl;
    }

    std::cout << "--------------------------------" << std::endl;
    return 0;


    const auto SIZE = 100;
    std::vector<int> function_data(SIZE, 0);

    auto data = std::make_shared<int>(0);
    tweeny::tween_action a = tweeny::tween_from_to(data,
                                                   0,
                                                   SIZE,
                                                   std::chrono::milliseconds(SIZE),
                                                   tweeny::ease::arch);
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
