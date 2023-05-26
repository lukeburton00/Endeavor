#include "time/time.hpp"

void Endeavor::Time::start()
{
    mIsStarted = true;
    mStartTime = std::chrono::high_resolution_clock::now();
}

void Endeavor::Time::stop()
{
    if (!mIsStarted)
    {
        printf("ERROR: Time::stop called without starting the timer.\n");
        return;
    }


    mIsStarted = false;
    mStopTime = std::chrono::high_resolution_clock::now();

    std::chrono::duration<float> elapsed = mStopTime - mStartTime;
    mElapsedTime = elapsed.count();
}

void Endeavor::Time::reset()
{
    mStartTime = std::chrono::high_resolution_clock::now();
}

float Endeavor::Time::getElapsedTime()
{
    std::chrono::duration<float> elapsed = std::chrono::high_resolution_clock::now() - mStartTime;
    mElapsedTime = elapsed.count();
    return mElapsedTime;
}