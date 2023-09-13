#include "Engine.h"

namespace Eternal
{
    Engine::Engine(EventLoop &eventLoop, Logger &logger, Window &window):
        m_EventLoop(eventLoop),
        m_Logger(logger),
        m_Window(window)
    {
    }

    EventLoop &Engine::GetEventLoop() const
    {
        return m_EventLoop;
    }

    Logger &Engine::GetLogger() const
    {
        return m_Logger;
    }

    Window &Engine::GetWindow() const
    {
        return m_Window;
    }
}
