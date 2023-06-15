#include "stdafx.h"
#include "Timer.h"

Timer::Timer()
{
}

bool Timer::Initialize()
{
    previous_time = std::chrono::high_resolution_clock::now();

    return true;
}

void Timer::Update()
{
    auto current_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms = current_time - previous_time;
    previous_time = current_time;

    delta_time_ms = ms.count();
}

Stopwatch::Stopwatch()
{
}

void Stopwatch::Start()
{
    start_time = std::chrono::high_resolution_clock::now();
}

const float Stopwatch::GetElapsedTimeSec()
{
    std::chrono::duration<double, std::milli> ms = std::chrono::high_resolution_clock::now() - start_time;
    return static_cast<float>(ms.count() / 1000.0);
}

const float Stopwatch::GetElapsedTimeMs()
{
    std::chrono::duration<double, std::milli> ms = std::chrono::high_resolution_clock::now() - start_time;
    return static_cast<float>(ms.count());
}

