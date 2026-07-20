#include "Application.h"

#include <raylib.h>

gsce::web::Application::Application() = default;
gsce::web::Application::~Application() = default;

void gsce::web::Application::Start()
{
    InitWindow(
        static_cast<int>(m_width),
        static_cast<int>(m_height),
        m_title
    );
}

void gsce::web::Application::Stop()
{
    CloseWindow();
}

void gsce::web::Application::SetWindowSize(const int width, const int height)
{
    m_width = static_cast<uint32_t>(width);
    m_height = static_cast<uint32_t>(height);
}

Vector2 gsce::web::Application::GetWindowSize()
{
    const auto width = static_cast<float>(m_width);
    const auto height = static_cast<float>(m_height);
    return Vector2{width, height};
}
