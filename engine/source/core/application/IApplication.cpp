#include "IApplication.h"

#include <raylib.h>

engine::core::IApplication::IApplication() = default;
engine::core::IApplication::~IApplication() = default;

void engine::core::IApplication::Start()
{
    InitWindow(
        static_cast<int>(m_width),
        static_cast<int>(m_height),
        m_title
    );
}

void engine::core::IApplication::Stop()
{
    CloseWindow();
}

void engine::core::IApplication::SetWindowSize(const int width, const int height)
{
    m_width = static_cast<uint32_t>(width);
    m_height = static_cast<uint32_t>(height);
}

Vector2 engine::core::IApplication::GetWindowSize()
{
    const auto width = static_cast<float>(m_width);
    const auto height = static_cast<float>(m_height);
    return Vector2{width, height};
}