#pragma once

#include <string>

namespace Endeavor
{
    struct Tag
    {
        std::string tag;
        Tag(const std::string &name) : tag(name) {}
    };
}