#pragma once
#include "GameObject.hpp"

class Scene
{
public:
    std::vector<std::shared_ptr<GameObject>> objects;
};