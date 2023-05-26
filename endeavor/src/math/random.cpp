#include "math/random.hpp"

#include <random>

int Endeavor::Random::randomIntInRange(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(min, max);
    int rand = distr(gen);
    return rand;
}

float Endeavor::Random::randomFloatInRange(float min, float max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distr(min, max);
    float rand = distr(gen);
    return rand;
}