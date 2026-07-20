#include "IApplication.h"

#include <raylib.h>

gsce::core::IApplication::IApplication() = default;
gsce::core::IApplication::~IApplication() = default;

void gsce::core::IApplication::Start()
{
    InitWindow(
        static_cast<int>(m_width),
        static_cast<int>(m_height),
        m_title
    );
}

void gsce::core::IApplication::Stop()
{
    CloseWindow();
}

void gsce::core::IApplication::SetWindowSize(const int width, const int height)
{
    m_width = static_cast<uint32_t>(width);
    m_height = static_cast<uint32_t>(height);
}

Vector2 gsce::core::IApplication::GetWindowSize()
{
    const auto width = static_cast<float>(m_width);
    const auto height = static_cast<float>(m_height);
    return Vector2{width, height};
}