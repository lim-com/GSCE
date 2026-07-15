// Engine.h
#pragma once
#include <cstdint>

namespace engine
{
    enum class PLATFORM {WEB, WINDOWS, LINUX, ANDROID, IOS, MACOS, UNIX};
}

namespace engine::types
{
    typedef struct IntegerVector2{
        uint32_t x;
        uint32_t y;
    } INT_Vector2;

    typedef struct IntegerVector3{
        uint32_t x;
        uint32_t y;
        uint32_t z;
    } INT_Vector3;

    typedef struct IntegerVector4{
        uint32_t x;
        uint32_t y;
        uint32_t z;
        uint32_t w;
    } INT_Vector4;
}