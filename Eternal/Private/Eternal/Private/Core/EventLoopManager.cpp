#include "EventLoopManager.h"

namespace Eternal
{
    EventLoopManager::EventLoopManager(std::unique_ptr<EventLoopProperties> properties, std::unique_ptr<EventLoop> eventLoop):
        m_Properties(std::move(properties)),
        m_EventLoop(std::move(eventLoop))
    {
    }

    EventLoop &EventLoopManager::GetEventLoop() const
    {
        return *m_EventLoop;
    }

    bool EventLoopManager::IsRunning() const
    {
        return m_Properties->Running;
    }

    void EventLoopManager::Start()
    {
        m_Properties->Running = true;
    }

    void EventLoopManager::Stop()
    {
        m_Properties->Running = false;
    }

    std::unique_ptr<EventLoopManager> CreateEventLoopManager()
    {
        auto properties = std::make_unique<EventLoopProperties>();
        auto eventLoop = std::make_unique<EventLoop>(*properties);
        return std::make_unique<EventLoopManager>(std::move(properties), std::move(eventLoop));
    }
}
