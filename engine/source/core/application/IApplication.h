// IApplication.h
#pragma once
#include "Engine.h"

namespace engine::core
{
    class IApplication
    {
        public:
            explicit IApplication(engine::PLATFORM platform);

            virtual void Start() = 0;
            virtual void Stop() = 0;


            virtual ~IApplication() = default;
    };
}