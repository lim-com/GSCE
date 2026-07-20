#pragma once

#include <core/application/IApplication.h>

namespace gsce::native{

    class Application : public core::IApplication
    {
        public:
            Application();

            void Start() override;
            void Stop() override;
    };

}
