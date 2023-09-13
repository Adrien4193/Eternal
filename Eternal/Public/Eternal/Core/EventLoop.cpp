#include "EventLoop.h"

namespace Eternal
{
    EventLoop::EventLoop(EventLoopProperties &properties):
        m_Properties(properties)
    {
    }

    void EventLoop::Stop()
    {
        m_Properties.Running = false;
    }
}
