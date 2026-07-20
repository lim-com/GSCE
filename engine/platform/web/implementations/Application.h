#pragma once
#include <core/application/IApplication.h>

namespace gsce::web
{
    class Application : public core::IApplication
    {
        public:
            Application();

            void Start() override;
            void Stop() override;

            Vector2 GetWindowSize() override;
            void SetWindowSize(int width, int height) override;

            ~Application() override;

        private:
            uint32_t m_width = 800;
            uint32_t m_height = 800;
            const char* m_title = "DefaultAppName";
    };
}
