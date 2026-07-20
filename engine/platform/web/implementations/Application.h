#pragma once
#include <core/application/IApplication.h>

namespace gsce::web
{
    class Application : public gsce::core::IApplication
    {
        public:
            Application();

            void Initialize() override;
            void Run() override;
            void Shutdown() override;

            Vector2 GetWindowSize() const override;
            void SetWindowSize(int width, int height) override;

            ~Application() override;

        private:
            uint32_t m_width = 800;
            uint32_t m_height = 800;
            const char* m_title = "DefaultAppName";
    };
}
