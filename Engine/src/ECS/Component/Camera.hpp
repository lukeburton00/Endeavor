#pragma once

struct Camera
{
    bool isPrimary;

    Camera() : isPrimary(false){}
    Camera(bool isPrimary) : isPrimary(isPrimary) {}
};