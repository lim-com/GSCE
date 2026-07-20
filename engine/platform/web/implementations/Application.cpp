#include "Application.h"

#include <raylib.h>

namespace gsce::web
{
    Application::Application() = default;
    Application::~Application() = default;

    void Application::Initialize()
    {
        InitWindow(
            static_cast<int>(m_width),
            static_cast<int>(m_height),
            m_title
        );
    }

    void Application::Run()
    {

    }

    void Application::Shutdown()
    {
        CloseWindow();
    }

    void Application::SetWindowSize(const int width, const int height)
    {
        m_width = static_cast<uint32_t>(width);
        m_height = static_cast<uint32_t>(height);
    }

    Vector2 Application::GetWindowSize() const
    {
        const auto width = static_cast<float>(m_width);
        const auto height = static_cast<float>(m_height);
        return Vector2{width, height};
    }
}