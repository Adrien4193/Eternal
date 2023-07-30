#pragma once

#include <memory>

#include "EventLoop.h"
#include "Log.h"

namespace Eternal
{
    class Engine
    {
    private:
        std::unique_ptr<EventLoop> m_EventLoop;
        std::unique_ptr<Logger> m_Logger;

    public:
        explicit Engine(std::unique_ptr<EventLoop> eventLoop, std::unique_ptr<Logger> logger);

        EventLoop &GetEventLoop() const;
        Logger &GetLogger() const;
    };
}
