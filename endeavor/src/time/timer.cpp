#include "time/timer.hpp"

namespace Endeavor {
    void Timer::start()
    {
        mIsStarted = true;
        mStartTime = std::chrono::high_resolution_clock::now();
    }

    void Timer::stop()
    {
        if (!mIsStarted)
        {
            printf("ERROR: Timer::stop called without starting the Timer.\n");
            return;
        }


        mIsStarted = false;
        mStopTime = std::chrono::high_resolution_clock::now();

        std::chrono::duration<float> elapsed = mStopTime - mStartTime;
        mElapsedTime = elapsed.count();
    }

    void Timer::reset()
    {
        mStartTime = std::chrono::high_resolution_clock::now();
    }

    float Timer::getElapsedTime()
    {
        std::chrono::duration<float> elapsed = std::chrono::high_resolution_clock::now() - mStartTime;
        mElapsedTime = elapsed.count();
        return mElapsedTime;
    }
}