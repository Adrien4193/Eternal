#pragma once

#include <memory>

#include "Engine.h"
#include "Plugin.h"

namespace Eternal
{
    class Application
    {
    public:
        virtual ~Application() = default;

        virtual Engine &GetEngine() const = 0;
        virtual void AddPlugin(std::unique_ptr<Plugin> plugin) = 0;
        virtual void Run() = 0;
    };
}
