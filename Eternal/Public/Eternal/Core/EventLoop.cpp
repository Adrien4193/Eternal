#include "EventLoop.h"

namespace Eternal
{
    bool ApplicationLoop::IsRunning() const
    {
        return m_Running;
    }

    void ApplicationLoop::Start()
    {
        m_Running = true;
    }

    void ApplicationLoop::Stop()
    {
        m_Running = false;
    }

    EventLoop::EventLoop(ApplicationLoop &loop):
        m_Loop(loop)
    {
    }

    void EventLoop::Stop()
    {
        m_Loop.Stop();
    }
}
