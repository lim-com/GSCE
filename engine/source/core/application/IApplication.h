// IApplication.h
#pragma once
#include <cstdint>
#include <raylib.h>
#include <string>

namespace gsce::core
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
            uint32_t m_width = 800;
            uint32_t m_height = 800;
            const char* m_title = "Title";
    };
}