// IApplication.h
#pragma once
#include <cstdint>
#include <raylib.h>
#include <string>

namespace engine::core
{
    class IApplication
    {
        public:
            IApplication();
            virtual void Start() = 0;
            virtual void Stop() = 0;

            virtual Vector2 GetWindowSize() = 0;
            virtual void SetWindowSize(int width, int height) = 0;

            virtual ~IApplication();

        private:
            uint32_t width;
            uint32_t height;
            const char* title;
    };
}