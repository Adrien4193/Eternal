#include "EventLoopPrivate.h"

namespace Eternal
{
    EventLoopPrivate::EventLoopPrivate(std::unique_ptr<EventLoopProperties> properties):
        m_Properties(std::move(properties))
    {
    }

    bool EventLoopPrivate::IsRunning() const
    {
        return m_Properties->Running;
    }

    void EventLoopPrivate::Start()
    {
        m_Properties->Running = true;
    }
}
