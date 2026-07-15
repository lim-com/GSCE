#pragma once
#include <Engine.h>

namespace engine::core
{

    class Window
    {
        enum class LAYER {Base, Working, Ui, System};

        public:



            Window(LAYER layer);
            ~Window();

        private:

    };
}