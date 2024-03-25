#include "EventLoop.h"

namespace Eternal
{
    EventLoop::EventLoop(EventLoopPrivate &eventLoop):
        m_EventLoop(eventLoop)
    {
    }

    void EventLoop::Stop()
    {
        m_EventLoop.Running = false;
    }
}
