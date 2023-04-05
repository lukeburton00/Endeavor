#pragma once

namespace Endeavor
{
    struct Camera
    {
        bool isPrimary;

        Camera() : isPrimary(false){}
        Camera(bool isPrimary) : isPrimary(isPrimary) {}
    };
} // namespace Endeavor