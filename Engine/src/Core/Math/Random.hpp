#pragma once

namespace Endeavor
{
    class Random
    {
    public:
        static int randomIntInRange(int min, int max);
        static float randomFloatInRange(float min, float max);
    };
} // namespace Endeavor