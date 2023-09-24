#include "EventLoop.h"

namespace Eternal
{
    ApplicationLoop::ApplicationLoop(std::unique_ptr<EventLoopProperties> properties):
        m_Properties(std::move(properties))
    {
    }

    bool ApplicationLoop::IsRunning() const
    {
        return m_Properties->Running;
    }

    void ApplicationLoop::Start()
    {
        m_Properties->Running = true;
    }

    EventLoop::EventLoop(EventLoopProperties &properties):
        m_Properties(properties)
    {
    }

    void EventLoop::Stop()
    {
        m_Properties.Running = false;
    }
}
