#pragma once

#include <vector>

namespace Endeavor
{
    class PerlinNoise 
    {
    public:
        PerlinNoise(int seed);
        float noise(float x, float y, float z) const;

    private:
        std::vector<int> p;
        float noiseImpl(float x, float y, float z) const;
        static float fade(float t);
        static float lerp(float t, float a, float b);
        static float grad(int hash, float x, float y, float z);
    };
} // namespace Endeavor