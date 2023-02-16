#pragma once
#ifdef _WIN32
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#else
#inclue "glm/glm.hpp"
#endif


class Component
{
public:
    int parent;

};

class Transform : public Component
{
public:
    glm::vec2 position;
    glm::vec2 scale;
    Transform() : position(glm::vec2(0.0f, 0.0f)), scale(glm::vec2(100.0f, 100.0f)) {};

    void setPosition(glm::vec2 posVector)
    {
        position = posVector;
    }

    void setScale(glm::vec2 scaleVector)
    {
        scale = scaleVector;
    }

};