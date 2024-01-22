#include "EventLoop.h"

namespace Eternal
{
    EventLoop::EventLoop(std::function<void()> stop):
        m_Stop(std::move(stop))
    {
    }

    void EventLoop::Stop()
    {
        m_Stop();
    }
}
