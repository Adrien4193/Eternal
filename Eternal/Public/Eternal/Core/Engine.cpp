#include "Engine.h"

namespace Eternal
{
    Engine::Engine(std::unique_ptr<EventLoop> eventLoop, std::unique_ptr<Logger> logger):
        m_EventLoop(std::move(eventLoop)),
        m_Logger(std::move(logger))
    {
    }

    EventLoop &Engine::GetEventLoop() const
    {
        return *m_EventLoop;
    }

    Logger &Engine::GetLogger() const
    {
        return *m_Logger;
    }
}
