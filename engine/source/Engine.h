// Engine.h
#pragma once

#include <cstdint>

namespace gsce
{
    enum class PLATFORM {WEB, WINDOWS, LINUX, ANDROID, IOS, MACOS, UNIX};
}

namespace gsce::types
{
    struct Size2D{
        uint32_t x;
        uint32_t y;
    };

    struct Size3D{
        uint32_t x;
        uint32_t y;
        uint32_t z;
    };

    struct Size4D{
        uint32_t x;
        uint32_t y;
        uint32_t z;
        uint32_t w;
    };
}