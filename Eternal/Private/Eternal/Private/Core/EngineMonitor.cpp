#include "EngineMonitor.h"

namespace Eternal
{
    EngineAdapter::EngineAdapter(EngineProperties &properties):
        m_Properties(properties)
    {
    }

    EventLoop &EngineAdapter::GetEventLoop() const
    {
        return m_Properties.EventLoopMonitor->GetEventLoop();
    }

    Logger &EngineAdapter::GetLogger() const
    {
        return *m_Properties.Logger;
    }

    Window &EngineAdapter::GetWindow() const
    {
        return m_Properties.WindowMonitor->GetWindow();
    }

    EngineMonitor::EngineMonitor(std::unique_ptr<EngineProperties> properties, std::unique_ptr<Engine> engine):
        m_Properties(std::move(properties)),
        m_Engine(std::move(engine))
    {
    }

    Engine &EngineMonitor::GetEngine() const
    {
        return *m_Engine;
    }

    bool EngineMonitor::IsRunning() const
    {
        return m_Properties->EventLoopMonitor->IsRunning();
    }

    void EngineMonitor::Start()
    {
        m_Properties->EventLoopMonitor->Start();
    }
}
