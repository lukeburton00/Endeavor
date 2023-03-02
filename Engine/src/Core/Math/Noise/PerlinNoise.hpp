#pragma once

#include <cmath>
#include <algorithm>
#include <random>
#include <vector>

class PerlinNoise 
{
public:
    PerlinNoise(int seed);
    float noise(float x, float y, float z, float frequency, float amplitude, int octaves, float lacunarity, float persistence) const;

private:
    std::vector<int> p;
    float noiseImpl(float x, float y, float z) const;
    static float fade(float t);
    static float lerp(float t, float a, float b);
    static float grad(int hash, float x, float y, float z);
};