#include "Engine.h"

namespace Eternal
{
    Engine::Engine(EnginePrivate &engine):
        m_Engine(engine)
    {
    }

    EventLoop &Engine::GetEventLoop() const
    {
        return *m_Engine.EventLoop;
    }

    Logger &Engine::GetLogger() const
    {
        return *m_Engine.Logger;
    }

    WindowManager &Engine::GetWindowManager() const
    {
        return *m_Engine.WindowManager;
    }
}
