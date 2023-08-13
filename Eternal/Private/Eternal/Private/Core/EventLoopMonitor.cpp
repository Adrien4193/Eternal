#include "EventLoopMonitor.h"

namespace Eternal
{
    EventLoopAdapter::EventLoopAdapter(EventLoopProperties &properties):
        m_Properties(properties)
    {
    }

    void EventLoopAdapter::Stop()
    {
        m_Properties.Running = false;
    }

    EventLoopMonitor::EventLoopMonitor(std::unique_ptr<EventLoopProperties> properties, std::unique_ptr<EventLoop> loop):
        m_Properties(std::move(properties)),
        m_Loop(std::move(loop))
    {
    }

    EventLoop &EventLoopMonitor::GetEventLoop() const
    {
        return *m_Loop;
    }

    bool EventLoopMonitor::IsRunning() const
    {
        return m_Properties->Running;
    }

    void EventLoopMonitor::Start()
    {
        m_Properties->Running = true;
    }

    std::unique_ptr<EventLoopMonitor> CreateEventLoopMonitor()
    {
        auto properties = std::make_unique<EventLoopProperties>();
        auto adapter = std::make_unique<EventLoopAdapter>(*properties);
        return std::make_unique<EventLoopMonitor>(std::move(properties), std::move(adapter));
    }
}
