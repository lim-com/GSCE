#pragma once
#include <core/application/IApplication.h>

namespace gsce::native
{
    class Application
    {
        public:
            Application();

            void Initialize() const;
            void Run();
            void Shutdown() const;

            Vector2 GetWindowSize() const;
            void SetWindowSize(int width, int height);

            ~Application();

        private:
            uint32_t m_width = 800;
            uint32_t m_height = 800;
            const char* m_title = "DefaultAppName";
    };
}