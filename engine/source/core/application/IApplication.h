// IApplication.h
#pragma once
#include <cstdint>

namespace gsce::core
{
    class IApplication
    {
        public:
            IApplication();
            virtual ~IApplication();

            virtual void Initialize();
            virtual void Run() = 0;
            virtual void Shutdown();

        private:
            uint32_t m_width;
            uint32_t m_height;
            const char* m_title;
    };
}