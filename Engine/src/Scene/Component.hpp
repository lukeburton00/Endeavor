#pragma once
#ifdef _WIN32
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#else
#include "glm/glm.hpp"
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

class Sprite : public Component
{
public:
    glm::vec4 color;
    Sprite() : color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)) {};

    void setColor(glm::vec4 colorVector)
    {
        color = colorVector;
    }
};

class Collider : public Component
{
public:
    glm::vec2 xBounds;
    glm::vec2 yBounds;

    Collider() : xBounds(glm::vec2(0.0f, 100.0f)), yBounds(glm::vec2(0.0f,100.0f)) {};

    void setBounds(glm::vec2 xVector, glm::vec2 yVector)
    {
        xBounds = xVector;
        yBounds = yVector;
    }
};