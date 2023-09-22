#include "Engine.h"

namespace Eternal
{
    Engine::Engine(std::unique_ptr<EngineProperties> properties):
        m_Properties(std::move(properties))
    {
    }

    EventLoop &Engine::GetEventLoop() const
    {
        return *m_Properties->EventLoop;
    }

    Logger &Engine::GetLogger() const
    {
        return *m_Properties->Logger;
    }

    WindowManager &Engine::GetWindowManager() const
    {
        return *m_Properties->WindowManager;
    }
}
