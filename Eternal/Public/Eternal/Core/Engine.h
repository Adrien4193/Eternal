#pragma once

#include <Eternal/Core/Log.h>

#include "EventLoop.h"
#include "Window.h"

namespace Eternal
{
    class Engine
    {
    public:
        virtual ~Engine() = default;

        virtual EventLoop &GetEventLoop() const = 0;
        virtual Logger &GetLogger() const = 0;
        virtual Window &GetWindow() const = 0;
    };
}
