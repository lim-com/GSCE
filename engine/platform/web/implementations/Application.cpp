#include "Application.h"

#include <raylib.h>

engine::web::Application::Application() = default;
engine::web::Application::~Application() = default;

void engine::web::Application::Start()
{
    InitWindow(
        static_cast<int>(m_width),
        static_cast<int>(m_height),
        m_title
    );
}

void engine::web::Application::Stop()
{
    CloseWindow();
}

void engine::web::Application::SetWindowSize(const int width, const int height)
{
    m_width = static_cast<uint32_t>(width);
    m_height = static_cast<uint32_t>(height);
}

Vector2 engine::web::Application::GetWindowSize()
{
    const auto width = static_cast<float>(m_width);
    const auto height = static_cast<float>(m_height);
    return Vector2{width, height};
}
