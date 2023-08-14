#include "EventLoopPrivate.h"

namespace Eternal
{
    bool EventLoopPrivate::IsRunning() const
    {
        return m_Running;
    }

    void EventLoopPrivate::Start()
    {
        m_Running = true;
    }

    void EventLoopPrivate::Stop()
    {
        m_Running = false;
    }

    EventLoopAdapter::EventLoopAdapter(EventLoopPrivate &eventLoop):
        m_EventLoop(eventLoop)
    {
    }

    void EventLoopAdapter::Stop()
    {
        m_EventLoop.Stop();
    }
}
