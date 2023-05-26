#pragma once

#include <stdio.h>
#include <chrono>

namespace Endeavor
{
    class Time
    {
    public:

        void start();
        void stop();
        void reset();
        float getElapsedTime();

    private:
        bool mIsStarted;
        std::chrono::high_resolution_clock::time_point mStartTime;
        std::chrono::high_resolution_clock::time_point mStopTime;
        float mElapsedTime;
    };
} // namespace Endeavor