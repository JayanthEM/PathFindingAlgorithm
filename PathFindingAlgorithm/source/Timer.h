#pragma once
#include <chrono>
#include <iostream>

class Timer
{
public:

    Timer()
    {
        start = std::chrono::high_resolution_clock::now();
    }

    ~Timer()
    {
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        std::cout << duration.count() * 1000.0f << "ms" << std::endl; // Print duration in ms
    }

private:
    std::chrono::time_point<std::chrono::steady_clock> start, end;
    std::chrono::duration<float> duration;
};