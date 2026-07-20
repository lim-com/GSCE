#pragma once

#include <cstdint>
#include <Engine.h>

namespace gsce::core
{

    enum class VIEWPORT_TYPE { VIEWER_3D, VIEWPORT_2D, VIEWPORT_SYSTEM};

    class IViewport
    {
        public:

            explicit IViewport(const uint32_t id, VIEWPORT_TYPE viewport_type) : m_id(id){};
            virtual ~IViewport();

            virtual void Update() = 0;
            virtual void Draw() = 0;



        private:
            const uint32_t m_id;
    };
}
