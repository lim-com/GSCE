#pragma once

#include <deque>
#include <cstdint>
#include <memory>

#include "IViewport.h"


namespace gsce::core
{
    class ViewportManager
    {
        public:
            inline static uint32_t activeViewports = 0;

            ViewportManager();
            ~ViewportManager();

            void AddViewport(VIEWPORT_TYPE viewport_type);
            void AddViewportById(uint32_t id);
            void DeleteViewport();
            void DeleteViewportById(uint32_t id);

            

        private:
            std::deque<std::unique_ptr<IViewport>> m_viewports;


    };
}
