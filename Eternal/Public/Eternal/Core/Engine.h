#pragma once

#include <memory>

#include <Eternal/Core/Log.h>

#include "EventLoop.h"
#include "Window.h"

namespace Eternal
{
    class Engine
    {
    private:
        EventLoop &m_EventLoop;
        Logger &m_Logger;
        Window &m_Window;

    public:
        explicit Engine(EventLoop &eventLoop, Logger &logger, Window &window);

        EventLoop &GetEventLoop() const;
        Logger &GetLogger() const;
        Window &GetWindow() const;
    };
}
